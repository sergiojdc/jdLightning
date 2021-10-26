/*****************************************************************************/
/**
 * @file    jlPoint3.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   Structure for integer points in 3-d space.
 *
 * Structure for integer points in 2-d space.
 *
 * @bug     No known bugs.
 */
/*****************************************************************************/
#pragma once

#include "jlPrerequisitesUtil.h"
#include "jlPoint2.h"
#include "jlVector3.h"
#include "jlVector4.h"

namespace jlUtilitiesSDK {

  class jlPoint3 {

/*****************************************************************************/
/**
 * Constructors
 */
/*****************************************************************************/
   public:
    /**
     * @brief Default constructor (no initialization).
     */
    jlPoint3() : x(0), y(0), z(0) {};

    /**
     * @brief Create and initialize a new instance with the specified coordinates.
     * @param InX The x-coordinate.
     * @param InY The y-coordinate.
     * @param InZ The z-coordinate.
     */
    jlPoint3(int32 _x, int32 _y, int32 _z) : x(_x), y(_y), z(_z) {};


    /**
     * @brief Create and initialize a new instance with the specified coordinates.
     * @param InX The x-coordinate.
     * @param InY The y-coordinate.
     * @param InZ The z-coordinate.
     */
    jlPoint3(const float& _x, const float& _y, const float& _z) : 
              x((int32)_x), y((int32)_y), z((int32)_z) {};

    /**
     * @brief Create and initialize a new instance with the specified coordinates.
     * @param point2 are xy-coordinate.
     * @param InZ is the z-coordinate.
     */
    jlPoint3(const jlPoint2& point2, const float& _z = 0.0f) : 
              x(point2.x), y(point2.y), z((int32)_z) {};

    /**
     * @brief Create and initialize a new instance with the specified coordinates.
     * @param point2 are xy-coordinate.
     * @param InZ is the z-coordinate.
     */
    jlPoint3(const jlPoint2& point2, int32 _z = 0) : 
              x(point2.x), y(point2.y), z((int32)_z) {};
    
    /**
     * @brief Create and initialize a new instance with the specified coordinates.
     * @param vec are a 3dvector with xyz-coordinate.
     */
    jlPoint3(const jlVector3& vec) : 
              x((int32)vec.x), y((int32)vec.y), z((int32)vec.z) {};

    /**
     * @brief Create and initialize a new instance with the specified coordinates.
     * @param vec are a 4dvector with xyz-coordinate.
     */
    jlPoint3(const jlVector4& vec) : 
              x((int32)vec.x), y((int32)vec.y), z((int32)vec.z) {};

/*****************************************************************************/
/**
 * Operators
 */
/*****************************************************************************/
   public:
    /**
     * @brief Compare two points for equality.
     * @param point The other point being compared.
     * @return true if the points are equal, false otherwise.
     */
    bool
    operator==(const jlPoint3& point) const;

    /**
     * @brief Compare two points for inequality.
     * @param point The other point being compared.
     * @return true if the point are not equal, false otherwise.
     */
    bool
    operator!=(const jlPoint3& point) const;

    /**
     * @brief Compare two points for inequality.
     * @param point The other point being compared.
     * @return true if the point are not equal, false otherwise.
     */
    bool
    operator<(const jlPoint3& point) const;

    /**
     * @brief Compare two point for inequality.
     * @param point The other point being compared.
     * @return true if the point are not equal, false otherwise.
     */
    bool
    operator>(const jlPoint3& point) const;

    /**
     * @brief Add another point component-wise to this point.
     * @param point The point to add to this point.
     * @return Reference to this point after addition.
     */
    jlPoint3&
    operator+=(const jlPoint3& point);

    /**
     * @brief Subtract another point component-wise from this point.
     * @param point The point to subtract from this point.
     * @return Reference to this point after subtraction.
     */
    jlPoint3&
    operator-=(const jlPoint3& point);

    /**
     * @brief Scale this point.
     * @param Scale What to multiply the point by.
     * @return Reference to this point after multiplication.
     */
    jlPoint3&
    operator*=(int32 Scale);

    /**
     * @brief Divide this point by a scalar.
     * @param Divisor What to divide the point by.
     * @return Reference to this point after division.
     */
    jlPoint3&
    operator/=(int32 Divisor);

