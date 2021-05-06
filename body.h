#ifndef BODY_H
#define BODY_H
#include <box2d/box2d.h>
#include <vector>
#include <QPainter>
//#include "shape.h"

//class Transform
//{
//public:
//    b2Vec2 velocity;

//};

class Shape;
class Rect;

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

    Shape* shape;

    float angularVelocity;
    float InvInertia;

    b2Vec2 center();
    void ApplyImpulse(b2Vec2 impulse,b2Vec2 contactVector);

    void initRect(Shape* sh);

    float getDensity() const;
    void setDensity(float value);
    float getInvMass() const;
    float getRestitution() const;
    void setRestitution(float value);
};

class Shape
{
public:
    Shape(){}

    virtual b2Vec2 findSupportPoint(b2Vec2& d)=0;
    virtual int findSupportPointIx(b2Vec2& d){}
    virtual b2Vec2 getVertex(int ix){}
    virtual void draw(QPainter& pp) = 0;

};

class Rect :public Shape
{
public:
    Rect(Body* b = nullptr, int w = 0, int h = 0){
        body = b;
        this->w = w;
        this->h = h;
        vertices = {
            b2Vec2(-w, h),
            b2Vec2(w, h),
            b2Vec2(w, -h),
            b2Vec2(-w, -h)
        };
        q.SetIdentity();
    }
    virtual b2Vec2 findSupportPoint(b2Vec2& d){
        b2Vec2 position = body->position;

        float maxDistance = -FLT_MAX;
        b2Vec2 maxVertex;
        for(auto v: vertices){
            v += position;
            float curDistance = b2Dot(d,v);
            if(curDistance>maxDistance){
                maxDistance = curDistance;
                maxVertex = v;
            }
        }
        return maxVertex;
    }
    virtual int findSupportPointIx(b2Vec2& d){
        b2Vec2 position = body->position;
        float maxDistance = -FLT_MAX;
        int maxIndex;
        for(int i=0;i<(int)vertices.size();i++){
            b2Vec2 v = vertices[i] + position;
            float curDistance = b2Dot(d,v);
            if(curDistance>maxDistance){
                maxDistance = curDistance;
                maxIndex = i;
            }
        }
        return maxIndex;
    }
    virtual b2Vec2 getVertex(int ix){
        b2Vec2 position = body->position;
        int len = vertices.size();
        //先加上len是为了处理ix为负数的情况
        return vertices[(ix+len)%len] + position;
    }
    virtual void draw(QPainter& pp){
        int s = 3;
//        pp.drawRect(body->position.x, body->position.y, w*s, h*s);
        QPoint rect[4];
        for(int i=0;i<(int)vertices.size();i++){
            b2Vec2 p = vertices[i]+body->position;
            rect[i].setX(p.x);
            rect[i].setY(p.y);
        }
        pp.drawPolygon(rect,4);

    }
    std::vector<b2Vec2> vertices;
    Body* body;
    int w;
    int h;
    //旋转矩阵
    b2Rot q;
};

#endif // BODY_H
