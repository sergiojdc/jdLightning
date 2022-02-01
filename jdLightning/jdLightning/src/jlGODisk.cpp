#include "jlGODisk.h"

const double jlDisk::kEpsilon = 0.01;

bool 
jlDisk::hit(const jlRay& ray, double& tmin, jlShadeRec& sr) {
  float t = (m_position - ray.m_origin).dot(m_normal / (ray.m_direction.dot(m_normal)));
  if (t <= kEpsilon)
    return (false);

  jlVector3 p = ray.m_origin + t * ray.m_direction;
  jlVector3 distanceVector = m_position - p;
  float distance = distanceVector.squareMagnitude();

  if (distance < m_squareRatio) {
    tmin = t;
    sr.m_normal = m_normal;
    sr.m_localHitPoint = p;
    return (true);
  }
  else
    return (false);
}

bool 
jlDisk::shadowHit(const jlRay& ray, float& tmin) {
  float t = (m_position - ray.m_origin).dot(m_normal / (ray.m_direction.dot(m_normal)));
  if (t <= kEpsilon)
    return (false);

  jlVector3 p = ray.m_origin + t * ray.m_direction;
  jlVector3 distanceVector = m_position - p;
  float distance = distanceVector.squareMagnitude();
  if (distance < m_squareRatio) {
    return (true);
  }
  else
    return (false);
}
