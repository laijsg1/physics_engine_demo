#include "body.h"

Body::Body()
{

}

void Body::initRect(b2Vec2 pos, int w, int h)
{
    position = pos;
    this->w = w;
    this->h = h;
}

b2Vec2 Body::support(b2Vec2 &d)
{
    std::vector<b2Vec2> vertices = {
        b2Vec2(position.x-w, position.y+h),
        b2Vec2(position.x+w, position.y+h),
        b2Vec2(position.x+w, position.y-h),
        b2Vec2(position.x-w, position.y-h)
    };
    float maxDistance = -FLT_MAX;
    b2Vec2 maxVertex;
    for(auto v: vertices){
        float curDistance = b2Dot(d,v);
        if(curDistance>maxDistance){
            maxDistance = curDistance;
            maxVertex = v;
        }
    }
    return maxVertex;
}

float Body::getRestitution() const
{
    return restitution;
}

void Body::setRestitution(float value)
{
    restitution = value;
}

float Body::getInvMass() const
{
    return InvMass;
}

float Body::getDensity() const
{
    return density;
}

void Body::setDensity(float value)
{
    density = value;
}
