#include "jlGOPlane.h"

const double jlPlane::kEpsilon = 0.00001;

jlPlane::jlPlane(const jlVector3 point, const jlNormal& normal) {
  m_point = point;
  m_normal = normal;
}

bool 
jlPlane::hit(const jlRay& ray, double& tmin, jlShadeRec& sr) {

  //compare normal direction an normal direction, is negative if there is a minimun oposite
  //if is negative means that geometri can be seen by the ray
//to test //can be optimized if compare kepsilon with this  if (relationship < 0) to test
  auto relationship = ray.m_direction.dot(m_normal);
  //get vector between center of plane and ray's origin
  auto vec = m_point - ray.m_origin;
  auto vecNorm = vec.dot(m_normal);
  //get how nearly is the point to ray, the distance from the ray to the point
  //in this case, if the distances is positive the object is in front of ray and it can be drawn
  double t = (double)(vecNorm / relationship);
  //check if t is postive
  if (t > kEpsilon) {
    //save to compare with other object
    tmin = t;
    sr.m_normal = m_normal;
    sr.m_localHitPoint = ray.m_origin + (float)t * ray.m_direction;
    return true;
  }
  return false;
}
