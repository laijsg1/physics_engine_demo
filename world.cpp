#include "world.h"

World::World()
{

}

void World::Step()
{
    //判断是否碰撞
    contacts.clear();
    CollisionDetection();

    //看看要不要去重contacts

    //计算动量
    for(int i=0;i<(int)contacts.size();i++){
        ApplyImpulse(contacts[i].first, contacts[i].second);
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
//                contacts.push_back(std::pair<Body*,Body*>(a,b));
//            }
            if(GJK(a,b)){
                contacts.push_back(std::pair<Body*,Body*>(a,b));
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
   b->InvMass = 1.0f/(r * b->getDensity());

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

bool World::GJK(Body *a, Body *b)
{
    b2Vec2 d = b->position - a->position;
    d.Normalize();
    std::vector<b2Vec2> simplex = {FindSupportPoint(a,b,d)};
    d = -simplex[0]; //其实是ORIGIN-simplex[0]，表示指向原点方向
    while(1){
        b2Vec2 A = FindSupportPoint(a,b,d);
        if(b2Dot(A,d)<0) {
            return false;
        }
        simplex.push_back(A);
        if(handleSimplex(simplex,d)) return true;
    }

}

b2Vec2 World::FindSupportPoint(Body *a, Body *b, b2Vec2 &d)
{
    b2Vec2 d_oppsite = -d;
    return a->support(d) - b->support(d_oppsite);
}

bool World::handleSimplex(std::vector<b2Vec2> &simplex, b2Vec2 &d)
{
   if(simplex.size()==2)
       return lineCase(simplex,d);
   return triangleCase(simplex,d);
}

bool World::lineCase(std::vector<b2Vec2> &simplex, b2Vec2 &d)
{
    b2Vec2 B = simplex[0];
    b2Vec2 A = simplex[1];

    b2Vec2 AB = B - A;
    b2Vec2 AO = -A;

    b2Vec2 ABperp = tripleProd(AB,AO,AB);
    d.Set(ABperp.x,ABperp.y);
    return false;
}

bool World::triangleCase(std::vector<b2Vec2> &simplex, b2Vec2 &d)
{
    b2Vec2 C = simplex[0];
    b2Vec2 B = simplex[1];
    b2Vec2 A = simplex[2];

    b2Vec2 AC = C - A;
    b2Vec2 AB = B - A;
    b2Vec2 AO = -A;

    b2Vec2 ABperp = tripleProd(AC, AB, AB);
    b2Vec2 ACperp = tripleProd(AB, AC, AC);
    if(b2Dot(ABperp,AO)>0){
        simplex.erase(simplex.begin());
        d.Set(ABperp.x,ABperp.y);
        return false;
    }
    if(b2Dot(ACperp,AO)>0){
        simplex.erase(simplex.begin()+1);
        d.Set(ACperp.x,ACperp.y);
        return false;
    }
    return true;
}

b2Vec2 World::tripleProd(b2Vec2 &a, b2Vec2 &b, b2Vec2 &c)
{
    return b2Cross(b2Cross(a,b),c);
}

