#include "jlCPinhole.h"
#include "jlWorld.h"
#include "jlViewPlane.h"
#include <jlColor.h>
#include "jlRay.h"

jlVector3 
jlCPinhole::rayDirection(const jlVector3& p) {
  jlVector3 dir = p.x * m_u + p.y * m_v - m_viewDistance * m_w;
  dir.normalize();
  return dir;
}

void 
jlCPinhole::renderScene(jlWorld* world) {
  if (world->m_bThreading) {
    renderSceneThreading(world);
  }
  else {
    world->m_threads[0] = std::thread(&jlCPinhole::renderSceneSoftware, this, world);
    world->m_threads[0].detach();
  }
}

void 
jlCPinhole::renderSceneThreading(jlWorld* world) {
  for (uint32 i = 0; i < world->m_numCpus; i++) {
    //m_threads[i] = std::thread(&jlWorld::threadRenderFunctionJitteredSampler, this, i);
    world->m_threads[i] = std::thread(&jlCPinhole::renderThread, this, world ,i);
  }
  for (uint32 i = 0; i < world->m_numCpus; i++) {
    world->m_threads[i].detach();
  }
}

void 
jlCPinhole::renderSceneSoftware(jlWorld* world) {
  jlColor L;
  jlViewPlane vp(world->m_vp);
  jlRay ray;
  uint32 depth = 0; // recursion depth
  jlVector2 sp; // sample point in [0, 1] X [0, 1]
  jlVector2 pp; // sample point on a pixel
  vp.m_pixelSize /= m_zoom;
  ray.m_origin = m_eye;
  auto black = jlColor::Black();
  while (world->run) {
    if (!world->run)
      break;
      for (uint32 cwidth = 0; cwidth < vp.m_wRes; ++cwidth) { // up
        if (!world->run)
          break;
        for (uint32 cheight = 0; cheight < vp.m_hRes; ++cheight) { // across 
          if (!world->run)
            break;
          L = black;
          //Sampler
          for (uint32 s = 0; s < vp.m_numSamples; ++s) {
            sp = vp.m_pSampler->sampleUnitSquare();
            pp.x = float(vp.m_pixelSize * (cwidth - 0.5 * vp.m_wRes + sp.x));
            pp.y = float(vp.m_pixelSize * (cheight - 0.5 * vp.m_hRes + sp.y));
            ray.m_direction = rayDirection(pp);
            //L += world->m_pTracer->traceRay(ray);
            L += world->m_pTracer->traceRay(ray, depth);
          }

          L /= (float)vp.m_numSamples;
          L *= m_exposureTime;
          world->displayPixel(cwidth, cheight, L);
        }
      }
    world->m_threadsFinishedFirst[0] = true;
  }

  world->m_threadsFinished[0] = true;
}

void 
jlCPinhole::renderThread(jlWorld* world, int threadIdx) {
  jlColor L;
  jlViewPlane vp(world->m_vp);
  jlRay ray;
  uint32 depth = 0; // recursion depth
  jlVector2 sp; // sample point in [0, 1] X [0, 1]
  jlVector2 pp; // sample point on a pixel
  vp.m_pixelSize /= m_zoom;
  ray.m_origin = m_eye;

  uint32 threadWidth = (uint32)world->m_IndexImageWidth[threadIdx].size();
  auto array = world->m_IndexImageWidth[threadIdx];

  while (world->run) {
    if (!world->run)
      break;
    for (uint32 width = 0; width < threadWidth; ++width) { // up
      if (!world->run)
        break;
      for (uint32 height = 0; height < vp.m_hRes; ++height) { // across 
        if (!world->run)
          break;
        L = jlColor::Black();
        uint32 currentX = array[width];
        
        for (uint32 j = 0; j < vp.m_numSamples; j++) {
          sp = vp.m_pSampler->sampleUnitSquare();
          pp.x = (float)(vp.m_pixelSize * (currentX - 0.5 * vp.m_wRes + sp.x));
          pp.y = (float)(vp.m_pixelSize * (height - 0.5 * vp.m_hRes + sp.y));
          ray.m_direction = rayDirection(pp);
          //L += world->m_pTracer->traceRay(ray);
          L += world->m_pTracer->traceRay(ray, depth);
        }
        L /= (float)vp.m_numSamples;
        L *= m_exposureTime;
        world->displayPixel(currentX, height, L);
      }
    }

    world->m_threadsFinishedFirst[threadIdx] = true;
  }
  world->m_threadsFinished[threadIdx] = true;
  
}
