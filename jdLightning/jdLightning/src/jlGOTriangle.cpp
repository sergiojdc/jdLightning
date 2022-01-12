#include "jlGOTriangle.h"

const double jlTriangle::kEpsilon = 0.00001;

bool 
jlTriangle::hit(const jlRay& ray, double& tmin, jlShadeRec& sr) {
  double a = (double)m_v0.x - m_v1.x, 
         b = (double)m_v0.x - m_v2.x, 
         c = ray.m_direction.x, 
         d = (double)m_v0.x - ray.m_origin.x;
  double e = (double)m_v0.y - m_v1.y, 
         f = (double)m_v0.y - m_v2.y, 
         g = ray.m_direction.y, 
         h = (double)m_v0.y - ray.m_origin.y;
  double i = (double)m_v0.z - m_v1.z, 
         j = (double)m_v0.z - m_v2.z, 
         k = ray.m_direction.z, 
         l = (double)m_v0.z - ray.m_origin.z;
  double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  double q = g * i - e * k, s = e * j - f * i;
  double inv_denom = 1.0 / (a * m + b * q + c * s);
  double e1 = d * m - b * n - c * p;
  double beta = e1 * inv_denom;
  if (beta < 0.0)
    return (false);

  double r = r = e * l - h * i;
  double e2 = a * n + d * q + c * r;
  double gamma = e2 * inv_denom;
  if (gamma < 0.0)
    return (false);
  if (beta + gamma > 1.0)
    return (false);
  
  double e3 = a * p - b * r + d * s;
  double t = e3 * inv_denom;
  if (t < kEpsilon)
    return (false);
  
  tmin = t;
  sr.m_normal = m_normal;
  sr.m_localHitPoint = ray.m_origin + t * ray.m_direction;
  return (true);
}

bool 
jlTriangle::shadowHit(const jlRay& ray, float& tmin) {
  double a = (double)m_v0.x - m_v1.x,
    b = (double)m_v0.x - m_v2.x,
    c = ray.m_direction.x,
    d = (double)m_v0.x - ray.m_origin.x;
  double e = (double)m_v0.y - m_v1.y,
    f = (double)m_v0.y - m_v2.y,
    g = ray.m_direction.y,
    h = (double)m_v0.y - ray.m_origin.y;
  double i = (double)m_v0.z - m_v1.z,
    j = (double)m_v0.z - m_v2.z,
    k = ray.m_direction.z,
    l = (double)m_v0.z - ray.m_origin.z;
  double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  double q = g * i - e * k, s = e * j - f * i;
  double inv_denom = 1.0 / (a * m + b * q + c * s);
  double e1 = d * m - b * n - c * p;
  double beta = e1 * inv_denom;
  if (beta < 0.0)
    return (false);

  double r = r = e * l - h * i;
  double e2 = a * n + d * q + c * r;
  double gamma = e2 * inv_denom;
  if (gamma < 0.0)
    return (false);
  if (beta + gamma > 1.0)
    return (false);

  double e3 = a * p - b * r + d * s;
  double t = e3 * inv_denom;
  if (t < kEpsilon)
    return (false);

  tmin = t;
  return (true);
}
