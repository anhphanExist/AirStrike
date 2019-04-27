#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include "SDL_utils.h"
#include "baseobject.h"
#include "bullet.h"
#include <vector>


#define MAIN_OBJECT_HEIGHT 84
#define MAIN_OBJECT_WIDTH 92

class MainObject : public BaseObject
{
private:
    int step_x;
    int step_y;
    std::vector<Bullet*> bulletList;
public:
    MainObject();
    ~MainObject();
    void createBullet(Bullet* b);
    void destroyBullet(const int bulletIndex);
    void handleBulletLogic();
    void handleInputAction(SDL_Event e);
    void setBulletList(std::vector<Bullet*> _bulletList);
    std::vector<Bullet*> getBulletList();
};

#endif // MAINOBJECT_H
