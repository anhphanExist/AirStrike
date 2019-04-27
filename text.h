#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <SDL_ttf.h>
#include <string>
#include "baseobject.h"
#include "SDL_utils.h"

class Text : public BaseObject
{
public:
    Text();
    Text(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color &color);
    ~Text();
    void setText(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color &color);
    static SDL_Texture* loadFont(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color &color);


};

#endif // TEXT_H
