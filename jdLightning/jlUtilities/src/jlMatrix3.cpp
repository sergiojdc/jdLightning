#include "jlMatrix3.h"

namespace jlUtilitiesSDK {

  jlMatrix3::jlMatrix3() {
    m[0] = 1; m[1] = 0; m[2] = 0;
    m[3] = 0; m[4] = 1; m[5] = 0;
    m[6] = 0; m[7] = 0; m[8] = 1;
  }
  
  jlMatrix3::jlMatrix3(const float src[9]) {
    m[0] = src[0]; m[1] = src[1]; m[2] = src[2];
    m[3] = src[3]; m[4] = src[4]; m[5] = src[5];
    m[6] = src[6]; m[7] = src[7]; m[8] = src[8];
  }
  
  jlMatrix3::jlMatrix3(float m0, 
                       float m1, 
                       float m2, 
                       float m3, 
                       float m4,
                       float m5, 
                       float m6, 
                       float m7, 
                       float m8) {
    m[0] = m0; m[1] = m1; m[2] = m2;
    m[3] = m3; m[4] = m4; m[5] = m5;
    m[6] = m6; m[7] = m7; m[8] = m8;
  }
  
  jlMatrix3::jlMatrix3(const jlVector3& m012, const jlVector3& m345, const jlVector3& m678) {
    m[0] = m012.x; m[1] = m012.y; m[2] = m012.z;
    m[3] = m345.x; m[4] = m345.y; m[5] = m345.z;
    m[6] = m678.x; m[7] = m678.y; m[8] = m678.z;
  }
  
  jlMatrix3
  jlMatrix3::operator-() const {
    jlMatrix3 tmp = 
    {-m_00, -m_01, -m_02,
     -m_10, -m_11, -m_12,
     -m_20, -m_21, -m_22};

    return tmp;
  }
  
  jlMatrix3
  jlMatrix3::operator+() const {
   return *this;
  }
  
  const float*
  jlMatrix3::get() const {
   return m;
  }
  
  float
  jlMatrix3::getDeterminant() const {
    return (m[0] * m[4] * m[8]) + (m[1] * m[5] * m[6]) + (m[2] * m[3] * m[7]) -
           (m[0] * m[5] * m[7]) - (m[1] * m[3] * m[8]) - (m[2] * m[4] * m[6]);
  }
  
  jlMatrix3&
  jlMatrix3::identity() {
    m[0] = 1; m[1] = 0; m[2] = 0;
    m[3] = 0; m[4] = 1; m[5] = 0;
    m[6] = 0; m[7] = 0; m[8] = 1;
    return *this;
  }
  
  jlMatrix3&
  jlMatrix3::transpose() {
    std::swap(m[1], m[3]);
    std::swap(m[2], m[6]);
    std::swap(m[5], m[7]);
    
    return *this;
  }
  
  jlMatrix3
  jlMatrix3::getTranspose() const {
    jlMatrix3 trans = *this;
    std::swap(trans.m[1], trans.m[3]);
    std::swap(trans.m[2], trans.m[6]);
    std::swap(trans.m[5], trans.m[7]);
    return trans;
  }
  
  jlMatrix3&
  jlMatrix3::invert() {
    float determinant, invDeterminant;
    float tmp[9];
    
    tmp[0] = (m[4] * m[8] - m[5] * m[7]);
    tmp[1] = -(m[3] * m[8] - m[5] * m[6]);
    tmp[2] = (m[3] * m[7] - m[4] * m[6]);
    tmp[3] = -(m[1] * m[8] - m[2] * m[7]);
    tmp[4] = (m[0] * m[8] - m[2] * m[6]);
    tmp[5] = -(m[0] * m[7] - m[1] * m[6]);
    tmp[6] = (m[1] * m[5] - m[2] * m[4]);
    tmp[7] = -(m[0] * m[5] - m[2] * m[3]);
    tmp[8] = (m[0] * m[4] - m[1] * m[3]);
    
    // check determinant if it is 0
    determinant = getDeterminant();
    if (determinant >= -0.00001f && determinant <= 0.00001f) {
      return identity(); // cannot inverse, make it idenety matrix
    }
    
    // divide by the determinant
    invDeterminant = 1.0f / determinant;
    m[0] = invDeterminant * tmp[0];
    m[1] = invDeterminant * tmp[1];
    m[2] = invDeterminant * tmp[2];
    m[3] = invDeterminant * tmp[3];
    m[4] = invDeterminant * tmp[4];
    m[5] = invDeterminant * tmp[5];
    m[6] = invDeterminant * tmp[6];
    m[7] = invDeterminant * tmp[7];
    m[8] = invDeterminant * tmp[8];
    transpose();
    
    return *this;
  }
  
