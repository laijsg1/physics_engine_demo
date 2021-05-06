#include "body.h"

Body::Body()
{
    orient = 0;
}

void Body::setOrient(float radians)
{
    orient = radians;
    shape->setOrient(radians);
}

b2Vec2 Body::center()
{
    return this->position;
}

void Body::ApplyImpulse(b2Vec2 impulse, b2Vec2 contactVector)
{
    velocity += InvMass * impulse;
    angularVelocity += InvInertia * b2Cross(contactVector, impulse);
}

void Body::initRect( Shape* sh)
{
//    position = pos;
    //这里应该clone的
    shape = sh;
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
