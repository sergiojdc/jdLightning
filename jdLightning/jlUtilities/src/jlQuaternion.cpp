#include "jlQuaternion.h"
#include "jlDegree.h"

namespace jlUtilitiesSDK {

  jlQuaternion::jlQuaternion(const float& _x, const float& _y, const float& _z) :
    x(_x), y(_y), z(_z), w(0.0f) {}

  jlQuaternion::jlQuaternion(const float& _x, const float& _y, const float& _z, const float& _w) :
    x(_x), y(_y), z(_z), w(_w) {}

  jlQuaternion::jlQuaternion(const jlRadian& _x, const jlRadian& _y, const jlRadian& _z) {
    float fSinPitch = Math::taylorSin(_x.valueRadians() * 0.5f);
    float fCosPitch = Math::taylorCos(_x.valueRadians() * 0.5f);
    float fSinYaw = Math::taylorSin(_y.valueRadians() * 0.5f);
    float fCosYaw = Math::taylorCos(_y.valueRadians() * 0.5f);
    float fSinRoll = Math::taylorSin(_z.valueRadians() * 0.5f);
    float fCosRoll = Math::taylorCos(_z.valueRadians() * 0.5f);
    float fCosPitchCosYaw(fCosPitch * fCosYaw);
    float fSinPitchSinYaw(fSinPitch * fSinYaw);
    z = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
    x = fSinRoll * fCosPitchCosYaw - fCosRoll * fSinPitchSinYaw;
    y = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
    w = fCosRoll * fCosPitchCosYaw + fSinRoll * fSinPitchSinYaw;
  }

  jlQuaternion::jlQuaternion(const jlDegree& _x, const jlDegree& _y, const jlDegree& _z) {
    // float xDegrees = _x.valueDegrees();
     //float fSinPitch = Math::sin(_x.valueRadians() * 0.5f);
     //float fCosPitch = Math::cos(_x.valueRadians() * 0.5f);
     //float fSinYaw = Math::sin(_y.valueRadians() * 0.5f);
     //float fCosYaw = Math::cos(_y.valueRadians() * 0.5f);
     //float fSinRoll = Math::sin(_z.valueRadians() * 0.5f);
     //float fCosRoll = Math::cos(_z.valueRadians() * 0.5f);
     //float fCosPitchCosYaw(fCosPitch * fCosYaw);
     //float fSinPitchSinYaw(fSinPitch * fSinYaw);
     //z = (fSinRoll * fCosPitchCosYaw) - (fCosRoll * fSinPitchSinYaw);
     //x = (fCosRoll * fSinPitch * fCosYaw) + (fSinRoll * fCosPitch * fSinYaw);
     //y = (fCosRoll * fCosPitch * fSinYaw) - (fSinRoll * fSinPitch * fCosYaw);
     //w = (fCosRoll * fCosPitchCosYaw) + (fSinRoll * fSinPitchSinYaw);

     //y = fSinRoll * fCosPitchCosYaw - fCosRoll * fSinPitchSinYaw;
     //z = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
     //x = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
     //w = fCosRoll * fCosPitchCosYaw + fSinRoll * fSinPitchSinYaw;
     // 
     //yaw
    float cy = Math::cos(_z.valueRadians() * 0.5f);
    float sy = Math::sin(_z.valueRadians() * 0.5f);
    //roll
    float cr = Math::cos(_x.valueRadians() * 0.5f);
    float sr = Math::sin(_x.valueRadians() * 0.5f);
    //pitch
    float cp = Math::cos(_y.valueRadians() * 0.5f);
    float sp = Math::sin(_y.valueRadians() * 0.5f);

    w = cy * cr * cp + sy * sr * sp;
    x = cy * sr * cp - sy * cr * sp;
    y = cy * cr * sp + sy * sr * cp;
    z = sy * cr * cp - cy * sr * sp;
  }

