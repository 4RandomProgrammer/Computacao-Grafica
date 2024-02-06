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
        vec3 n1;
        vec3 n2;
        vec3 n3;
        bool there_is_normal;
        shared_ptr<material> mat;

        /**
         * @brief Construtor do triangulo. Responsável por receber todos os seus valores e inicializalos
         * @param _v1 Vertice 1 do triangulo.
         * @param _v2 Vertice 2 do triangulo.
         * @param _v3 Vertice 3 do triangulo.
         * @param _normal normal do vertice 1 do triangulo.
         * @param _normal2 normal do vertice 2 do triangulo.
         * @param _normal3 normal do vertice 3 do triangulo.
         * @param _material material para a textura do triangulo.
         * @param _there_is_normal booleano utilizado para entender caso o triangulo teve normais fornecidas.
        */  
        triangle(vec3 _v1, vec3 _v2, vec3 _v3, vec3 _normal,vec3 _normal2,vec3 _normal3, shared_ptr<material> _material, bool _there_is_normal) : v0(_v1), v1(_v2), v2(_v3),n1(_normal), mat(_material), there_is_normal(_there_is_normal) {}


        /**
         * @brief faz o calculo e a lógica para entender se o triangulo foi acertado. Caso o triangulo seja acertado e tenha normal, realiza o calculo das baricentrica para entender a influencia de cada ponto na normal obtida. Caso não fora fornecidas as normais apenas retorna a normal calculada.
         * @param r O raio que se deseja ver se acerta o triangulo.
         * @param rec O objeto fornecido para realizar .
         * @return retorna verdadeiro em caso de acerto e falso em caso de erro.
        */  
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
            rec.mat = mat;

            if( there_is_normal ) {
                double weights[3];
                baricentric(v0, v1,v2,P,weights);
                vec3 new_normal = weights[0] * n1 + weights[1] * n2 + weights[2] * n3;
                new_normal = unit_vector(new_normal);
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

    private:
        void baricentric(vec3 point1, vec3 point2, vec3 point3, vec3 intersec_point, double *ret) const {
            vec3 v0 = point2 - point1;
            vec3 v1 = point3 - point1;
            vec3 v2 = intersec_point - point1;

            double d00 = dot(v0,v0);
            double d01 = dot(v0,v1);
            double d11 = dot(v1,v1);
            double d20 = dot(v2,v0);
            double d21 = dot(v2,v1);

            double denom = d00 * d11 - d01 * d01;

            double v = (d11 * d20 - d01 * d21) / denom;
            double w = (d00 * d21 - d01 * d20) / denom;
            double u = 1.0 - v - w;
            
            ret[0] = u;
            ret[1] = v;
            ret[2] = w;

            // std::clog << u << ' ' << v << ' ' << w << '\n';
        }

};

#endif