#ifndef TOPOMAP_HPP
#define TOPOMAP_HPP

#include <string>

#include "DisjointSets.hpp"
#include "geomutils.h"

#ifdef WIN32
#ifdef TOPOMAP_LIB
#define TOPOMAP_API __declspec(dllexport)
#else
#define TOPOMAP_API __declspec(dllimport)
#endif
#else
#define TOPOMAP_API
#endif

class TOPOMAP_API TopoMap
{
public:
    TopoMap(size_t emstLeafSize = 1, bool verbose = false);
    std::vector<Point> project(std::vector<double> &data, int dimension);

protected:
    void emst(std::vector<double> &data, int dimension, std::vector<std::pair<int, int>> &edges, std::vector<double> &weights);
    std::vector<Point> placePoints(const std::vector<std::pair<int, int>> &edges, const std::vector<double> &weights);

protected:
    Component mergeComponents(Component &c1, Component &c2, int v1, int v2, double length);
    void transformComponent(const Component &c, const Transformation &t, double yOffset);
    Transformation alignHull(const Polygon &hull, const Point &p, bool topEdge);
    void log(std::string str);

protected:
    DisjointSets<int> comps;
    std::vector<Component> compMap;
    std::vector<Vertex> verts;

    size_t leafSize;
    bool verbose;
};

#endif // TOPOMAP_HPP
