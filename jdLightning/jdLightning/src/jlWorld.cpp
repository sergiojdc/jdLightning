#include "jlWorld.h"
#include <jlColor.h>
#include <jlVector4.h>
#include <jlTimer.h>
#include <jlRandom.h>

#include "jlTSingleSphere.h"
#include "jlTMultipleObjects.h"
#include "jlGOPlane.h"

void 
jlWorld::build(const uint32 width, const uint32 height, bool activeThreading) {
  m_bThreading = activeThreading;
  if (m_bThreading) {

    jlTimer time;
    m_numCpus = (uint32)std::thread::hardware_concurrency();
    std::cout << "Launching " << m_numCpus << " threads\n";
    m_threads.resize(m_numCpus);
    m_IndexImageWidth.resize(m_numCpus);
    m_threadsFinished.resize(m_numCpus);
    uint32 widthPerCpus = width / m_numCpus; // get number of pixel on widht per cpu
    uint32 CpusWithExtra = height % m_numCpus; // check if have decimal to repart the extra width

    uint32 currentWidthIdx = 0;
    uint32 currentHeightIdx = 0;
    //Prepare data
    for (uint32 i = 0; i < m_numCpus; i++) {
      //Get width pixels per cpu
      uint32 numIndexWidth = widthPerCpus;
      m_threadsFinished[i] = false;
      if (i < CpusWithExtra) {  
        numIndexWidth++;
      }
      m_IndexImageWidth[i].resize(numIndexWidth);
      for (int idx = 0; idx < numIndexWidth; ++idx) {
        m_IndexImageWidth[i][idx] = currentWidthIdx++;
      }
    }

    std::cout << "Milliseconds Thread creaction" << time.getMilliseconds() << std::endl;
  }
  else {
    m_numCpus = 1;
    m_threads.resize(1);
    m_threadsFinished.resize(1);
  }


  m_vp = jlViewPlane(width, height, 1.0f, 1.0f);
  m_backgroundColor = jlColor::Black();

  //m_pTracer.reset(new jlTSingleSphere(this));
  m_pTracer.reset(new jlTMultipleObjects(this));

  m_sphere = jlSphere({0,0,0}, 40.0f);

  SPtr<jlSphere> newSphere(new jlSphere);
  newSphere->m_position = { 0, -25, 0 };
  newSphere->m_radius = 80.0f;
  newSphere->m_color = { 1,0,0 };
  addObject(newSphere);

  newSphere.reset(new jlSphere({ 0,30,0 }, 60));
  newSphere->m_color = { 1,1,0 };
  addObject(newSphere);

  SPtr<jlPlane> newPLane(new jlPlane({ 0,0,0 }, {0,1,1}));
  newPLane->m_color = { 0,0.3,0 };
  addObject(newPLane);

  openWindow(width, height);
  updateRender();
}