  jlQuaternion::jlQuaternion(jlVector3 xyz, const float& w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {
  }

  jlQuaternion::jlQuaternion(const jlQuaternion& quaternion) : x(quaternion.x), y(quaternion.y),
    z(quaternion.z), w(quaternion.w) {}

  jlQuaternion&
    jlQuaternion::operator=(const jlQuaternion& quaternion) {
    x = quaternion.x;
    y = quaternion.y;
    z = quaternion.z;
    w = quaternion.w;
    return *this;
  }

  jlQuaternion&
    jlQuaternion::operator+=(const jlQuaternion& quaternion) {
    x += quaternion.x;
    y += quaternion.y;
    z += quaternion.z;
    w += quaternion.w;
    return *this;
  }

  jlQuaternion
    jlQuaternion::operator+(const jlQuaternion& quaternion) const {
    jlQuaternion tmpQuaternion;
    tmpQuaternion.x = x + quaternion.x;
    tmpQuaternion.y = y + quaternion.y;
    tmpQuaternion.z = z + quaternion.z;
    tmpQuaternion.w = w + quaternion.w;
    return tmpQuaternion;
  }

  jlQuaternion&
    jlQuaternion::operator-=(const jlQuaternion& quaternion) {
    x -= quaternion.x;
    y -= quaternion.y;
    z -= quaternion.z;
    w -= quaternion.w;
    return *this;
  }

  jlQuaternion
    jlQuaternion::operator-(const jlQuaternion& quaternion) const {
    jlQuaternion tmpQuaternion;
    tmpQuaternion.x = x - quaternion.x;
    tmpQuaternion.y = y - quaternion.y;
    tmpQuaternion.z = z - quaternion.z;
    tmpQuaternion.w = w - quaternion.w;
    return tmpQuaternion;
  }

  jlQuaternion&
    jlQuaternion::operator*=(const jlQuaternion& quaternion) {
    jlQuaternion tmpQuaternion = *this * quaternion;
    *this = tmpQuaternion;
    return *this;
  }

  jlQuaternion
    jlQuaternion::operator*(const jlQuaternion& quaternion) const {
    jlQuaternion tmpQuaternion;
    tmpQuaternion.x = w * quaternion.x + x * quaternion.w + y * quaternion.z - z * quaternion.y;
    tmpQuaternion.y = w * quaternion.y + y * quaternion.w + z * quaternion.x - x * quaternion.z;
    tmpQuaternion.z = w * quaternion.z + z * quaternion.w + x * quaternion.y - y * quaternion.x;
    tmpQuaternion.w = w * quaternion.w - x * quaternion.x - y * quaternion.y - z * quaternion.z;
    return tmpQuaternion;
  }

  jlQuaternion&
    jlQuaternion::operator*=(const float& scale) {
    x *= scale;
    y *= scale;
    z *= scale;
    w *= scale;
    return *this;
  }

  jlQuaternion jlQuaternion::operator*(const float& scale) const
  {
    jlQuaternion tmpQuaternion;
    tmpQuaternion.x = x * scale;
    tmpQuaternion.y = y * scale;
    tmpQuaternion.z = z * scale;
    tmpQuaternion.w = w * scale;
    return tmpQuaternion;
  }

  bool
    jlQuaternion::operator==(const jlQuaternion& quaternion) const {
    if (Math::abs(x - quaternion.x) < Math::EPSILONF &&
      Math::abs(y - quaternion.y) < Math::EPSILONF &&
      Math::abs(z - quaternion.z) < Math::EPSILONF &&
      Math::abs(w - quaternion.w) < Math::EPSILONF) {
      return true;
    }
    return false;
  }

  bool
    jlQuaternion::operator!=(const jlQuaternion& quaternion) const {
    if (Math::abs(x - quaternion.x) > Math::EPSILONF ||
      Math::abs(y - quaternion.y) > Math::EPSILONF ||
      Math::abs(z - quaternion.z) > Math::EPSILONF ||
      Math::abs(w - quaternion.w) > Math::EPSILONF) {
      return true;
    }
    return false;
  }

  bool
    jlQuaternion::operator<(const jlQuaternion& quaternion) const {
    if (magnitude() < quaternion.magnitude()) {
      return true;
    }
    return false;
  }

  bool
    jlQuaternion::operator>(const jlQuaternion& quaternion) const {
    if (magnitude() > quaternion.magnitude()) {
      return true;
    }
    return false;
  }

  float
    jlQuaternion::magnitude() const {
    return Math::sqrt(squareMagnitude());
  }

  float jlQuaternion::squareMagnitude() const
  {
    return x * x + y * y + z * z + w * w;
  }

  jlQuaternion&
    jlQuaternion::normalize() {
    *this = getNormalize();
    return *this;
  }

  jlQuaternion
    jlQuaternion::getNormalize() const {
    float inverMag = squareMagnitude();
    JL_ASSERT(0.0f <= inverMag);

    inverMag = Math::invSqrt(inverMag);
    jlQuaternion tmpQuaternion;
    tmpQuaternion.x = x * inverMag;
    tmpQuaternion.y = y * inverMag;
    tmpQuaternion.z = z * inverMag;
    tmpQuaternion.w = w * inverMag;
    return tmpQuaternion;
  }

  jlQuaternion&
    jlQuaternion::conjugate() {
    *this = getConjugate();
    return *this;
  }

  jlQuaternion jlQuaternion::getConjugate() const
  {
    float scalar = w;
    jlVector3 tmpAxis = { x,y,z };
    tmpAxis *= -1;
    return jlQuaternion(tmpAxis, scalar);
  }

  jlQuaternion&
    jlQuaternion::inverse() {
    *this = getInverse();
    return *this;
  }

  jlQuaternion
    jlQuaternion::getInverse() const {
    float invSMagnitude = magnitude();
    invSMagnitude *= invSMagnitude;
    invSMagnitude = 1 / invSMagnitude;

    jlQuaternion tmpConjugate = getConjugate();

    float scalar = tmpConjugate.w * invSMagnitude;
    jlVector3 tmpAxis = { tmpConjugate.x, tmpConjugate.y, tmpConjugate.z };
    tmpAxis *= invSMagnitude;
    return jlQuaternion(invSMagnitude, scalar);
  }

  jlQuaternion&
    jlQuaternion::rotate(const float& _x, const float& _y, const float& _z, bool degree) {
    if (!degree)
    {
      return rotate(_x * Math::RAD2DEG, _y * Math::RAD2DEG, _z * Math::RAD2DEG);
    }
    else
    {
      return rotate(_x, _y, _z);
    }
  }

  jlQuaternion&
    jlQuaternion::rotate(jlDegree _x, jlDegree _y, jlDegree _z) {
    jlQuaternion q2(_x, _y, _z), q = *this, qinv = q;
    qinv.conjugate();

    *this = q * q2 * qinv;
    return *this;
  }

  jlVector3
    jlQuaternion::getEuler() {
    jlVector3 euler;

    //euler.z = Math::atan(2 * (x * y + w * z), w * w + x * x - y * y - z * z);
    //euler.z *= Math::RAD2DEG;
    //euler.y = Math::asin(-2 * (x * z - w * y));
    //euler.y *= Math::RAD2DEG;
    //euler.x = Math::atan((2) * (y * z + w * x), w * w - x * x - y * y + z * z);
    //euler.x *= Math::RAD2DEG;

    //euler.x = Math::atan(2 * (x * y + w * z), w * w + x * x - y * y - z * z);
    //euler.x *= Math::RAD2DEG;
    //euler.y = Math::asin(-2 * (x * z - w * y));
    //euler.y *= Math::RAD2DEG;
    //euler.z = Math::atan((2) * (y * z + w * x), w * w - x * x - y * y + z * z);
    //euler.z *= Math::RAD2DEG;

    //euler.x = Math::atan(2 * (x * y + w * z), 1 - (2 * (z * z + x * x)));
    //euler.x *= Math::RAD2DEG;
    //
    //euler.y = Math::atan((2) * (x * z + w * y), 1 - (2 * (x * x + y * y)));
    //euler.y *= Math::RAD2DEG;
    //
    //euler.y = Math::asin(2 * (w * x - y * z));
    //euler.y *= Math::RAD2DEG;

    float sinr_cosp = +2.0f * ((w * x) + (y * z));
    float cosr_cosp = +1.0f - 2.0f * ((x * x) + (y * y));
    euler.x = atan2(sinr_cosp, cosr_cosp);

    // Pitch (y-axis rotation)
    float sinp = +2.0f * ((w * y) - (z * x));
    if (fabs(sinp) >= 1) {
      euler.y = copysign(Math::PI / 2, sinp); // use 90 degrees if out of range
    }
    else
      euler.y = asin(sinp);

    // Yaw (z-axis rotation)
    float siny_cosp = +2.0f * ((w * z) + (x * y));
    float cosy_cosp = +1.0f - 2.0f * ((y * y) + (z * z));
    euler.z = atan2(siny_cosp, cosy_cosp);

    euler *= Math::RAD2DEG;

    return euler;
  }

  jlVector3
    jlQuaternion::getRadians() {
    jlVector3 rad;

    rad.z = Math::atan(2 * (x * y + w * z), w * w + x * x - y * y - z * z);
    //euler.z *= Math::RAD2DEG;
    rad.y = Math::asin(-2 * (x * z - w * y));
    //euler.y *= Math::RAD2DEG;
    rad.x = Math::atan((2) * (y * z + w * x), w * w - x * x - y * y + z * z);
    //euler.x *= Math::RAD2DEG;

    return rad;
  }

  jlMatrix4 jlQuaternion::getMatrix() const
  {
    jlMatrix4 mat;
    mat.m[0] = 1.0f - 2.0f * (y * y + z * z);
    mat.m[1] = 2.0f * (x * y - z * w);
    mat.m[2] = 2.0f * (x * z + y * w);
    mat.m[3] = 0;

    mat.m[4] = 2.0f * (x * y + z * w);
    mat.m[5] = 1.0f - 2.0f * (x * x + z * z);
    mat.m[6] = 2.0f * (y * z - x * w);
    mat.m[7] = 0;

    mat.m[8] = 2.0f * (x * z - y * w);
    mat.m[9] = 2.0f * (y * z + x * w);
    mat.m[10] = 1.0f - 2.0f * (x * x + y * y);
    mat.m[11] = 0;

    mat.m[12] = 0;
    mat.m[13] = 0;
    mat.m[14] = 0;
    mat.m[15] = 1;

    //mat.m[0] = 1.0f - (2.0f * (y * y - z * z));
    //mat.m[1] = 2.0f * (x * y - z * w);
    //mat.m[2] = 2.0f * (x * z + y * w);
    //mat.m[3] = 0;
    //
    //mat.m[4] = 2.0f * (x * y + z * w);
    //mat.m[5] = 1.0f - (2.0f * (x * x - z * z));
    //mat.m[6] = 2.0f * (y * z - x * w);
    //mat.m[7] = 0;
    //
    //mat.m[8] = 2.0f * (x * z - y * w);
    //mat.m[9] = 2.0f * (y * z + x * w);
    //mat.m[10] = 1.0f - (2.0f * (x * x - y * y));
    //mat.m[11] = 0;
    //
    //mat.m[12] = 0; mat.m[13] = 0; mat.m[14] = 0; mat.m[15] = 1;
    //mat.m[0] = 1.0f - 2.0f * (y * y + z * z);
    //mat.m[4] = 2.0f * (x * y - z * w);
    //mat.m[8] = 2.0f * (x * z + y * w);
    //mat.m[3] = 0;
    //
    //mat.m[1] = 2.0f * (x * y + z * w);
    //mat.m[5] = 1.0f - 2.0f * (x * x + z * z);
    //mat.m[9] = 2.0f * (y * z - x * w);
    //mat.m[7] = 0;
    //
    //mat.m[2] = 2.0f * (x * z - y * w);
    //mat.m[6] = 2.0f * (y * z + x * w);
    //mat.m[10] = 1.0f - 2.0f * (x * x + y * y);
    //mat.m[11] = 0;
    //
    //mat.m[12] = 0;
    //mat.m[13] = 0;
    //mat.m[14] = 0;
    //mat.m[15] = 1;
    return mat;

    //resMatrix.a1 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (y * y + z * z);
    //resMatrix.a2 = static_cast<TReal>(2.0) * (x * y - z * w);
    //resMatrix.a3 = static_cast<TReal>(2.0) * (x * z + y * w);
    //resMatrix.b1 = static_cast<TReal>(2.0) * (x * y + z * w);
    //resMatrix.b2 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (x * x + z * z);
    //resMatrix.b3 = static_cast<TReal>(2.0) * (y * z - x * w);
    //resMatrix.c1 = static_cast<TReal>(2.0) * (x * z - y * w);
    //resMatrix.c2 = static_cast<TReal>(2.0) * (y * z + x * w);
    //resMatrix.c3 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (x * x + y * y);
  }

}
