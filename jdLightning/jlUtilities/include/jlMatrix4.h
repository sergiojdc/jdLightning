/*****************************************************************************/
/**
 * @file    jlMatrix4.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   Structure for float matrix 4x4 row mallet.
 *
 * Structure for float matrix 4x4 row mallet.
 *
 * @bug     No known bugs.
 */
/*****************************************************************************/
#pragma once

#include "jlPlatformDefines.h"
#include "jlVector4.h"
#include "jlMatrix3.h"
#include "jlRadian.h"

namespace jlUtilitiesSDK
{
  class JL_UTILITY_EXPORT jlMatrix4
  {
/*****************************************************************************/
/**
 * Constructor
 */
/*****************************************************************************/
   public:
    /**
     * @brief Default constructor with a identity matrix.
     */
    jlMatrix4();
    
    /**
     * @brief Default constructor with a array.
     * @param src is a array with the data
     */
    jlMatrix4(const float src[16]);
    
    /**
     * @brief Default constructor with floats.
     */
    jlMatrix4(const float& m0 ,  const float& m1,  const float& m2 ,  
              const float& m3 ,  const float& m4,  const float& m5 ,  
              const float& m6 ,  const float& m7,  const float& m8 ,  
              const float& m9 ,  const float& m10, const float& m11,
              const float& m12, const float& m13, const float& m14, 
              const float& m15);
    
    /**
     * @brief Default constructor with 4 jdvector4.
     */
    jlMatrix4(const jlVector4& m0123,
              const jlVector4& m4567,
              const jlVector4& m891011,
              const jlVector4& m12131415);

    /**
     * @brief Default constructor with jdmatrix3.
     */
    jlMatrix4(const jlMatrix3& mat3);

/*****************************************************************************/
/**
 * Operators
 */
/*****************************************************************************/

    /**
     * @brief Positive operator
     * @return A new matrix positive of this matrix
     */
    jlMatrix4
    operator+() const;
    
    /**
     * @brief Negative operator
     * @return A new matrix negative of this matrix
     */
    jlMatrix4
    operator-() const;
    
    /**
     * @brief add two matrix
     * @param mat is the other matrix to add
     * @return the addition of this vector with other
     */
    jlMatrix4 
    operator+(const jlMatrix4& mat) const;
    
    /**
     * @brief substraction two matrix
     * @param mat is the other matrix to subtrac
     * @return the substraction of this vector with other
     */
    jlMatrix4 
    operator-(const jlMatrix4& mat) const;
    
    /**
     * @brief add this matrix with other
     * @param mat is the other matrix to add
     * @return the addition of this matrix with other in this matrix
     */
    jlMatrix4& 
    operator+=(const jlMatrix4& mat);     
    
    /**
     * @brief substraction this matrix with an other matrix
     * @param mat is the other matrix to subtrac
     * @return the substraction of this matrix with other in this matrix
     */
    jlMatrix4& 
    operator-=(const jlMatrix4& mat);     
    
    /**
     * @brief multiply this matrix with a vector4
     * @param vec is the vector to multiply this matirx
     * @return the multiplication of this matrix with a vector4
     */
    jlVector4
    operator*(const jlVector4& vec) const;
    
    /**
     * @brief multiply this matrix with a vector3
     * @param vec is the vector to multiply this matirx
     * @return the multiplication of this matrix with a vector3
     */
    jlVector3 
    operator*(const jlVector3& vec) const;
    
    /**
     * @brief multiply this matrix with a vector3
     * @param mat is the mat to multiply this matirx
     * @return the multiplication of this matrix with oyher matrix
     */
    jlMatrix4
    operator*(const jlMatrix4& mat) const;
    
    /**
     * @brief multiply this matirx with an other matrix
     * @param mat is the matrix to multiply this matrix
     * @return the multiplication of this matrix with a matrix in this matrix
     */
    jlMatrix4& 
    operator*=(const jlMatrix4& mat);   
    
    /**
     * @brief compare this matrix with an other matrix.
     * @param mat is matrix what to compare vector by.
     * @return true if all components are equal
     */
    bool 
    operator==(const jlMatrix4& mat) const; 
    
    /**
     * @brief compare this matrix with an other matrix.
     * @param mat is matrix what to compare matrix by.
     * @return true if one component is diferent
     */
    bool 
    operator!=(const jlMatrix4& mat) const; 
    
    /**
     * @brief get matrix value on index
     * @param index index of value.
     * @return a const of the value on index
     * @note if index less 0 return value on index 0, if index greater 15 
     *       return value on index 15
     */
    float
    operator[](uint32 index) const;            
    
    /**
     * @brief get matrix value on index
     * @param index index of value.
     * @return the value on index
     * @note if index less 0 return value on index 0, if index greater 15
     *       return value on index 15
     */
    float& 
    operator[](uint32 index);                  

/*****************************************************************************/
/**
 * Friends
 */
/*****************************************************************************/

    /**
     * @brief subtrac two matrix
     * @param mat is the matrix with which to subtract
     * @return the subtraction
     */
    friend jlMatrix4 
    operator-(const jlMatrix4& mat);        
    
