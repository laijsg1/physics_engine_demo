#ifndef WORLD_H
#define WORLD_H
#include "body.h"
#include <vector>

class World
{
public:
    World();
    void Step();
    void CollisionDetection();
    void ApplyImpulse(Body* a, Body* b);
    void addBody(Body* b);
    Body* CreateBody(float r, float density);
    void BoundDetection(Body* b);

    bool GJK(Body* a, Body* b);
    b2Vec2 FindSupportPoint(Body* a, Body* b, b2Vec2& d);
    bool handleSimplex(std::vector<b2Vec2>& simplex, b2Vec2& d);
    bool lineCase(std::vector<b2Vec2>& simplex, b2Vec2& d);
    bool triangleCase(std::vector<b2Vec2>& simplex, b2Vec2& d);
    b2Vec2 tripleProd(b2Vec2& a, b2Vec2& b,b2Vec2& c);

    std::vector<Body*> bodyList;
    std::vector<std::pair<Body*,Body*>> contacts;
    float dt;
};

#endif // WORLD_H
