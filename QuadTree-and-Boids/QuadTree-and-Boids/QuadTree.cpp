#include "QuadTree.h"

QuadTree::QuadTree(AABB boundary, int capacity) : m_capacity(capacity), m_boundary(boundary)
{
    m_points = std::vector<Point>(m_capacity);
}

QuadTree::~QuadTree()
{
    delete m_northWest;
    delete m_northEast;
    delete m_southWest;
    delete m_southEast;
}

bool QuadTree::Insert(Point point)
{
    if (!m_boundary.ContainsPoint(point))
    {
        return false;
    }

    if (static_cast<int>(m_points.size()) < m_capacity && !m_subdivided)
    {
        m_points.push_back(point);
        return true;
    }

    if(!m_subdivided)
    {
        Subdivide();
    }

    if(m_northWest->Insert(point))
    {
        return true;
    }
    if(m_northEast->Insert(point))
    {
        return true;
    }
    if(m_southWest->Insert(point))
    {
        return true;
    }
    if(m_southEast->Insert(point))
    {
        return true;
    }
    
    return false;
}

std::vector<Point> QuadTree::QueryRange(AABB range)
{
    
}


void QuadTree::Subdivide()
{
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
}



