#include "jlSampler.h" 

void 
jlSampler::mapSamplerToUnitDisk() {
  uint32 size = (uint32)m_samples.size();
  float r, phi; // polar coordinates
  jlVector2 sp; // sample point on unit disk
  m_diskSamples.resize(size);
  for (uint32 j = 0; j < size; j++) {
    // map sample point to [-1, 1] [-1,1]
    sp.x = 2.0f * m_samples[j].x - 1.0f;
    sp.y = 2.0f * m_samples[j].y - 1.0f;
    if (sp.x > -sp.y) { // sectors 1 and 2
      if (sp.x > sp.y) { // sector 1 
        r = sp.x;
        phi = sp.y / sp.x;
      }
      else { // sector 2
        r = sp.y;
        phi = 2 - sp.x / sp.y;
      }
    }
    else { // sectors 3 and 4
      if (sp.x < sp.y) { // sector 3
        r = -sp.x;
        phi = 4 + sp.y / sp.x;
      }
      else { // sector 4
        r = -sp.y;
        if (sp.y != 0.0) // avoid division by zero at origin
          phi = 6 - sp.x / sp.y;
        else
          phi = 0.0;
      }
    }
    phi *= Math::PI / 4.0f;
    m_diskSamples[j].x = r * cos(phi);
    m_diskSamples[j].y = r * sin(phi);
  }
}

void 
jlSampler::mapSamplesToHemisphere(const float& e) {
  uint32 size = (uint32)m_samples.size();
  uint32 totalsets = m_numSamples * m_numSets;
  m_hemisphereSamples.reserve(totalsets);
  for (uint32 j = 0; j < size; j++) {
    float cos_phi = cos(2.0f * Math::PI * m_samples[j].x);
    float sin_phi = sin(2.0f * Math::PI * m_samples[j].x);
    float cos_theta = pow((1.0f - m_samples[j].y), 1.0f / (e + 1.0f));
    float cosTheta2 = cos_theta * cos_theta;
    float sin_theta = sqrt(1.0f - cosTheta2);
    float pu = sin_theta * cos_phi;
    float pv = sin_theta * sin_phi;
    float pw = cos_theta;
    m_hemisphereSamples.push_back(jlVector3(pu, pv, pw));
  }
}
