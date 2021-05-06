#include "world.h"

World::World()
{

}

void World::Step()
{
    //判断是否碰撞
//    contacts.clear();
    CollisionDetection();

    //看看要不要去重contacts

    //计算动量
//    for(int i=0;i<(int)contacts.size();i++){
//        ApplyImpulse(contacts[i].first, contacts[i].second);
//    }
    while(!contacts.empty()){
        Collision* c = contacts.top();
//        ApplyImpulse(c->body1, c->body2);
        ApplyImpulse(c->body1, c->body2,c->contactPoints,c->p_n);
        contacts.pop();
        delete c;
    }

    for(int i=0;i<(int)bodyList.size();i++){
        Body* b = bodyList[i];
//        b->velocity += dt * b->force;
        b->position += dt * b->velocity;
        BoundDetection(b);
    }

}

void World::CollisionDetection()
{
   for(int i = 0;i<(int)bodyList.size();i++){
       for(int j=i+1;j<(int)bodyList.size();j++){
            Body* a = bodyList[i];
            Body* b = bodyList[j];
//            b2Vec2 distance = a->position - b->position;
//            float D = a->radius + b->radius;
//            if(distance.LengthSquared()<= D*D){
//                contacts.push(std::pair<Body*,Body*>(a,b));
//            }
            Collision* collision = new Collision(a,b);
            if(collision->GJK()){
                collision->EPA();
                collision->ContactPointGeneration();
//                contacts.push(std::pair<Body*,Body*>(a,b));
                contacts.push(collision);
            }
       }
   }
}

void World::ApplyImpulse(Body *a, Body *b)
{
    b2Vec2 normal = b->position - a->position;
    normal.Normalize();
    b2Vec2 rv = b->velocity - a->velocity;

    float velAlongNormal = b2Dot(normal,rv);

    //???为什么这样就是正在分离
    if(velAlongNormal>0) return;

    float e = fmin(a->getRestitution(),b->getRestitution());

    float j = -(1.0+e) * velAlongNormal;

    j /= (a->getInvMass() + b->getInvMass());

    b2Vec2 impulse = j*normal;
    a->velocity -= a->getInvMass() *impulse;
    b->velocity += b->getInvMass() *impulse;

}

void World::ApplyImpulse(Body *a, Body *b, std::vector<b2Vec2> contactPoints, b2Vec2 normal)
{
    for(auto point: contactPoints){
        b2Vec2 ra = point - a->center();
        b2Vec2 rb = point - b->center();

        b2Vec2 rv = b->velocity + b2Cross(b->angularVelocity,rb);
        rv -= (a->velocity + b2Cross(a->angularVelocity,ra));

        float contactVel = b2Dot(rv, normal);

        if(contactVel > 0) return;

        float raCrossN = b2Cross(ra, normal);
        float rbCrossN = b2Cross(rb, normal);

        float invMassSum = a->InvMass + b->InvMass +
                pow(raCrossN,2)* a->InvInertia +
                pow(rbCrossN,2)* b->InvInertia;

        float e = fmin(a->getRestitution(),b->getRestitution());
        float j = -(1.0+e) * contactVel;
        j /= invMassSum;
        j /= (float)contactPoints.size();

        b2Vec2 impulse = j * normal;
        a->ApplyImpulse(-impulse, ra);
        b->ApplyImpulse(impulse, rb);
    }

}

void World::addBody(Body *b)
{
    bodyList.push_back(b);
}

Body* World::CreateBody(float r, float density)
{
   Body* b = new Body();
   b->setDensity(density);
   b->setRestitution(1);
   b->radius = r;
   b->InvMass = 1.0f/(3.14 * r * r * b->getDensity());
   b->angularVelocity = 0;
   b->InvInertia = 1.0f/(r*r) * b->InvMass;

   bodyList.push_back(b);
   return b;
}

//仅测试用
void World::BoundDetection(Body *b)
{
   int x = b->position.x;
   int y = b->position.y;


   float vx = b->velocity.x;
   float vy = b->velocity.y;

   int base = 0;

   if(x<0 && vx<0){
       b->velocity.x = -vx + base;
   }
   if(x>=1000 && vx>0){
       b->velocity.x = -vx -base;
   }
   if(y<0 && vy<0){
       b->velocity.y = -vy + base;
   }
   if(y>=1000 && vy>0){
       b->velocity.y = -vy -base;
   }
}
