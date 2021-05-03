#ifndef BODY_H
#define BODY_H
#include <box2d/box2d.h>

class Body
{
public:
    Body();
    b2Vec2 velocity;
    b2Vec2 force;
    b2Vec2 position;
    float radius;
    float density;
    float InvMass;
    float restitution;

    float getDensity() const;
    void setDensity(float value);
    float getInvMass() const;
    float getRestitution() const;
    void setRestitution(float value);
};

#endif // BODY_H
