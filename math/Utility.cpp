#include "Utility.h"
#include <iostream>
using namespace std;
/* Calculates the distance between two points
 */
float distPoints(Vector3 v1, Vector3 v2)
{
  return sqrt((v1[0] - v2[0])*(v1[0] - v2[0]) +
              (v1[1] - v2[1])*(v1[1] - v2[1]) +
              (v1[2] - v2[2])*(v1[2] - v2[2]));
}

/* Calculates the distance squared, to save one sqrt function
 */
float distPointsSquared(Vector3 v1, Vector3 v2)
{
  return (v1[0] - v2[0])*(v1[0] - v2[0]) +
         (v1[1] - v2[1])*(v1[1] - v2[1]) +
         (v1[2] - v2[2])*(v1[2] - v2[2]);
}

/* Calculates the distance from a plane to a point
   -If its 0 the point is on the plane
   -If its positive the point is on the same side of the normal of the plane
   -If its negative the point is on the other side of the nomral of the plane
*/
float distPointPlane(float a, float b, float c, float d, Vector3 v)
{
  return (a*v[0] + b*v[1] + c*v[2] + d)/sqrt(a*a + b*b + c*c);
}

/* Checks if two spheres are colliding
 */
bool areColliding(Sphere *a, Sphere *b)
{
    float r = (a->getR()+b->getR())*(a->getR()+b->getR());
    if (r >= distPointsSquared(a->getPos(),b->getPos()))
    {
        Vector3 netVel = a->getVel() - b->getVel();
        Vector3 disp = a->getPos() - b->getPos();
        return netVel.dot(disp) < 0;
    }
    else
        return false;
}

/* Check if a sphere is colliding with a wall
 */
bool sphereWallColliding(Sphere *a, Wall *b)
{
    GLfloat r = a->getR();
    return r >= distPointPlane(b->getA(), b->getB(), b->getC(), b->getD(), a->getPos())
        && a->getVel().dot(-Vector3(b->getA(), b->getB(), b->getC())) > 0;
    //return r >= distPointPlane(b.getA(), b.getB(), b.getC(), b.getD(), a.getPos());
}

/* 
   Calculates the new vel of the sphere
   If the angle is 0 is full reflection, if is 90, there is none
   So the dot product tells the angle beewteen the normal of the plane and
   The velocity so I know how much to reflect.
 */
void wallCollision(Sphere *s, Wall *w, bool lose=false)
{
	double delta = (lose)?0.95:0.992;
    Vector3 norm(w->getA(), w->getB(), w->getC());
    s->setVel((s->getVel() - ((-norm)*s->getVel().dot(-norm))*2)*delta);
}

/* Calculates the new vel and direction of the sphere */
void collision(Sphere *a, Sphere *b, bool lose=false)
{
	double delta = (lose)?0.95:0.992;
  /**
   * X = a.pos - b.pos;
   * X.normalize();
   * Then we calculate the x-direction and velocity vector
   * v1 = s1.vel
   * x1 = x.dot(v1)
   * v1x = x * x1  <-- x1 is not a vector.
   * v1y = v1 - v1x
   * m1 = s1.mass
   **** For the other sphere ****
   * x = x X -1
   * v2 = s2.vel
   * x2 = x.dot(v2)
   * v2x = x * x2 <-- x2 is not a vector.
   * v2y = v2-v2x
   * m2 = s2.mass
   * **** Then we need the velocity vector ****
   */
    /*NOT WORKING
    float dx = a.getPos()[0] - b.getPos()[0],dy = a.getPos()[2] - b.getPos()[2];
  
    float velx_1=a.getVel()[0],vely_1=a.getVel()[1];
    float velx_2=b.getVel()[0],vely_2=b.getVel()[1];
    
    float m_1 = a.getMass(), m_2 = b.getMass();
    
    double collision_angle = atan2(dy,dx);
  
    float mag_1 = a.getRap(), mag_2=b.getRap();
    double dir_1 = atan2(vely_1,velx_1);
    double dir_2 = atan2(vely_2,velx_2);
    
    float n_xspeed_1 = mag_1*cos(dir_1 - collision_angle);
    float n_yspeed_1 = mag_1*sin(dir_1 - collision_angle);
    
    float n_xspeed_2 = mag_2*cos(dir_2 - collision_angle);
    float n_yspeed_2 = mag_2*sin(dir_2 - collision_angle);
    
    float final_xspeed_1 = ((m_1-m_2)*n_xspeed_1 + (m_2+m_2)*n_xspeed_2)/(m_1+m_2);
    float final_xspeed_2 = ((m_1+m_1)*n_xspeed_1+(m_2 - m_1)*n_xspeed_2)/(m_1+m_2);
    
    float final_yspeed_1 = n_yspeed_1;
    float final_yspeed_2 = n_yspeed_2;
    
    float fx_1,fx_2,fy_1,fy_2;
    
    fx_1 = cos(collision_angle)*final_xspeed_1+cos(collision_angle+(PI/2))*final_yspeed_1;
    fy_1 = sin(collision_angle)*final_xspeed_1+sin(collision_angle+(PI/2))*final_yspeed_1;
    
    fx_2 = cos(collision_angle)*final_xspeed_2+cos(collision_angle+(PI/2))*final_yspeed_2;
    fy_2 = sin(collision_angle)*final_xspeed_2+sin(collision_angle+(PI/2))*final_yspeed_2;
    
    Vector3 v1(fx_1,0,fy_1), v2(fx_2,0,fy_2);
    a.setRap(v1.magnitude()),b.setRap(v2.magnitude());
    a.setVel(v1),b.setVel(v2);
    
    //cout << v1 << " " << v2 << endl;*/
    
//TEMPORAL MEHTOD
    Vector3 disp = (a->getPos() - b->getPos()).normalize();
    a->setVel(a->getVel() - (disp * a->getVel().dot(disp) * 2)*delta);
    b->setVel(b->getVel() - (disp * b->getVel().dot(disp) * 2)*delta);

}
