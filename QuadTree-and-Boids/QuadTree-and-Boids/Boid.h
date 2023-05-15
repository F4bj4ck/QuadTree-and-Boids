#pragma once
#include <vector>

struct Point
{
    float x;
    float y;
};

class Boid
{
public:
    Boid();
    ~Boid();

    void SetPosition(float x, float y);
    Point GetPosition();
    Point GetVelocity();
    
    void Flock(const std::vector<Boid*>& boidsInRange);
private:
    Point m_position;
    Point m_velocity;

    const float m_maxSpeed = 6.0f;
    const float m_minSpeed = 3.0f;

    float m_turnfactor = 0.5f;
    float m_avoidFactor = 0.005f;
    float m_matchingFactor = 0.05f;
    float m_centeringFactor = 0.05f;
    
    void Separation(const std::vector<Boid*>& boidsInRange);
    void Alignment(const std::vector<Boid*>& boidsInRange);
    void Cohesion(const std::vector<Boid*>& boidsInRange);
};
