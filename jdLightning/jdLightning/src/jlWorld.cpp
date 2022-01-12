#include "jlWorld.h"
#include <jlColor.h>
#include <jlVector4.h>
#include <jlTimer.h>
#include <jlRandom.h>
//Tracers
#include "jlTSingleSphere.h"
#include "jlTMultipleObjects.h"
#include "jlTRayCast.h"
//Geometri objects
#include "jlGOPlane.h"
#include "jlGOBox.h"
#include "jlGOCylinder.h"
#include "jlGOTriangle.h"
//Samplers
#include "jlSJittered.h"
//Cameras
#include "jlCPinhole.h"
//Lights
#include "jlLAmbient.h"
#include "jlPointLight.h"
#include "jlLAmbientOccluder.h"
//Materials
#include "jlMMatte.h"
#include "jlMPhong.h"
#include "jlMPlastic.h"

void 
jlWorld::build(const uint32 width, const uint32 height, bool activeThreading) {
  m_bThreading = activeThreading;
//////////////////////////////////////////////////////////////////////////////////////////////
// Prepare threads
//////////////////////////////////////////////////////////////////////////////////////////////
  jlTimer time;
  if (m_bThreading) {
    m_numCpus = (uint32)std::thread::hardware_concurrency();
    std::cout << "Launching " << m_numCpus << " threads\n";
    m_threads.resize(m_numCpus);
    m_IndexImageWidth.resize(m_numCpus);
    m_threadsFinished.resize(m_numCpus);
    m_threadsFinishedFirst.resize(m_numCpus);
    uint32 widthPerCpus = width / m_numCpus; // get number of pixel on widht per cpu
    uint32 CpusWithExtra = width % m_numCpus; // check if have decimal to repart the extra width

    uint32 currentWidthIdx = 0;
    //uint32 currentHeightIdx = 0;
    //Prepare data
    for (uint32 i = 0; i < m_numCpus; i++) {
      //Get width pixels per cpu
      uint32 numIndexWidth = widthPerCpus;
      m_threadsFinished[i] = false;
      m_threadsFinishedFirst[i] = false;
      if (i < CpusWithExtra) {
        numIndexWidth++;
      }
      m_IndexImageWidth[i].resize(numIndexWidth);
      for (uint32 idx = 0; idx < numIndexWidth; ++idx) {
        m_IndexImageWidth[i][idx] = currentWidthIdx++;
      }
    }

    std::cout << "Milliseconds Thread creaction" << time.getMilliseconds() << std::endl;
  }
  else {
    m_numCpus = 1;
    m_threads.resize(1);
    m_threadsFinished.resize(1);
    m_threadsFinishedFirst.resize(1);
  }

//////////////////////////////////////////////////////////////////////////////////////////////
// create list of things
//////////////////////////////////////////////////////////////////////////////////////////////
  //materials
  m_MaterialsListString.resize(3);
  String name = "Matte";
  char* cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_MaterialsListString[0] = cname;
  name = "Phong";
  cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_MaterialsListString[1] = cname;
  name = "Plastic";
  cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_MaterialsListString[2] = cname;
  //objects
  name = "Plane";
  cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_geometriObjectsListString.push_back(cname);
  name = "Sphere";
  cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_geometriObjectsListString.push_back(cname);
  name = "Box";
  cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_geometriObjectsListString.push_back(cname);
  name = "Cylinder";
  cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_geometriObjectsListString.push_back(cname);
  name = "Triangle";
  cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_geometriObjectsListString.push_back(cname);

  name = "Simple AmbientLight";
  cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_ambientLightsListString.push_back(cname);
  name = "AmbientOccluder";
  cname = new char[name.size() + 1];
  strcpy(cname, name.c_str());
  m_ambientLightsListString.push_back(cname);
//////////////////////////////////////////////////////////////////////////////////////////////
// Prepare view plane and samples
//////////////////////////////////////////////////////////////////////////////////////////////
  SPtr<jlSJittered> sampler(new jlSJittered(16));
  //SPtr<jlSRegular> sampler(new jlSRegular(16));
  m_vp = jlViewPlane(width, height, 1.0f, 1.0f, 255, sampler);
  sampler->setNumSets(width * height);
  time.reset();
  //do it// try to change generate samples and shuffledIndices with threads
  std::cout << "generating samples" << std::endl;
  sampler->generateSamples();
  std::cout << "samples were generated in " << time.getSeconds() << " seconds" << std::endl;
  time.reset();
  std::cout << "shuffling indices"  << std::endl;
  sampler->setupShuffledIndices();
  std::cout << "indices shuffled in " << time.getSeconds() << " seconds" << std::endl;
  time.reset();
  std::cout << "mapping unit disk"  << std::endl;
  sampler->mapSamplerToUnitDisk();
  std::cout << "unit disk mapped " << time.getSeconds() << " seconds" << std::endl;

  m_vp.m_bShowOutOfGamut = true;
//////////////////////////////////////////////////////////////////////////////////////////////
// Set background color
//////////////////////////////////////////////////////////////////////////////////////////////
  //m_vp.m_numSamples = 16;
  m_backgroundColor = jlColor::Black();


//////////////////////////////////////////////////////////////////////////////////////////////
// set Tracer
//////////////////////////////////////////////////////////////////////////////////////////////
  //m_pTracer.reset(new jlTSingleSphere(this));
  //m_pTracer.reset(new jlTMultipleObjects(this));
  m_pTracer.reset(new jlTRayCast(this));

//////////////////////////////////////////////////////////////////////////////////////////////
// Create prefabs
//////////////////////////////////////////////////////////////////////////////////////////////

//BRDF
  //Lambertian
  m_pDefaultBRDFLambertian.reset(new jlBRDFLambertian({0.2f, 1.0f, 0.0f}, 0.5f));
  //Glossy specular
  m_pDefaultBRDFGlossySpecular.reset(new jlBRDFGlossySpecular({ 0.2f, 1.0f, 0.0f }, 0.5f));
//Materials  
  //Matte material
  m_pDefaultMMatte.reset(new jlMMatte);
  m_pDefaultMMatte->setKa(0.25f);
  m_pDefaultMMatte->setKd(0.65f);
  m_pDefaultMMatte->setCd({ 1, 1, 0 });
  //Phong material
  m_pDefaultMPhong.reset(new jlMPhong);
  m_pDefaultMPhong->setCd({ 0, 1, 0 });
  m_pDefaultMPhong->setKa(0.25f);
  m_pDefaultMPhong->setKd(0.5f);
  m_pDefaultMPhong->setKs(0.5f);
  m_pDefaultMPhong->setSpecularExponent(1);
  //Plastic material
  m_pDefaultMPlastic.reset(new jlMPlastic);
  m_pDefaultMPlastic->m_ambientBRDF.reset(new jlBRDFLambertian(*m_pDefaultBRDFLambertian));
  m_pDefaultMPlastic->m_diffuseBRDF.reset(new jlBRDFLambertian(*m_pDefaultBRDFLambertian));
  m_pDefaultMPlastic->m_specularBRDF.reset(new jlBRDFLambertian(*m_pDefaultBRDFLambertian));
//Lights
  //Ambient light
  m_pDefaultLAmbient.reset(new jlLAmbient(1, { 1, 1, 1 }));
  //Point light
  m_pDefaultPointLight.reset(new jlPointLight);
  m_pDefaultPointLight->setPosition({ 0, 0, 0 });
  m_pDefaultPointLight->setRadianceScalingFactor(3.0f);
  
  m_pDefaultLAmbientOccluder.reset(new jlLAmbientOccluder(1.0f, { 1,1,1 }));
  m_pDefaultLAmbientOccluder->setMinAmount({ 0,0,0 });
  m_pDefaultLAmbientOccluder->setSampler(sampler);
//Geometri Objects
  //Sphere
  m_pDefaultSphere.reset(new jlSphere);
  m_pDefaultSphere->m_position = { 0, 0, 0 };
  m_pDefaultSphere->m_radius = 50.0f;
  m_pDefaultSphere->m_pMaterial.reset(new jlMMatte(*m_pDefaultMMatte));
  //Plane
  m_pDefaultPlane.reset(new jlPlane({ 0,0,-1000 }, { 0,0,1 }));
  m_pDefaultPlane->m_pMaterial.reset(new jlMMatte(*m_pDefaultMMatte));
  //Box
  m_pDefaultBox.reset(new jlBox({ -25,-25,-25 }, { 25,25,25 }, { 0,0,0 }, { 0,-25,0 }));
  m_pDefaultBox->m_pMaterial.reset(new jlMMatte(*m_pDefaultMMatte));
  //Cylinder
  m_pDefaultCylinder.reset(new jlCylinder(50, 100, { 0,0,0 }));
  m_pDefaultCylinder->m_pMaterial.reset(new jlMMatte(*m_pDefaultMMatte));
  //Triangle
  m_pDefaultTriangle.reset(new jlTriangle({ 0,0,0 }, { 0,100,0 }, { 100,0,0 }));
  m_pDefaultTriangle->m_pMaterial.reset(new jlMMatte(*m_pDefaultMMatte));
//////////////////////////////////////////////////////////////////////////////////////////////
// Create and add objects to scene wiht their materials
//////////////////////////////////////////////////////////////////////////////////////////////
  m_sphere = jlSphere({0,0,0}, 40.0f);

  SPtr<jlTriangle> newtriangle(new jlTriangle({ 0,0,0 }, { 0,100,0 }, { 100,0,0 }));
  //newSphere->m_pMaterial.reset(new jlMMatte(*m_pDefaultMMatte));
  newtriangle->m_pMaterial.reset(new jlMPhong(*m_pDefaultMPhong));
  addObject(newtriangle);
  newtriangle.reset(new jlTriangle({ 100,0,0 }, { 0,100,0 }, { 0,0,0 }));
  //newSphere->m_pMaterial.reset(new jlMMatte(*m_pDefaultMMatte));
  newtriangle->m_pMaterial.reset(new jlMPhong(*m_pDefaultMPhong));
  addObject(newtriangle);
  
  //SPtr<jlSphere> newSphere(new jlSphere(*m_pDefaultSphere));
  //newSphere->m_position = { 90, -25, 0 };
  //newSphere->m_radius = 80.0f;
  ////newSphere->m_pMaterial.reset(new jlMMatte(*m_pDefaultMMatte));
  //newSphere->m_pMaterial.reset(new jlMPhong(*m_pDefaultMPhong));
  //addObject(newSphere);
  //
  //newSphere.reset(new jlSphere(*m_pDefaultSphere));
  //newSphere->m_position = { -90, -25, 0 };
  //newSphere->m_radius = 80.0f;
  //newSphere->m_pMaterial.reset(new jlMPhong(*m_pDefaultMPhong));
  //addObject(newSphere);
  //
  //SPtr<jlBox> newbox(new jlBox(*m_pDefaultBox));
  //newbox->m_pMaterial.reset(new jlMPhong(*m_pDefaultMPhong));
  //addObject(newbox);
  //newbox.reset(new jlBox(*m_pDefaultBox));
  //newbox->m_pMaterial.reset(new jlMPhong(*m_pDefaultMPhong));
  //addObject(newbox);
  //
  //SPtr<jlCylinder> newcylinder(new jlCylinder(*m_pDefaultCylinder));
  //newcylinder->m_pMaterial.reset(new jlMPhong(*m_pDefaultMPhong));
  //addObject(newcylinder);
  //newcylinder.reset(new jlCylinder(*m_pDefaultCylinder));
  //newcylinder->m_pMaterial.reset(new jlMPhong(*m_pDefaultMPhong));
  //addObject(newcylinder);
  //
  //SPtr<jlMMatte> matte(new jlMMatte(*m_pDefaultMMatte));
  //matte->setKa(0.25f);
  //matte->setKd(0.65f);
  //matte->setCd({ 0.5f, 0.5f, 0 });
  //SPtr<jlPlane> newPlane(new jlPlane({ 0,0,-1000 }, { 0,0,1 }));
  //newPlane->m_pMaterial = matte;
  //addObject(newPlane);
  //
  //matte.reset(new jlMMatte(*m_pDefaultMMatte));
  //matte->setKa(0.25f);
  //matte->setKd(0.65f);
  //matte->setCd({ 0.5f, 0.0f, 0.5f });
  //newPlane.reset(new jlPlane({ 0,-200,0 }, { 0, 1, 0 }));
  //newPlane->m_pMaterial = matte;
  //addObject(newPlane);

//////////////////////////////////////////////////////////////////////////////////////////////
// Create and add Lights to scene
//////////////////////////////////////////////////////////////////////////////////////////////

  //m_pAmbientLight.reset(new jlLAmbient(1, {1, 1, 1}));
  m_pAmbientLight = m_pDefaultLAmbientOccluder;

  SPtr<jlPointLight> pointLight(new jlPointLight);
  pointLight->setPosition({0, 50, 500});
  pointLight->setRadianceScalingFactor(3.0f);
  addLight(pointLight);


//////////////////////////////////////////////////////////////////////////////////////////////
// Configure and set camera
//////////////////////////////////////////////////////////////////////////////////////////////
  jlCPinhole* cpinhole = new jlCPinhole;
  cpinhole->m_viewDistance = 850;
  cpinhole->m_zoom = 1;

  m_pCamera.reset(cpinhole);
  m_pCamera->m_eye = { 0, 0, 400 };
  m_pCamera->m_lookAt = { 0,0,0 };
  m_pCamera->m_up = { 0,1,0 };
  m_pCamera->m_exposureTime = 1;
  m_pCamera->computeUVW();


//////////////////////////////////////////////////////////////////////////////////////////////
// open window and update the image
//////////////////////////////////////////////////////////////////////////////////////////////
  openWindow(width, height);
  updateRender();
}

