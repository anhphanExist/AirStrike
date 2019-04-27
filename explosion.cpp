#include "explosion.h"

Explosion::Explosion()
{
    rect.w = EXPLOSION_WIDTH;
    rect.h = EXPLOSION_HEIGHT;
}

Explosion::~Explosion()
{
    //dtor
}

/*
void Explosion::setClips()
{
    clips[0].x = 0;
    clips[0].y = 0;
    clips[0].w = EXPLOSION_WIDTH;
    clips[0].h = EXPLOSION_HEIGHT;

    clips[1].x = EXPLOSION_WIDTH;
    clips[1].y = 0;
    clips[1].w = EXPLOSION_WIDTH;
    clips[1].h = EXPLOSION_HEIGHT;

    clips[2].x = EXPLOSION_WIDTH * 2;
    clips[2].y = 0;
    clips[2].w = EXPLOSION_WIDTH;
    clips[2].h = EXPLOSION_HEIGHT;

    clips[3].x = EXPLOSION_WIDTH * 3;
    clips[3].y = 0;
    clips[3].w = EXPLOSION_WIDTH;
    clips[3].h = EXPLOSION_HEIGHT;
}

void setFrame(const int _frame)
{
    this->frame = _frame;
}

void move()
{

}

void showExplosion()
{
    if(frame >= 4)
    {
        frame = 0;
    }

}
*/
