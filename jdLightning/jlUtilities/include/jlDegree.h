/*****************************************************************************/
/**
 * @file    jlDegree.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   Wrapper class which indicates a given angle value is in Degrees.
 *
 * Degree values are interchangeable with Degree values, and conversions will
 * be done automatically between them.
 *
 * @bug	   No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include "jlPrerequisitesUtil.h"

namespace jlUtilitiesSDK
{
  class jlRadian;
  class JL_UTILITY_EXPORT jlDegree
  {
    /*****************************************************************************/
    /**
     * Constructors
     */
     /*****************************************************************************/
   public:
    /**
     * @brief Default constructor degree.
     */
    jlDegree() = default;

    /**
     * @brief constructor with other degree.
     * @param degree is the degree with which is equaled
     */
    constexpr jlDegree(const jlDegree& degree) = default;

    /**
     * @brief constructor with float.
     * @param degree is the float value
     */
    constexpr jlDegree(float f) : m_degree(f) {}

    /**
     * @brief constructor with a radian.
     * @param radian is the radian to cast
     */
    jlDegree(const jlRadian& radian);

    /*****************************************************************************/
    /**
     * Operators
     */
     /*****************************************************************************/
  public:
    /**
     * @brief equals to degree
     * @param degree is the degree with which is equaled
     */
    constexpr jlDegree&
    operator=(const jlDegree& degree) = default;

    /**
     * @brief equals to float
     * @param f is the float with which is equaled
     */
    jlDegree&
    operator=(const float& f) {
      m_degree = f;
      return *this;
    }

    /**
     * @brief equals to radian
     * @param radian is the radian to cast with which is equaled
     */
    jlDegree&
    operator=(const jlRadian& radian);

    /**
     * @brief Get this degree on positive
     * @return the value of this degree on positive
     */
    const jlDegree&
    operator+() const {
      return *this;
    }

    /**
     * @brief add two degree
     * @param degree is the othe degree to add
     * @return the addition of this degree with other
     */
    jlDegree
    operator+(const jlDegree& degree) const {
      return jlDegree(m_degree + degree.m_degree);
    }

    /**
     * @brief add a radian with this degree
     * @param radian is the radian to add
     * @return the addition of this degree with the radian
     */
    jlDegree
    operator+(const jlRadian& radian) const;

    /**
     * @brief add two degree
     * @param degree is the othe degree to add
     * @return the addition of this degree with other in this degree
     */
    jlDegree&
    operator+=(const jlDegree& degree) {
      m_degree += degree.m_degree;
      return *this;
    }

    /**
     * @brief add a radian with this degree
     * @param radian is the radian to add
     * @return the addition of this degree with the radian in this degree
     */
    jlDegree&
    operator+=(const jlRadian& radian);

    /**
     * @brief Get this degree on negative
     * @return the value of this degree on negative
     */
    jlDegree
    operator-() const {
      return jlDegree(-m_degree);
    }

    /**
    * @brief subtrac two degree
    * @param degree is the other degree to subtrac
    * @return the subtraction of this degree with other
    */
    jlDegree
    operator-(const jlDegree& degree) const {
      return jlDegree(m_degree - degree.m_degree);
    }

    /**
     * @brief subtrac this degree with a radian
     * @param radian is the radian to subtrac
     * @return the subtraction of this degree with radian
     */
    jlDegree
    operator-(const jlRadian& radian) const;

    /**
    * @brief subtrac two degree
    * @param degree is the other degree to subtrac
    * @return the subtraction of this degree with other in this degree
    */
    jlDegree&
    operator-=(const jlDegree& degree) {
      m_degree -= degree.m_degree;
      return *this;
    }

    /**
     * @brief subtrac this degree with a radian
     * @param radian is the radian to subtrac
     * @return the subtraction of this degree with radian in this degree
     */
    jlDegree&
    operator-=(const jlRadian& radian);

    /**
     * @brief multiplicate this degree with a float
     * @param f is the float to multply the degree
     * @return the result of multiplication
     */
    jlDegree
    operator*(float f) const {
      return jlDegree(m_degree * f);
    }

    /**
     * @brief multiplicate two degree
     * @param degree is the degree to multply this degree
     * @return the result of multiplication
     */
    jlDegree
    operator*(const jlDegree& degree) const {
      return jlDegree(m_degree * degree.m_degree);
    }

    /**
     * @brief multiplicate this degree with a float
     * @param f is the float to multply the degree
     * @return the result of multiplication in this degree
     */
    jlDegree&
    operator*=(float f) {
      m_degree *= f;
      return *this;
    }

    /**
     * @brief multiplicate two degree
     * @param degree is the degree to multply this degree
     * @return the result of multiplication in this degree
     */
    jlDegree&
    operator*=(const jlDegree& degree) {
      m_degree *= degree.m_degree;
      return *this;
    }

    /**
     * @brief divide this degree with a float
     * @param f is the float to divide the degree
     * @return the result of division
     */
    jlDegree
    operator/(float f) const {
      return jlDegree(m_degree / f);
    }

    /**
     * @brief divide this degree with a float
     * @param f is the float to divide the degree
     * @return the result of division in this degree
     */
    jlDegree&
    operator/=(float f) {
      m_degree /= f;
      return *this;
    }

    /**
     * @brief divide two degree
     * @param degree is the degree to divide this degree
     * @return the result of division
     */
    jlDegree
    operator/(const jlDegree& degree) const {
      return jlDegree(m_degree / degree.m_degree);
    }

    /**
     * @brief divide two degree
     * @param degree is the degree to divide this degree
     * @return the result of division in this degree
     */
    jlDegree&
    operator/=(const jlDegree& degree) {
      m_degree /= degree.m_degree;
      return *this;
    }

    /**
     * @brief compare two degree
     * @param degree is the degree to compare
     * @return true if this degree is less
     */
    bool
    operator<(const jlDegree& degree) const {
      return m_degree < degree.m_degree;
    }

    /**
     * @brief compare two degree
     * @param degree is the degree to compare
     * @return true if this degree is less or equal
     */
    bool
    operator<=(const jlDegree& degree) const {
      return m_degree <= degree.m_degree;
    }

    /**
     * @brief compare two degree
     * @param degree is the degree to compare
     * @return true if this degree is identical
     */
    bool
    operator==(const jlDegree& degree) const {
      return m_degree == degree.m_degree;
    }

    /**
     * @brief compare two degree
     * @param degree is the degree to compare
     * @return true if this degree is diferent
     */
    bool
    operator!=(const jlDegree& degree) const {
      return m_degree != degree.m_degree;
    }

    /**
     * @brief compare two degree
     * @param degree is the degree to compare
     * @return true if this is greater or equal
     */
    bool
    operator>=(const jlDegree& degree) const {
      return m_degree >= degree.m_degree;
    }

    /**
     * @brief compare two degree
     * @param degree is the degree to compare
     * @return true if this is greater
     */
    bool
    operator>(const jlDegree& degree) const {
      return m_degree > degree.m_degree;
    }

    /**
     * @brief compare this degree withc a float
     * @param f is the float to compare
     * @return true if this degree's value is less than the float
     */
    bool
    operator<(const float& f) const {
      return m_degree < f;
    }

    /**
     * @brief compare this degree withc a float
     * @param f is the float to compare
     * @return true if this degree's value is less or equal than the float
     */
    bool
    operator<=(const float& f) const {
      return m_degree <= f;
    }

    /**
     * @brief compare this degree withc a float
     * @param f is the float to compare
     * @return true if this degree's value and the float are identical
     */
    bool
    operator==(const float& f) const {
      return m_degree == f;
    }

    /**
     * @brief compare this degree withc a float
     * @param f is the float to compare
     * @return true if this degree's value and the float are diferent
     */
    bool
    operator!=(const float& f) const {
      return m_degree != f;
    }

    /**
     * @brief compare this degree withc a float
     * @param f is the float to compare
     * @return true if this degree's value is greater or equal than the float
     */
    bool
    operator>=(const float& f) const {
      return m_degree >= f;
    }

    /**
     * @brief compare this degree withc a float
     * @param f is the float to compare
     * @return true if this degree's value is greater than the float
     */
    bool
    operator>(const float& f) const {
      return m_degree > f;
    }

