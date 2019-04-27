#include "text.h"

Text::Text()
{}

Text::Text(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color& color)
{
    object = loadFont(fontPath, fontSize, messageText, color);
    SDL_QueryTexture(object, nullptr, nullptr, &rect.w, &rect.h);
}

Text::~Text()
{}

void Text::setText(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color &color)
{
    object = loadFont(fontPath, fontSize, messageText, color);
    SDL_QueryTexture(object, nullptr, nullptr, &rect.w, &rect.h);
}

SDL_Texture* Text::loadFont(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color& color)
{
    TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if(!font)
    {
        logSDLError(std::cout, "Load font", true);
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, messageText.c_str(), color);
    if(!textSurface)
    {
        logSDLError(std::cout, "Create text surface", true);
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(!textTexture)
    {
        logSDLError(std::cout, "Create text texture", true);
    }
    SDL_FreeSurface(textSurface);
    return textTexture;
}