void jlWorld::renderScene() {
  m_window->setFramerateLimit(30);
  while (m_window->isOpen())
  {
    if (!m_allThreadFinished) {
      m_allThreadFinished = true;
      for (uint32 i = 0; i < m_numCpus; i++) {
        if (!m_threadsFinishedFirst[i]) {
          m_allThreadFinished = false;
          break;
        }
      }
      if (m_allThreadFinished) {
        std::cout << "Seconds" << m_renderTime.getSeconds() << std::endl;
      }
    }
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    sf::Clock deltaClock;
    while (m_window->pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) {
        m_window->close();
        run = false;
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
          m_pCamera->moveForward();
        }
        if (event.key.code == sf::Keyboard::S) {
          m_pCamera->moveBackward();
        }
        if (event.key.code == sf::Keyboard::A) {
          m_pCamera->moveLeft();
        }
        if (event.key.code == sf::Keyboard::D) {
          m_pCamera->moveRight();
        }
        if (event.key.code == sf::Keyboard::R) {
          m_pCamera->moveUp();
        }
        if (event.key.code == sf::Keyboard::F) {
          m_pCamera->moveDown();
        }
        if (event.key.code == sf::Keyboard::Up) {
          m_pCamera->rotateUp();
        }
        if (event.key.code == sf::Keyboard::Down) {
          m_pCamera->rotateDown();
        }
        if (event.key.code == sf::Keyboard::Left) {
          m_pCamera->rotateLeft();
        }
        if (event.key.code == sf::Keyboard::Right) {
          m_pCamera->rotateRight();
        }
      }
    }
    ImGui::SFML::Update(*m_window, deltaClock.restart());
    
    //ImGui::Begin("Hello, world!");
    //ImGui::Button("Look at this pretty button");
    //ImGui::End();

    //modifyPointlight();
    imguiAmbientLight();
    imguiShowObjects(); 
    imguiShowObjectProperties();
    imguiShowLights();
    imguiShowLightProperties();
    imguiShowCameraProperties();

    m_texture.update(m_image);
    m_sprite.setTexture(m_texture);
    sf::Color backGround((uint8)m_backgroundColor.x, 
                         (uint8)m_backgroundColor.y, 
                         (uint8)m_backgroundColor.z);
    //m_camera->renderScenePerFrame(this);
    m_window->clear(backGround);
    m_window->draw(m_sprite);
    ImGui::SFML::Render(*m_window);
    m_window->display();
  }

  m_allThreadFinished = false;
  while (!m_allThreadFinished) {
    m_allThreadFinished = true;
    for (uint32 i = 0; i < m_numCpus; i++) {
      if (!m_threadsFinished[i]) {
        m_allThreadFinished = false;
        break;
      }
    }
  }

  uint32 materialListNum = (uint32)m_MaterialsListString.size();
  for (uint32 i = 0; i < materialListNum; ++i)
    delete[] m_MaterialsListString[i];
  uint32 shapesListNum = (uint32)m_geometriObjectsListString.size();
  for (uint32 i = 0; i < materialListNum; ++i)
    delete[] m_geometriObjectsListString[i];
  uint32 ambientListNum = (uint32)m_ambientLightsListString.size();
  for (uint32 i = 0; i < ambientListNum; ++i)
    delete[] m_ambientLightsListString[i];
  
  ImGui::SFML::Shutdown();
}

