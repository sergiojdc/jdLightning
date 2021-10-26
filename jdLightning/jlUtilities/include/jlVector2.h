/*****************************************************************************/
/**
 * @file    jlVector2.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   A basic class for  2d vector
 *
 *
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include "jlPrerequisitesUtil.h"

namespace jlUtilitiesSDK {

  class jlVector2{

/*****************************************************************************/
/**
 * Constructors
 */
/*****************************************************************************/
   public:
    /**
     * @brief Default constructor (equal x and y 0).
     */
    FORCEINLINE jlVector2() = default;
    
    /**
     * @brief Constructor with data.
     * @param _x for x coordinate
     * @param _y for y coordinate
     */
    FORCEINLINE jlVector2(const float& _x, const float& _y);
    
    /**
     * @brief Constructor with an array.
     * @param _xy where index 0 is for X coordinate and index 1 is for Y coordinate
     */
    FORCEINLINE jlVector2(float _xy[2]) : x(_xy[0]), y(_xy[1]) {};
    
    /**
     * @brief Constructor with an vector.
     * @param _vec where _vec.x is for X coordinate and _vec.y is for Y coordinate
     */
    FORCEINLINE jlVector2(const jlVector2& _vec) : x(_vec.x), y(_vec.y) {};

/*****************************************************************************/
/**
 * Operators
 */
/*****************************************************************************/
    public:
    /**
     * @brief negqative Vector
     * @return the values of vector in negative form
     */
    FORCEINLINE jlVector2 
    operator-() const;
    
    /**
     * @brief Gets the result of adding this vector with another
     * @param vec the vector to add to this.
     * @return the result of adding the two vectors.
     */
    FORCEINLINE jlVector2 
    operator+(const jlVector2& vec) const;
    
    /**
     * @brief Gets the result of subtracting this vector with another
     * @param vec The other vector to subtract from this.
     * @return The result of the subtraction the tow vectors.
     */
    FORCEINLINE jlVector2 
    operator-(const jlVector2& vec) const;
    
    /**
     * @brief add this vector with another
     * @param vec the vector to add to this.
     * @return the result of adding in this vector.
     */
    FORCEINLINE jlVector2& 
    operator+=(const jlVector2& vec);
    
    /**
     * @brief substrac this vector with another
     * @param vec the vector to add to this.
     * @return the result of substraction in this vector.
     */
    FORCEINLINE jlVector2& 
    operator-=(const jlVector2& vec);
    
    /**
     * @brief multiplicate the components of this vector for a constant
     * @param scale multply the components
     * @return the result of multiplication in this vector.
     */
    FORCEINLINE jlVector2 
    operator*(const float& scale) const;
    
    /**
     * @brief Gets the result of component-wise multiplication of this vector by another.
     * @param vec is the other vector to multiply this by.
     * @return the result of the multiplication.
     */
    FORCEINLINE jlVector2 
    operator*(const jlVector2& vec) const;
    
    /**
     * @brief Gets the result of component-wise multiplication of this vector by another.
     * @param vec is the other vector to multiply this by.
     * @return the result of the multiplication in this vector.
     */
    FORCEINLINE jlVector2& 
    operator*=(const float& scale);
    
    /**
     * @brief Gets the result of component-wise multiplication of this vector by another.
     * @param vec is the other vector to multiply this by.
     * @return the result of the multiplicationin this vector.
     */
    FORCEINLINE jlVector2& 
    operator*=(const jlVector2& vec);					// multiply each element and update this object
    
    /**
     * @brief Gets the result of component-wise division of this vector by a constant.
     * @param vec is the other vector to divide this by.
     * @return the result of the division this vector.
     */	
    FORCEINLINE jlVector2 
    operator/(const float& scale) const;
    
    /**
     * @brief Gets the result of component-wise division of this vector a constant.
     * @param vec is the other vector to divide this by.
     * @return the result of the division this vector in this vector.
     */
    FORCEINLINE jlVector2& 
    operator/=(const float& scale);			
    
    /**
     * @brief Gets the result of comparation of this vector with another.
     * @param vec is the other vector to compare this by.
     * @return true if are equal, else return false.
     */
    FORCEINLINE bool 
    operator==(const jlVector2& vec) const;
    
    /**
     * @brief Gets the result of comparation of this vector with another.
     * @param vec is the other vector to compare this by.
     * @return true if are diferent, else return false.
     */
    FORCEINLINE bool 
    operator!=(const jlVector2& vec) const;
    
    /**
     * @brief Gets the result of comparation of this vector with another.
     * @param vec is the other vector to compare this by.
     * @return true if a component in this vector is less than the other vector, else return false.
     */
    FORCEINLINE bool 
    operator<(const jlVector2& vec) const;
    
    /**
     * @brief Gets the result of comparation of this vector with another.
     * @param vec is the other vector to compare this by.
     * @return true if a component in this vector is greater than the other vector, else return false.
     */
    FORCEINLINE bool 
    operator>(const jlVector2& vec) const;
    
    /**
     * @brief Gets specific component of the vector.
     * @param Index the index of vector component
     * @return a const to component in index.
     */
    FORCEINLINE float 
    operator[](uint32 index) const;
    
    /**
     * @brief Gets specific component of the vector.
     * @param Index the index of vector component
     * @return a reference of component in index.
     */
    FORCEINLINE float& 
    operator[](uint32 index);
    
    /**
     * @brief Equal this vector to another
     * @param vec is the other vector to equalize.
     * @return the values of the another vector in this vector
     */
    FORCEINLINE jlVector2& 
    operator=(const jlVector2& vec);

