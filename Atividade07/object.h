#ifndef OBJECT_H
#define OBJECT_H

#include "hittable.h"
#include "vec3.h"

using namespace std;

class object {
    public:
        triangle(point3 _v1, point3 _v2, point3 _v3, vec3 _normal, shared_ptr<material> _material) : v0(_v1), v1(_v2), v2(_v3),normal(_normal), mat(_material) {}

        

    private:
        
        point3 v0;
        point3 v1;
        point3 v2;
        vec3 normal;
        shared_ptr<material> mat;

};

#endif