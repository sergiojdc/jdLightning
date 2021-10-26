/*****************************************************************************/
/**
 * @file    jlPoint2.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   Structure for integer points in 2-d space.
 *
 * Structure for integer points in 2-d space.
 *
 * @bug     No known bugs.
 */
/*****************************************************************************/
#pragma once

#include "jlPrerequisitesUtil.h"

namespace jlUtilitiesSDK {

  class jlPoint2 {

/*****************************************************************************/
/**
 * Constructors
 */
/*****************************************************************************/
   public:
    /**
     * @brief Default constructor (no initialization).
     */
    jlPoint2() = default;

    /**
     * @brief Create and initialize a new instance with the specified coordinates.
     * @param InX The x-coordinate.
     * @param InY The y-coordinate.
     */
    jlPoint2(int32 _x, int32 _y) : x(_x), y(_y) {};

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
    operator==(const jlPoint2& point) const;

    /**
     * @brief Compare two points for inequality.
     * @param point The other point being compared.
     * @return true if the point are not equal, false otherwise.
     */
    bool
    operator!=(const jlPoint2& point) const;

    /**
     * @brief Compare two points for inequality.
     * @param point The other point being compared.
     * @return true if the point are not equal, false otherwise.
     */
    bool
    operator<(const jlPoint2& point) const;

    /**
     * @brief Compare two point for inequality.
     * @param point The other point being compared.
     * @return true if the point are not equal, false otherwise.
     */
    bool
    operator>(const jlPoint2& point) const;

    /**
     * @brief Add another point component-wise to this point.
     * @param point The point to add to this point.
     * @return Reference to this point after addition.
     */
    jlPoint2&
    operator+=(const jlPoint2& point);

    /**
     * @brief Subtract another point component-wise from this point.
     * @param point The point to subtract from this point.
     * @return Reference to this point after subtraction.
     */
    jlPoint2&
    operator-=(const jlPoint2& point);

    /**
     * @brief Scale this point.
     * @param Scale What to multiply the point by.
     * @return Reference to this point after multiplication.
     */
    jlPoint2&
    operator*=(int32 Scale);

    /**
     * @brief Divide this point by a scalar.
     * @param Divisor What to divide the point by.
     * @return Reference to this point after division.
     */
    jlPoint2&
    operator/=(int32 Divisor);

    /**
     * @brief Divide this point component-wise by another point.
     * @param point The point to divide with.
     * @return Reference to this point after division.
     */
    jlPoint2&
    operator/=(const jlPoint2& point);
    /**
     * @brief Multiply this point component-wise by another point.
     * @param point The point to multuply with.
     * @return Reference to this point after multiplication.
     */
    jlPoint2&
    operator*=(const jlPoint2& point);

    /**
     * @brief Get the result of scaling on this point.
     * @param Scale What to multiply the point by.
     * @return A new scaled point.
     */
    jlPoint2
    operator*(int32 Scale) const;

    /**
     * @brief Get the result of division on this point.
     * @param Divisor What to divide the point by.
     * @return A new divided point.
     */
    jlPoint2
    operator/(int32 Divisor) const;

    /**
     * @brief Get the result of addition on this point.
     * @param point The other point to add to this.
     * @return A new combined point.
     */
    jlPoint2
    operator+(const jlPoint2& point) const;

    /**
     * @brief Get the result of subtraction from this point.
     * @param point The other point to subtract from this.
     * @return A new subtracted point.
     */
    jlPoint2
    operator-(const jlPoint2& point) const;

    /**
     * @brief Get the result of division on this point.
     * @param point The other point to divide from this.
     * @return A new division point.
     */
    jlPoint2
    operator/(const jlPoint2& point) const;

    /**
     * @brief Positive operator
     * @return A reference to the real value of the point
     */
    const jlPoint2&
    operator+() const;

    /**
     * @brief Negative operator
     * @return A new point negative of this one
     */
    jlPoint2
    operator-() const;

    /**
     * @brief Equal this point to another
     * @param point is the other point to equalize.
     * @return the values of the another point in this point
     */
    FORCEINLINE jlPoint2& 
    operator=(const jlPoint2& point);
    

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
    FORCEINLINE friend jlPoint2
    operator*(const int32& a, const jlPoint2 vec);

    /**
     * @brief out stream the vector
     * @return the values of the vector.
     */
    FORCEINLINE friend std::ostream&
    operator<<(std::ostream& os, const jlPoint2& vec);

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
    dot(const jlPoint2& point);