/*****************************************************************************/
/**
 * Friends
 */
/*****************************************************************************/
    /**
     * @brief multiplicate the components of the vector for a constant
     * @param scale multply the components
     * @return the result of multiplication.
     */
    FORCEINLINE friend jlVector2 
    operator*(const float& a, const jlVector2 vec);
    
    /**
     * @brief out stream the vector
     * @return the values of the vector.
     */
    FORCEINLINE friend std::ostream& 
    operator<<(std::ostream& os, const jlVector2& vec);

/*****************************************************************************/
/**
 * Functions
 */
/*****************************************************************************/
   public:
    /**
     * @brief calculate the magnitude of vector
     * @return the magnitud of vector
     */
    FORCEINLINE float 
    magnitude() const;
    
    /**
     * @brief Calculate the square magnitude of vector
     * @return the square magnitude of vector
     */
    FORCEINLINE float 
    squareMagnitude() const;
    
    /**
     * @brief Distance between two vectors, calculate de substrac and calculate the magnitud
     * @param vec is the vector for calculate the distance
     * @return the magnitud of vector result of subtrac two vectors
     */
    FORCEINLINE float 
    distance(const jlVector2& vec) const;
    
    /**
     * @brief Normalize this vector
     */
    FORCEINLINE jlVector2& 
    normalize();
    
    /**
     * @brief Get the normalize form of this vector
     * @return a vector with the values normalized of this vector
     */
    FORCEINLINE jlVector2 
    getnormalize();
    
    /**
     * @brief dot product
     * @param vec if the vector with do dot product
     * @return the result of dot product
     */
    FORCEINLINE float 
    dot(const jlVector2& vec) const;
    
    /**
     * @brief dot product
     * @param vec if the vector with do cross product
     * @return the result of cross product
     */
    FORCEINLINE float 
    cross(const jlVector2& vec) const;

/*****************************************************************************/
/**
 * Members
 */
