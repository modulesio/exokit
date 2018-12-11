#ifdef LUMIN

#include <browser-ml.h>

#include <iostream>

using namespace std;
using namespace v8;
using namespace node;

namespace browser {

bool initializeEmbedded(const std::string &dataPath) {
  return true;
}
EmbeddedBrowser createEmbedded(
  const std::string &url,
  WebGLRenderingContext *gl,
  NATIVEwindow *window,
  GLuint tex,
  int width,
  int height,
  int *textureWidth,
  int *textureHeight,
  std::function<void()> onloadstart,
  std::function<void(const std::string &)> onloadend,
  std::function<void(int, const std::string &, const std::string &)> onloaderror,
  std::function<void(const std::string &, const std::string &, int)> onconsole,
  std::function<void(const std::string &)> onmessage
) {
  if (width == 0) {
    width = 1280;
  }
  if (height == 0) {
    height = 1024;
  }
  
  *textureWidth = width;
  *textureHeight = height;

  {
    EGLint error = eglGetError();
    if (error) {
      std::cout << "createEmbedded error 1 " << error << std::endl;
    }
  }
  windowsystem::SetCurrentWindowContext(window);
  {
    EGLint error = eglGetError();
    if (error) {
      std::cout << "createEmbedded error 2 " << error << std::endl;
    }
  }
  
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  {
    EGLint error = eglGetError();
    if (error) {
      std::cout << "createEmbedded error 3 " << error << std::endl;
    }
  }
  
  EmbeddedBrowser browser_ = new Servo2D();
  {
    EGLint error = eglGetError();
    if (error) {
      std::cout << "createEmbedded error 4 " << error << std::endl;
    }
  }
  browser_->init(url, window, tex, width, height, onloadstart, onloadend, onloaderror, onconsole, onmessage);
  browsers.push_back(browser_);
  
  {
    EGLint error = eglGetError();
    if (error) {
      std::cout << "createEmbedded error 5 " << error << std::endl;
    }
  }
  
  /* if (gl->HasTextureBinding(gl->activeTexture, GL_TEXTURE_2D)) {
    glBindTexture(GL_TEXTURE_2D, gl->GetTextureBinding(gl->activeTexture, GL_TEXTURE_2D));
  } else {
    glBindTexture(GL_TEXTURE_2D, 0);
  } */
  
  std::cout << "createEmbedded 6 " << std::endl;
  
  onloadstart();
  std::cout << "createEmbedded 7 " << std::endl;
  onloadend(url);
  std::cout << "createEmbedded 8 " << std::endl;
  
  return browser_;
}
void destroyEmbedded(EmbeddedBrowser browser_) {
  browser_->deInit();
  browsers.erase(std::find(browsers.begin(), browsers.end(), browser_));
}
void embeddedDoMessageLoopWork() {
  for (EmbeddedBrowser browser_ : browsers) {
    heartbeat_servo(browser_->getInstance());
    browser_->flushTexture();
  }
}
int getEmbeddedWidth(EmbeddedBrowser browser_) {
  return browser_->getWidth();
}
void setEmbeddedWidth(EmbeddedBrowser browser_, int width) {
  browser_->setWidth(width);
}
int getEmbeddedHeight(EmbeddedBrowser browser_) {
  return browser_->getHeight();
}
void setEmbeddedHeight(EmbeddedBrowser browser_, int height) {
  browser_->setHeight(height);
}
void embeddedGoBack(EmbeddedBrowser browser_) {
  traverse_servo(browser_->getInstance(), -1);
}
void embeddedGoForward(EmbeddedBrowser browser_) {
  traverse_servo(browser_->getInstance(), 1);
}
void embeddedReload(EmbeddedBrowser browser_) {
  traverse_servo(browser_->getInstance(), 0);
}
void embeddedMouseMove(EmbeddedBrowser browser_, int x, int y) {
  move_servo(browser_->getInstance(), x, y);
}
void embeddedMouseDown(EmbeddedBrowser browser_, int x, int y, int button) {
  trigger_servo(browser_->getInstance(), x, y, true);
}
void embeddedMouseUp(EmbeddedBrowser browser_, int x, int y, int button) {
  trigger_servo(browser_->getInstance(), x, y, false);
}
void embeddedMouseWheel(EmbeddedBrowser browser_, int x, int y, int deltaX, int deltaY) {
  // nothing
}
void embeddedKeyDown(EmbeddedBrowser browser_, int key, int modifiers) {
  // nothing
}
void embeddedKeyUp(EmbeddedBrowser browser_, int key, int modifiers) {
  // nothing
}
void embeddedKeyPress(EmbeddedBrowser browser_, int key, int wkey, int modifiers) {
  // nothing
}
void embeddedRunJs(EmbeddedBrowser browser_, const std::string &jsString, const std::string &scriptUrl, int startLine) {
  // nothing
}

std::list<EmbeddedBrowser> browsers;

}

#endif