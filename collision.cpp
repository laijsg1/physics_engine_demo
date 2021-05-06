#include "collision.h"

Collision::Collision(Body *a, Body *b)
{
    body1 = a;
    body2 = b;
}

bool Collision::GJK()
{

    d = body2->position - body1->position;
    d.Normalize();
    simplex = {FindSupportPoint(body1,body2,d)};
    d = -simplex[0]; //其实是ORIGIN-simplex[0]，表示指向原点方向
    while(1){
        b2Vec2 A = FindSupportPoint(body1,body2,d);
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
    return a->shape->findSupportPoint(d) - b->shape->findSupportPoint(d_oppsite);
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

void Collision::EPA()
{
    int minIndex = 0;
    float minDistance = FLT_MAX;
    b2Vec2 minNormal;

    while(minDistance == FLT_MAX){
        for(int i=0;i<(int)simplex.size();i++){
            int j = (i+1)%simplex.size();

            b2Vec2 Vij = simplex[j] - simplex[i];

            b2Vec2 normal = b2Cross(Vij,1.0);
            normal.Normalize();

            float distance = b2Dot(normal,simplex[i]);

            if(distance < 0){
                distance *= -1;
                normal *= -1;
            }

            if(distance<minDistance){
                minDistance = distance;
                minNormal = normal;
                minIndex = j;
            }
        }

        b2Vec2 support = FindSupportPoint(body1,body2,minNormal);

        float sDistance = b2Dot(minNormal,support);

        if(std::abs(sDistance - minDistance) > 0.001) {
            minDistance = FLT_MAX;
            simplex.insert(simplex.begin()+minIndex,support);
        }
    }

    p_n = minNormal;
    depth = minDistance + 0.001;

}

bool Collision::ContactPointGeneration()
{
    b2Vec2 n = p_n;
    //分别查找两个形状最接近碰撞切面的边
    Edge e1 = best(-n, body2);
    Edge e2 = best(n, body1);

    //reference edges是最垂直于n的边
    Edge ref,inc;
    bool flip = false;
    if(std::abs(e1.Dot(n)) <= std::abs(e2.Dot(n))){
        ref = e1;
        inc = e2;
    } else{
        ref = e2;
        inc = e1;

        flip = true;
    }

    //裁剪分3步
    b2Vec2 refv = ref.edge;
    refv.Normalize();

    //1. 从ref edge的v1那边开始
    float o1 = b2Dot(refv,ref.v1);
    clip(inc.v1, inc.v2,refv,o1);
    if(contactPoints.size()<2) return false;

    //2. 从ref edge的v2那边开始
    float o2 = b2Dot(refv,ref.v2);
    clip(contactPoints[0],contactPoints[1],-refv,-o2);
    if(contactPoints.size()<2) return false;

    //3. 从ref edge方向开始
//    b2Vec2 refNorm = b2Cross(ref.edge,-1.0);
    b2Vec2 refNorm = ref.Cross(1.0);

    if(flip){
        refNorm *= -1;
    }

    float max = b2Dot(refNorm, ref.max);

    for(auto it = contactPoints.begin();it!=contactPoints.end();){
        if(b2Dot(refNorm,*it) - max < 0.0){
            contactPoints.erase(it);
        }else{
            it++;
        }
    }

    return !contactPoints.empty();
}

Edge Collision::best(b2Vec2 d,Body* body)
{
   int index = body->shape->findSupportPointIx(d);

   b2Vec2 v = body->shape->getVertex(index);
   //假如index为0,怎么搞
   b2Vec2 v1 = body->shape->getVertex(index-1);
   b2Vec2 v0 = body->shape->getVertex(index+1);

   b2Vec2 l = v - v1;
   b2Vec2 r = v - v0;

   l.Normalize();
   r.Normalize();

   if(b2Dot(r,d) <= b2Dot(l,d)){
       return Edge(v,v0,v);
   } else {
       return Edge(v,v,v1);
   }

}

void Collision::clip(b2Vec2 v1, b2Vec2 v2, b2Vec2 n, float o)
{
    contactPoints.clear();
    float d1 = b2Dot(n,v1) - o;
    float d2 = b2Dot(n,v2) - o;

    if(d1 >= 0.0) contactPoints.push_back(v1);
    if(d2 >= 0.0) contactPoints.push_back(v2);

    if(d1 * d2 <0.0){
        b2Vec2 e = v2 - v1;
        float u = d1 /(d1-d2);
        e *= u;
        e += v1;

        contactPoints.push_back(e);
    }
}


