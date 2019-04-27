#ifndef BUTTON_H
#define BUTTON_H

#include "baseobject.h"
#include "SDL_utils.h"

#define BUTTON_WIDTH 270
#define BUTTON_HEIGHT 98

class Button : public BaseObject
{
public:
    Button();
    ~Button();
    bool handleEvent(SDL_Event e);

};

#endif // BUTTON_H