void 
jlWorld::openWindow(const uint32 width, const uint32 height) {
  m_window = new sf::RenderWindow(sf::VideoMode(width, height), "Jade Lightning");
  // Create a image filled with black color
  ImGui::SFML::Init(*m_window);
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
  sf::Color backGround((uint8)m_backgroundColor.x, 
                       (uint8)m_backgroundColor.y, 
                       (uint8)m_backgroundColor.z);
  m_image.create(width, height, backGround);

  m_texture.create(width, height);
  m_texture.update(m_image);

  m_sprite.setTexture(m_texture);
  m_sprite.setOrigin(0.0f, (float)height);
  m_sprite.setScale({ 1,-1 });
  //updateRender();
}

void 
jlWorld::updateRender() {
  //jlTimer time;
  m_renderTime.reset();
  m_pCamera->renderScene(this);
  //if (m_bThreading)
  //  threadRender();
  //else {
  //  m_threads[0] = std::thread(&jlWorld::softwareRenderSimpleSampler, this);
  //  m_threads[0].detach();
  //  softwareRender();
  //
  //}

  //std::cout << "Milliseconds" << time.getSeconds() << std::endl;
}

void 
jlWorld::threadRender() {
  for (uint32 i = 0; i < m_numCpus; i++) {
    //m_threads[i] = std::thread(&jlWorld::threadRenderFunctionJitteredSampler, this, i);
    m_threads[i] = std::thread(&jlWorld::threadRenderFunctionSamplerClass, this, i);
  }
  for (uint32 i = 0; i < m_numCpus; i++) {
    m_threads[i].detach();
  }

}

