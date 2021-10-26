/*****************************************************************************/
/**
 * @file    jlVector4.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   Structure for float points in 4-d space.
 *
 * Structure for float points in 4-d space.
 *
 * @bug     No known bugs.
 */
#pragma once

#include "jlPlatformDefines.h"
#include "jlVector3.h"

namespace jlUtilitiesSDK {
  class jlVector4 {

/*****************************************************************************/
/**
 * Constructors
 */
/*****************************************************************************/	
   public:

    /**
     * @brief constructor with float params with default 0.
     * @param _x for x cordinate
     * @param _y for y cordinate
     * @param _z for z cordinate
     * @param _w for w cordinate
     */
    jlVector4(const float& _x = 0.0f, 
              const float& _y = 0.0f,
    		        const float& _z = 0.0f, 
              const float& _w = 0.0f) : x(_x), y(_y), z(_z), w(_w) {};
    
    /**
     * @brief constructor with a array float 4 params.
     * @param _xyzw for x, y ,z ,w cordinate
     */
    jlVector4(float _xyzw[4]) : x(_xyzw[0]), y(_xyzw[1]), z(_xyzw[2]), w(_xyzw[3]) {};
    
    /**
     * @brief constructor with a jlVector2 and two float params.
     * @param _xy for x, y cordinate
     * @param _z for z cordinate
     * @param _w for w cordinate
     */
    jlVector4(const jlVector2& _xy, const float& _z = 0.0f, const float& _w = 0.0f) :
    		x(_xy.x), y(_xy.y), z(_z), w(_w) {};
    
    /**
     * @brief constructor with two jlVector2 params.
     * @param _xy for x, y cordinate
     * @param _zw for z ,w cordinate
     */
    jlVector4(const jlVector2& _xy, const jlVector2& _zw) :
    		x(_xy.x), y(_xy.y), z(_zw.x), w(_zw.y) {};
    
    /**
     * @brief constructor with a jlVector3 and float params.
     * @param _xyz for x, y, z cordinate
     * @param _w for w cordinate
     */
    jlVector4(const jlVector3& _xyz, const float& _w = 0.0f) :
    		x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w) {};
    
    /**
     * @brief constructor with a float and jlVector3 params.
     * @param _x for x cordinate.
     * @param _yzw for y, z, w cordinate.
     */
    jlVector4(const float& _x, const jlVector3& _yzw) 
      : x(_x), y(_yzw.x), z(_yzw.y), w(_yzw.z) {};

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
    jlVector4
    operator-() const;
    
    /**
     * @brief Positive operator
     * @return A new point Positive of this vector
     */
    jlVector4
    operator+() const;
    
    /**
     * @brief add two vectors
     * @param vec is the othe vector to add
     * @return the addition of this vector with other
     */
    jlVector4
    operator+(const jlVector4& vec) const;
    
    /**
     * @brief substraction of two vectors
     * @param vec is the othe vector to subtrac
     * @return the substraction of this vector with other
     */
    jlVector4
    operator-(const jlVector4& vec) const;
    
    /**
     * @brief modificque this vector adding other vector
     * @param vec is the othe vector to add
     * @return the addition of this vector with other in this vector
     */
    jlVector4&
    operator+=(const jlVector4& vec);
    
    /**
     * @brief modificque this vector subtacting other vector
     * @param vec is the othe vector to subtrac
     * @return the substraction of this vector with other in this vector
     */
    jlVector4&
    operator-=(const jlVector4& vec);
    
    /**
     * @brief Get the result of scaling on this vector.
     * @param scale What to multiply the vector by.
     * @return A new scaled vector.
     */
    jlVector4
    operator*(const float& scale) const;
    
    /**
     * @brief Get the result of multiply this vector with other vector.
     * @param vec What to multiply the vector by.
     * @return the result of the multiply this vector with other.
     */
    jlVector4
    operator*(const jlVector4& vec) const;
    
    /**
     * @brief Scale this vector
     * @param Scale What to multiply this vector by.
     * @return the result of the multiply in this vector.
     */
    jlVector4&
    operator*=(const float& scale);
    
    /**
     * @brief multiply this vector with other vector.
     * @param vec What to multiply this vector by.
     * @return the result of the multiply this vector with other in this vector.
     */
    jlVector4&
    operator*=(const jlVector4& vec);
    