    friend std::ostream& 
    operator<<(std::ostream& os, const jlMatrix4& m);

/*****************************************************************************/
/**
 * Functions
 */
/*****************************************************************************/

    /**
     * @brief get the matrix´s data
     * @return the matrix's data
     */
    jlMatrix4 
    get() const;
    
    /**
     * @brief get the transpose of this matrix
     * @return a const of this matrix transposed
     */
    jlMatrix4 
    getTranspose();   
    
    /**
     * @brief get the matrix´s data
     * @return the matrix's data
     */
    float
    getDeterminant();
    
    /**
     * @brief transform this matrix to matrix identity
     * @return this matrix as a identity matrix
     */
    jlMatrix4& 
    identity();
    
    /**
     * @brief transform this matrix to its transpose
     * @return this matrix as a its traspose form
     */
    jlMatrix4& 
    transpose();                           
    
    /**
     * @brief transform this matrix to its invert
     * @return this matrix as a its invert form
     */
    jlMatrix4&
    invert();    
    
    /**
     * @brief traslate this matrix on x, y and z cordinates
     * @param x value to traslate on x cordinate
     * @param y value to traslate on y cordinate
     * @param z value to traslate on z cordinate
     * @return this matrix traslated
     */
    jlMatrix4&
    translate(float x, float y, float z);
    
    /**
     * @brief traslate this matrix on x, y and z cordinates
     * @param vec value to traslate on x, y,z cordinate
     * @return this matrix traslated
     */
    jlMatrix4&
    translate(const jlVector3& vec);
    
    /**
     * @brief rotate this matrix
     * @param angle angle on radians
     * @param axis is the direction to rotate
     * @return this matrix rotated
     */
    jlMatrix4&
    rotate(const jlRadian& angleRadian, const jlVector3& axis);
    
    /**
     * @brief rotate this matrix
     * @param angle angle on radians
     * @param x is the direction on x to rotate
     * @param y is the direction on y to rotate
     * @param z is the direction on z to rotate
     * @return this matrix rotated
     */
    jlMatrix4&
    rotate(const jlRadian& angleRadian, float x, float y, float z);
    
    /**
     * @brief rotate this matrix on x axis
     * @param angle angle on radians
     * @return this matrix rotated on axis
     * @note this * matrotX
     */
    jlMatrix4&
    rotateX(const jlRadian& angleRadian);
    
    /**
     * @brief rotate this matrix on x axis
     * @param angle angle on radians
     * @return this matrix rotated on x axis
     * @note matrotX * this
     */
    jlMatrix4&
    rotateXstayPos(const jlRadian& angleRadian);
    
    /**
     * @brief rotate this matrix on y axis
     * @param angle angle on radians
     * @return this matrix rotated on y axis
     * @note this * matrotY
     */
    jlMatrix4&
    rotateY(const jlRadian& angleRadian);
    
    /**
     * @brief rotate this matrix on y axis
     * @param angle angle on radians
     * @return this matrix rotated on y axis
     * @note matrotY * this
     */
    jlMatrix4&
    rotateYstayPos(const jlRadian& angleRadian);
    
    /**
     * @brief rotate this matrix on Z axis
     * @param angle angle on radians
     * @return this matrix rotated on Z axis
     * @note this * matrotX
     */
    jlMatrix4&
    rotateZ(const jlRadian& angleRadian);
    
    /**
     * @brief rotate this matrix on z axis
     * @param angle angle on radians
     * @return this matrix rotated on z axis
     * @note matrotZ * this
     */
    jlMatrix4&
    rotateZstayPos(const jlRadian& angleRadian);
    
    /**
     * @brief scale this matrix
     * @param scale is the value to scale this matrix
     * @return this matrix scaled
     */
    jlMatrix4&
    scale(float scale);
    
    /**
     * @brief scale this matrix
     * @param sx is the value to scale on x axis this matrix
     * @param sy is the value to scale on y axis this matrix
     * @param sz is the value to scale on z axis this matrix
     * @return this matrix scaled
     */
    jlMatrix4&
    scale(float sx, float sy, float sz);

    /**
     * @brief scale this matrix
     * @param sx is the value to scale on x axis this matrix
     * @param sy is the value to scale on y axis this matrix
     * @param sz is the value to scale on z axis this matrix
     * @return this matrix scaled
     */
    jlMatrix4&
    scale(const jlVector3& vec);

/*****************************************************************************/
/**
 * Members
 */
/*****************************************************************************/
   public:
    /**
     * @brief union of diferents estructs
     */
	 		union	{
      struct	{
        /**
         * @brief array of 16 floats
         */
        float m[16];
      };
      struct		{
        /**
         * @brief 16 floats
         */
        float m_00, m_01, m_02, m_03,
        		    m_10, m_11, m_12, m_13,
        		    m_20, m_21, m_22, m_23,
        		    m_30, m_31, m_32, m_33;
      };
      /**
       * @brief 4 arrays with 4 arrays of floats
       */
      float M[4][4];
    };                                   
  };
/*****************************************************************************/
/**
 * Extern Funtions
 */
/*****************************************************************************/
  /**
   * @brief Transpose a matrix
   * @param mat is the matrix to traspose
   * @return a new matrix with the data of the param matrix transpose
   */
  JL_UTILITY_EXPORT jlMatrix4
  transposeMatrix(const jlMatrix4& mat);
  
