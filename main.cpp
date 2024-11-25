#include <gdal.h>
#include <gdal_priv.h>
#include <ogr_api.h>
#include <ogr_geometry.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

// Helper function to check if a point is near another point
bool isPointNear(sf::Vector2f point, sf::Vector2f target, float threshold)
{
    return std::sqrt(std::pow(point.x - target.x, 2) + std::pow(point.y - target.y, 2)) <= threshold;
}

int main()
{
    // Initialize GDAL library
    GDALAllRegister();

    // Path to your shapefile
    const char *shapefilePath = "C:/Users/HP/Documents/Projects/TrafficManagementSystem/QGIS/roads/roads.shp";

    // Open the shapefile
    GDALDatasetH dataset = GDALOpenEx(shapefilePath, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (dataset == NULL)
    {
        std::cerr << "Failed to open shapefile!" << std::endl;
        return 1;
    }

    // Get the first layer
    OGRLayerH layer = GDALDatasetGetLayer(dataset, 0);
    if (layer == NULL)
    {
        std::cerr << "Failed to get layer from shapefile!" << std::endl;
        GDALClose(dataset);
        return 1;
    }

    // Bounding box coordinates (provided by the user)
    double minX = 15.3118;
    double minY = -407.645;
    double maxX = 429.882;
    double maxY = -14.2892;

    // SFML window dimensions
    float windowWidth = 800.0f;
    float windowHeight = 800.0f;

    // Calculate scaling factors to map coordinates to SFML window
    float scaleX = windowWidth / (maxX - minX);
    float scaleY = windowHeight / (maxY - minY);
    float scale = std::min(scaleX, scaleY); // Maintain aspect ratio
    float offsetX = -minX * scale;
    float offsetY = -minY * scale;

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(static_cast<int>(windowWidth), static_cast<int>(windowHeight)), "Shapefile Viewer");

    // Store the line segments and their original colors from the shapefile
    std::vector<std::vector<sf::Vertex>> lines;
    std::vector<std::vector<sf::Color>> lineColors;

    // Read features from the shapefile
    OGRFeatureH feature;
    OGR_L_ResetReading(layer); // Reset reading to start iterating through features
    while ((feature = OGR_L_GetNextFeature(layer)) != NULL)
    {
        OGRGeometryH geometry = OGR_F_GetGeometryRef(feature);
        if (geometry != NULL && wkbFlatten(OGR_G_GetGeometryType(geometry)) == wkbLineString)
        {
            OGRLineString *line = (OGRLineString *)geometry;

            // Create an SFML VertexArray for the line and store the original colors (White)
            std::vector<sf::Vertex> lineVertices;
            std::vector<sf::Color> lineVertexColors;
            for (int i = 0; i < line->getNumPoints(); ++i)
            {
                // Scale and offset coordinates to fit within the SFML window
                sf::Vector2f vertexPos(
                    (line->getX(i) * scale + offsetX),
                    windowHeight - (line->getY(i) * scale + offsetY) // Invert Y-axis
                );
                lineVertices.push_back(sf::Vertex(vertexPos, sf::Color::White));
                lineVertexColors.push_back(sf::Color::White);
            }
            lines.push_back(lineVertices);
            lineColors.push_back(lineVertexColors);
        }
        OGR_F_Destroy(feature); // Free memory
    }

    // Close the GDAL dataset
    GDALClose(dataset);

    // Main rendering loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for mouse click events
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f clickPos(event.mouseButton.x, event.mouseButton.y);

                // Check if the click is near any line segment
                for (std::size_t lineIndex = 0; lineIndex < lines.size(); ++lineIndex)
                {
                    auto &line = lines[lineIndex];
                    auto &lineColor = lineColors[lineIndex];

                    for (std::size_t i = 0; i < line.size() - 1; ++i)
                    {
                        // Check if the click is near the start or end of the line segment
                        if (isPointNear(line[i].position, clickPos, 5.0f) || isPointNear(line[i + 1].position, clickPos, 5.0f))
                        {
                            // Change the color of the clicked edge to Blue
                            lineColor[i] = sf::Color::Black;
                            lineColor[i + 1] = sf::Color::Black;

                            // Log the coordinates of the edge (the segment clicked)
                            std::cout << "Edge clicked! Coordinates: ("
                                      << line[i].position.x << ", " << line[i].position.y
                                      << ") -> ("
                                      << line[i + 1].position.x << ", " << line[i + 1].position.y
                                      << ")" << std::endl;
                                                }
                    }
                }
            }
            window.clear();
            // Draw each line with its corresponding vertex colors
        }
    }
    for (std::size_t i = 0; i < lines.size(); ++i)
    {
        window.draw(&lines[i][0], lines[i].size(), sf::LineStrip);
    }
    window.display();

    return 0;
}
