#include "vec.h"

Edge::Edge(b2Vec2 max, b2Vec2 v1, b2Vec2 v2)
{
    this->max = max;
    this->v1 = v1;
    this->v2 = v2;
    this->edge = v2 - v1;
}

float Edge::Dot(b2Vec2 &v)
{
    b2Vec2 e_n = edge;
    e_n.Normalize();
    return b2Dot(e_n,v);
}

b2Vec2 Edge::Cross(float s)
{
    b2Vec2 e_n = edge;
    e_n.Normalize();
    //b2Cross(v,1.0), 其实就是（v.y,-v.x)了
    return b2Cross(e_n,s);
}
