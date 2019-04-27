#include "bullet.h"

Bullet::Bullet()
{
    rect.w = BULLET_WIDTH;
    rect.h = BULLET_HEIGHT;
    step_x = 0;
    step_y = BULLET_HEIGHT / 5;
    isMove = false;
}

Bullet::~Bullet()
{}

void Bullet::handleBulletMovement()
{
    this->rect.y -= 50;
    if(this->rect.y < 0)
    {
        this->isMove = false;
    }
}

void Bullet::handleEnemyBulletMovement()
{
    this->rect.y += step_y;
    if(this->rect.y > SCREEN_HEIGHT + BULLET_HEIGHT)
    {
        this->isMove = false;
    }
}

void Bullet::setStep(float _step_x, float _step_y)
{
    this->step_x = _step_x;
    this->step_y = _step_y;
}

float Bullet::getStepX()
{
    return this->step_x;
}

float Bullet::getStepY()
{
    return this->step_y;
}

bool Bullet::getMoveStatus()
{
    return isMove;
}
void Bullet::setMoveStatus(const bool& moveStatus)
{
    this->isMove = moveStatus;
}



