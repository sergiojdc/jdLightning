/*****************************************************************************/
/**
 * @file    jlVector3.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   Structure for float points in 3-d space.
 *
 * 
 *
 * @bug     No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include "jlPlatformDefines.h"
#include "jlVector2.h"
#include "jlString.h"

namespace jlUtilitiesSDK {

  class jlPoint3;
  class JL_UTILITY_EXPORT jlVector3 {
    /*****************************************************************************/
    /**
     * Constructors
     */
     /*****************************************************************************/
   public:
    /**
     * @brief defaul constructor
     */
    jlVector3() = default;

    /**
     * @brief constructor with float params with default 0.
     * @param _x for x cordinate
     * @param _y for y cordinate
     * @param _z for z cordinate
     */
    jlVector3(const float& _x, const float& _y = 0.0f, const float& _z = 0.0f)
    : x(_x), y(_y), z(_z) {};

    /**
     * @brief constructor with a array float 4 params.
     * @param _xyz for x, y ,z cordinate
     */
    jlVector3(const float _xyz[3]) : x(_xyz[0]), y(_xyz[1]), z(_xyz[2]) {};

    /**
     * @brief constructor with a jlVector2 and float params.
     * @param _xy for x, y cordinate
     * @param _z for z cordinate
     */
    jlVector3(const jlVector2& _xy, const float& _z = 0.0f) : x(_xy.x), y(_xy.y), z(_z) {};

    /**
     * @brief constructor with a jlVector3 params.
     * @param vec for x, y, z cordinate
     */
    jlVector3(const jlVector3& vec) : x(vec.x), y(vec.y), z(vec.z) {};

    /**
     * @brief constructor with a jlPoint3.
     * @param point for x, y, z cordinate
     */
    jlVector3(const jlPoint3& point);

    /*****************************************************************************/
    /**
     * Operators
     */
     /*****************************************************************************/
  public:
    /**
     * @brief Negative operator
     * @return A new point negative of this vector
     */
    FORCEINLINE jlVector3
    operator-() const;

    /**
     * @brief Positive operator
     * @return A new point positive of this vector
     */
    FORCEINLINE jlVector3
    operator+() const;

    /**
     * @brief add two vectors
     * @param vec is the othe vector to add
     * @return the addition of this vector with other
     */
    FORCEINLINE jlVector3
    operator+(const jlVector3& Vec) const;

    /**
     * @brief substraction of two vectors
     * @param vec is the othe vector to subtrac
     * @return the substraction of this vector with other
     */
    FORCEINLINE jlVector3
    operator-(const jlVector3& Vec) const;

    /**
     * @brief modificque this vector adding other vector
     * @param vec is the othe vector to add
     * @return the addition of this vector with other in this vector
     */
    FORCEINLINE jlVector3&
    operator+=(const jlVector3& Vec);

    /**
     * @brief modificque this vector subtacting other vector
     * @param vec is the othe vector to subtrac
     * @return the substraction of this vector with other in this vector
     */
    FORCEINLINE jlVector3&
    operator-=(const jlVector3& Vec);

    /**
     * @brief Get the result of scaling on this vector.
     * @param scale What to multiply the vector by.
     * @return A new scaled vector.
     */
    FORCEINLINE jlVector3
    operator*(const float& scale) const;

    /**
     * @brief Get the result of multiply this vector with other vector.
     * @param vec What to multiply the vector by.
     * @return the result of the multiply this vector with other.
     */
    FORCEINLINE jlVector3
    operator*(const jlVector3& Vec) const;

    /**
     * @brief Scale this vector
     * @param Scale What to multiply this vector by.
     * @return the result of the multiply in this vector.
     */
    FORCEINLINE jlVector3&
    operator*=(const float& scale);

    /**
     * @brief multiply this vector with other vector.
     * @param vec What to multiply this vector by.
     * @return the result of the multiply this vector with other in this vector.
     */
    FORCEINLINE jlVector3&
    operator*=(const jlVector3& Vec);

    /**
     * @brief divition of vector with a scale.
     * @param scale What to divide the vector by.
     * @return the result of the dividetion.
     */
    FORCEINLINE jlVector3
    operator/(const float& scale) const;

    /**
     * @brief divition of vector with an other vector.
     * @param vec is a vector What to divide the vector by.
     * @return a vector with the result of the dividetion.
     */
    FORCEINLINE jlVector3
    operator/(const jlVector3& vec) const;

    /**
     * @brief divition of this vector with a scale.
     * @param scale What to divide this vector by.
     * @return the result of the dividetion in this vector.
     */
    FORCEINLINE jlVector3&
    operator/=(const float& scale);

    /**
     * @brief divition of this vector with an other vector.
     * @param vec is vector What to divide this vector by.
     * @return the result of the dividetion in this vector.
     */
    FORCEINLINE jlVector3&
    operator/=(const jlVector3& vec);

    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if all components are equal
     */
    FORCEINLINE bool
    operator==(const jlVector3& Vec) const;

    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if one component is diferent
     */
    FORCEINLINE bool
    operator!=(const jlVector3& Vec) const;

    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if one component is less
     */
    FORCEINLINE bool
    operator<(const jlVector3& Vec) const;

    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if one component is less or equal
     */
    FORCEINLINE bool
    operator<=(const jlVector3& Vec) const;

    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if one component is major
     */
    FORCEINLINE bool
    operator>(const jlVector3& Vec) const;

    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if one component is major or equal
     */
    FORCEINLINE bool
    operator>=(const jlVector3& Vec) const;

    /**
     * @brief get the component in a index
     * @param index is index of component in the vector.
     * @return a const of the component in the index
     */
    FORCEINLINE float
    operator[](uint32 index) const;

    /**
     * @brief get the component in a index
     * @param index is index of component in the vector.
     * @return a reference of the component in the index
     */
    FORCEINLINE float&
    operator[](uint32 index);

    /**
     * @brief queal this vector to other vector.
     * @param vec is vector What to equal vector by.
     * @return this vector equaled
     */
    FORCEINLINE jlVector3&
    operator=(const jlVector3& Vec);
    /**
     * @brief queal this vector to other vector.
     * @param vec is vector What to equal vector by.
     * @return this vector equaled
     */
    //jlVector3&
    //operator=(const jlPoint3& point);

