#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "baseobject.h"
#include "SDL_utils.h"

#define EXPLOSION_WIDTH 165
#define EXPLOSION_HEIGHT 165

class Explosion : public BaseObject
{
public:
    Explosion();
    ~Explosion();

};

#endif // EXPLOSION_H
