//#ifndef SHAPE_H
//#define SHAPE_H
//#include "body.h"
//#include<box2d/b2_math.h>
//#include<vector>
//#include <QPainter>

//class Body;
//class Shape
//{
//public:
    //Shape(){}

    //virtual b2Vec2 findSupportPoint(b2Vec2& d)=0;
    //virtual int findSupportPointIx(b2Vec2& d){}
    //virtual b2Vec2 getVertex(int ix){}
    //virtual void draw(QPainter& pp) = 0;

//};

//class Rect :public Shape
//{
//public:
    //Rect(Body* b = nullptr, int w = 0, int h = 0){
        //body = b;
        //this->w = w;
        //this->h = h;
    //}
    //virtual b2Vec2 findSupportPoint(b2Vec2& d){
        //b2Vec2 position = body->position;
        //std::vector<b2Vec2> vertices = {
            //b2Vec2(position.x-w, position.y+h),
            //b2Vec2(position.x+w, position.y+h),
            //b2Vec2(position.x+w, position.y-h),
            //b2Vec2(position.x-w, position.y-h)
        //};
        //float maxDistance = -FLT_MAX;
        //b2Vec2 maxVertex;
        //for(auto v: vertices){
            //float curDistance = b2Dot(d,v);
            //if(curDistance>maxDistance){
                //maxDistance = curDistance;
                //maxVertex = v;
            //}
        //}
        //return maxVertex;
    //}
    //virtual int findSupportPointIx(b2Vec2& d){
        //b2Vec2 position = body->position;
        //std::vector<b2Vec2> vertices = {
            //b2Vec2(position.x-w, position.y+h),
            //b2Vec2(position.x+w, position.y+h),
            //b2Vec2(position.x+w, position.y-h),
            //b2Vec2(position.x-w, position.y-h)
        //};
        //float maxDistance = -FLT_MAX;
        //int maxIndex;
        //for(int i=0;i<(int)vertices.size();i++){
            //float curDistance = b2Dot(d,vertices[i]);
            //if(curDistance>maxDistance){
                //maxDistance = curDistance;
                //maxIndex = i;
            //}
        //}
        //return maxIndex;
    //}
    //virtual b2Vec2 getVertex(int ix){
        //b2Vec2 position = body->position;
        //std::vector<b2Vec2> vertices = {
            //b2Vec2(position.x-w, position.y+h),
            //b2Vec2(position.x+w, position.y+h),
            //b2Vec2(position.x+w, position.y-h),
            //b2Vec2(position.x-w, position.y-h)
        //};
        //int len = vertices.size();
        ////先加上len是为了处理ix为负数的情况
        //return vertices[(ix+len)%len];
    //}
    //virtual void draw(QPainter& pp){
        //int s = 2;
        //pp.drawRect(body->position.x, body->position.y, w*s, h*s);
    //}
    //Body* body;
    //int w;
    //int h;
//};

//#endif // SHAPE_H
