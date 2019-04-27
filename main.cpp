#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL_utils.h"
#include "baseobject.h"
#include "mainobject.h"
#include "enemy.h"
#include "explosion.h"
#include "button.h"
#include "text.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Air Strike 2D";
unsigned int ENEMY_QUANTITY = 3;

SDL_Window* window;
SDL_Renderer* renderer;

Mix_Chunk* soundBullet = NULL;
Mix_Chunk* soundExplosion = NULL;


int main(int argc, char* argv[])
{
    // Khoi tao man hinh SDL
    initSDL(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Khoi tao TTF
    if(TTF_Init() == -1)
    {
        logSDLError(cout, "TTF_Init", true);
        return -1;
    }

    // Khoi tao Mixer
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        logSDLError(cout, "Mix_OpenAudio", true);
        return -1;
    }

    // Clear render
    SDL_RenderClear(renderer);

    // Khoi tao background
    // Khoi tao background chinh
    SDL_Texture* backGround = utils::loadTexture("images/blueSky.png");
    // Ve background chinh
    utils::renderTexture(backGround, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Khoi tao bien su kien
    SDL_Event e;

    // Khoi tao bien chay chuong trinh
    bool isMenuRunning = true;
    bool isJetAlive = false;
    bool isHighScoreScreenRunning = false;
    bool isInstructorRunning = false;

    // Khoi tao nut bam
    // Nut bam play
    Button startButton;
    startButton.loadImg("images/button-start.png");
    // Nut bam quit
    Button quitButton;
    quitButton.loadImg("images/button-quit.png");
    // Nut bam diem cao
    Button highScoreButton;
    highScoreButton.loadImg("images/button-high-score.png");
    // Nut huong dan
    Button instructorButton;
    instructorButton.loadImg("images/button-instructor.png");
    // Nut quay lai
    Button backButton;
    backButton.loadImg("images/button-back.png");

    // Diem so
    // Khoi tao diem so
    long long int score = 0;
    // Khoi tao diem cao
    long long int highScore = utils::getHighScore();

    // Khoi tao cac thong bao
    // Khoi tao menu title
    Text gameTitle("fonts/arial.ttf", 50, "WELCOME TO AIR STRIKE 2D", RED_COLOR);

    // Khoi tao file am thanh
    soundBullet = Mix_LoadWAV("sound/awp.wav");
    soundExplosion = Mix_LoadWAV("sound/exp1.wav");
    Mix_Music* soundMain = Mix_LoadMUS("sound/wind.wav");
    Mix_Music* soundInGame = Mix_LoadMUS("sound/Avengers.wav");

    // Bat dau game -> Game Menu
    while(isMenuRunning)
    {
        // Ve background
        utils::renderTexture(backGround, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        // Bat nhac nen
        Mix_HaltMusic();
        if(!Mix_PlayingMusic())
        {
            Mix_PlayMusic(soundMain, -1);
        }
        // Dat toa do cho nut bam
        gameTitle.setRect(SCREEN_WIDTH / 2 - gameTitle.getRect().w / 2, 30);
        startButton.setRect(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT);
        highScoreButton.setRect(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2);
        instructorButton.setRect(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + BUTTON_HEIGHT);
        quitButton.setRect(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + BUTTON_HEIGHT * 2);
        // Hien thi nut bam
        gameTitle.show();
        startButton.show();
        highScoreButton.show();
        instructorButton.show();
        quitButton.show();
        // In ra man hinh
        SDL_RenderPresent(renderer);

        // Nhan su kien ban phim o Menu
        while(SDL_PollEvent(&e))
        {
            if(startButton.handleEvent(e))
            {
                isJetAlive = true;
                // Tat hien thi chuot tren man hinh
                SDL_ShowCursor(SDL_DISABLE);
                // Tat am thanh Menu
                Mix_HaltMusic();
                if(!Mix_PlayingMusic())
                {
                   Mix_PlayMusic(soundInGame, -1);
                }


                // Van choi moi
                // Set diem ve 0
                score = 0;

                // Delay 0.5s roi vao game
                SDL_Delay(500);

                // Khoi tao doi tuong chinh cua van choi
                // Khoi tao Nhan vat chinh
                MainObject* jet = new MainObject;
                jet->setRect((SCREEN_WIDTH - MAIN_OBJECT_WIDTH) / 2, (SCREEN_HEIGHT - MAIN_OBJECT_HEIGHT) / 2);
                jet->loadImg("images/jet_red.png");
                jet->show();
                // Khoi tao Doi thu
                vector<Enemy> enemyJets(ENEMY_QUANTITY);
                for(int i = 0; i < ENEMY_QUANTITY; i++)
                {
                    enemyJets[i].setRect(rand() % (SCREEN_WIDTH - ENEMY_WIDTH), - (i + 1) * ENEMY_HEIGHT);
                    enemyJets[i].loadImg("images/enemy.png");
                    enemyJets[i].CreateEnemyBullet();
                }
                // Khoi tao Vu no
                Explosion* exp = new Explosion[4];
                exp[0].loadImg("images/exp0.png");
                exp[1].loadImg("images/exp1.png");
                exp[2].loadImg("images/exp2.png");
                exp[3].loadImg("images/exp3.png");

                // Khoi tao cac nut bam trong Tro choi chinh
                // Khoi tao thanh diem so
                Button scoreButton;
                scoreButton.loadImg("images/button-score.png");

                // Khoi tao cac thong bao trong Tro choi chinh
                // Khoi tao thong bao game over
                Text gameOver("fonts/arial.ttf", 50, "GAME OVER", {0, 0, 255, 255});
                // khoi tao thong bao game pause
                Text gamePause("fonts/arial.ttf", 40, "Game paused, press ESC again to resume", GREEN_COLOR);
                Text gamePause2("fonts/arial.ttf", 40, "press ENTER to go back to main menu", GREEN_COLOR);
                // Khoi tao thong bao diem so
                Text scoreText;

                // Tro choi chinh
                while(isJetAlive)
                {
                    // Delay 10 ms
                    SDL_Delay(1);

                    // Trong khi co su kien
                    while(SDL_PollEvent(&e))
                    {
                        if(e.type == SDL_QUIT)
                        {
                            isMenuRunning = false;
                            isJetAlive = false;
                            break;
                        }
                        else if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                bool isPaused = true;
                                // Hien thi chi dan trong luc pause
                                gamePause.setRect(SCREEN_WIDTH / 2 - gamePause.getRect().w / 2, SCREEN_HEIGHT / 2 - gamePause.getRect().h);
                                gamePause.show();
                                gamePause2.setRect(SCREEN_WIDTH / 2 - gamePause.getRect().w / 2, SCREEN_HEIGHT / 2);
                                gamePause2.show();
                                // In ra man hinh
                                SDL_RenderPresent(renderer);
                                // Pause
                                while(isPaused)
                                {
                                    while(SDL_PollEvent(&e))
                                    {
                                        if(e.type == SDL_KEYDOWN)
                                        {
                                            if(e.key.keysym.sym == SDLK_ESCAPE)
                                            {
                                                isPaused = false;
                                                break;
                                            }
                                            else if(e.key.keysym.sym == SDLK_RETURN)
                                            {
                                                isPaused = false;
                                                isJetAlive = false;
                                                SDL_ShowCursor(SDL_ENABLE);
                                                break;
                                            }
                                            else if(e.key.keysym.sym == SDLK_KP_ENTER)
                                            {
                                                isPaused = false;
                                                isJetAlive = false;
                                                SDL_ShowCursor(SDL_ENABLE);
                                                break;
                                            }
                                        }
                                        else if(e.type == SDL_QUIT)
                                        {
                                            isPaused = false;
                                            isJetAlive = false;
                                            isMenuRunning = false;
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        // Xu ly nhan su kien cho nhan vat chinh
                        jet->handleInputAction(e);

                    }
                    // Hien thi lai background lien tuc
                    utils::renderTexture(backGround, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    // Hien thi nhan vat chinh
                    jet->show();
                    // Xu ly ban dan
                    jet->handleBulletLogic();


                    // Hien thi doi thu
                    for(int i = 0; i < enemyJets.size(); i++)
                    {
                        enemyJets[i].handleEnemyMovement();
                        enemyJets[i].show();
                        enemyJets[i].handleBulletLogic();

                        // Xu ly va cham giua nhan vat chinh va doi thu
                        if(utils::checkCollision(enemyJets[i].getRect(), jet->getRect()))
                        {
                            // Hien thi vu no
                            Explosion* jetExp = new Explosion[4];
                            Explosion* enemyJetExp = new Explosion[4];
                            jetExp = exp;
                            enemyJetExp = exp;
                            for(int j = 0; j < 4; j++)
                            {
                                jetExp[j].setRect(jet->getRect().x + MAIN_OBJECT_WIDTH / 2 - EXPLOSION_WIDTH / 2, jet->getRect().y + MAIN_OBJECT_HEIGHT / 2 - EXPLOSION_HEIGHT / 2);
                                jetExp[j].show();
                                enemyJetExp[j].setRect(enemyJets[i].getRect().x + ENEMY_WIDTH / 2 - EXPLOSION_WIDTH / 2, enemyJets[i].getRect().y + ENEMY_HEIGHT / 2 - EXPLOSION_HEIGHT / 2);
                                enemyJetExp[j].show();
                                Mix_PlayChannel(-1 , soundExplosion, 0);
                                SDL_Delay(20);
                                SDL_RenderPresent(renderer);
                            }
                            // thoat chuong trinh ve menu chinh neu nhan vat chinh chet
                            isJetAlive = false;
                            isMenuRunning = true;
                            SDL_ShowCursor(SDL_ENABLE);
                            // Hien thong bao game over
                            gameOver.setRect(SCREEN_WIDTH / 2 - gameOver.getRect().w / 2, SCREEN_HEIGHT / 2 - gameOver.getRect().h / 2);
                            gameOver.show();
                            // Hien diem so vua choi duoc
                                scoreText.setText("fonts/arial.ttf", 30, to_string(score), RED_COLOR);
                                scoreText.setRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + scoreText.getRect().h);
                                scoreText.show();
                            // In ra man hinh
                            SDL_RenderPresent(renderer);
                            SDL_Delay(2000);
                            break;
                        }

                        // Xu ly va cham giua nhan vat chinh va dan cua doi thu
                        vector<Bullet*> enemyBulletList = enemyJets[i].getBulletList();
                        for(int j = 0; j < enemyBulletList.size(); j++)
                        {
                            Bullet* currentBullet = enemyBulletList[j];
                            if(utils::checkCollision(currentBullet->getRect(), jet->getRect()))
                            {
                                Explosion* jetExp = new Explosion[4];
                                jetExp = exp;
                                for(int j = 0; j < 4; j++)
                                {
                                    jetExp[j].setRect(jet->getRect().x + MAIN_OBJECT_WIDTH / 2 - EXPLOSION_WIDTH / 2, jet->getRect().y + MAIN_OBJECT_HEIGHT / 2 - EXPLOSION_HEIGHT / 2);
                                    jetExp[j].show();
                                    Mix_PlayChannel(-1, soundExplosion, 0);
                                    SDL_Delay(20);
                                    SDL_RenderPresent(renderer);

                                }
                                // thoat chuong trinh ve menu chinh neu nhan vat chinh chet
                                isJetAlive = false;
                                isMenuRunning = true;
                                SDL_ShowCursor(SDL_ENABLE);
                                // Hien thong bao game over
                                gameOver.setRect(SCREEN_WIDTH / 2 - gameOver.getRect().w / 2, SCREEN_HEIGHT / 2 - gameOver.getRect().h / 2);
                                gameOver.show();
                                // Hien diem so vua choi duoc
                                scoreText.setText("fonts/arial.ttf", 30, to_string(score), {255, 0 , 0, 255});
                                scoreText.setRect(SCREEN_WIDTH / 2 - scoreText.getRect().w / 2, SCREEN_HEIGHT / 2 + scoreText.getRect().h);
                                scoreText.show();
                                // Chuc mung khi dat diem cao moi
                                if(score > highScore)
                                {
                                    Text congratzText("fonts/arial.ttf", 30, "CONGRATZ! You made new record.", DEFAULT_COLOR);
                                    congratzText.setRect(SCREEN_WIDTH / 2 - congratzText.getRect().w / 2, SCREEN_HEIGHT / 2 + 2 * congratzText.getRect().h);
                                    congratzText.show();
                                }
                                // In ra man hinh
                                SDL_RenderPresent(renderer);
                                SDL_Delay(1000);
                                break;
                            }
                        }
                        // Xu ly va cham giua dan cua nhan vat chinh va doi thu
                        vector<Bullet*> bulletList = jet->getBulletList();
                        for(int j = 0; j < bulletList.size(); j++)
                        {
                            Bullet* currentBullet = bulletList[j];
                            if(utils::checkCollision(currentBullet->getRect(), enemyJets[i].getRect()))
                            {
                                Explosion* enemyJetExp = new Explosion[4];
                                enemyJetExp = exp;
                                for(int j = 0; j < 4; j++)
                                {
                                    enemyJetExp[j].setRect(enemyJets[i].getRect().x + ENEMY_WIDTH / 2 - EXPLOSION_WIDTH / 2, enemyJets[i].getRect().y + ENEMY_HEIGHT / 2 - EXPLOSION_HEIGHT / 2);
                                    enemyJetExp[j].show();
                                    SDL_Delay(10);
                                    //SDL_RenderPresent(renderer);
                                }
                                score++;
                                enemyJets[i].reset(i);
                                jet->destroyBullet(j);
                                break;
                            }
                        }
                    }

                    // Tang do kho
                    if(score > 0 && score % 2 == 0)
                    {
                        // Tang toc do cho ke thu va dan
                        for(int i = 0; i < enemyJets.size(); i++)
                        {
                            float enemySpeed = enemyJets[i].getStepY();
                            float enemyAccelerator = enemySpeed + 0.005;
                            vector<Bullet*> enemyJetBulletList = enemyJets[i].getBulletList();
                            for(int j = 0; j < enemyJetBulletList.size(); j++)
                            {
                                float enemyBulletSpeed = enemyJetBulletList[j]->getStepY();
                                float enemyBulletAccelerator = enemyBulletSpeed + 0.005;
                                enemyJetBulletList[j]->setStep(0, enemyBulletAccelerator);
                            }
                            enemyJets[i].setStep(0, enemyAccelerator);
                        }
                    }

                    // Hien thi diem so
                    scoreButton.setRect(0, SCREEN_HEIGHT - BUTTON_HEIGHT / 2, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2);
                    scoreButton.show();
                    scoreText.setText("fonts/arial.ttf", 40, to_string(score), LIME_COLOR);
                    scoreText.setRect(BUTTON_WIDTH * 1 / 3, SCREEN_HEIGHT - BUTTON_HEIGHT / 2);
                    scoreText.show();
                    // In ra man hinh
                    SDL_RenderPresent(renderer);
                }

                // Update diem cao
                highScore = utils::updateHighScore(score);
                // Xoa object cua van choi cu
                delete jet;
                enemyJets.clear();
                delete[] exp;

                break;
            }
            else if(quitButton.handleEvent(e))
            {
                isMenuRunning = false;
                isJetAlive = false;
                break;
            }
            else if(highScoreButton.handleEvent(e))
            {
                isHighScoreScreenRunning = true;

                // High Score Screen
                // Khoi tao text diem cao de hien thi
                Text highScoreText("fonts/arial.ttf", 50, "HIGH SCORE", GREEN_COLOR);
                Text highScoreMainText;

                // Khoi tao reset high score button
                Button resetHighScoreButton;
                resetHighScoreButton.loadImg("images/button-reset-high-score.png");

                // Main High Score Screen
                while(isHighScoreScreenRunning)
                {
                    // Hien thi back ground
                    utils::renderTexture(backGround, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    // Hien thi All Time High Score
                    highScoreText.setRect(SCREEN_WIDTH / 2 - highScoreText.getRect().w / 2, 65);
                    highScoreText.show();
                    highScoreMainText.setText("fonts/arial.ttf", 50, to_string(highScore), GREEN_COLOR);
                    highScoreMainText.setRect(SCREEN_WIDTH / 2 - highScoreMainText.getRect().w / 2, SCREEN_HEIGHT / 2 - highScoreMainText.getRect().h / 2);
                    highScoreMainText.show();
                    // Hien thi nut bam reset high score
                    resetHighScoreButton.setRect(SCREEN_WIDTH / 2 - resetHighScoreButton.getRect().w / 2, SCREEN_HEIGHT / 2 + resetHighScoreButton.getRect().h, 300, 97);
                    resetHighScoreButton.show();
                    // Hien thi nut bam quay lai
                    backButton.setRect(0, 0, 180, 65);
                    backButton.show();
                    // In ra man hinh
                    SDL_RenderPresent(renderer);
                    // Xu ly su kien ban phim
                    while(SDL_PollEvent(&e))
                    {
                        if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                isHighScoreScreenRunning = false;
                                break;
                            }
                        }
                        else if(resetHighScoreButton.handleEvent(e))
                        {
                            // Set diem cao ve 0
                            highScore = 0;
                            utils::setHighScore(0);
                            isHighScoreScreenRunning = false;
                            break;
                        }
                        else if(backButton.handleEvent(e))
                        {
                            isHighScoreScreenRunning = false;
                            break;
                        }
                        else if(e.type == SDL_QUIT)
                        {
                            isHighScoreScreenRunning = false;
                            isMenuRunning = false;
                            break;
                        }
                    }
                }
                break;
            }
            else if(instructorButton.handleEvent(e))
            {
                isInstructorRunning = true;
                // Khoi tao va hien thi instructor
                SDL_Texture* instructorBackground = utils::loadTexture("images/background-instructor.png");
                utils::renderTexture(instructorBackground, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                // Hien thi nut bam quay lai
                backButton.setRect(0, 0, 180, 65);
                backButton.show();

                // In ra man hinh
                SDL_RenderPresent(renderer);

                // Instructor Screen
                while(isInstructorRunning)
                {
                    // xu ly su kien ban phim
                    while(SDL_PollEvent(&e))
                    {
                        if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                isInstructorRunning = false;
                                break;
                            }
                        }
                        else if(backButton.handleEvent(e))
                        {
                            isInstructorRunning = false;
                            break;
                        }
                        else if(e.type == SDL_QUIT)
                        {
                            isInstructorRunning = false;
                            isMenuRunning = false;
                            break;
                        }
                    }
                }
            }
            else if(e.type == SDL_QUIT)
            {
                isMenuRunning = false;
                isJetAlive = false;

                break;
            }
        }
    }

    quitSDL();

    return 0;
}
