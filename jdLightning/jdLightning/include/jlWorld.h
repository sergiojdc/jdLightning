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
#include <jlRay.h>

#include "jlViewPlane.h"
#include "jlGOSphere.h"
#include "jlTracer.h"
#include "jlGeometriObject.h"
#include "jlCamera.h"
#include "jlLight.h"
#include <GL/freeglut.h>
#include <GL/GL.h>
#include <imgui.h>
#include <imgui-SFML.h>

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
  openWindow(const uint32 width, const uint32 height);

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
   * @brief function for render with threads and Jittered Sampler
   */
  void 
  threadRenderFunctionSamplerClass(uint32 threadIdx);

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
   * @brief function for render normaly without threads and Jittered Sampler
   */
  void 
  softwareRenderSamplerClass();

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
   * @brief function to add object to the scene
   * @param object is the new object to add
   */
  void
  addLight(WeakSptr<jlLight> light) {
    m_sceneLights.push_back(light.lock());
  }

  /**
   * @brief function to check hits with many objects
   * @param ray is the ray to check with
   */
  jlShadeRec 
  hitBareBonesObjects(const jlRay& ray);

  /**
   * @brief function to check hits with many objects with Materials
   */
  jlShadeRec
  hitObjects(const jlRay& ray);

  /**
   * @brief function clamp the color to the max value in r, g or b
   * @return the result color
   */
  jlColor
  maxToOne(const jlColor& color) const;

  /**
   * @brief function clamp the color to 1 if r, g or b are major than 1
   * @return the result color
   */
  jlColor
  clampToColor(const jlColor& color) const;

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
   * @brief default camera to render
   */
  SPtr<jlCamera> m_pCamera;
  
  /**
   * @brief ambient light
   */
  SPtr<jlLight> m_pAmbientLight = nullptr;
  SPtr<jlLight> m_pPointLight = nullptr;

  /**
   * @brief vector with lights in scene
   */
  Vector<SPtr<jlLight>> m_sceneLights;
  
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
  Vector<bool> m_threadsFinishedFirst; // to check if all finished
  jlTimer m_renderTime; // to check the time of render, not only for thread 
  bool m_allThreadFinished = false;// for no chek the time again

  /**
   * @brief bool to let the thread run indefini
   */
  bool run = true;
  
//////////////////////////////////////////////////////////////////////////////////////////////
//   IMGUI FUNCTIONS
//   FOR INTERFACE (MAYBE CHANGE THE CPP OF THEM)
//////////////////////////////////////////////////////////////////////////////////////////////

  /**
   * @brief temporal function to modify a point light (can use for future)
   */
  void 
  modifyPointlight();

  /**
   * @brief function to modify the ambient light
   */
  void
  imguiAmbientLight();

  /**
   * @brief function to see objects in the scene (they don't have a name, may be will give them one)
   */
  void
  imguiShowObjects();

  /**
   * @brief function to show Properties of selected object
   */
  void
  imguiShowObjectProperties();

  /**
   * @brief function to show Properties of a sphere
   */
  void
  imguiShowSphereProperties();

  /**
   * @brief function to show Properties of a Box
   */
  void
  imguiShowBoxProperties();

  /**
   * @brief function to show Properties of a Plane
   */
  void
  imguiShowPlaneProperties();

  /**
   * @brief function to show Properties of a Cylinder
   */
  void
  imguiShowCylindreProperties();

  /**
   * @brief function to show Properties of materials
   */
  void
  imguiShowMaterialProperties();

  /**
   * @brief function to show Properties of a matte material
   */
  void
  imguiShowMatteMaterialProperties();

  /**
   * @brief function to show Properties of a matte material
   */
  void
  imguiShowPhongMaterialProperties();

  /**
   * @brief function to show Properties of a matte material
   */
  void
  imguiShowPlasticMaterialProperties();

  /**
   * @brief function to show lights in scene
   */
  void
  imguiShowLights();

  /**
   * @brief function to show selected light Properties
   */
  void
  imguiShowLightProperties();

  /**
   * @brief function to show light point Properties
   */
  void
  imguiShowPointLightProperties();

  /**
   * @brief function to show light point Properties
   */
  void
  imguiShowCameraProperties();

  /**
   * @brief vector with all objects in scene
   */
  SPtr<jlGeometricObject> m_selectedObject;

  /**
   * @brief vector with all objects in scene
   */
  SPtr<jlLight> m_selectedLight;

};