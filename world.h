#ifndef WORLD_H
#define WORLD_H
#include "body.h"
#include "collision.h"
#include <vector>
#include <stack>

class World
{
public:
    World();
    void Step();
    void CollisionDetection();
    void ApplyImpulse(Body* a, Body* b);
    void ApplyImpulse(Body* a, Body* b, std::vector<b2Vec2> contactPoints, b2Vec2 normal);
    void addBody(Body* b);
    Body* CreateBody(float r, float density);
    void BoundDetection(Body* b);



    std::vector<Body*> bodyList;
//    std::stack<std::pair<Body*,Body*>> contacts;
    std::stack<Collision*> contacts;
    float dt;
};

#endif // WORLD_H
