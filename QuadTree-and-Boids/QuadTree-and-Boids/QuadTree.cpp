#include "QuadTree.h"

QuadTree::QuadTree(AABB boundary, int capacity) : m_capacity(capacity), m_boundary(boundary)
{
    
}

QuadTree::~QuadTree()
{
    delete m_northWest;
    delete m_northEast;
    delete m_southWest;
    delete m_southEast;
}

bool QuadTree::Insert(Boid* boid)
{
    if (!m_boundary.ContainsPoint(boid))
    {
        return false;
    }

    if (static_cast<int>(m_boids.size()) < m_capacity && !m_subdivided)
    {
        m_boids.push_back(boid);
        return true;
    }

    if(!m_subdivided)
    {
        Subdivide();
    }

    if(m_northWest->Insert(boid))
    {
        return true;
    }
    if(m_northEast->Insert(boid))
    {
        return true;
    }
    if(m_southWest->Insert(boid))
    {
        return true;
    }
    if(m_southEast->Insert(boid))
    {
        return true;
    }
    
    return false;
}

std::vector<Boid*> QuadTree::QueryRange(AABB& range)
{
    std::vector<Boid*> pointsInRange;

    if(!m_boundary.IntersectsAABB(range))
    {
        return pointsInRange;
    }

    for (int p = 0; p < static_cast<int>(m_boids.size()); p++)
    {
        if(range.ContainsPoint(m_boids[p]))
        {
            pointsInRange.push_back(m_boids[p]);
        }
    }

    if(!m_subdivided)
    {
        return pointsInRange;
    }

    std::vector<Boid*> pointsInChild = m_northWest->QueryRange(range);
    pointsInRange.insert(pointsInRange.end(), pointsInChild.begin(), pointsInChild.end());
    
    pointsInChild = m_northEast->QueryRange(range);
    pointsInRange.insert(pointsInRange.end(), pointsInChild.begin(), pointsInChild.end());
    
    pointsInChild = m_southWest->QueryRange(range);
    pointsInRange.insert(pointsInRange.end(), pointsInChild.begin(), pointsInChild.end());
    
    pointsInChild = m_southEast->QueryRange(range);
    pointsInRange.insert(pointsInRange.end(), pointsInChild.begin(), pointsInChild.end());
    
    return pointsInRange;
}

std::vector<AABB> QuadTree::GetBoundaries()
{
    std::vector<AABB> boundaries;

    boundaries.push_back(m_boundary);

    if (!m_subdivided)
    {
        return boundaries;
    }

    std::vector<AABB> childBoundaries = m_northWest->GetBoundaries();
    boundaries.insert(boundaries.end(), childBoundaries.begin(), childBoundaries.end());
    
    childBoundaries = m_northEast->GetBoundaries();
    boundaries.insert(boundaries.end(), childBoundaries.begin(), childBoundaries.end());
    
    childBoundaries = m_southWest->GetBoundaries();
    boundaries.insert(boundaries.end(), childBoundaries.begin(), childBoundaries.end());
    
    childBoundaries = m_southEast->GetBoundaries();
    boundaries.insert(boundaries.end(), childBoundaries.begin(), childBoundaries.end());

    return boundaries;
}


void QuadTree::Subdivide()
{
    m_subdivided = true;
    
    Point northWestCenter;
    northWestCenter.x = m_boundary.center.x - m_boundary.halfWidth / 2;
    northWestCenter.y = m_boundary.center.y - m_boundary.halfHeight / 2;
    
    AABB northWestBoundary;
    northWestBoundary.center = northWestCenter;
    northWestBoundary.halfWidth = m_boundary.halfWidth / 2;
    northWestBoundary.halfHeight = m_boundary.halfHeight / 2;

    m_northWest = new QuadTree(northWestBoundary, m_capacity);

    Point northEastCenter;
    northEastCenter.x = m_boundary.center.x + m_boundary.halfWidth / 2;
    northEastCenter.y = m_boundary.center.y - m_boundary.halfHeight / 2;
    
    AABB northEasBoundary;
    northEasBoundary.center = northEastCenter;
    northEasBoundary.halfWidth = m_boundary.halfWidth / 2;
    northEasBoundary.halfHeight = m_boundary.halfHeight / 2;

    m_northEast = new QuadTree(northEasBoundary, m_capacity);

    Point southWestCenter;
    southWestCenter.x = m_boundary.center.x - m_boundary.halfWidth / 2;
    southWestCenter.y = m_boundary.center.y + m_boundary.halfHeight / 2;
    
    AABB southWestBoundary;
    southWestBoundary.center = southWestCenter;
    southWestBoundary.halfWidth = m_boundary.halfWidth / 2;
    southWestBoundary.halfHeight = m_boundary.halfHeight / 2;

    m_southWest = new QuadTree(southWestBoundary, m_capacity);

    Point southEastCenter;
    southEastCenter.x = m_boundary.center.x + m_boundary.halfWidth / 2;
    southEastCenter.y = m_boundary.center.y + m_boundary.halfHeight / 2;
    
    AABB southEastBoundary;
    southEastBoundary.center = southEastCenter;
    southEastBoundary.halfWidth = m_boundary.halfWidth / 2;
    southEastBoundary.halfHeight = m_boundary.halfHeight / 2;

    m_southEast = new QuadTree(southEastBoundary, m_capacity);

    for (auto& boid : m_boids)
    {
        if(m_northWest->Insert(boid))
        {
            continue;
        }
        if(m_northEast->Insert(boid))
        {
            continue;
        }
        if(m_southWest->Insert(boid))
        {
            continue;
        }
        if(m_southEast->Insert(boid))
        {
            continue;
        }
    }
}



