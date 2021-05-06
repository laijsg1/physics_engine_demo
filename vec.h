#ifndef MATH_H
#define MATH_H
#include<box2d/box2d.h>

class Edge
{
public:
    Edge(){}
    Edge(b2Vec2 max,b2Vec2 v1,b2Vec2 v2);
    float Dot(b2Vec2& v);
    b2Vec2 Cross(float s);
    b2Vec2 edge;
    b2Vec2 v1;
    b2Vec2 v2;

    //其实就是support point
    b2Vec2 max;
};

#endif // MATH_H
