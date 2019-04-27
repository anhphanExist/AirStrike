/*
Làm theo tutorial tại:
http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-2-dont-put-everything-in-main
*/
#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};
const SDL_Color DEFAULT_COLOR = BLACK_COLOR;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const char WINDOW_TITLE[];

extern SDL_Window* window;
extern SDL_Renderer* renderer;


namespace utils
{
    void refreshScreen(const SDL_Rect& filled_rect);

    // Hai hàm về texture, lấy nguyên về tutorial tại:
    // http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-2-dont-put-everything-in-main

    // Hàm nạp texture từ file ảnh, để vẽ lên renderer tương ứng
    // SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
    SDL_Texture* loadTexture(const std::string &file);

    // Hàm đưa texture ra renderer (để hiển thị ra màn hình) tại toạ độ (x,y) và giữ nguyên kích cỡ ban đầu của ảnh
    void renderTexture(SDL_Texture *tex, int x, int y);

    // Hàm (cùng trên nhưng khác tham số với hàm ngay trên)
    // đưa texture ra renderer (để hiển thị ra màn hình) tại toạ độ (x,y) và
    // với kích cỡ rộng (w) và cao (h) cho trước.
    // Ảnh sẽ được co dãn (phóng to thu nhỏ) cho khớp kích cỡ này.
    // Đây là hàm không có trong tutorial ban đầu, được sửa từ hàm trong tutorial.
    void renderTexture(SDL_Texture *tex, int x, int y, int w, int h);
    bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2);

    // Xu ly vao ra file luu high score
    long long int updateHighScore(long long int score);
    long long int getHighScore();
    void setHighScore(long long int _highScore);
}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void initSDL(int screenWidth, int screenHeight);

void quitSDL();


#endif // SDL_UTILS_H
