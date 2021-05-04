#ifndef BODY_H
#define BODY_H
#include <box2d/box2d.h>
#include <vector>

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
    int w;
    int h;

    void initRect(b2Vec2 pos, int w, int h);
    b2Vec2 support(b2Vec2& d);

    float getDensity() const;
    void setDensity(float value);
    float getInvMass() const;
    float getRestitution() const;
    void setRestitution(float value);
};

#endif // BODY_H