  jlMatrix3
  jlMatrix3::getInvert() const {
    jlMatrix3 inver = *this;
    float determinant, invDeterminant;
    float tmp[9];
    
    tmp[0] = (inver.m[4] * inver.m[8] - inver.m[5] * inver.m[7]);
    tmp[1] = -(inver.m[3] * inver.m[8] - inver.m[5] * inver.m[6]);
    tmp[2] = (inver.m[3] * inver.m[7] - inver.m[4] * inver.m[6]);
    tmp[3] = -(inver.m[1] * inver.m[8] - inver.m[2] * inver.m[7]);
    tmp[4] = (inver.m[0] * inver.m[8] - inver.m[2] * inver.m[6]);
    tmp[5] = -(inver.m[0] * inver.m[7] - inver.m[1] * inver.m[6]);
    tmp[6] = (inver.m[1] * inver.m[5] - inver.m[2] * inver.m[4]);
    tmp[7] = -(inver.m[0] * inver.m[5] - inver.m[2] * inver.m[3]);
    tmp[8] = (inver.m[0] * inver.m[4] - inver.m[1] * inver.m[3]);
    
    // check determinant if it is 0
    determinant = getDeterminant();
    if (determinant >= -0.00001f && determinant <= 0.00001f){
      return inver.identity(); // cannot inverse, make it idenety matrix
    }
    
    // divide by the determinant
    invDeterminant = 1.0f / determinant;
    inver.m[0] = invDeterminant * tmp[0];
    inver.m[1] = invDeterminant * tmp[1];
    inver.m[2] = invDeterminant * tmp[2];
    inver.m[3] = invDeterminant * tmp[3];
    inver.m[4] = invDeterminant * tmp[4];
    inver.m[5] = invDeterminant * tmp[5];
    inver.m[6] = invDeterminant * tmp[6];
    inver.m[7] = invDeterminant * tmp[7];
    inver.m[8] = invDeterminant * tmp[8];
    inver.transpose();
    
    return inver;
  }
  
  jlMatrix3&
  jlMatrix3::translate(float x, float y) {
    translate(jlVector2(x, y));
    return *this;
  }
  
  jlMatrix3&
  jlMatrix3::translate(const jlVector2& vec) {
    jlMatrix3 tras =
      {1,0,vec.x,
       0,1,vec.y,
       0,0,1};

    *this *= tras;
    return *this;
  }
  
  jlMatrix3&
  jlMatrix3::rotate(const jlRadian& angleRadian) {
    jlMatrix3 rot =
      {Math::cos(angleRadian.valueRadians()), -Math::sin(angleRadian.valueRadians()),0,
       Math::sin(angleRadian.valueRadians()), Math::cos(angleRadian.valueRadians()),0,
       0,0,1};
    *this *= rot;
    return *this;
  }
  
  jlMatrix3&
  jlMatrix3::scale(float scal) {
    scale(scal, scal);
    return *this;
  }
  
  jlMatrix3&
  jlMatrix3::scale(float sx, float sy) {
    jlMatrix3 sca =
      {sx,0,0,
       0,sy,0,
       0,0,1};

    *this *= sca;
    return *this;
  }
  
  jlMatrix3
  jlMatrix3::operator+(const jlMatrix3& mat) const {
    return jlMatrix3(m[0] + mat.m[0], m[1] + mat.m[1], m[0] + mat.m[2],
                     m[3] + mat.m[3], m[4] + mat.m[4], m[5] + mat.m[5],
                     m[6] + mat.m[6], m[7] + mat.m[7], m[8] + mat.m[8]);
  }
  
  jlMatrix3
  jlMatrix3::operator-(const jlMatrix3& mat) const {
    return jlMatrix3(m[0] - mat.m[0], m[1] - mat.m[1], m[0] - mat.m[2],
                     m[3] - mat.m[3], m[4] - mat.m[4], m[5] - mat.m[5],
                     m[6] - mat.m[6], m[7] - mat.m[7], m[8] - mat.m[8]);
  }
  
