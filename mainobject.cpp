#include "mainobject.h"

MainObject::MainObject()
{
    rect.h = MAIN_OBJECT_HEIGHT;
    rect.w = MAIN_OBJECT_WIDTH;
    step_x = MAIN_OBJECT_WIDTH / 2;
    step_y = MAIN_OBJECT_HEIGHT / 2;
}

MainObject::~MainObject()
{}

void MainObject::createBullet(Bullet* b)
{
    if(b)
    {
        b->loadImg("images/bullet.png");
        b->setRect(rect.x + MAIN_OBJECT_WIDTH / 2, rect.y);
        b->setMoveStatus(true);

        bulletList.push_back(b);
    }

}

void MainObject::destroyBullet(const int bulletIndex)
{
    Bullet* bulletToDestroy = bulletList.at(bulletIndex);
    this->bulletList.erase(bulletList.begin() + bulletIndex);
    delete bulletToDestroy;
}

void MainObject::handleBulletLogic()
{
    for(int i = 0; i < this->bulletList.size(); i++)
    {
        Bullet* currentBullet = bulletList.at(i);
        if(currentBullet != NULL)
        {
            if(currentBullet->getMoveStatus())
            {
                currentBullet->show();
                currentBullet->handleBulletMovement();
            }
            else
            {
                if(currentBullet != NULL)
                {
                    bulletList.erase(bulletList.begin() + i);
                    delete currentBullet;
                    currentBullet = NULL;
                }
            }
         }
     }
}

void MainObject::handleInputAction(SDL_Event e)
{

    if (e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_LEFT:
            {
                rect.x -= step_x;
                if(rect.x < 0) rect.x = 0;
                break;
            }
        case SDLK_RIGHT:
            {
                rect.x += step_x;
                if(rect.x + MAIN_OBJECT_WIDTH > SCREEN_WIDTH) rect.x = SCREEN_WIDTH - MAIN_OBJECT_WIDTH;
                break;
            }
        case SDLK_UP:
            {
                rect.y -= step_y;
                if(rect.y < 0) rect.y = 0;
                break;
            }
        case SDLK_DOWN:
            {
                rect.y += step_y;
                if(rect.y + MAIN_OBJECT_HEIGHT > SCREEN_HEIGHT) rect.y = SCREEN_HEIGHT - MAIN_OBJECT_HEIGHT;
                break;
            }
        case SDLK_KP_ENTER:
            {
                // Tao dan moi
                Bullet* b = new Bullet;
                createBullet(b);
                // Bat am thanh ban dan
                Mix_PlayChannel(-1, soundBullet, 0);

                break;
            }
        case SDLK_RETURN:
            {
                // Tao dan moi
                Bullet* b = new Bullet;
                createBullet(b);
                // Bat am thanh ban dan
                Mix_PlayChannel(-1, soundBullet, 0);

                break;
            }
        default:
            {
                break;
            }
        }

    }
    else if(e.type == SDL_KEYUP)
    {

    }
    else if(e.type == SDL_MOUSEMOTION)
    {
        if(e.motion.x <= SCREEN_WIDTH - MAIN_OBJECT_WIDTH)
        {
           rect.x = e.motion.x;
        }
        if(e.motion.y <= SCREEN_HEIGHT - MAIN_OBJECT_HEIGHT)
        {
            rect.y = e.motion.y;
        }
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        switch(e.button.button)
        {
        case SDL_BUTTON_LEFT:
            {
                // Tao dan moi
                Bullet* b = new Bullet;
                createBullet(b);
                // Bat am thanh ban dan
                Mix_PlayChannel(-1, soundBullet, 0);

                break;
            }
        default:
            {
                break;
            }
        }

    }
    else if(e.type == SDL_MOUSEBUTTONUP)
    {

    }
}

void MainObject::setBulletList(std::vector<Bullet*> _bulletList)
{
    this->bulletList = _bulletList;
}

std::vector<Bullet*> MainObject::getBulletList()
{
    return this->bulletList;
}