    /**
     * @brief Divide this point component-wise by another point.
     * @param point The point to divide with.
     * @return Reference to this point after division.
     */
    jlPoint3&
    operator/=(const jlPoint3& point);
    /**
     * @brief Multiply this point component-wise by another point.
     * @param point The point to multuply with.
     * @return Reference to this point after multiplication.
     */
    jlPoint3&
    operator*=(const jlPoint3& point);

    /**
     * @brief Get the result of scaling on this point.
     * @param Scale What to multiply the point by.
     * @return A new scaled point.
     */
    jlPoint3
    operator*(int32 Scale) const;

    /**
     * @brief Get the result of division on this point.
     * @param Divisor What to divide the point by.
     * @return A new divided point.
     */
    jlPoint3
    operator/(int32 Divisor) const;

    /**
     * @brief Get the result of addition on this point.
     * @param point The other point to add to this.
     * @return A new combined point.
     */
    jlPoint3
    operator+(const jlPoint3& point) const;

    /**
     * @brief Get the result of subtraction from this point.
     * @param point The other point to subtract from this.
     * @return A new subtracted point.
     */
    jlPoint3
    operator-(const jlPoint3& point) const;

    /**
     * @brief Get the result of division on this point.
     * @param point The other point to divide from this.
     * @return A new division point.
     */
    jlPoint3
    operator/(const jlPoint3& point) const;

    /**
     * @brief Positive operator
     * @return A reference to the real value of the point
     */
    const jlPoint3&
    operator+() const;

    /**
     * @brief Negative operator
     * @return A new point negative of this one
     */
    jlPoint3
    operator-() const;

    /**
     * @brief Equal this point to another
     * @param point is the other point to equalize.
     * @return the values of the another point in this point
     */
    FORCEINLINE jlPoint3& 
    operator=(const jlPoint3& point);
    

    /**
     * @brief Gets specific component of the vector.
     * @param Index the index of vector component
     * @return a const to component in index.
     */
    FORCEINLINE int32
    operator[](uint32 index) const;

    /**
     * @brief Gets specific component of the vector.
     * @param Index the index of vector component
     * @return a reference of component in index.
     */
    FORCEINLINE int32&
    operator[](uint32 index);

/*****************************************************************************/
/**
 * Friends
 */
/*****************************************************************************/

    /**
     * @brief multiplicate the components of the point for a constant
     * @param scale multply the components
     * @return the result of multiplication.
     */
    FORCEINLINE friend jlPoint3
    operator*(const int32& a, const jlPoint3 point);

    /**
     * @brief out stream the vector
     * @return the values of the vector.
     */
    FORCEINLINE friend std::ostream&
    operator<<(std::ostream& os, const jlPoint3& point);

/*****************************************************************************/
/**
 * Functions
 */
/*****************************************************************************/
    /**
     * @brief Calculate the dot product
     * @param point is the other point.
     * @return the values of the dot product of this point and another
     */
    FORCEINLINE int32
    dot(const jlPoint3& point);

    /**
     * @brief Calculate the cross product
     * @param point is the other point.
     * @return the values of the cross product of this point and another
     */
    FORCEINLINE jlPoint3
    cross(const jlPoint3& point);

/*****************************************************************************/
/**
 * Members
 */
/*****************************************************************************/
   public:
    /**
     * @brief Holds the point's x-coordinate.
     */
    int32 x;

    /**
     * @brief Holds the point's y-coordinate.
     */
    int32 y;

    /**
     * @brief Holds the point's x-coordinate.
     */
    int32 z;
  };


  FORCEINLINE bool
  jlPoint3::operator==(const jlPoint3& point) const {
    return (x == point.x && y == point.y && z == point.z);
  }

  FORCEINLINE bool 
  jlPoint3::operator!=(const jlPoint3& point) const {
    return (x != point.x || y != point.y || z != point.z);
  }

  FORCEINLINE bool
  jlPoint3::operator<(const jlPoint3& point) const {
    return (x < point.x || y < point.y ||z < point.z);
  }

  FORCEINLINE bool
  jlPoint3::operator>(const jlPoint3& point) const {
    return (x > point.x || y > point.y || z > point.z);
  }

