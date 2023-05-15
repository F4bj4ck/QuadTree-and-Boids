#pragma once
#include <vector>
#include "Boid.h"

struct AABB
{
    Point center;
    float halfWidth;
    float halfHeight;

    bool ContainsPoint(Boid* boid)
    {
        return boid->GetPosition().x > center.x - halfWidth &&
               boid->GetPosition().x < center.x + halfWidth &&
               boid->GetPosition().y > center.y - halfHeight &&
               boid->GetPosition().y < center.y + halfHeight;    
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
    bool Insert(Boid* boid);
    std::vector<Boid*> QueryRange(AABB& range);
    std::vector<AABB> GetBoundaries();
    
private:
    int m_capacity;
    AABB m_boundary;
    std::vector<Boid*> m_boids;
    bool m_subdivided = false;

    QuadTree* m_northWest;
    QuadTree* m_northEast;
    QuadTree* m_southWest;
    QuadTree* m_southEast;
    
    void Subdivide();
};