void jlWorld::renderScene() {
  while (m_window->isOpen())
  {
    if (!m_allThreadFinished) {
      m_allThreadFinished = true;
      for (uint32 i = 0; i < m_numCpus; i++) {
        if (!m_threadsFinished[i]) {
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
    while (m_window->pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        m_window->close();
    }

    m_texture.update(m_image);
    m_sprite.setTexture(m_texture);
    sf::Color backGround(m_backgroundColor.x, m_backgroundColor.y, m_backgroundColor.z);
    //m_camera->renderScenePerFrame(this);
    m_window->clear(backGround);
    m_window->draw(m_sprite);
    m_window->display();
  }
}

void 
jlWorld::openWindow(const int width, const int height) {
  m_window = new sf::RenderWindow(sf::VideoMode(width, height), "My window");
  // Create a image filled with black color

  sf::Color backGround(m_backgroundColor.x, m_backgroundColor.y, m_backgroundColor.z);
  m_image.create(width, height, backGround);

  m_texture.create(width, height);
  m_texture.update(m_image);

  m_sprite.setTexture(m_texture);
  m_sprite.setOrigin(0, height);
  m_sprite.setScale({ 1,-1 });
  //updateRender();
}

void 
jlWorld::updateRender() {
  jlTimer time;
  m_renderTime.reset();
  if (m_bThreading)
    threadRender();
  else {
    m_threads[0] = std::thread(&jlWorld::softwareRender, this);
    m_threads[0].detach();
    softwareRender();

  }

  std::cout << "Milliseconds" << time.getSeconds() << std::endl;
}

void 
jlWorld::threadRender() {
  for (uint32 i = 0; i < m_numCpus; i++) {
    m_threads[i] = std::thread(&jlWorld::threadRenderFunction, this, i);
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

  uint32 threadWidth = m_IndexImageWidth[threadIdx].size();
  auto array = m_IndexImageWidth[threadIdx];
  auto vp = m_vp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 width = 0; width < threadWidth; ++width) { // up
    for (uint32 height = 0; height < vp.m_hRes; ++height) { // across 
      uint32 currentX = array[width];
      x = vp.m_pixelSize * (currentX - 0.5 * (vp.m_wRes - 1.0));
      y = vp.m_pixelSize * (height - 0.5 * (vp.m_hRes - 1.0));
      ray.m_origin = { x, y, zw };
      pixelColor = m_pTracer->traceRay(ray);
      displayPixel(currentX, height, pixelColor);
    }
  }
  m_threadsFinished[threadIdx] = true;
}

void jlWorld::threadRenderFunctionV2(uint32 threadIdx) {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;
  double x, y;

  uint32 threadWidth = m_IndexImageWidth[threadIdx].size();
  auto array = m_IndexImageWidth[threadIdx];
  auto vp = m_vp;

  uint32 n = (uint32)Math::sqrt((float)m_vp.m_numSamples);
  auto black = jlColor::Black();
  jlPoint2 pp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 width = 0; width < threadWidth; ++width) { // up
    for (uint32 height = 0; height < vp.m_hRes; ++height) { // across 
      pixelColor = black;
      uint32 currentX = array[width];
      x = vp.m_pixelSize * (currentX - 0.5 * (vp.m_wRes - 1.0));
      y = vp.m_pixelSize * (height - 0.5 * (vp.m_hRes - 1.0));
      ray.m_origin = { x, y, zw };
      pixelColor = m_pTracer->traceRay(ray);
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
      ray.m_origin = { x, y, zw };
      pixelColor = m_pTracer->traceRay(ray);
      displayPixel(cwidth, cheight, pixelColor);
    }
  }
  m_threadsFinished[0] = true;
}

void jlWorld::softwareRenderV2() {
  jlColor pixelColor;
  jlRay ray;
  double zw = 100.0;
  double x, y;

  uint32 n = (uint32)Math::sqrt((float)m_vp.m_numSamples);
  auto black = jlColor::Black();
  jlPoint2 pp;

  ray.m_direction = { 0, 0, -1 };
  for (uint32 cwidth = 0; cwidth < m_vp.m_wRes; ++cwidth) { // up
    for (uint32 cheight = 0; cheight < m_vp.m_hRes; ++cheight) { // across 
      pixelColor = black;
      x = m_vp.m_pixelSize * (cwidth - 0.5 * (m_vp.m_wRes - 1.0));
      y = m_vp.m_pixelSize * (cheight - 0.5 * (m_vp.m_hRes - 1.0));
      ray.m_origin = { x, y, zw };
      pixelColor = m_pTracer->traceRay(ray);
      displayPixel(cwidth, cheight, pixelColor);
    }
  }
  m_threadsFinished[0] = true;
}

void
jlWorld::displayPixel(const int x, const int y, const jlColor& pixel_color) {
  auto color = pixel_color.getIn255();
  sf::Color sfColor(color.x, color.y, color.z);
  m_image.setPixel(x, y, sfColor);
}

jlShadeRec 
jlWorld::hitBareBonesObjects(const jlRay& ray) {
  jlShadeRec sr(this);
  double t;
  double tmin = HUGE_VAL;
  int num_objects = m_sceneObjects.size();
  for (int j = 0; j < num_objects; j++) {
    if (m_sceneObjects[j]->hit(ray, t, sr) && (t < tmin)) {
      sr.m_hitAnObject = true;
      tmin = t;
      sr.m_color = m_sceneObjects[j]->m_color;
    }
  }
  return sr;
}
