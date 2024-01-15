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
        bool there_is_normal;
        shared_ptr<material> mat;

        triangle(vec3 _v1, vec3 _v2, vec3 _v3, vec3 _normal, shared_ptr<material> _material, bool _there_is_normal) : v0(_v1), v1(_v2), v2(_v3),normal(_normal), mat(_material), there_is_normal(_there_is_normal) {}

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
            rec.normal = normal;
            vec3 outward_normal = normal;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            if( there_is_normal ) {
                float d00 = dot(edge0,edge0);
                float d01 = dot(edge0,edge1);
                float d11 = dot(edge1,edge1);
                float d20 = dot(vp1,edge0);
                float d21 = dot(vp1,edge1);

                float denominador = d00 * d11 - d01 * d01;

                float u,w,v;

                v = (d11 * d20 - d01 * d21) / denominador;
                w = (d00 * d21 - d01 * d20) / denominador;
                u = 1.0 - v - w;
                vec3 new_normal = u * normal + v * normal + w * normal;

                rec.normal = new_normal;
                vec3 outward_normal = new_normal;
                rec.set_face_normal(r, outward_normal);
            }
            else {
                
                rec.normal = N;
                vec3 outward_normal = N;
                rec.set_face_normal(r, outward_normal);
            }

            return true;


    }

        bool hit( const ray& r, interval ray_t, hit_record& rec) const override {
    
            if (hit_triangle(r, rec)){    
                    return true;
            }
            
            return false;

        }

        void disloc(vec3 disloc) {
            v0 += disloc;
            v1 += disloc;
            v2 += disloc; 
        }

};

#endif