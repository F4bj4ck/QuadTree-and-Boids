#include "Boid.h"
#include <iostream>

Boid::Boid()
{
    m_velocity.x = (std::rand() % 3) - 1;
    m_velocity.y = (std::rand() % 3) - 1;
}

Boid::~Boid()
{
    
}

void Boid::SetPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}


Point Boid::GetPosition()
{
    return m_position;
}

Point Boid::GetVelocity()
{
    return m_velocity;
}

void Boid::Flock(const std::vector<Boid*>& boidsInRange)
{
    //std::cout << "Found: " << boidsInRange.size() << " other Boids\n";
    
    Separation(boidsInRange);
    Alignment(boidsInRange);
    Cohesion(boidsInRange);
    
    m_position.x += m_velocity.x;
    m_position.y += m_velocity.y;

    //std::cout << "Boid pos: " << GetPosition().x << ", " << GetPosition().y << "; vel: " << GetVelocity().x << ", " << GetVelocity().y <<"\n";
    
    if(m_position.x < 100)
    {
        m_velocity.x += m_turnfactor;
    }
    if(m_position.x > 1820)
    {
        m_velocity.x -= m_turnfactor;
    }
    if(m_position.y < 100)
    {
        m_velocity.y += m_turnfactor;
    }
    if(m_position.y > 980)
    {
        m_velocity.y -= m_turnfactor;
    }

    float speed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

    if (speed > m_maxSpeed)
    {
        m_velocity.x = (m_velocity.x / speed) * m_maxSpeed;
        m_velocity.y = (m_velocity.y / speed) * m_maxSpeed;
    }
    else if(speed < m_minSpeed)
    {
        m_velocity.x = (m_velocity.x / speed) * m_minSpeed;
        m_velocity.y = (m_velocity.y / speed) * m_minSpeed;
    }
}

void Boid::Separation(const std::vector<Boid*>& boidsInRange)
{
    float closeDeltaX = 0.f;
    float closeDeltaY = 0.f;
    
    for (auto boid : boidsInRange)
    {
        closeDeltaX += m_position.x - boid->GetPosition().x;
        closeDeltaY += m_position.y - boid->GetPosition().y;
    }

    m_velocity.x += closeDeltaX * m_avoidFactor;
    m_velocity.y += closeDeltaY * m_avoidFactor;
}

void Boid::Alignment(const std::vector<Boid*>& boidsInRange)
{
    float averageXVelocity = 0.f;
    float averageYVelocity = 0.f;

    for (auto boid : boidsInRange)
    {
        Point otherVelocity = boid->GetVelocity();
        averageXVelocity += otherVelocity.x;
        averageYVelocity += otherVelocity.y;
    }

    if(boidsInRange.size() > 0)
    {
        averageXVelocity /= boidsInRange.size();
        averageYVelocity /= boidsInRange.size();
    }

    m_velocity.x += (averageXVelocity - m_velocity.x) * m_matchingFactor;
    m_velocity.y += (averageYVelocity - m_velocity.y) * m_matchingFactor;
}

void Boid::Cohesion(const std::vector<Boid*>& boidsInRange)
{
    float averageXPosition = 0.f;
    float averageYPosition = 0.f;

    for (auto boid : boidsInRange)
    {
        averageXPosition += boid->GetPosition().x;
        averageYPosition += boid->GetPosition().y;
    }

    if(boidsInRange.size() > 0)
    {
        averageXPosition /= boidsInRange.size();
        averageYPosition /= boidsInRange.size();
    }

    m_velocity.x += (averageXPosition - m_position.x) * m_centeringFactor;
    m_velocity.y += (averageYPosition - m_position.y) * m_centeringFactor;
}
