#include "jlGOBox.h"

const double jlBox::kEpsilon = 0.00001;

bool 
jlBox::hit(const jlRay& ray, double& t, jlShadeRec& s) {
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

  uint32 face_in, face_out;
  double t0, t1;
  // find largest entering t value
  if (tx_min > ty_min) {
    t0 = tx_min;
    face_in = (a >= 0.0) ? 0 : 3;
  }
  else {
    t0 = ty_min;
    face_in = (b >= 0.0) ? 1 : 4;
  }
  if (tz_min > t0) {
    t0 = tz_min;
    face_in = (c >= 0.0) ? 2 : 5;
  }
  // find smallest exiting t value
  if (tx_max < ty_max) {
    t1 = tx_max;
    face_out = (a >= 0.0) ? 3 : 0;
  }
  else {
    t1 = ty_max;
    face_out = (b >= 0.0) ? 4 : 1;
  }
  if (tz_max < t1) {
    t1 = tz_max;
    face_out = (c >= 0.0) ? 5 : 2;
  }

  if (t0 < t1 && t1 > kEpsilon) { // condition for a hit
    if (t0 > kEpsilon) {
      t = t0; // ray hits outside surface
      s.m_normal = getNormalFace(face_in);
    }
    else {
      t = t1; // ray hits inside surface
      s.m_normal = getNormalFace(face_out);
    }
    auto localHitP = ray.m_origin + (float)t * ray.m_direction;
    s.m_localHitPoint.x = localHitP.x;
    s.m_localHitPoint.y = localHitP.y;
    s.m_localHitPoint.z = localHitP.z;
    return (true);
  }
  else
    return (false);
}

bool 
jlBox::shadowHit(const jlRay& ray, float& tmin) {
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

  if (t0 < t1 && t1 > kEpsilon) { // condition for a hit
    if (t0 > kEpsilon) {
      tmin = (float)t0;
      return true;
    }
  }

  return false;
}

jlNormal
jlBox::getNormalFace(uint32 faceHit) {
  switch (faceHit) {
   case 0: 
    return (jlNormal(-1, 0, 0)); // -x face
   case 1: 
    return (jlNormal(0, -1, 0)); // -y face
   case 2: 
    return (jlNormal(0, 0, -1)); // -z face
   case 3: 
    return (jlNormal(1, 0, 0)); // +x face
   case 4: 
    return (jlNormal(0, 1, 0)); // +y face
   case 5: 
    return (jlNormal(0, 0, 1)); // +z face
  }
  return jlNormal(0, 0, 0);
}
