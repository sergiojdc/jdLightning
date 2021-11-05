/*****************************************************************************/
/**
	* @file    jlCamera.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    1/11/2021
	* @brief   A virtual class for any camera
	*
	*
	* @bug	    No known bugs.
	*/
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlVector3.h"

class jlWorld;

class jlCamera {
 public:
  /**
   * @brief default constructor
   */
		jlCamera() = default;

  /**
   * @brief default destructor
   */
  ~jlCamera() {};

  /**
   * @brief function to calculate the vector u, v and w
   */
  void
  computeUVW() {
    //--------if change the front, chage too in functions that require it in each camera---------
    //-----------------------info in pinhole getDirection function-----------------------
    //m_w = m_eye - m_lookAt; // -front 
    m_w = m_lookAt - m_eye; //front
    m_w.normalize();
    m_u = m_up.cross(m_w);//right
    m_u.normalize();
    m_v = m_w.cross(m_u); //real up
    m_v.normalize();
  };

  void
  moveForward() {
    m_eye += m_w * m_moveSpeed;
  };

  void
  moveBackward() {
    m_eye -= m_w * m_moveSpeed;
  };
  
  void
  moveRight() {
    m_eye += m_u * m_moveSpeed;
  };

  void
  moveLeft() {
    m_eye -= m_u * m_moveSpeed;
  };

  void
  moveUp() {
    m_eye += m_v * m_moveSpeed;
  };

  void
  moveDown() {
    m_eye -= m_v * m_moveSpeed;
  };

  void
  rotateRight() {
    //m_eye += m_u * m_moveSpeed;
    auto dir = m_u - m_w;
    m_w += dir * m_rotationPercen;
    m_w.normalize();
    m_u = m_up.cross(m_w);//right
    m_u.y = 0;
    m_u.normalize();
    m_v = m_w.cross(m_u); //real up
    m_v.normalize();
  };

  void
  rotateLeft() {
    //m_eye += m_u * m_moveSpeed;
    auto dir = m_u - m_w;
    m_w -= dir * m_rotationPercen;
    m_w.normalize();
    m_u = m_up.cross(m_w);//right
    m_u.y = 0;
    m_u.normalize();
    m_v = m_w.cross(m_u); //real up
    m_v.normalize();
  };

  void
  rotateUp() {
    //m_eye += m_u * m_moveSpeed;
    auto dir = m_v - m_w;
    m_w += dir * m_rotationPercen;
    m_w.normalize();
    m_u = m_v.cross(m_w);//right
    m_u.y = 0;
    m_u.normalize();
    m_v = m_w.cross(m_u); //real up
    m_v.normalize();
  };

  void
  rotateDown() {
    auto dir = m_v - m_w;
    m_w -= dir * m_rotationPercen;
    m_w.normalize();
    m_u = m_v.cross(m_w);//right
    m_u.y = 0;
    m_u.normalize();
    m_v = m_w.cross(m_u); //real up
    m_v.normalize();
  };

  /**
   * @brief function to render the scene
   */
  virtual void
  renderScene(jlWorld* world) {
    UNREFERENCED_PARAMETER(world);
  };

  /**
   * @brief function to render the scene
   */
  virtual void
  renderSceneThreading(jlWorld* world) {
    UNREFERENCED_PARAMETER(world);
  };

  /**
   * @brief function to render the scene
   */
  virtual void
  renderSceneSoftware(jlWorld* world) {
    UNREFERENCED_PARAMETER(world);
  };

  /**
   * @brief the camera's position
   */
  jlVector3 m_eye;

  /**
   * @brief the camera's look at
   */
  jlVector3 m_lookAt;

  /**
   * @brief the camera's relative up vector
   */
  jlVector3 m_up;

  /**
   * @brief the vector to simulate a perspective viewing
   * @notes w is the front vector, u = right vector and v = realUp vector
   */
  jlVector3 m_u, m_v, m_w;

  /**
   * @brief the expesure time
   */
  float m_exposureTime = 1.0f;

  /**
   * @brief the move speed 
   */
  float m_moveSpeed = 5.0f;

  /**
   * @brief 1 = 100 = 90degree
   */
  float m_rotationPercen = 0.050f;

};
