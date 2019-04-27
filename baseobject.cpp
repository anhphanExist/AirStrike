#include "baseobject.h"

BaseObject::BaseObject()
{
    rect.x = 0;
    rect.y = 0;
    object = nullptr;
}

BaseObject::~BaseObject()
{
    SDL_DestroyTexture(object);
}

void BaseObject::loadImg(const std::string path)
{
    //Nạp ảnh từ tên file (với đường dẫn)
    SDL_Surface *loadedImage = IMG_Load(path.c_str());
    //Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
    if (loadedImage != nullptr)
    {
        object = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        //Đảm bảo việc chuyển đổi không có lỗi
        if (object == nullptr)
        {
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
    }
    else
    {
        logSDLError(std::cout, "LoadIMG");
    }
}

bool BaseObject::show()
{
    if(object != nullptr)
    {
        SDL_RenderCopy(renderer, object, nullptr, &rect);
        return true;
    }
    else
    {
        return false;
    }
}

void BaseObject::setRect(const int& _x, const int& _y)
{
    rect.x = _x;
    rect.y = _y;
}

void BaseObject::setRect(const int& _x, const int& _y, const int& _w, const int& _h)
{
    rect.x = _x;
    rect.y = _y;
    rect.w = _w;
    rect.h = _h;
}

SDL_Rect BaseObject::getRect()
{
    return rect;
}

SDL_Texture* BaseObject::getObject()
{
    return object;
}