    /**
     * @brief Calculate the cross product
     * @param point is the other point.
     * @return the values of the cross product of this point and another
     */
    FORCEINLINE int32
    cross(const jlPoint2& point);

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
  };


  FORCEINLINE bool
  jlPoint2::operator==(const jlPoint2& point) const {
    return (x == point.x && y == point.y);
  }

  FORCEINLINE bool 
  jlPoint2::operator!=(const jlPoint2& point) const {
    return (x != point.x || y != point.y);
  }

  FORCEINLINE bool
  jlPoint2::operator<(const jlPoint2& point) const {
    return (x < point.x || y < point.y);
  }

  FORCEINLINE bool
  jlPoint2::operator>(const jlPoint2& point) const {
    return (x > point.x || y > point.y);
  }

  FORCEINLINE jlPoint2& 
  jlPoint2::operator+=(const jlPoint2& point) {
    x += point.x;
    y += point.y;
    return *this;
  }

  FORCEINLINE jlPoint2& 
  jlPoint2::operator-=(const jlPoint2& point) {
    x -= point.x;
    y -= point.y;
    return *this;
  }

  FORCEINLINE jlPoint2& 
  jlPoint2::operator*=(int32 Scale) {
    x *= Scale;
    y *= Scale;
    return *this;
  }

  FORCEINLINE jlPoint2& 
  jlPoint2::operator/=(int32 Divisor) {
    x /= Divisor;
    y /= Divisor;
    return *this;
  }
  
  FORCEINLINE jlPoint2& 
  jlPoint2::operator/=(const jlPoint2& point) {
    x /= point.x;
    y /= point.y;
    return *this;
  }

  FORCEINLINE jlPoint2&
  jlPoint2::operator*=(const jlPoint2& point) {
    x *= point.x;
    y *= point.y;
    return *this;
  }

  FORCEINLINE jlPoint2 
  jlPoint2::operator*(int32 Scale) const {
    jlPoint2 tempPoint;
    tempPoint.x = x * Scale;
    tempPoint.y = y * Scale;
    return tempPoint;
  }

  FORCEINLINE jlPoint2 
  jlPoint2::operator/(int32 Divisor) const {
    jlPoint2 tempPoint;
    tempPoint.x = x / Divisor;
    tempPoint.y = y / Divisor;
    return tempPoint;
  }
  
  FORCEINLINE jlPoint2 
  jlPoint2::operator+(const jlPoint2& point) const {
    jlPoint2 tempPoint;
    tempPoint.x = x + point.x;
    tempPoint.y = y + point.y;
    return tempPoint;
  }

  FORCEINLINE jlPoint2 
  jlPoint2::operator-(const jlPoint2& point) const {
    jlPoint2 tempPoint;
    tempPoint.x = x - point.x;
    tempPoint.y = y - point.y;
    return tempPoint;
  }
 
  FORCEINLINE jlPoint2
    jlPoint2::operator/(const jlPoint2& point) const {
    jlPoint2 tempPoint;
    tempPoint.x = x / point.x;
    tempPoint.y = y / point.y;
    return tempPoint;
  }

  FORCEINLINE const jlPoint2& 
  jlPoint2::operator+() const {
    return *this;
  }

  FORCEINLINE jlPoint2 
  jlPoint2::operator-() const {
    return jlPoint2(-x,-y);
  }
  
  FORCEINLINE jlPoint2& 
  jlPoint2::operator=(const jlPoint2& point) {
    x = point.x;
    y = point.y;
    return *this;
  }

  FORCEINLINE int32 
  jlPoint2::operator[](uint32 index) const {
    JL_ASSERT(index < 2);
    return (&x)[index];
  }

  FORCEINLINE int32& 
  jlPoint2::operator[](uint32 index) {
    JL_ASSERT(index < 2);
    return (&x)[index];
  }

  FORCEINLINE int32
  jlPoint2::dot(const jlPoint2& point) {
    return (x * point.x + y * point.y);
  }

  FORCEINLINE int32 
  jlPoint2::cross(const jlPoint2& point) {
    return (x * point.y - y * point.x);
  }

  FORCEINLINE jlPoint2
  operator*(const int32& a, const jlPoint2 vec) {
    return jlPoint2(a * vec.x, a * vec.y);
  }

  FORCEINLINE std::ostream&
  operator<<(std::ostream& os, const jlPoint2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
  }

}
