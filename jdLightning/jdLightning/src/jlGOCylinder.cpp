#include "jlGOCylinder.h"
#include "jlShadeRec.h"
#include "jlWorld.h"


const double jlCylinder::kEpsilon = 0.00001;

bool 
jlCylinder::hit(const jlRay& ray, double& t, jlShadeRec& s) {
  jlVector3 temp = ray.m_origin - m_position;
  auto dir = ray.m_direction;
  auto pos = ray.m_origin;
  //dir.y = 0;
  //dir.normalize();
  auto centerToRayX = pos.x - m_position.x;
  auto centerToRayZ = pos.z - m_position.z;
  float a = (dir.x * dir.x) + (dir.z * dir.z);
  float b = 2.0f * (dir.x * (centerToRayX)+dir.z * (centerToRayZ));
  float c = (centerToRayX * centerToRayX) + (centerToRayZ * centerToRayZ) - (m_radius * m_radius);
  float disc = b * b - 4.0f * a * c;
  if (disc < 0.0)
    return false;

  float t1 = (-b - sqrt(disc)) / (2 * a);
  float t2 = (-b + sqrt(disc)) / (2 * a);
  //float t;

  if (t1 > t2)
    t = t2;
  else
    t = t1;

  float r = ray.m_origin.y + (float)t * ray.m_direction.y;

  if ((r >= m_position.y) && (r <= m_position.y + m_height)) {

    auto localHitP = ray.m_origin + (float)t * ray.m_direction;
    auto tempNormal = jlVector3(localHitP.x - m_position.x, 0, localHitP.z - m_position.z);
    tempNormal.y = 0;
    s.m_normal = tempNormal.getnormalize();
    s.m_localHitPoint = localHitP;
    return true;
  }
  return false;
}

bool 
jlCylinder::shadowHit(const jlRay& ray, float& tmin) {
  jlVector3 temp = ray.m_origin - m_position;
  auto dir = ray.m_direction;
  auto pos = ray.m_origin;
  //dir.y = 0;
  //dir.normalize();
  auto centerToRayX = pos.x - m_position.x;
  auto centerToRayZ = pos.z - m_position.z;
  float a = (dir.x * dir.x) + (dir.z * dir.z);
  float b = 2.0f * (dir.x * (centerToRayX)+dir.z * (centerToRayZ));
  float c = (centerToRayX * centerToRayX) + (centerToRayZ * centerToRayZ) - (m_radius * m_radius);
  float disc = b * b - 4.0f * a * c;
  if (disc < 0.0f)
    return false;

  float t1 = (-b - sqrt(disc)) / (2 * a);
  //float t;

  if (t1 > kEpsilon) {
    float r = ray.m_origin.y + t1 * ray.m_direction.y;

    if ((r >= m_position.y) && (r <= m_position.y + m_height)) {
      tmin = t1;
      return true;
    }
  }
  return false;
}
