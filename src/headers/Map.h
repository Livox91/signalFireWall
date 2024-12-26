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
        const char *Direction;

        OGR_L_ResetReading(layer);
        while ((feature = OGR_L_GetNextFeature(layer)) != NULL)
        {
            OGRGeometryH geometry = OGR_F_GetGeometryRef(feature);
            if (geometry != NULL && wkbFlatten(OGR_G_GetGeometryType(geometry)) == wkbLineString)
            {
                OGRLineString *line = (OGRLineString *)geometry;

                weight = OGR_G_Length(geometry);
                const char *signalFieldName = "hasSignal";
                const char *JunctionIdFieldName = "JunctionID";
                const char *DirectionFieldName = "Direction";

                // Retrieve field indices
                int signalFieldIndex = OGR_F_GetFieldIndex(feature, signalFieldName);
                int JunctionIdFieldIndex = OGR_F_GetFieldIndex(feature, JunctionIdFieldName);
                int DirectionFieldIndex = OGR_F_GetFieldIndex(feature, DirectionFieldName);

                hasSignal = false;
                JunctionID = -1;

                if (signalFieldIndex >= 0 && !OGR_F_IsFieldNull(feature, signalFieldIndex))
                {
                    hasSignal = OGR_F_GetFieldAsInteger(feature, signalFieldIndex) != 0; // Convert to bool
                }

                if (JunctionIdFieldIndex >= 0 && !OGR_F_IsFieldNull(feature, JunctionIdFieldIndex))
                {
                    JunctionID = OGR_F_GetFieldAsInteger(feature, JunctionIdFieldIndex);
                }

                if (DirectionFieldIndex)
                {
                    Direction = OGR_F_GetFieldAsString(feature, DirectionFieldIndex);
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
                edges.push_back(new Edge(start, end, weight, hasSignal, JunctionID, Direction[0]));
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
                    tempEdge.push_back(edge);
                }
            }

            switch (i)
            {
            case 1:
                junctions.push_back(new Junction(4, 89.11, 89.11, 'a', tempEdge, i));
                tempEdge.clear();
                break;
            case 2:
                junctions.push_back(new Junction(3, 526.67, 89.11, 'b', tempEdge, i));
                tempEdge.clear();
                break;
            case 3:
                junctions.push_back(new Junction(3, 708, 89.11, 'c', tempEdge, i));
                tempEdge.clear();
                break;
            case 4:
                junctions.push_back(new Junction(4, 89.11, 270.59, 'a', tempEdge, i));
                tempEdge.clear();
                break;
            case 5:
                junctions.push_back(new Junction(3, 343.14, 270.59, 'b', tempEdge, i));
                tempEdge.clear();
                break;
            case 6:
                junctions.push_back(new Junction(3, 708, 393.68, 'c', tempEdge, i));
                tempEdge.clear();
                break;
            case 7:
                junctions.push_back(new Junction(3, 708, 578.55, 'd', tempEdge, i));
                tempEdge.clear();
                break;
            default:
                tempEdge.clear();
                break;
            }
        }
        for (const auto &junction : junctions)
        {
            junction->setSignalPostion();
        }
    }

    void setGraph()
    {
        std::cout << "Setting Graph" << std::endl;
        graph = new Graph(nodes, edges);
        graph->setAdjacencyList();
        graph->printAdjacencyList();
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

    std::vector<Node *> ShortestPath(int srcID, int DestID)
    {
        return graph->calShortestPath(srcID, DestID);
    }

    Node *getNearestNode(sf::Vector2f clickPos)
    {
        Node *nearestNode = nullptr;
        float minDistance = 999999999.99;
        for (const auto &node : nodes)
        {
            float distance = std::sqrt(std::pow(node->x - clickPos.x, 2) + std::pow(node->y - clickPos.y, 2));
            if (distance < minDistance)
            {
                minDistance = distance;
                nearestNode = node;
            }
        }
        return nearestNode;
    }

    Edge *findEdge(Node *start, Node *end)
    {
        for (const auto &edge : edges)
        {
            if (edge->start == start && edge->end == end)
            {
                return edge;
            }
        }
        return NULL;
    }

    void resetSignals()
    {
        for (const auto &junction : junctions)
        {
            junction->resetSignals();
        }
    }

    void setPriority(Node *start, Node *end)
    {
        Edge *edge = findEdge(start, end);

        int JunctionId = edge->JunctionId;
        for (const auto &junction : junctions)
        {
            if (junction->getId() == JunctionId)
            {
                junction->setPrioritySignal(edge);
            }
        }
    }

    void drawJunctions(sf::RenderWindow *window)
    {
        for (const auto &junction : junctions)
        {
            junction->drawSignals(window);
        }
    }

    ~Map()
    {
        GDALClose(dataset);
    }
};