/*****************************************************************************/
/**
	* @file    jlCPinhole.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    1/11/2021
	* @brief   A class for pinhole camera
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlCamera.h"
#include <jlRay.h>

class jlCPinhole : public jlCamera {
 public:
		/**
			* @brief default constructor
			*/
		jlCPinhole() = default;

		/**
			* @brief default destructor
			*/
		~jlCPinhole() {};

		/**
   * @brief function to get the ray direction with a point
   * @param p is the point
   * @return the ray's direction
   */
  jlVector3
  rayDirection(const jlVector3& p);

  /**
   * @brief function to render the scene
   */
  virtual void
  renderScene(jlWorld* world) override;

  /**
   * @brief function to render the scene
   */
  virtual void
  renderSceneThreading(jlWorld* world) override;

  /**
   * @brief function to render the scene
   */
  virtual void
  renderSceneSoftware(jlWorld* world) override;

  /**
   * @brief function to render the scene
   */
  virtual void
  renderThread(jlWorld* world, int threadIdx);

  jlVector3
  classSamplerRender(int x, int y, jlWorld* world, jlRay& ray) {
    UNREFERENCED_PARAMETER(x);
    UNREFERENCED_PARAMETER(y);
    UNREFERENCED_PARAMETER(world);
    UNREFERENCED_PARAMETER(ray);
  };

  /**
   * @brief the view-plane distance
   */
  float m_viewDistance;

  /**
   * @brief the zoom factor
   */
  float m_zoom = 1;

};
