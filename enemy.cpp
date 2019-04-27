#include "enemy.h"

Enemy::Enemy()
{
    rect.w = ENEMY_WIDTH;
    rect.h = ENEMY_HEIGHT;
    step_x = ENEMY_WIDTH / 30;
    step_y = ENEMY_HEIGHT / 30;
}

Enemy::~Enemy()
{}

void Enemy::CreateEnemyBullet()
{
    Bullet* eB = new Bullet;
    eB->loadImg("images/bullet2.png");
    eB->setRect(this->rect.x + ENEMY_WIDTH / 2 - 10, this->rect.y + ENEMY_HEIGHT);
    eB->setMoveStatus(true);

    enemyBulletList.push_back(eB);
}

void Enemy::handleBulletLogic()
{
    for(int i = 0; i < this->enemyBulletList.size(); i++)
    {
        Bullet* currentEnemyBullet = enemyBulletList.at(i);
        if(currentEnemyBullet)
        {
            if(currentEnemyBullet->getMoveStatus())
            {
                currentEnemyBullet->show();
                currentEnemyBullet->handleEnemyBulletMovement();
            }
            else
            {
                currentEnemyBullet->setMoveStatus(true);
                currentEnemyBullet->setRect(this->rect.x + ENEMY_WIDTH / 2 - 10, this->rect.y + ENEMY_HEIGHT);
            }
        }
    }
}

std::vector<Bullet*> Enemy::getBulletList()
{
        return enemyBulletList;
}

void Enemy::handleEnemyMovement()
{
    rect.y += step_y;
    if(rect.y >= SCREEN_HEIGHT)
    {
        rect.y = 0;
        rect.x = rand()%(SCREEN_WIDTH - ENEMY_WIDTH);
    }
}

void Enemy::setStep(float _step_x, float _step_y)
{
    this->step_x = _step_x;
    this->step_y = _step_y;
}

float Enemy::getStepX()
{
    return step_x;
}

float Enemy::getStepY()
{
    return step_y;
}

void Enemy::reset(const int index)
{
    rect.y = - (index + 1) * ENEMY_HEIGHT;
    rect.x = rand() % (SCREEN_WIDTH - ENEMY_WIDTH);
}