    /**
     * @brief divition of vector with a scale.
     * @param scale What to divide the vector by.
     * @return the result of the dividetion.
     */
    jlVector4
    operator/(const float& scale) const;
    
    /**
     * @brief divition of vector with an other vector.
     * @param vec is a vector What to divide the vector by.
     * @return a vector with the result of the dividetion.
     */
    jlVector4
    operator/(const jlVector4& vec) const;
    
    /**
     * @brief divition of this vector with a scale.
     * @param scale What to divide this vector by.
     * @return the result of the dividetion in this vector.
     */
    jlVector4&
    operator/=(const float& scale);
    
    /**
     * @brief divition of this vector with an other vector.
     * @param vec is vector What to divide this vector by.
     * @return the result of the dividetion in this vector.
     */
    jlVector4&
    operator/=(const jlVector4& vec);
    
    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if all components are equal
     */
    bool
    operator==(const jlVector4& vec) const;
    
    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if one component is diferent
     */
    bool
    operator!=(const jlVector4& vec) const;
    
    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if one component is less
     */
    bool
    operator<(const jlVector4& vec) const;
    
    /**
     * @brief compare a vector with an other vector.
     * @param vec is vector What to compare vector by.
     * @return true if one component is major
     */
    bool
    operator>(const jlVector4& vec) const;
    
    /**
     * @brief get the component in a index
     * @param index is index of component in the vector.
     * @return a const of the component in the index
     */
    float
    operator[](uint32 index) const;
    
    /**
     * @brief get the component in a index
     * @param index is index of component in the vector.
     * @return a reference of the component in the index
     */
    float&
    operator[](uint32 index);
    
    /**
     * @brief queal this vector to other vector.
     * @param vec is vector What to equal vector by.
     * @return this vector equaled
     */
    jlVector4&
    operator=(const jlVector4& vec);

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
    friend jlVector4
    operator*(const float& a, const jlVector4& vec);
    
    /**
     * @brief out stream the vector
     * @return the values of the vector.
     */
    friend std::ostream&
    operator<<(std::ostream& os, const jlVector4& vec);

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
    float
    magnitude() const;
    
    /**
     * @brief function to get the square of the magnitude of vector
     * @return a flot with the square of the magnitud of vector
     */
    float
    squareMagnitude() const;
    
    /**
     * @brief function to get the square of the magnitude of vector
     * @param vec is the vectir to
     * @return a flot with the square of the magnitud of vector
     */
    float
    distance(const jlVector4& vec) const;
    
    /**
     * @brief function to normalize this vector
     * @return this vector normalized
     */
    jlVector4&
    normalize();
    
    /**
     * @brief function to get the normalize of this vector
     * @return a copy of this vector normalized
     */
    jlVector4
    getNormalize();
    
    /**
     * @brief dot product
     * @param vec if the vector with do dot product
     * @return the result of dot product
     */
    float
    dot(const jlVector4& vec) const;
    