  jlMatrix3&
  jlMatrix3::operator+=(const jlMatrix3& mat) {
    m[0] += mat.m[0]; m[1] += mat.m[1]; m[0] += mat.m[2];
    m[3] += mat.m[3]; m[4] += mat.m[4]; m[5] += mat.m[5];
    m[6] += mat.m[6]; m[7] += mat.m[7]; m[8] += mat.m[8];
    return *this;
  }
  
  jlMatrix3&
  jlMatrix3::operator-=(const jlMatrix3& mat) {
    m[0] -= mat.m[0]; m[1] -= mat.m[1]; m[0] -= mat.m[2];
    m[3] -= mat.m[3]; m[4] -= mat.m[4]; m[5] -= mat.m[5];
    m[6] -= mat.m[6]; m[7] -= mat.m[7]; m[8] -= mat.m[8];
    return *this;
  }
  
  jlVector3
  jlMatrix3::operator*(const jlVector3& vec) const {
    return jlVector3(m[0] * vec.x + m[3] * vec.y + m[6] * vec.z,
                     m[1] * vec.x + m[4] * vec.y + m[7] * vec.z,
                     m[2] * vec.x + m[5] * vec.y + m[8] * vec.z);
  }
  
  jlMatrix3
  jlMatrix3::operator*(const jlMatrix3& mat) const {
    return jlMatrix3(((m[0] * mat.m[0]) + (m[1] * mat.m[3]) + (m[2] * mat.m[6])),
                     ((m[0] * mat.m[1]) + (m[1] * mat.m[4]) + (m[2] * mat.m[7])),
                     ((m[0] * mat.m[2]) + (m[1] * mat.m[5]) + (m[2] * mat.m[8])),
                     ((m[3] * mat.m[0]) + (m[4] * mat.m[3]) + (m[5] * mat.m[6])),
                     ((m[3] * mat.m[1]) + (m[4] * mat.m[4]) + (m[5] * mat.m[7])),
                     ((m[3] * mat.m[2]) + (m[4] * mat.m[5]) + (m[5] * mat.m[8])),
                     ((m[6] * mat.m[0]) + (m[7] * mat.m[3]) + (m[8] * mat.m[6])),
                     ((m[6] * mat.m[1]) + (m[7] * mat.m[4]) + (m[8] * mat.m[7])),
                     ((m[6] * mat.m[2]) + (m[7] * mat.m[5]) + (m[8] * mat.m[8])));
  }
  
  jlMatrix3&
  jlMatrix3::operator*=(const jlMatrix3& mat) {
    *this = *this * mat;
    return *this;
  }
  
  bool
  jlMatrix3::operator==(const jlMatrix3& mat) const {
    return (m[0] == mat.m[0]) && (m[1] == mat.m[1]) && (m[2] == mat.m[2]) && 
           (m[3] == mat.m[3]) && (m[4] == mat.m[4]) && (m[5] == mat.m[5]) && 
           (m[6] == mat.m[6]) && (m[7] == mat.m[7]) && (m[8] == mat.m[8]);
  }
  
  bool
  jlMatrix3::operator!=(const jlMatrix3& mat) const {
    return (m[0] != mat.m[0]) || (m[1] != mat.m[1]) || (m[2] != mat.m[2]) || 
           (m[3] != mat.m[3]) || (m[4] != mat.m[4]) || (m[5] != mat.m[5]) || 
           (m[6] != mat.m[6]) || (m[7] != mat.m[7]) || (m[8] != mat.m[8]);
  }
  
  float
  jlMatrix3::operator[](uint32 index) const {
    JL_ASSERT(index < 9);
    return (&m_00)[index];
  }
  
  float&
  jlMatrix3::operator[](uint32 index) {
    JL_ASSERT(index < 9);
    return (&m_00)[index];
  }
  
  jlMatrix3
  operator-(const jlMatrix3& mat) {
    return jlMatrix3(-mat.m[0], -mat.m[1], -mat.m[2], 
                     -mat.m[3], -mat.m[4], -mat.m[5], 
                     -mat.m[6], -mat.m[7], -mat.m[8]);
  }
  