/*****************************************************************************/
/**
 * Friends
 */
/*****************************************************************************/

    /**
     * @brief multiplicate the components of a vector for a constant
     * @param scale multply the components
     * @return the result of multiplication.
     */
    FORCEINLINE friend jlVector3
    operator*(const float& a, const jlVector3 vec);

    /**
     * @brief out stream the vector
     * @return the values of the vector.
     */
    FORCEINLINE friend std::ostream&
    operator<<(std::ostream& os, const jlVector3& vec);

/*****************************************************************************/
/**
 * Functions
 */
/*****************************************************************************/
  public:

    /**
     * @brief function to get the magnitude of vector
     * @return a flot with the magnitud of vector
     */
    FORCEINLINE float
    magnitude() const;

    /**
     * @brief function to get the square of the magnitude of vector
     * @return a flot with the square of the magnitud of vector
     */
    FORCEINLINE float
    squareMagnitude() const;

    /**
     * @brief function to get the square of the magnitude of vector
     * @param vec is the vectir to
     * @return a flot with the square of the magnitud of vector
     */
    FORCEINLINE float
    distance(const jlVector3& vec) const;

    /**
     * @brief function to normalize this vector
     * @return this vector normalized
     */
    FORCEINLINE jlVector3&
    normalize();

    /**
     * @brief function to get the normalize of this vector
     * @return a copy of this vector normalized
     */
    FORCEINLINE jlVector3
    getnormalize();

    /**
     * @brief dot product
     * @param vec if the vector with do dot product
     * @return the result of dot product
     */
    FORCEINLINE float
    dot(const jlVector3& vec) const;

    /**
     * @brief dot product
     * @param vec if the vector with do cross product
     * @return the result of cross product
     */
    FORCEINLINE jlVector3
    cross(const jlVector3& vec) const;

    /**
     * @brief get the vector in a string
     * @return a string with the vector data
     */
    FORCEINLINE String
    getString() const;

/*****************************************************************************/
/**
 * Members
 */
