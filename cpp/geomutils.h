#ifndef GEOMUTILS_H
#define GEOMUTILS_H

#include <vector>

struct Point {
    double x,y;

    Point(){}
    Point(double x, double y):x(x),y(y){}
};

typedef std::vector<Point> Polygon;

struct Vertex {
    Point p;
    int id;
};

struct Component {
    std::vector<int> vertices;
    Polygon hull;
};

// Translate by (tx,ty) and then rotate around origin
struct Transformation {
    double tx, ty;
    double cos, sin;
};

#define len(p) (std::sqrt(p.x * p.x + p.y * p.y))
#define distance2(p1,p2) ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y))

std::vector<int> sortEdges(const std::vector<std::pair<int, int>> &edges, const std::vector<double> &weights);
void findAngle(const Point &p1, const Point &p2, Transformation &t);
void computeConvexHull(Polygon &pts, Polygon &chull);

#endif // GEOMUTILS_H
