#ifndef ENEMY_H
#define ENEMY_H


#include "SDL_utils.h"
#include <vector>
#include "baseobject.h"
#include "bullet.h"

#define ENEMY_WIDTH 130
#define ENEMY_HEIGHT 69

class Enemy : public BaseObject
{
private:
    float step_x;
    float step_y;
    std::vector<Bullet*> enemyBulletList;

public:
    Enemy();
    ~Enemy();
    void CreateEnemyBullet();
    void handleBulletLogic();
    std::vector<Bullet*> getBulletList();
    void handleEnemyMovement();
    void setStep(float _step_x, float _step_y);
    float getStepX();
    float getStepY();
    void reset(const int index);

};

#endif // ENEMY_H


