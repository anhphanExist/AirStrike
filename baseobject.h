#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "SDL_utils.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const char WINDOW_TITLE[];

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern Mix_Chunk* soundBullet;
extern Mix_Chunk* soundExplosion;

class BaseObject
{
protected:
    SDL_Rect rect;
    SDL_Texture* object;
public:
    BaseObject();
    ~BaseObject();
    void loadImg(const std::string path);
    bool show();
    void setRect(const int& _x, const int& _y);
    void setRect(const int& _x, const int& _y, const int& _w, const int& _h);
    SDL_Rect getRect();
    SDL_Texture* getObject();
};

#endif // BASEOBJECT_H
