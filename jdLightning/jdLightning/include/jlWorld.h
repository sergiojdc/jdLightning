/*****************************************************************************/
/**
 * @file    jlWorld.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    27/10/2021
 * @brief   A basic class for a world
 *
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"

#include <thread>
#include <SFML/Graphics.hpp>
#include <jlColor.h>
#include <jlTimer.h>

#include "jlViewPlane.h"
#include "jlGOSphere.h"
#include "jlTracer.h"
#include "jlGeometriObject.h"
#include "jlRay.h"

class jlWorld {
 public:
  /**
   * @brief defaul constructor
   */
		jlWorld() {};

  /**
   * @brief defaul destructor
   */
  ~jlWorld() {};

  /**
   * @brief function to build the world
   * @param width is the window's width
   * @param height is the window's height
   */
  void
  build(const uint32 width = 200, const uint32 height = 200, bool activeThreading = true);

  /**
   * @brief function to renderScene
   */
  void
  renderScene();

  /**
   * @brief function to init and open window
   * @param width is the window's width
   * @param height is the window's height
   */
  void
  openWindow(const int width, const int height);

  /**
   * @brief function to update the image
   */
  void
  updateRender();

  /**
   * @brief function for render with threads
   */
  void 
  threadRender();
  
  /**
   * @brief function for render with threads
   */
  void 
  threadRenderFunction(uint32 threadIdx);

  /**
   * @brief function for render with threads and SimpleSampler
   */
  void 
  threadRenderFunctionSimpleSampler(uint32 threadIdx);


  /**
   * @brief function for render with threads and Random Sampler
   */
  void 
  threadRenderFunctionRandomSampler(uint32 threadIdx);

  /**
   * @brief function for render with threads and Jittered Sampler
   */
  void 
  threadRenderFunctionJitteredSampler(uint32 threadIdx);

  /**
   * @brief function for render normaly without threads
   */
  void 
  softwareRender();

  /**
   * @brief function for render normaly without threads and SimpleSampler
   */
  void 
  softwareRenderSimpleSampler();

  /**
   * @brief function for render normaly without threads and Random Sampler
   */
  void 
  softwareRenderRandomSampler();
  
  /**
   * @brief function for render normaly without threads and Jittered Sampler
   */
  void 
  softwareRenderJitteredSampler();

  /**
   * @brief function to change color to a pixel
   */
  void
  displayPixel(const int x,
               const int y,
               const jlColor& pixel_color);

  /**
   * @brief function to add object to the scene
   * @param object is the new object to add
   */
  void
  addObject(WeakSptr<jlGeometricObject> object) {
    m_sceneObjects.push_back(object.lock());
  }

  /**
   * @brief function to check hits with many objects
   * @param ray is the ray to check with
   */
  jlShadeRec 
  hitBareBonesObjects(const jlRay& ray);

  /**
   * @brief view plane
   */
  jlViewPlane m_vp;

  /**
   * @brief background color
   */
  jlColor m_backgroundColor = { 0, 0 ,0 };

  /**
   * @brief a sphere
   */
  jlSphere m_sphere;

  /**
   * @brief pointer to tracer, can be to a single sphere or multiple objects
   */
  SPtr<jlTracer> m_pTracer;

  /**
   * @brief vector with all objects in scene
   */
  Vector<SPtr<jlGeometricObject>> m_sceneObjects;

  /**
   * @brief window
   */
  sf::RenderWindow* m_window = nullptr;

  /**
   * @brief image
   * @note where the pixels are painted
   */
  sf::Image m_image;

  /**
   * @brief texture which is connected with the image
   */
  sf::Texture m_texture;

  /**
   * @brief sprtie which is setted the texture
   */
  sf::Sprite m_sprite;
  
  /**
   * @brief if is true is drawing with trheads
   */
  bool m_bThreading =  true;

  /**
   * @brief vector of thread
   */
  Vector<std::thread> m_threads;

  /**
   * @brief vector of width size for each thread
   */
  Vector<Vector<uint32>> m_IndexImageWidth;
  
  /**
   * @brief vector of thread
   */
  uint32 m_numCpus;

  /**
   * @brief members for thread debug
   */
  Vector<bool> m_threadsFinished; // to check if all finished
  jlTimer m_renderTime; // to check the time of render, not only for thread 
  bool m_allThreadFinished = false;// for no chek the time again
};