/*****************************************************************************/
  public:
    /**
     * @brief Vector's x component.
     */
    float x;
    /**
     * @brief Vector's y component.
     */
    float y;
    /**
     * @brief Vector's z component.
     */
    float z;
  };

  FORCEINLINE jlVector3
  jlVector3::operator-() const {
    return jlVector3(-x, -y, -z);
  }

  FORCEINLINE jlVector3
  jlVector3::operator+() const {
    return *this;
  }

  FORCEINLINE jlVector3
  jlVector3::operator+(const jlVector3& Vec) const {
    return jlVector3(x + Vec.x, y + Vec.y, z + Vec.z);
  }

  FORCEINLINE jlVector3
  jlVector3::operator-(const jlVector3& Vec) const {
    return jlVector3(x - Vec.x, y - Vec.y, z - Vec.z);
  }

  FORCEINLINE jlVector3&
  jlVector3::operator+=(const jlVector3& Vec) {
    x += Vec.x; y += Vec.y; z += Vec.z;
    return *this;
  }

  FORCEINLINE jlVector3&
  jlVector3::operator-=(const jlVector3& Vec) {
    x -= Vec.x; y -= Vec.y; z -= Vec.z;
    return *this;
  }

  FORCEINLINE jlVector3
  jlVector3::operator*(const float& scale) const {
    return jlVector3(x * scale, y * scale, z * scale);
  }

  FORCEINLINE jlVector3
  jlVector3::operator*(const jlVector3& Vec) const {
    return jlVector3(x * Vec.x, y * Vec.y, z * Vec.z);
  }

  FORCEINLINE jlVector3&
  jlVector3::operator*=(const float& scale) {
    x *= scale; y *= scale; z *= scale;
    return *this;
  }

  FORCEINLINE jlVector3&
  jlVector3::operator*=(const jlVector3& Vec) {
    x *= Vec.x; y *= Vec.y; z *= Vec.z;
    return *this;
  }

  FORCEINLINE jlVector3
  jlVector3::operator/(const float& scale) const {
    return jlVector3(x / scale, y / scale, z / scale);
  }

  FORCEINLINE jlVector3
  jlVector3::operator/(const jlVector3& vec) const {
    return jlVector3(x / vec.x, y / vec.y, z / vec.z);
  }

  FORCEINLINE jlVector3&
  jlVector3::operator/=(const float& scale) {
    x /= scale; y /= scale; z /= scale;
    return *this;
  }

  FORCEINLINE jlVector3&
  jlVector3::operator/=(const jlVector3& vec) {
    x /= vec.x; y /= vec.y; z /= vec.z;
    return *this;
  }

  FORCEINLINE bool
  jlVector3::operator==(const jlVector3& Vec) const {
    return (x == Vec.x) && (y == Vec.y) && (z == Vec.z);
  }

  FORCEINLINE bool
  jlVector3::operator!=(const jlVector3& Vec) const {
    return (x != Vec.x) || (y != Vec.y) || (z != Vec.z);
  }

  FORCEINLINE bool
  jlVector3::operator<(const jlVector3& Vec) const {
    if (x < Vec.x || y < Vec.y || z < Vec.z) {
      return true;
    }
    return false;
  }

  FORCEINLINE bool
  jlVector3::operator<=(const jlVector3& Vec) const {
    if (x <= Vec.x && y <= Vec.y && z <= Vec.z) {
      return true;
    }
    return false;
  }

  FORCEINLINE bool
  jlVector3::operator>(const jlVector3& Vec) const {
    if (x > Vec.x || y > Vec.y || z > Vec.z) {
      return true;
    }
    return false;
  }

  FORCEINLINE bool
  jlVector3::operator>=(const jlVector3& Vec) const {
    if (x >= Vec.x && y >= Vec.y && z >= Vec.z) {
      return true;
    }
    return false;
  }

  FORCEINLINE float
  jlVector3::operator[](uint32 index) const {
   JL_ASSERT(index < 3);
    return (&x)[index];
  }

  FORCEINLINE float&
  jlVector3::operator[](uint32 index) {
    JL_ASSERT(index < 3);
    return (&x)[index];
  }

  FORCEINLINE jlVector3&
  jlVector3::operator=(const jlVector3& Vec) {
    x = Vec.x; y = Vec.y; z = Vec.z;
    return *this;
  }

  FORCEINLINE jlVector3
    operator*(const float& a, const jlVector3 vec) {
    return jlVector3(a * vec.x, a * vec.y, a * vec.z);
  }

  FORCEINLINE std::ostream&
    operator<<(std::ostream& os, const jlVector3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
  }

  FORCEINLINE float
  jlVector3::magnitude() const {
    return Math::sqrt(x * x + y * y + z * z);
  }

  FORCEINLINE float
  jlVector3::squareMagnitude() const {
    float mag = x * x + y * y + z * z;
    if (mag <= 0) {
      mag = 0.000001f;
    }
    return mag;
  }

  FORCEINLINE float
  jlVector3::distance(const jlVector3& vec) const {
    return Math::sqrt((x - vec.x) * (x - vec.x) + (y - vec.y) *
    (y - vec.y) + (z - vec.z) * (z - vec.z));
  }

  FORCEINLINE jlVector3&
  jlVector3::normalize() {
    *this = getnormalize();
    return *this;
  }

  FORCEINLINE jlVector3
  jlVector3::getnormalize() {
    float sMag = squareMagnitude();
    JL_ASSERT(0.0f <= sMag);
    jlVector3 result = *this;

    float invLength = Math::invSqrt(sMag);
    result.x *= invLength;
    result.y *= invLength;
    result.z *= invLength;
    return result;
  }

  FORCEINLINE float
  jlVector3::dot(const jlVector3& vec) const {
    return (x * vec.x + y * vec.y + z * vec.z);
  }

  FORCEINLINE jlVector3
  jlVector3::cross(const jlVector3& vec) const {
    return jlVector3(y * vec.z - z * vec.y, -(x * vec.z - z * vec.x), x * vec.y - y * vec.x);
  }

  FORCEINLINE String
  jlVector3::getString() const {
    String str = "(x:" + 
                 std::to_string(x) + 
                 ", y:" + 
                 std::to_string(y) + 
                 ", z:" + 
                 std::to_string(z) + 
                 ")";
    return str;
  }
}
