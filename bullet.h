#ifndef BULLET_H
#define BULLET_H

#include "SDL_utils.h"
#include "baseobject.h"

#define BULLET_WIDTH 20
#define BULLET_HEIGHT 20

class Bullet : public BaseObject
{
private:
    float step_x;
    float step_y;
    bool isMove;

public:
    Bullet();
    ~Bullet();
    void handleBulletMovement();
    void handleEnemyBulletMovement();
    void setStep(float _step_x, float _step_y);
    float getStepX();
    float getStepY();
    bool getMoveStatus();
    void setMoveStatus(const bool& moveStatus);
};

#endif // BULLET_H