void 
jlWorld::threadRenderFunction(uint32 threadIdx) {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;
  double x, y;

  uint32 threadWidth = (uint32)m_IndexImageWidth[threadIdx].size();
  auto array = m_IndexImageWidth[threadIdx];
  auto vp = m_vp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 width = 0; width < threadWidth; ++width) { // up
    for (uint32 height = 0; height < vp.m_hRes; ++height) { // across 
      uint32 currentX = array[width];
      x = vp.m_pixelSize * (currentX - 0.5 * (vp.m_wRes - 1.0));
      y = vp.m_pixelSize * (height - 0.5 * (vp.m_hRes - 1.0));
      ray.m_origin = { (float)x, (float)y, (float)zw };
      pixelColor = m_pTracer->traceRay(ray);
      displayPixel(currentX, height, pixelColor);
    }
  }
  m_threadsFinished[threadIdx] = true;
}

void jlWorld::threadRenderFunctionSimpleSampler(uint32 threadIdx) {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;

  uint32 threadWidth = (uint32)m_IndexImageWidth[threadIdx].size();
  auto array = m_IndexImageWidth[threadIdx];
  auto vp = m_vp;

  uint32 n = (uint32)Math::sqrt((float)m_vp.m_numSamples);
  auto black = jlColor::Black();
  jlVector2 pp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 width = 0; width < threadWidth; ++width) { // up
    for (uint32 height = 0; height < vp.m_hRes; ++height) { // across 
      pixelColor = black;
      uint32 currentX = array[width];
      //Sampler
      for (uint32 p = 0; p < n; ++p) {
        for (uint32 q = 0; q < n; ++q) {
          pp.x = float(vp.m_pixelSize * (currentX - 0.5 * vp.m_wRes +(q + 0.5f) /n));
          pp.y = float(vp.m_pixelSize * (height - 0.5 * vp.m_hRes + (p + 0.5f) /n));
          ray.m_origin = { (float)pp.x, (float)pp.y, (float)zw };
          pixelColor += m_pTracer->traceRay(ray);
        }
      }
      pixelColor /= (float)vp.m_numSamples;
      displayPixel(currentX, height, pixelColor);
    }
  }
  m_threadsFinished[threadIdx] = true;
}

