#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include <jlColor.h>
using namespace jlUtilitiesSDK;
struct Point {
  int x = 0;
  int y = 0;
};

/**
 * @brief window
 */
sf::RenderWindow* m_window = nullptr;
int gWidth;
int gheight;

std::vector<std::vector<int>> gIndexImageWidth;
std::vector<std::vector<int>> gIndexImageHeight;
std::vector<Point> gImageRes;
std::vector<bool> gCoreFinished;
std::vector<sf::Color> gThreadColor;
bool gProccesFishihed = false;


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

void openWindow(const int width, const int height);
void displayPixel(const int x, const int y, const sf::Color& pixel_color);
void executeThread(const int index);
void windowThread();

int main() {

  gWidth = 400;
  gheight = 400;
  openWindow(gWidth, gheight);
  m_window->setActive(true);
  //std::thread windowT = std::thread(windowThread);

  int num_cpus = std::thread::hardware_concurrency();
  std::cout << "Launching " << num_cpus << " threads\n";

  // A mutex ensures orderly access to std::cout from multiple threads.
  std::mutex iomutex;
  int numCpuToDraw = num_cpus;
  std::vector<std::thread> threads(numCpuToDraw);
  //for (unsigned i = 0; i < num_cpus; ++i) {
  //  threads[i] = std::thread([&iomutex, i] {  
  //    {
  //      // Use a lexical scope and lock_guard to safely lock the mutex only for
  //      // the duration of std::cout usage.
  //      std::lock_guard<std::mutex> iolock(iomutex);
  //      std::cout << "Thread #" << i << " is running\n";
  //    }
  //
  //    // Simulate important work done by the tread by sleeping for a bit...
  //    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  //
  //  });
  //}
  //
  //for (auto& t : threads) {
  //  t.join();
  //}



  gIndexImageWidth.resize(numCpuToDraw);
  gIndexImageHeight.resize(numCpuToDraw);
  gImageRes.resize(numCpuToDraw);
  gCoreFinished.resize(numCpuToDraw);
  gThreadColor.resize(numCpuToDraw);

  int widthPerCpus = gWidth / numCpuToDraw; // get number of pixel on widht per cpu
  int CpusWithExtra = gWidth % numCpuToDraw; // check if have decimal to repart the extra width
  int heightPerCpus = gheight / numCpuToDraw; // get number of pixel on height per cpu
  int CpusHeightExtra = gheight % numCpuToDraw; // check if have decimal to repart the extra height

  int currentWidthIdx = 0; 
  int currentHeightIdx = 0;
  jlColor color;
  //Prepare data
  for (int i = 0; i < numCpuToDraw; i++) {
    gCoreFinished[i] = false;
    int colorR = rand() % 256;
    int colorG = rand() % 256;
    int colorB = rand() % 256;
    gThreadColor[i] = sf::Color(colorR, colorG, colorB, 255);
    //Get width pixels per cpu
    int numIndexWidth = widthPerCpus;
    if (i < CpusWithExtra) {
      numIndexWidth++;
    }
    gImageRes[i].x = numIndexWidth;
    gIndexImageWidth[i].resize(numIndexWidth);
    for (int idx = 0; idx < numIndexWidth; ++idx) {
      gIndexImageWidth[i][idx] = currentWidthIdx++;
    }
    //Get height pixels per cpu
    int numIndexHeight = heightPerCpus;
    if (i < CpusHeightExtra) {
      numIndexHeight++;
    }
    gImageRes[i].y = numIndexHeight;
    gIndexImageHeight[i].resize(numIndexHeight);
    for (int idx = 0; idx < numIndexHeight; ++idx) {
      gIndexImageHeight[i][idx] = currentHeightIdx++;
    }
    threads[i] = std::thread(executeThread,i);
  }

  for (int i = 0; i < numCpuToDraw; i++) {
    threads[i].detach();
  }
  //windowT.join();
  windowThread();
  return 0;
}




void openWindow(const int width, const int height) {
  m_window = new sf::RenderWindow(sf::VideoMode(width, height), "My window");
  // Create a image filled with black color

  sf::Color backGround = sf::Color::Black;
  m_image.create(width, height, backGround);

  m_texture.create(width, height);
  m_texture.update(m_image);

  m_sprite.setTexture(m_texture);
  m_sprite.setOrigin(0, height);
  m_sprite.setScale({ 1,-1 });
  //updateRender();
}

void
displayPixel(const int x, const int y, const sf::Color& pixel_color) {
  m_image.setPixel(x, y, pixel_color);
  m_texture.update(m_image);
  m_sprite.setTexture(m_texture);
}

void executeThread(const int index) {
  int width = gIndexImageWidth[index].size();
  int height = gIndexImageHeight[index].size();
  for (int x = 0; x < width; ++x) {
    for (int y = 0; y < gheight; ++y) {
      displayPixel(gIndexImageWidth[index][x], 
                   y, 
                   gThreadColor[index]);
    }
  }
  gCoreFinished[index] = true;
}

void windowThread() {
  while (m_window->isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (m_window->pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        m_window->close();
    }

    sf::Color backGround = sf::Color::Black;
    m_window->clear(backGround);
    m_window->draw(m_sprite);
    m_window->display();
  }


  if (nullptr != m_window) {
    delete m_window;
    m_window = nullptr;
  }
}
