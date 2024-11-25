#include <gdal.h>
#include <gdal_priv.h>
#include <ogr_api.h>
#include <ogr_geometry.h>
#include <iostream>

int main()
{
    GDALAllRegister(); // Initialize GDAL library

    const char *shapefilePath = "C:/Users/HP/Documents/Projects/TrafficManagementSystem/QGIS/roads/roads.shp"; // Path to your shapefile

    GDALDatasetH dataset = GDALOpenEx(shapefilePath, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (dataset == NULL)
    {
        std::cerr << "Failed to open shapefile!" << std::endl;
        return 1;
    }

    OGRLayerH layer = GDALDatasetGetLayer(dataset, 0); // Get the first layer
    if (layer == NULL)
    {
        std::cerr << "Failed to get layer from shapefile!" << std::endl;
        GDALClose(dataset);
        return 1;
    }

    OGREnvelope envelope;
    if (OGR_L_GetExtent(layer, &envelope, TRUE) != OGRERR_NONE)
    {
        std::cerr << "Failed to get layer extent!" << std::endl;
        GDALClose(dataset);
        return 1;
    }

    // Print the bounding box coordinates
    std::cout << "Bounding Box:" << std::endl;
    std::cout << "Min X: " << envelope.MinX << std::endl;
    std::cout << "Min Y: " << envelope.MinY << std::endl;
    std::cout << "Max X: " << envelope.MaxX << std::endl;
    std::cout << "Max Y: " << envelope.MaxY << std::endl;

    GDALClose(dataset); // Close the dataset
    return 0;
}