  FORCEINLINE jlPoint3& 
  jlPoint3::operator+=(const jlPoint3& point) {
    x += point.x;
    y += point.y;
    z += point.z;
    return *this;
  }

  FORCEINLINE jlPoint3& 
  jlPoint3::operator-=(const jlPoint3& point) {
    x -= point.x;
    y -= point.y;
    z -= point.z;
    return *this;
  }

  FORCEINLINE jlPoint3& 
  jlPoint3::operator*=(int32 Scale) {
    x *= Scale;
    y *= Scale;
    z *= Scale;
    return *this;
  }

  FORCEINLINE jlPoint3& 
  jlPoint3::operator/=(int32 Divisor) {
    x /= Divisor;
    y /= Divisor;
    z /= Divisor;
    return *this;
  }
  
  FORCEINLINE jlPoint3& 
  jlPoint3::operator/=(const jlPoint3& point) {
    x /= point.x;
    y /= point.y;
    z /= point.z;
    return *this;
  }

  FORCEINLINE jlPoint3&
  jlPoint3::operator*=(const jlPoint3& point) {
    x *= point.x;
    y *= point.y;
    z *= point.z;
    return *this;
  }

  FORCEINLINE jlPoint3 
  jlPoint3::operator*(int32 Scale) const {
    jlPoint3 tempPoint;
    tempPoint.x = x * Scale;
    tempPoint.y = y * Scale;
    tempPoint.z = z * Scale;
    return tempPoint;
  }

  FORCEINLINE jlPoint3 
  jlPoint3::operator/(int32 Divisor) const {
    jlPoint3 tempPoint;
    tempPoint.x = x / Divisor;
    tempPoint.y = y / Divisor;
    tempPoint.z = z / Divisor;
    return tempPoint;
  }
  
  FORCEINLINE jlPoint3 
  jlPoint3::operator+(const jlPoint3& point) const {
    jlPoint3 tempPoint;
    tempPoint.x = x + point.x;
    tempPoint.y = y + point.y;
    tempPoint.z = z + point.z;
    return tempPoint;
  }

  FORCEINLINE jlPoint3 
  jlPoint3::operator-(const jlPoint3& point) const {
    jlPoint3 tempPoint;
    tempPoint.x = x - point.x;
    tempPoint.y = y - point.y;
    tempPoint.z = z - point.z;
    return tempPoint;
  }
 
  FORCEINLINE jlPoint3
    jlPoint3::operator/(const jlPoint3& point) const {
    jlPoint3 tempPoint;
    tempPoint.x = x / point.x;
    tempPoint.y = y / point.y;
    tempPoint.z = z / point.z;
    return tempPoint;
  }

  FORCEINLINE const jlPoint3& 
  jlPoint3::operator+() const {
    return *this;
  }

  FORCEINLINE jlPoint3 
  jlPoint3::operator-() const {
    return jlPoint3(-x,-y,-z);
  }
  
  FORCEINLINE jlPoint3& 
  jlPoint3::operator=(const jlPoint3& point) {
    x = point.x;
    y = point.y;
    z = point.z;
    return *this;
  }

  FORCEINLINE int32 
  jlPoint3::operator[](uint32 index) const {
    JL_ASSERT(index < 3);
    return (&x)[index];
  }

  FORCEINLINE int32& 
  jlPoint3::operator[](uint32 index) {
    JL_ASSERT(index < 3);
    return (&x)[index];
  }

  FORCEINLINE int32
  jlPoint3::dot(const jlPoint3& point) {
    return (x * point.x + y * point.y + z * point.z);
  }

  FORCEINLINE jlPoint3
  jlPoint3::cross(const jlPoint3& point) {
    return jlPoint3(y * point.z - z * point.y, 
                    -(x * point.z - z * point.x), 
                    x * point.y - y * point.x);
  }

  FORCEINLINE jlPoint3
  operator*(const int32& a, const jlPoint3 point) {
    return jlPoint3(a * point.x, a * point.y, a * point.z);
  }

  FORCEINLINE std::ostream&
  operator<<(std::ostream& os, const jlPoint3& point) {
    os << "(" << point.x << ", " << point.y << point.z << ")";
    return os;
  }

}
