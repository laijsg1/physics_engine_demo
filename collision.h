#ifndef COLLISION_H
#define COLLISION_H
#include "body.h"
#include "vec.h"
#include <cmath>


class Collision
{
public:
    Collision(Body* a, Body* b);

    bool GJK();
    b2Vec2 FindSupportPoint(Body* a, Body* b, b2Vec2& d);
    bool handleSimplex();
    bool lineCase();
    bool triangleCase();
    b2Vec2 tripleProd(b2Vec2& a, b2Vec2& b,b2Vec2& c);

    void EPA();

    bool ContactPointGeneration();
    Edge best(b2Vec2 d,Body* body);
    void clip(b2Vec2 v1, b2Vec2 v2, b2Vec2 n, float o);

    Body* body1;
    Body* body2;
    b2Vec2 d;
    std::vector<b2Vec2> simplex;

    std::vector<b2Vec2> contactPoints;
    b2Vec2 p_n;
    float depth;

};

#endif // COLLISION_H
