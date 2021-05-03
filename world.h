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

    std::vector<Body*> bodyList;
    std::vector<std::pair<Body*,Body*>> contacts;
    float dt;
};

#endif // WORLD_H
