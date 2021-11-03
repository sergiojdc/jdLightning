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
    m_w = m_eye - m_lookAt; //front
    m_w.normalize();
    m_u = m_up.cross(m_w);//real up
    m_u.normalize();
    m_v = m_w.cross(m_u); //right
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

};
