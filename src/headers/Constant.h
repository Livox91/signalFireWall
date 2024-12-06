#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <gdal.h>
#include <gdal_priv.h>
#include <ogr_api.h>
#include "ogrsf_frmts.h"
#include <ogr_geometry.h>
#include <SFML/Graphics.hpp>
#include <unordered_map>
// Constants

const char *shapefilePath = "C:/Users/HP/Documents/Projects/TrafficManagementSystem/QGIS/roads/roads.shp";
double minX = -0.364612;
double minY = -546.329;
double maxX = 600.438;
double maxY = -1.48159;

float WIN_WIDTH = 800.0f;
float WIN_HEIGHT = 800.0f;

// Calculate scaling factors to map coordinates to SFML window
float scaleX = WIN_WIDTH / (maxX - minX);
float scaleY = WIN_HEIGHT / (maxY - minY);
float scale = std::min(scaleX, scaleY);
float offsetX = -minX * scale;
float offsetY = 800;

const char *MapImagePath = "C:/Users/HP/Documents/Projects/TrafficManagementSystem/assets/map.png";
const char *RedImagePath = "C:/Users/HP/Documents/Projects/TrafficManagementSystem/assets/red.png";
const char *YellowImagePath = "C:/Users/HP/Documents/Projects/TrafficManagementSystem/assets/yellow.png";
const char *GreenImagePath = "C:/Users/HP/Documents/Projects/TrafficManagementSystem/assets/green.png";

#include "Signal.h"
#include "Node.h"
#include "Edge.h"
#include "List.h"
#include "Dictionary.h"