void 
jlWorld::threadRenderFunctionRandomSampler(uint32 threadIdx) {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;

  uint32 threadWidth = (uint32)m_IndexImageWidth[threadIdx].size();
  auto array = m_IndexImageWidth[threadIdx];
  auto vp = m_vp;

  uint32 n = (uint32)m_vp.m_numSamples;
  auto black = jlColor::Black();
  jlVector2 pp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 width = 0; width < threadWidth; ++width) { // up
    for (uint32 height = 0; height < vp.m_hRes; ++height) { // across 
      pixelColor = black;
      uint32 currentX = array[width];
      //Sampler
      for (uint32 p = 0; p < n; ++p) {
        pp.x = float(vp.m_pixelSize * (currentX - 0.5 * vp.m_wRes + jlRandom::randomFloat()));
        pp.y = float(vp.m_pixelSize * (height - 0.5 * vp.m_hRes + jlRandom::randomFloat()));
        ray.m_origin = { pp.x, pp.y, (float)zw };
        pixelColor += m_pTracer->traceRay(ray);
      }
      pixelColor /= (float)n;
      displayPixel(currentX, height, pixelColor);
    }
  }
  m_threadsFinished[threadIdx] = true;
}

void 
jlWorld::threadRenderFunctionJitteredSampler(uint32 threadIdx) {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;

  uint32 threadWidth = (uint32)m_IndexImageWidth[threadIdx].size();
  auto array = m_IndexImageWidth[threadIdx];
  auto vp = m_vp;

  uint32 n = (uint32)Math::sqrt((float)m_vp.m_numSamples);
  auto black = jlColor::Black();
  jlVector2 pp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 width = 0; width < threadWidth; ++width) { // up
    for (uint32 height = 0; height < vp.m_hRes; ++height) { // across 
      pixelColor = black;
      uint32 currentX = array[width];
      //Sampler
      for (uint32 p = 0; p < n; ++p) {
        for (uint32 q = 0; q < n; ++q) {
          pp.x = (float)(vp.m_pixelSize * (currentX - 0.5 * vp.m_wRes + (q + jlRandom::randomFloat()) / n));
          pp.y = (float)(vp.m_pixelSize * (height - 0.5 * vp.m_hRes + (p + jlRandom::randomFloat()) / n));
          ray.m_origin = { pp.x, pp.y, (float)zw };
          pixelColor += m_pTracer->traceRay(ray);
        }
      }
      pixelColor /= (float)vp.m_numSamples;
      displayPixel(currentX, height, pixelColor);
    }
  }
  m_threadsFinished[threadIdx] = true;
}

