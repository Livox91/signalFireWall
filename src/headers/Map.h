#include "Constant.h"
#include "Graph.h"
#include "Junction.h"

class Map
{
    int j;
    GDALDatasetH dataset;
    OGRFeatureH feature;
    OGRLayerH layer;

    std::vector<sf::VertexArray> lines;
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    std::vector<Junction *> junctions;
    Graph *graph;

    std::unordered_map<std::string, Node *> nodeMap;
    sf::Texture mapTexture;
    sf::Sprite mapSprite;

public:
    Map()
    {
        GDALAllRegister();
        dataset = GDALOpenEx(shapefilePath, GDAL_OF_VECTOR, NULL, NULL, NULL);
        if (dataset == NULL)
        {
            std::cerr << "Failed to open shapefile!" << std::endl;
        }

        layer = GDALDatasetGetLayer(dataset, 0);
        if (layer == NULL)
        {
            std::cerr << "Failed to get layer from shapefile!" << std::endl;
            GDALClose(dataset);
        }
        if (!mapTexture.loadFromFile(MapImagePath))
        {
            std::cerr << "Failed to load map image!" << std::endl;
        }
        mapSprite.setTexture(mapTexture);
        mapSprite.setPosition(0, 0);
        mapSprite.setScale(1.3318, 1.3318);
        graph = new Graph();
        j = 1;
    }

    std::string getKey(double x, double y)
    {
        return std::to_string(round(x * 1e6) / 1e6) + "," + std::to_string(round(y * 1e6) / 1e6);
    }

    void setlines()
    {
        OGR_L_ResetReading(layer);
        while ((feature = OGR_L_GetNextFeature(layer)) != NULL)
        {

            OGRGeometryH geometry = OGR_F_GetGeometryRef(feature);
            if (geometry != NULL && wkbFlatten(OGR_G_GetGeometryType(geometry)) == wkbLineString)
            {
                OGRLineString *line = (OGRLineString *)geometry;

                sf::VertexArray lineStrip(sf::LineStrip, line->getNumPoints());
                for (int i = 0; i < line->getNumPoints(); ++i)
                {

                    lineStrip[i].position = sf::Vector2f(
                        (line->getX(i) * scale + offsetX),
                        WIN_HEIGHT - (line->getY(i) * scale + offsetY));
                    lineStrip[i].color = sf::Color::White;
                }
                lines.push_back(lineStrip);
            }
            OGR_F_Destroy(feature);
        }
    }

    void setNodesAndEdges()
    {
        Node *start;
        Node *end;
        double weight;
        bool hasSignal;
        int JunctionID;

        OGR_L_ResetReading(layer);
        while ((feature = OGR_L_GetNextFeature(layer)) != NULL)
        {
            OGRGeometryH geometry = OGR_F_GetGeometryRef(feature);
            if (geometry != NULL && wkbFlatten(OGR_G_GetGeometryType(geometry)) == wkbLineString)
            {
                OGRLineString *line = (OGRLineString *)geometry;

                weight = OGR_G_Length(geometry);
                const char *signalFieldName = "hasSignal";      // Boolean field
                const char *JunctionIdFieldName = "JunctionID"; // Integer field

                // Retrieve field indices
                int signalFieldIndex = OGR_F_GetFieldIndex(feature, signalFieldName);
                int JunctionIdFieldIndex = OGR_F_GetFieldIndex(feature, JunctionIdFieldName);

                bool hasSignal = false;
                int signalId = -1;

                if (signalFieldIndex >= 0 && !OGR_F_IsFieldNull(feature, signalFieldIndex))
                {
                    hasSignal = OGR_F_GetFieldAsInteger(feature, signalFieldIndex) != 0; // Convert to bool
                }

                if (JunctionIdFieldIndex >= 0 && !OGR_F_IsFieldNull(feature, JunctionIdFieldIndex))
                {
                    JunctionID = OGR_F_GetFieldAsInteger(feature, JunctionIdFieldIndex);
                }

                std::string key = getKey(line->getX(0), line->getY(0));

                start = new Node(line->getX(0), line->getY(0), j++);
                end = new Node(line->getX(line->getNumPoints() - 1), line->getY(line->getNumPoints() - 1), j++);

                if (nodeMap.find(key) == nodeMap.end())
                {
                    nodes.push_back(start);
                    nodeMap[key] = nodes.back();
                }
                else
                {
                    start = nodeMap[key];
                }
                key = getKey(line->getX(line->getNumPoints() - 1), line->getY(line->getNumPoints() - 1));
                if (nodeMap.find(key) == nodeMap.end())
                {
                    nodes.push_back(end);
                    nodeMap[key] = nodes.back();
                }
                else
                {
                    end = nodeMap[key];
                }
                edges.push_back(new Edge(start, end, weight, hasSignal, JunctionID));
            }
            OGR_F_Destroy(feature);
        }
    }

    void setJunctions()
    {
        std::vector<Edge *> tempEdge;

        for (int i = 1; i <= 7; i++)
        {
            for (const auto &edge : edges)
            {
                if (edge->hasSignal && edge->JunctionId == i)
                {
                    edge->setSignal();
                    tempEdge.push_back(edge);
                }
            }

            switch (i)
            {
            case 1:
                junctions.push_back(new Junction(4, 89.11, 89.11, 'a', tempEdge));
                tempEdge.clear();
                break;
            case 2:
                junctions.push_back(new Junction(3, 526.67, 89.11, 'b', tempEdge));
                tempEdge.clear();
                break;
            case 3:
                junctions.push_back(new Junction(3, 708, 89.11, 'c', tempEdge));
                tempEdge.clear();
                break;
            case 4:
                junctions.push_back(new Junction(4, 89.11, 270.59, 'a', tempEdge));
                tempEdge.clear();
                break;
            case 5:
                junctions.push_back(new Junction(3, 343.14, 270.59, 'b', tempEdge));
                tempEdge.clear();
                break;
            case 6:
                junctions.push_back(new Junction(3, 708, 393.68, 'c', tempEdge));
                tempEdge.clear();
                break;
            case 7:
                junctions.push_back(new Junction(3, 708, 578.55, 'd', tempEdge));
                tempEdge.clear();
                break;
            default:
                break;
            }
        }
    }

    void setGraph()
    {
        graph->addNodes(nodes);
        graph->addEdge(edges);
    }

    std::vector<sf::VertexArray> getLines()
    {
        return lines;
    }

    sf::Sprite getSprite()
    {
        return mapSprite;
    }

    std::vector<Node *> getNodes()
    {
        return nodes;
    }

    std::vector<Edge *> getEdges()
    {
        return edges;
    }

    std::vector<Junction *> getJunctions()
    {
        return junctions;
    }

    std::vector<int> ShortestPath(int srcID, int DestID)
    {
        return graph->dijkstra(srcID, DestID);
    }

    ~Map()
    {
        GDALClose(dataset);
    }
};