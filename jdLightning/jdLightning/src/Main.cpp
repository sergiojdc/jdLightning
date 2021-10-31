#include "jlWorld.h"

int 
main() {
  jlWorld w;
  w.build(800,800, false);
  w.renderScene();
  return 0;
}