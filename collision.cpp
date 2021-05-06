#include "collision.h"

Collision::Collision()
{

}

bool Collision::GJK(Body *a, Body *b)
{
    d = b->position - a->position;
    d.Normalize();
    simplex = {FindSupportPoint(a,b,d)};
    d = -simplex[0]; //其实是ORIGIN-simplex[0]，表示指向原点方向
    while(1){
        b2Vec2 A = FindSupportPoint(a,b,d);
        if(b2Dot(A,d)<0) {
            return false;
        }
        simplex.push_back(A);
        if(handleSimplex()) return true;
    }
}

b2Vec2 Collision::FindSupportPoint(Body *a, Body *b, b2Vec2 &d)
{
    b2Vec2 d_oppsite = -d;
    return a->support(d) - b->support(d_oppsite);
}

bool Collision::handleSimplex()
{
    if(simplex.size()==2)
        return lineCase();
    return triangleCase();
}

bool Collision::lineCase()
{
    b2Vec2 B = simplex[0];
    b2Vec2 A = simplex[1];

    b2Vec2 AB = B - A;
    b2Vec2 AO = -A;

    b2Vec2 ABperp = tripleProd(AB,AO,AB);
    d.Set(ABperp.x,ABperp.y);
    return false;
}

bool Collision::triangleCase()
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

b2Vec2 Collision::tripleProd(b2Vec2 &a, b2Vec2 &b, b2Vec2 &c)
{
    return b2Cross(b2Cross(a,b),c);
}


