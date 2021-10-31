#include "jlGOSphere.h"

const double jlSphere::kEpsilon = 0.00001;

jlSphere::jlSphere(const jlPoint3 pos, const float& ratio) {
  m_position = pos;
  m_radius = ratio;
}

bool 
jlSphere::hit(const jlRay& ray, double& tmin, jlShadeRec& sr) {
  double t;
  jlVector3 temp = ray.m_origin - m_position;
  double a = ray.m_direction.dot(ray.m_direction);
  double b = 2.0 * temp.dot(ray.m_direction);
  double c = (double)(temp.dot(temp) - m_radius * m_radius);
  double disc = b * b - 4.0 * a * c;

  if (disc < 0.0)
    return false;
  else {
    double e = sqrt(disc);
    double denom = 2.0 * a;
    t = (-b - e) / denom; // smaller root
    if (t > kEpsilon) {
      tmin = t;
      sr.m_normal = (temp + t * ray.m_direction) / m_radius;
      sr.m_localHitPoint = ray.m_origin + t * ray.m_direction;
      return true;
    }
    t = (-b + e) / denom; // larger root
    if (t > kEpsilon) {
      tmin = t;
      sr.m_normal = (temp + t * ray.m_direction) / m_radius;
      sr.m_localHitPoint = ray.m_origin + t * ray.m_direction;
      return true;
    }
  }
  return false;
}