/*****************************************************************************/
/**
 * Friends
 */
/*****************************************************************************/
    /**
     * @brief multiplicate a float with a degree
     * @param lhs is the float to multply the degree
     * @param rhs is the degree that will be multiplied
     * @return the result of multiplication
     */
    friend jlDegree
    operator*(float lhs, const jlDegree& rhs) {
      return jlDegree(lhs * rhs.m_degree);
    }

    /**
     * @brief divide a float with a degree
     * @param lhs is the float to divide the degree
     * @param rhs is the degree that will be dvided
     * @return the result of divition
     */
    friend jlDegree
    operator/(float lhs, const jlDegree& rhs) {
      return jlDegree(lhs / rhs.m_degree);
    }

    /**
     * @brief add a degree with a float
     * @param lhs is the degree to will add the float
     * @param rhs is the float that will be added
     * @return the result of addition
     */
    friend jlDegree
    operator+(jlDegree& lhs, float rhs) {
      return jlDegree(lhs.m_degree + rhs);
    }

    /**
     * @brief add a float with a degree
     * @param lhs is the float to will add the degree
     * @param rhs is the degree that will be added
     * @return the result of addition
     */
    friend jlDegree
    operator+(float lhs, const jlDegree& rhs) {
      return jlDegree(lhs + rhs.m_degree);
    }

    /**
     * @brief subtract a degree with a float
     * @param lhs is the degree to will subtract the float
     * @param rhs is the float that will be subtracted
     * @return the result of subtraction
     */
    friend jlDegree
    operator-(const jlDegree& lhs, float rhs) {
      return jlDegree(lhs.m_degree - rhs);
    }

    /**
     * @brief subtract a float with a degree
     * @param lhs is the float to will subtract the degree
     * @param rhs is the degree that will be subtracted
     * @return the result of subtraction
     */
    friend jlDegree
    operator-(const float lhs, const jlDegree& rhs) {
      return jlDegree(lhs - rhs.m_degree);
    }

    /**
     * @brief compare a float with a degree
     * @param lhs is the float to will compare the degree
     * @param rhs is the degree that will be compared
     * @return true if the float is less
     */
    friend bool
    operator<(float lhs, const jlDegree& rhs) {
      return lhs < rhs.m_degree;
    }

    /**
     * @brief compare a float with a degree
     * @param lhs is the float to will compare the degree
     * @param rhs is the degree that will be compared
     * @return true if the float is less or equal
     */
    friend bool
    operator<=(float lhs, const jlDegree& rhs) {
      return lhs <= rhs.m_degree;
    }

    /**
     * @brief compare a float with a degree
     * @param lhs is the float to will compare the degree
     * @param rhs is the degree that will be compared
     * @return true if the float are identical to the degree
     */
    friend bool
    operator==(float lhs, const jlDegree& rhs) {
      return lhs == rhs.m_degree;
    }

    /**
     * @brief compare a float with a degree
     * @param lhs is the float to will compare the degree
     * @param rhs is the degree that will be compared
     * @return true if the float are diferent to the degree
     */
    friend bool
    operator!=(float lhs, const jlDegree& rhs) {
      return lhs != rhs.m_degree;
    }

    /**
     * @brief compare a float with a degree
     * @param lhs is the float to will compare the degree
     * @param rhs is the degree that will be compared
     * @return true if the float is greater or equal than the degree
     */
    friend bool
    operator>=(float lhs, const jlDegree& rhs) {
      return lhs >= rhs.m_degree;
    }

    /**
     * @brief compare a float with a degree
     * @param lhs is the float to will compare the degree
     * @param rhs is the degree that will be compared
     * @return true if the float is greater than the degree
     */
    friend bool
    operator>(float lhs, const jlDegree& rhs) {
      return lhs > rhs.m_degree;
    }

    /*****************************************************************************/
    /**
     * Functions
     */
     /*****************************************************************************/
   public:
    /**
     * @brief get the value of this degree on degree
     * @return the value of this degree on degree
     */
    float
    valueDegrees() const {
      return m_degree;
    }

    /**
     * @brief get the value of this degree on radian
     * @return the value of this degree on radian
     */
    FORCEINLINE float
    valueRadians() const;

    /**
     * @brief Utility to ensure angle is between +/- 180 degrees by unwinding.
     */
    void
    unwindDegrees();
    /*****************************************************************************/
    /**
     * Mmebers
     */
     /*****************************************************************************/
   private:
    /**
    * @brief jlDegree value
    */
    float m_degree = 0.0f;
  };
}
