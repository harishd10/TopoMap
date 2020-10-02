#include "geomutils.h"

#include <stdint.h>
#include <algorithm>
#include <cassert>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

std::vector<int> sortEdges(const std::vector<std::pair<int, int>> &edges, const std::vector<double> &weights) {
    std::vector<int> order(edges.size());
    for(int i = 0;i < order.size();i ++) {
        order[i] = i;
    }

    std::sort(order.begin(),order.end(), [weights](int i, int j){
        return (weights[i] < weights[j]);
    });
    return order;
}

void findAngle(const Point &p1, const Point &p2, Transformation &t) {
    Point vec(p2.x - p1.x,p2.y - p1.y);
    double n = len(vec);
    vec.x /= n;
    vec.y /= n;
    t.cos = vec.x;
    t.sin = std::sqrt(1 - t.cos * t.cos);
    if(vec.y >= 0) {
        t.sin = -t.sin;
    }
}

void computeConvexHull(Polygon &pts, Polygon &chull) {
    chull.clear();
    if(pts.size() == 1) {
        chull.push_back(pts[0]);
        chull.push_back(pts[0]);
        return;
    } else if(pts.size() == 2) {
        chull.push_back(pts[0]);
        chull.push_back(pts[1]);
        chull.push_back(pts[0]);
        return;
    }

    typedef boost::tuple<double, double> point;
    typedef boost::geometry::model::multi_point<point> mpoints;
    typedef boost::geometry::model::polygon<point> polygon;

    mpoints mpts;

    for(int i = 0;i < pts.size();i ++) {
        boost::geometry::append(mpts,point(pts[i].x,pts[i].y));
    }
    polygon hull;

    // Polygon is closed
    boost::geometry::convex_hull(mpts, hull);
    for(auto pt : hull.outer()) {
        chull.push_back(Point(pt.get<0>(), pt.get<1>()));
    }
}