void 
jlWorld::threadRenderFunctionSamplerClass(uint32 threadIdx) {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;

  uint32 threadWidth = (uint32)m_IndexImageWidth[threadIdx].size();
  auto array = m_IndexImageWidth[threadIdx];
  auto vp = m_vp;

  auto black = jlColor::Black();
  jlVector2 pp;
  jlVector2 sp; //sampler Point

  ray.m_direction = { 0, 0, -1 };
  for (uint32 width = 0; width < threadWidth; ++width) { // up
    for (uint32 height = 0; height < vp.m_hRes; ++height) { // across 
      pixelColor = black;
      uint32 currentX = array[width];
      //Sampler
      for (uint32 p = 0; p < vp.m_numSamples; ++p) {
        //sp = vp.m_pSampler->sampleUnitSquare();
        sp = vp.m_pSampler->sampleUnitDisk();
        pp.x = (float)(vp.m_pixelSize * (currentX - 0.5 * vp.m_wRes + sp.x));
        pp.y = (float)(vp.m_pixelSize * (height - 0.5 * vp.m_hRes + sp.y));
        ray.m_origin = { pp.x, pp.y, (float)zw };
        pixelColor += m_pTracer->traceRay(ray);
      }
      pixelColor /= (float)vp.m_numSamples;
      displayPixel(currentX, height, pixelColor);
    }
  }
  m_threadsFinished[threadIdx] = true;
}

