#include "Constant.h"
#include "Node.h"

class Map
{
    GDALDatasetH dataset;
    OGRFeatureH feature;
    std::vector<sf::VertexArray> lines;
    sf::Texture mapTexture;
    OGRLayerH layer;
    std::vector<Node *> nodes;
    std::vector<Edge> edges;
    std::unordered_map<std::string, Node *> nodeMap;
    int j;

public:
    sf::Sprite mapSprite;

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

                std::string key = getKey(line->getX(0), line->getY(0));
                if (nodeMap.find(key) == nodeMap.end())
                {
                    nodes.push_back(new Node(line->getX(0), line->getY(0), j++));
                    nodeMap[key] = nodes.back();
                }
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
    std::vector<sf::VertexArray> getLines()
    {
        return lines;
    }
    sf::Sprite getSprite()
    {
        return mapSprite;
    }
    void print()
    {
        for (const auto &node : nodes)
        {
            std::cout << node->x << " " << node->y << " " << node->id << std::endl;
        }
    }
    ~Map()
    {
        GDALClose(dataset);
    }
};