/*****************************************************************************/
			public:
    union
    {
      struct
      {
        /**
         * @brief Vector's x component.
         */
        float x;
        /**
         * @brief Vector's y component.
         */
        float y;
      };
      /**
       * @brief Vector's components as array.
       */
      float Vector[2];
    };
  };
  
  FORCEINLINE jlVector2 
  jlVector2::operator-() const {
    return jlVector2(-x, -y);
  }
  
  FORCEINLINE jlVector2 
  jlVector2::operator+(const jlVector2& vec) const	{
    return jlVector2(x + vec.x, y + vec.y);
  }
  
  FORCEINLINE jlVector2 
  jlVector2::operator-(const jlVector2& vec) const {
    return jlVector2(x - vec.x, y - vec.y);
  }
  
  FORCEINLINE jlVector2& 
  jlVector2::operator+=(const jlVector2& vec)	{
    x += vec.x; y += vec.y;
    return *this;
  }
  
  FORCEINLINE jlVector2& 
  jlVector2::operator-=(const jlVector2& vec)	{
     x -= vec.x; y -= vec.y;
     return *this;
  }
  
  FORCEINLINE jlVector2 
  jlVector2::operator*(const float& scale) const	{
    return jlVector2(x * scale, y * scale);
  }
		
  FORCEINLINE jlVector2 
  jlVector2::operator*(const jlVector2& vec) const	{
    return jlVector2(x * vec.x, y * vec.y);
  }
  
  FORCEINLINE jlVector2& 
  jlVector2::operator*=(const float& scale)	{
    x *= scale; y *= scale;
    return *this;
  }
  
  FORCEINLINE jlVector2& 
  jlVector2::operator*=(const jlVector2& vec)	{
    x *= vec.x; y *= vec.y;
    return *this;
  }
		
  FORCEINLINE jlVector2 
  jlVector2::operator/(const float& scale) const {
  return jlVector2(x / scale, y / scale);
  }
		
  FORCEINLINE jlVector2& 
  jlVector2::operator/=(const float& scale)	{
    x /= scale; y /= scale;
    return *this;
  }
  
  FORCEINLINE bool 
  jlVector2::operator==(const jlVector2& vec) const{
    return (x == vec.x) && (y == vec.y);
  }
  
  FORCEINLINE bool 
  jlVector2::operator!=(const jlVector2& vec) const{
    return (x != vec.x) || (y != vec.y);
  }
  
  FORCEINLINE bool 
  jlVector2::operator<(const jlVector2& vec) const	{
    if (x < vec.x) return true;
    if (y < vec.y) return true;
    return false;
  }
  
  FORCEINLINE bool 
  jlVector2::operator>(const jlVector2& vec) const	{
    if (x > vec.x) return true;
    if (y > vec.y) return true;
    return false;
  }
  
  FORCEINLINE float 
  jlVector2::operator[](uint32 index) const	{
    JL_ASSERT(index < 2);
    return (&x)[index];
  }
  
  FORCEINLINE float& 
  jlVector2::operator[](uint32 index) {
    JL_ASSERT(index < 2);
    return (&x)[index];
  }
  
  FORCEINLINE jlVector2& 
  jlVector2::operator=(const jlVector2& vec) {
    x = vec.x; y = vec.y;
    return *this;
  }
		
  FORCEINLINE jlVector2::jlVector2(const float& _x, const float& _y) : x(_x), y(_y) {}
  
  FORCEINLINE float 
  jlVector2::magnitude() const {
    return Math::sqrt(x * x + y * y);
  }
  
  FORCEINLINE float 
  jlVector2::squareMagnitude() const	{
    return (x * x + y * y);
  }
  
  FORCEINLINE float 
  jlVector2::distance(const jlVector2& vec) const {
    return Math::sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
  }
  
  FORCEINLINE jlVector2& 
  jlVector2::normalize()	{
    float mod = squareMagnitude();
    if (mod == 0){
      x = 0;
      y = 0;
    }
    else{
      float invLength = 1.0f / Math::sqrt(mod);
      x *= invLength;
      y *= invLength;
    }
    return *this;
  }
  
  FORCEINLINE jlVector2 
  jlVector2::getnormalize() {
    float sMag = squareMagnitude();
    JL_ASSERT(0.0f <= sMag);
    jlVector2 result = *this;
    
    float invLength = Math::invSqrt(sMag);
    result.x *= invLength;
    result.y *= invLength;
    return result;
  }
  
  FORCEINLINE float 
  jlVector2::dot(const jlVector2& vec) const {
    return (x * vec.x + y * vec.y);
  }
  
  FORCEINLINE float 
  jlVector2::cross(const jlVector2& vec) const {
    return ((x * vec.y) - (y * vec.x));
  }
  
  FORCEINLINE jlVector2 
  operator*(const float& a, const jlVector2 vec) {
    return jlVector2(a * vec.x, a * vec.y);
  }
  
  FORCEINLINE std::ostream& 
  operator<<(std::ostream& os, const jlVector2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
  }
}
