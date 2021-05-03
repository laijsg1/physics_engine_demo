#include "body.h"

Body::Body()
{

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