void
jlWorld::softwareRender() {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;
  double x, y;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 cwidth = 0; cwidth < m_vp.m_wRes; ++cwidth) { // up
    for (uint32 cheight = 0; cheight < m_vp.m_hRes; ++cheight) { // across 
      x = m_vp.m_pixelSize * (cwidth - 0.5 * (m_vp.m_wRes - 1.0));
      y = m_vp.m_pixelSize * (cheight - 0.5 * (m_vp.m_hRes - 1.0));
      ray.m_origin = { (float)x, (float)y, (float)zw };
      pixelColor += m_pTracer->traceRay(ray);
      displayPixel(cwidth, cheight, pixelColor);
    }
  }
  m_threadsFinished[0] = true;
}

void jlWorld::softwareRenderSimpleSampler() {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;

  uint32 n = (uint32)Math::sqrt((float)m_vp.m_numSamples);
  auto black = jlColor::Black();
  jlVector2 pp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 cwidth = 0; cwidth < m_vp.m_wRes; ++cwidth) { // up
    for (uint32 cheight = 0; cheight < m_vp.m_hRes; ++cheight) { // across 
      pixelColor = black;
      //Sampler
      for (uint32 p = 0; p < n; ++p) {
        for (uint32 q = 0; q < n; ++q) {
          pp.x = float(m_vp.m_pixelSize * (cwidth - 0.5 * m_vp.m_wRes + (q + 0.5f) / n));
          pp.y = float(m_vp.m_pixelSize * (cheight - 0.5 * m_vp.m_hRes + (p + 0.5f) / n));
          ray.m_origin = { pp.x, pp.y, (float)zw };
          pixelColor = m_pTracer->traceRay(ray);
        }
      }

      pixelColor /= (float)m_vp.m_numSamples;
      displayPixel(cwidth, cheight, pixelColor);
    }
  }
  m_threadsFinished[0] = true;
}

void 
jlWorld::softwareRenderRandomSampler() {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;

  uint32 n = (uint32)Math::sqrt((float)m_vp.m_numSamples);
  auto black = jlColor::Black();
  jlVector2 pp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 cwidth = 0; cwidth < m_vp.m_wRes; ++cwidth) { // up
    for (uint32 cheight = 0; cheight < m_vp.m_hRes; ++cheight) { // across 
      pixelColor = black;
      //Sampler
      for (uint32 p = 0; p < n; ++p) {
        pp.x = float(m_vp.m_pixelSize * (cwidth - 0.5 * m_vp.m_wRes + jlRandom::randomFloat()));
        pp.y = float(m_vp.m_pixelSize * (cheight - 0.5 * m_vp.m_hRes + jlRandom::randomFloat()));
        ray.m_origin = { pp.x, pp.y, (float)zw };
        pixelColor += m_pTracer->traceRay(ray);
      }

      pixelColor /= (float)m_vp.m_numSamples;
      displayPixel(cwidth, cheight, pixelColor);
    }
  }
  m_threadsFinished[0] = true;
}

void 
jlWorld::softwareRenderJitteredSampler() {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;

  uint32 n = (uint32)Math::sqrt((float)m_vp.m_numSamples);
  auto black = jlColor::Black();
  jlVector2 pp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 cwidth = 0; cwidth < m_vp.m_wRes; ++cwidth) { // up
    for (uint32 cheight = 0; cheight < m_vp.m_hRes; ++cheight) { // across 
      pixelColor = black;
      //Sampler
      for (uint32 p = 0; p < n; ++p) {
        for (uint32 q = 0; q < n; ++q) {
          pp.x = float(m_vp.m_pixelSize * (cwidth - 0.5 * m_vp.m_wRes + (q + jlRandom::randomFloat()) / n));
          pp.y = float(m_vp.m_pixelSize * (cheight - 0.5 * m_vp.m_hRes + (p + jlRandom::randomFloat()) / n));
          ray.m_origin = { pp.x, pp.y, (float)zw };
          pixelColor = m_pTracer->traceRay(ray);
        }
      }

      pixelColor /= (float)m_vp.m_numSamples;
      displayPixel(cwidth, cheight, pixelColor);
    }
  }
  m_threadsFinished[0] = true;
}

