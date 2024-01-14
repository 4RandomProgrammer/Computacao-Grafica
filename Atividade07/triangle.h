#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

using namespace std;

class triangle : public hittable {
    public:
        vec3 v0;
        vec3 v1;
        vec3 v2;
        vec3 normal;
        shared_ptr<material> mat;

        triangle(vec3 _v1, vec3 _v2, vec3 _v3, vec3 _normal, shared_ptr<material> _material) : v0(_v1), v1(_v2), v2(_v3),normal(_normal), mat(_material) {}

        bool hit_triangle(const ray& r, hit_record& rec) const {
            vec3 v0v1 = v1 - v0;
            vec3 v0v2 = v2 - v0;

            constexpr double kEpsilon = std::numeric_limits<double>::epsilon();

            vec3 N = cross(v0v1,v0v2);

            double area2 = N.length();
            
            double NdotRayDirection = dot(N,r.direction());

            if (fabs(NdotRayDirection) < kEpsilon) // almost 0
                return false; // they are parallel, so they don't intersect! 

            double d = dot(N, v0);

            double t = (d - dot(N,r.origin())) / NdotRayDirection;

            if (t < 0) return false;    

            vec3 P = r.origin() + t * r.direction();

            vec3 C;

            vec3 edge0 = v1 - v0; 
            vec3 vp0 = P - v0;
            C = cross(edge0,vp0);

            if (dot(N,C) < 0) return false;

            vec3 edge1 = v2 - v1; 
            vec3 vp1 = P - v1;
            C = cross(edge1,vp1);

            if (dot(N,C) < 0) return false;

            vec3 edge2 = v0 - v2; 
            vec3 vp2 = P - v2;
            C = cross(edge2,vp2);

            if (dot(N,C) < 0) return false;

            rec.t = t;
            rec.p = P;
            rec.normal = N;
            vec3 outward_normal = N;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            // if( normal_sizes > 0) {
                
            // }
            // else {
            //     rec.t = t;
            //     rec.p = P;
            //     rec.normal = N;
            //     vec3 outward_normal = N;
            //     rec.set_face_normal(r, outward_normal);
            // }
            std::clog << "waaaaa" << '\n';
            return true;


    }

        bool hit( const ray& r, interval ray_t, hit_record& rec) const override {
    
            if (hit_triangle(r, rec)){    
                    return true;
            }
            
            return false;

        }


};

#endif