    /**
     * @brief dot product
     * @param vec if the vector with do cross product
     * @return the result of cross product
     */
    jlVector4
    cross(const jlVector4& vec) const;

/*****************************************************************************/
/**
 * Members
 */
/*****************************************************************************/
   public:
    /**
     * @brief Vector's components.
     */
    union {
      struct {
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
        /**
         * @brief Vector's w component.
         */
        float w;
						};
      /**
       * @brief Vector's components as array.
       */
      float Vector[4];
    };
	 };

  FORCEINLINE jlVector4
  jlVector4::operator-() const {
   return jlVector4(-x, -y, -z, -w);
  }
  
  FORCEINLINE jlVector4
  jlVector4::operator+() const {
    return *this;
  }
  
  FORCEINLINE jlVector4
  jlVector4::operator+(const jlVector4& vec) const {
    return jlVector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
  }
  
  FORCEINLINE jlVector4
  jlVector4::operator-(const jlVector4& vec) const {
    return jlVector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
  }
  
  FORCEINLINE jlVector4&
  jlVector4::operator+=(const jlVector4& vec) {
    x += vec.x; y += vec.y; z += vec.z; w += vec.w;
    return *this;
  }
  
  FORCEINLINE jlVector4&
  jlVector4::operator-=(const jlVector4& vec) {
    x -= vec.x; y -= vec.y; z -= vec.z; w -= vec.w;
    return *this;
  }
  
  FORCEINLINE jlVector4
  jlVector4::operator*(const float& scale) const {
    return jlVector4(x * scale, y * scale, z * scale, w * scale);
  }
  
  FORCEINLINE jlVector4
  jlVector4::operator*(const jlVector4& vec) const {
    return jlVector4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
  }
  
  FORCEINLINE jlVector4&
  jlVector4::operator*=(const float& scale) {
    x *= scale; y *= scale; z *= scale; w *= scale;
    return *this;
  }
  
  FORCEINLINE jlVector4&
  jlVector4::operator*=(const jlVector4& vec) {
    x *= vec.x; y *= vec.y; z *= vec.z; w *= vec.w;
    return *this;
  }

  FORCEINLINE jlVector4
  jlVector4::operator/(const float& scale) const {
    return jlVector4(x / scale, y / scale, z / scale, w / scale);
  }
  
  FORCEINLINE jlVector4
  jlVector4::operator/(const jlVector4& vec) const {
    return jlVector4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
  }

  FORCEINLINE jlVector4& 
  jlVector4::operator/=(const float& scale)	{
    x /= scale; y /= scale; z /= scale; w /= scale;
    return *this;
  }
  
  FORCEINLINE jlVector4& 
  jlVector4::operator/=(const jlVector4& vec) {
    x /= vec.x; y /= vec.y; z /= vec.z; w /= vec.w;
    return *this;
  }
  
  FORCEINLINE bool
  jlVector4::operator==(const jlVector4& vec) const {
    return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w);
  }
  
  FORCEINLINE bool
  jlVector4::operator!=(const jlVector4& vec) const {
    return (x != vec.x) || (y != vec.y) || (z != vec.z) || (w != vec.w);
  }

  FORCEINLINE bool
  jlVector4::operator<(const jlVector4& vec) const {
    if (x < vec.x || y < vec.y || z < vec.z || w < vec.w) {
      return true;
    }
    return false;
  }
  
  FORCEINLINE bool
  jlVector4::operator>(const jlVector4& vec) const {
    if (x > vec.x || y > vec.y || z > vec.z || w > vec.w) {
      return true;
    }
    return false;
  }

  FORCEINLINE float
  jlVector4::operator[](uint32 index) const {
    JL_ASSERT(index < 4);
    return (&x)[index];
  }

  FORCEINLINE float&
  jlVector4::operator[](uint32 index) {
    JL_ASSERT(index < 4);
    return (&x)[index];
  }
  
  FORCEINLINE jlVector4&
  jlVector4::operator=(const jlVector4& vec) {
    x = vec.x; y = vec.y; z = vec.z; w = vec.w;
    return *this;
  }
  
  FORCEINLINE jlVector4
  operator*(const float& a, const jlVector4& vec) {
    return jlVector4(a * vec.x, a * vec.y, a * vec.z, a * vec.w);
  }

  FORCEINLINE std::ostream&
  operator<<(std::ostream& os, const jlVector4& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
  }

  FORCEINLINE float
  jlVector4::magnitude() const {
    return sqrtf(squareMagnitude());
  }
  
  FORCEINLINE float
  jlVector4::squareMagnitude() const {
    return (x * x + y * y + z * z + w * w);
  }

  FORCEINLINE float
  jlVector4::distance(const jlVector4& vec) const {
    return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) +
      (vec.z - z) * (vec.z - z) + (vec.w - w) * (vec.w - w));
  }

  FORCEINLINE jlVector4&
  jlVector4::normalize() {
    *this = getNormalize();
    return *this;
  }

  FORCEINLINE jlVector4
  jlVector4::getNormalize() {
    float sMag = squareMagnitude();
    JL_ASSERT(0.0f <= sMag);
    jlVector4 result = *this;
    
    float invLength = Math::invSqrt(sMag);
    result.x *= invLength;
    result.y *= invLength;
    result.z *= invLength;
    result.w *= invLength;
    return result;
  }
  
  FORCEINLINE float
  jlVector4::dot(const jlVector4& vec) const {
    return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
  }

  FORCEINLINE jlVector4
  jlVector4::cross(const jlVector4& vec) const {
    return 	jlVector4((y * vec[2] - z * vec[1]), -(x * vec[2] - z * vec[0]),
      (x * vec[1] - y * vec[0]), 0.0f);
  }
}