void 
jlWorld::softwareRenderSamplerClass() {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;

  auto black = jlColor::Black();
  jlVector2 pp;
  jlVector2 sp;//Sampler point

  ray.m_direction = { 0, 0, -1 };
  for (uint32 cwidth = 0; cwidth < m_vp.m_wRes; ++cwidth) { // up
    for (uint32 cheight = 0; cheight < m_vp.m_hRes; ++cheight) { // across 
      pixelColor = black;
      //Sampler
      for (uint32 s = 0; s < m_vp.m_numSamples; ++s) {
        sp = m_vp.m_pSampler->sampleUnitSquare();
        pp.x = float(m_vp.m_pixelSize * (cwidth - 0.5 * m_vp.m_wRes + sp.x));
        pp.y = float(m_vp.m_pixelSize * (cheight - 0.5 * m_vp.m_hRes + sp.y));
        ray.m_origin = { pp.x, pp.y, (float)zw };
        pixelColor = m_pTracer->traceRay(ray);
      }

      pixelColor /= (float)m_vp.m_numSamples;
      displayPixel(cwidth, cheight, pixelColor);
    }
  }
  m_threadsFinished[0] = true;
}

void
jlWorld::displayPixel(const int x, const int y, const jlColor& pixel_color) {
  //auto color = pixel_color.getIn255();
  jlColor color;
  if (m_vp.m_bShowOutOfGamut)
    color = clampToColor(pixel_color);
  else
    color = maxToOne(pixel_color);
  
  if (m_vp.m_gamma != 1.0)
    color = color.powc(m_vp.m_invGamma);
  color.make255();
  sf::Color sfColor((uint8)color.x, (uint8)color.y, (uint8)color.z);
  m_image.setPixel(x, y, sfColor);
}

jlShadeRec 
jlWorld::hitBareBonesObjects(const jlRay& ray) {
  jlShadeRec sr(this);
  double t;
  double tmin = HUGE_VAL;
  int num_objects = (uint32)m_sceneObjects.size();
  for (int j = 0; j < num_objects; j++) {
    if (m_sceneObjects[j]->hit(ray, t, sr) && (t < tmin)) {
      sr.m_hitAnObject = true;
      tmin = t;
      sr.m_color = m_sceneObjects[j]->m_color;
    }
  }
  return sr;
}

jlShadeRec 
jlWorld::hitObjects(const jlRay& ray) {
  jlShadeRec sr(this);
  double t;
  jlNormal normal;
  jlVector3 localHitPoint;

  float tmin = HUGE_VAL;
  uint32 numObjects = (uint32)m_sceneObjects.size();

  for (uint32 i = 0; i < numObjects; ++i) {
    if (m_sceneObjects[i]->hit(ray, t, sr) && (t < tmin)) {
      sr.m_hitAnObject = true;
      tmin = (float)t;
      sr.m_pMaterial = m_sceneObjects[i]->m_pMaterial;
      sr.m_HitPoint = ray.m_origin + ((float)t * ray.m_direction);
      normal = sr.m_normal;
      localHitPoint = sr.m_localHitPoint;
    }
  }
  if (sr.m_hitAnObject) {
    sr.m_t = tmin; //check this
    sr.m_depth = (int32)tmin;
    sr.m_normal = normal;
    sr.m_localHitPoint = localHitPoint;
  }
  return sr;
}

jlColor 
jlWorld::maxToOne(const jlColor& color) const {
  float max_value = std::max(color.r, std::max(color.g, color.b));
  if (max_value > 1.0)
    return (color / max_value);
    
  return (color);
}

jlColor 
jlWorld::clampToColor(const jlColor& color) const {
  jlColor c(color);
  if (color.r > 1.0 || color.g > 1.0 || color.b > 1.0) {
    c.r = 1.0f; c.g = 1.0f; c.b = 1.0f;
  }
  return (c);
}

