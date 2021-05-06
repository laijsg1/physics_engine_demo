#ifndef COLLISION_H
#define COLLISION_H
#include "body.h"


class Collision
{
public:
    Collision();
    bool GJK(Body* a, Body* b);
    b2Vec2 FindSupportPoint(Body* a, Body* b, b2Vec2& d);
    bool handleSimplex();
    bool lineCase();
    bool triangleCase();
    b2Vec2 tripleProd(b2Vec2& a, b2Vec2& b,b2Vec2& c);

private:
    b2Vec2 d;
    std::vector<b2Vec2> simplex;
};

#endif // COLLISION_H
