#include "Constant.h"

class Map
{
public:
    GDALDatasetH dataset;
    OGRLayerH layer;
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::VertexArray> lines;
    OGRFeatureH feature;

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
        OGR_L_ResetReading(layer);
        while ((feature = OGR_L_GetNextFeature(layer)) != NULL)
        {
            OGRGeometryH geometry = OGR_F_GetGeometryRef(feature);
            if (geometry != NULL && wkbFlatten(OGR_G_GetGeometryType(geometry)) == wkbLineString)
            {
                OGRLineString *line = (OGRLineString *)geometry;

                // Create an SFML VertexArray for the line
                sf::VertexArray lineStrip(sf::LineStrip, line->getNumPoints());
                for (int i = 0; i < line->getNumPoints(); ++i)
                {
                    // Scale and offset coordinates to fit within the SFML window
                    lineStrip[i].position = sf::Vector2f(
                        (line->getX(i) * scale + offsetX),
                        WIN_HEIGHT - (line->getY(i) * scale + offsetY) // Invert Y-axis
                    );
                    lineStrip[i].color = sf::Color::White;
                }
                lines.push_back(lineStrip);
            }
            OGR_F_Destroy(feature); // Free memory
        }
    }

    ~Map()
    {
        GDALClose(dataset);
    }
};