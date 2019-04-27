#include "button.h"

Button::Button()
{
    rect.w = BUTTON_WIDTH;
    rect.h = BUTTON_HEIGHT;
}

Button::~Button()
{}

bool Button::handleEvent(SDL_Event e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            int currentX = e.button.x;
            int currentY = e.button.y;

            if((currentX > rect.x) && (currentX < rect.x + rect.w) && (currentY > rect.y) && (currentY < rect.y + rect.h))
            {
                return true;
            }
        }
    }
    return false;
}
