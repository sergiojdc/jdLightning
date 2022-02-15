#include "jlGOSphere.h"
#include "jlBoundingBox.h"


const double jlSphere::kEpsilon = 0.00001;

jlSphere::jlSphere(const jlVector3 pos, const float& ratio) {
  m_position = pos;
  m_radius = ratio;
  m_type = GEOMETRITYPE::SPHERE;
  m_bbox.reset(new jlBBox);
  m_bbox->setPosition(pos);
  //ratio diference, this use for get min and max of bbox
  jlVector3 dr = { ratio, ratio, ratio }; 
  m_bbox->setMin(pos - dr);
  m_bbox->setMax(pos + dr);

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
      sr.m_normal = (temp + (float)t * ray.m_direction) / m_radius;
      sr.m_localHitPoint = ray.m_origin + (float)t * ray.m_direction;
      return true;
    }
    t = (-b + e) / denom; // larger root
    if (t > kEpsilon) {
      tmin = t;
      sr.m_normal = (temp + (float)t * ray.m_direction) / m_radius;
      sr.m_localHitPoint = ray.m_origin + (float)t * ray.m_direction;
      return true;
    }
  }
  return false;
}

bool 
jlSphere::shadowHit(const jlRay& ray, float& tmin) {
  float  t = 0;
  jlVector3 temp = ray.m_origin - m_position;
  float a = ray.m_direction.dot(ray.m_direction);
  float b = 2.0 * temp.dot(ray.m_direction);
  float c = temp.dot(temp) - (m_radius * m_radius);
  float disc = b * b - 4.0 * a * c;

  if (disc < 0.0)
    return false;
  else {
    float e = sqrt(disc);
    float denom = 2.0 * a;
    t = (-b - e) / denom; // smaller root
    if (t > kEpsilon) {
      tmin = t;
      return true;
    }
  }
  return false;
}

void 
jlSphere::updateBoundigBox() {
  m_bbox.reset(new jlBBox);
  m_bbox->setPosition(m_position);
  //ratio diference, this use for get min and max of bbox
  jlVector3 dr = { m_radius, m_radius, m_radius };
  m_bbox->setMin(m_position - dr);
  m_bbox->setMax(m_position + dr);
}