  std::ostream&
  operator<<(std::ostream& os, const jlMatrix3& m) {
    os << std::fixed << std::setprecision(5);
    os << "[" << std::setw(10) << m.m[0] << " " << std::setw(10) << m.m[1] << " " << std::setw(10) << m.m[2] << "]\n"
       << "[" << std::setw(10) << m.m[3] << " " << std::setw(10) << m.m[4] << " " << std::setw(10) << m.m[5] << "]\n"
       << "[" << std::setw(10) << m.m[6] << " " << std::setw(10) << m.m[7] << " " << std::setw(10) << m.m[8] << "]\n";
    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
  }
  
  jlMatrix3
  matrix3Transpose(const jlMatrix3& mat) {
    jlMatrix3 trans = mat;
    std::swap(trans.m[1], trans.m[3]);
    std::swap(trans.m[2], trans.m[6]);
    std::swap(trans.m[5], trans.m[7]);
    return trans;
  }
  
  jlMatrix3
  matrix3Invert(const jlMatrix3& mat) {
    jlMatrix3 inver = mat;
    float determinant, invDeterminant;
    float tmp[9];
    
    tmp[0] = (inver.m[4] * inver.m[8] - inver.m[5] * inver.m[7]);
    tmp[1] = -(inver.m[3] * inver.m[8] - inver.m[5] * inver.m[6]);
    tmp[2] = (inver.m[3] * inver.m[7] - inver.m[4] * inver.m[6]);
    tmp[3] = -(inver.m[1] * inver.m[8] - inver.m[2] * inver.m[7]);
    tmp[4] = (inver.m[0] * inver.m[8] - inver.m[2] * inver.m[6]);
    tmp[5] = -(inver.m[0] * inver.m[7] - inver.m[1] * inver.m[6]);
    tmp[6] = (inver.m[1] * inver.m[5] - inver.m[2] * inver.m[4]);
    tmp[7] = -(inver.m[0] * inver.m[5] - inver.m[2] * inver.m[3]);
    tmp[8] = (inver.m[0] * inver.m[4] - inver.m[1] * inver.m[3]);
    
    // check determinant if it is 0
    determinant = inver.getDeterminant();
    if (determinant >= -0.00001f && determinant <= 0.00001f) {
      return inver.identity(); // cannot inverse, make it idenety matrix
    }
    
    // divide by the determinant
    invDeterminant = 1.0f / determinant;
    inver.m[0] = invDeterminant * tmp[0];
    inver.m[1] = invDeterminant * tmp[1];
    inver.m[2] = invDeterminant * tmp[2];
    inver.m[3] = invDeterminant * tmp[3];
    inver.m[4] = invDeterminant * tmp[4];
    inver.m[5] = invDeterminant * tmp[5];
    inver.m[6] = invDeterminant * tmp[6];
    inver.m[7] = invDeterminant * tmp[7];
    inver.m[8] = invDeterminant * tmp[8];
    inver.transpose();
    
    return inver;
  }
  
  jlMatrix3
  matrix3Identity() {
    jlMatrix3 ident =
      {1,0,0,
       0,1,0,
       0,0,1};
    return ident;
  }
  
  jlMatrix3
  matrix3Translate(float x, float y) {
    jlMatrix3 tras = matrix3Translate(jlVector2(x, y));
    return tras;
  }
  
  jlMatrix3
  matrix3Translate(const jlVector2& vec) {
    jlMatrix3 tras =
      {1,0,vec.x,
       0,1,vec.y,
       0,0,1};
    return tras;
  }
  
  jlMatrix3
  matrix3Rotate(const jlRadian& angleRadian) {
    jlMatrix3 rot =
      {Math::cos(angleRadian.valueRadians()), -Math::sin(angleRadian.valueRadians()),0,
       Math::sin(angleRadian.valueRadians()), Math::cos(angleRadian.valueRadians()),0,
       0,0,1};
    return rot;
  }
  
  jlMatrix3
  matrix3Scale(float scale) {
    jlMatrix3 scal = matrix3Scale(scale, scale);
    return scal;
  }
  
  jlMatrix3
  matrix3Scale(float sx, float sy) {
    jlMatrix3 scal =
      {sx,0,0,
       0,sy,0,
       0,0,1};
    return scal;
  }
}