  /**
   * @brief invert a matrix
   * @param mat is the matrix to invert
   * @return a new matrix with the data of the param matrix invert
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  invertMatrix(const jlMatrix4& mat);
  
  /**
   * @brief get identity matrix
   * @return a new matrix with the data of the param matrix invert
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  identityMatrix();
  
  /**
   * @brief get translate matrix
   * @param x is for x axis
   * @param y is for y axis
   * @param z is for z axis
   * @return a matrix traslalate
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  matrix4Translate(const float& x, const float& y, const float& z);
  
  /**
   * @brief get translate matrix
   * @param vec is for x, y, z axis
   * @return a matrix traslalate
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  matrix4Translate(const jlVector3& vec);					
  
  /**
   * @brief get a rotation matrix
   * @param angle angle on radians
   * @param vec is the axis to rotate
   * @return a rotation matrix
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  matrix4Rotate(const jlRadian& angleRadian, const jlVector3& axis);
  
  /**
   * @brief get a rotation matrix
   * @param angle angle on radians
   * @param x is the x axis to rotate
   * @param y is the y axis to rotate
   * @param z is the z axis to rotate
   * @return a rotation matrix
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  matrix4Rotate(const jlRadian& angleRadian, const float& x, const float& y, const float& z);
  
  /**
   * @brief get a rotation matrix on x axis
   * @param angle angle on radians
   * @return a rotation matrix on x axis
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  matrix4RotateX(const jlRadian& angleRadian);
  
  /**
   * @brief get a rotation matrix on y axis
   * @param angle angle on radians
   * @return a rotation matrix on y axis
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  matrix4RotateY(const jlRadian& angleRadian);
  
  /**
   * @brief get a rotation matrix on y axis
   * @param angle angle on radians
   * @return a rotation matrix on y axis
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  matrix4RotateZ(const jlRadian& angleRadian);
  
  /**
   * @brief get a scale matrix
   * @param scale is the value to scale the matrix
   * @return a scale matrix
   */
  JL_UTILITY_EXPORT extern jlMatrix4
  matrix4Scale(const float& scale);
  
  /**
   * @brief scale a matrix
   * @param sx is the value to scale on x axis the matrix
   * @param sy is the value to scale on y axis the matrix
   * @param sz is the value to scale on z axis the matrix
   * @return a scale a matrix
   */
  JL_UTILITY_EXPORT extern  jlMatrix4
  matrix4Scale(const float& sx, const float& sy, const float& sz);
  
  /**
   * @brief generate a projection perspective matrix
   * @param fovAngle is the angle of view
   * @param width is the width of the view
   * @param height is the height of the view
   * @param _near is how close you can see
   * @param _far is how far can you see
   * @return a projection perspective matrix
   */
  JL_UTILITY_EXPORT extern  jlMatrix4
  createProjectionPerspectiveMatrix(const float& fovAngle,
                                    const float& width, 
                                    const float& height,
                                    const float& _near, 
                                    const float& _far);
  
  /**
   * @brief generate a projection perspective matrix
   * @param fovAngle is the angle of view
   * @param aspectRatio  is the ratio of its width to its height.
   * @param _near is how close you can see
   * @param _far is how far can you see
   * @return a projection perspective matrix
   * @note aspecRatio = width / height
   */
  JL_UTILITY_EXPORT extern  jlMatrix4
  createProjectionPerspectiveMatrix(const float& fovAngle,
                                    const float& aspectRatio, 
                                    const float& _near, 
                                    const float& _far);
  
  /**
   * @brief create projection orthographic matrix 
   * @param botton is max distance detected on botton
   * @param top is max distance detected on top
   * @param left is max distance detected on left
   * @param right is max distance detected on right
   * @param _near is max distance detected on back
   * @param _far is max distance detected on front
   * @return a projection orthographic matrix 
   */
  JL_UTILITY_EXPORT extern  jlMatrix4
  createProjectionOrthographicMatrix(const float& botton, 
                                     const float& top, 
                                     const float& left,
                                     const float& right,
                                     const float& _near, 
                                     const float& _far);

  JL_UTILITY_EXPORT extern  jlMatrix4
  createProjectionOrthographicMatrixLH(const float& width, 
                                       const float& height, 
                                       const float& _near, 
                                       const float& _far);
  
  /**
   * @brief create view matrix on Left Hand
   * @param _eye is the position of view matrix
   * @param _at is the matrix look at 
   * @param _up is the relative Up of view
   * @return a view matrix on Left Hand
   */
  JL_UTILITY_EXPORT extern  jlMatrix4
  createViewMatrix(const jlVector4& _eye, const jlVector4& _at, const jlVector4& _up);
}
