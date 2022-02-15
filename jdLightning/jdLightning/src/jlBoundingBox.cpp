#include "..\include\jlBoundingBox.h"

const double jlBBox::kEpsilon = 0.00001;

bool 
jlBBox::hit(const jlRay& ray, double& t, jlShadeRec& s) {
  double ox = ray.m_origin.x;
  double oy = ray.m_origin.y;
  double oz = ray.m_origin.z;

  double dx = ray.m_direction.x;
  double dy = ray.m_direction.y;
  double dz = ray.m_direction.z;

  double tx_min, ty_min, tz_min;
  double tx_max, ty_max, tz_max;

  double a = 1.0 / dx;
  if (a >= 0) {
    tx_min = (m_realMin.x - ox) * a;
    tx_max = (m_realMax.x - ox) * a;
  }
  else {
    tx_min = (m_realMax.x - ox) * a;
    tx_max = (m_realMin.x - ox) * a;
  }
  double b = 1.0 / dy;
  if (b >= 0) {
    ty_min = (m_realMin.y - oy) * b;
    ty_max = (m_realMax.y - oy) * b;
  }
  else {
    ty_min = (m_realMax.y - oy) * b;
    ty_max = (m_realMin.y - oy) * b;
  }
  double c = 1.0 / dz;
  if (c >= 0) {
    tz_min = (m_realMin.z - oz) * c;
    tz_max = (m_realMax.z - oz) * c;
  }
  else {
    tz_min = (m_realMax.z - oz) * c;
    tz_max = (m_realMin.z - oz) * c;
  }
  double t0, t1;
  // find largest entering t value
  if (tx_min > ty_min) {
    t0 = tx_min;
  }
  else {
    t0 = ty_min;
  }
  if (tz_min > t0) {
    t0 = tz_min;
  }
  // find smallest exiting t value
  if (tx_max < ty_max) {
    t1 = tx_max;
  }
  else {
    t1 = ty_max;
  }
  if (tz_max < t1) {
    t1 = tz_max;
  }

  if (t0 < t1 && t1 > kEpsilon) {
    t = t0;
    return true;
  }
  return false;
}

bool 
jlBBox::inside(const jlVector3& point) {
  if (point >= m_realMin && point <= m_realMax)
    return true;
  return false;
}