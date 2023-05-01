#pragma once
#include <vector>

struct Point
{
    float x;
    float y;
};

struct AABB
{
    Point center;
    float halfWidth;
    float halfHeight;

    bool ContainsPoint(Point& point)
    {
        return point.x > center.x - halfWidth &&
               point.x < center.x + halfWidth &&
               point.y > center.y - halfHeight &&
               point.y < center.y + halfHeight;    
    }
    
    bool IntersectsAABB(AABB& other)
    {
        return !(other.center.x - other.halfWidth > center.x + halfWidth ||
                 other.center.x + other.halfWidth < center.x - halfWidth ||
                 other.center.y - other.halfHeight > center.y + halfHeight ||
                 other.center.y + other.halfHeight < center.y - halfHeight
        );
    }
};

class QuadTree
{
public:
    QuadTree(AABB boundary, int capacity);
    ~QuadTree();
    bool Insert(Point& point);
    std::vector<Point> QueryRange(AABB& range);
    std::vector<AABB> GetBoundaries();
    
private:
    int m_capacity;
    AABB m_boundary;
    std::vector<Point> m_points;
    bool m_subdivided = false;

    QuadTree* m_northWest;
    QuadTree* m_northEast;
    QuadTree* m_southWest;
    QuadTree* m_southEast;
    
    void Subdivide();
};
