#include "SDL_utils.h"

//*****************************************************
// Các hàm chung về khởi tạo và huỷ SDL

// Xoá và vẽ lại toàn bộ màn hình với 1 hình chữ nhật
void utils::refreshScreen(const SDL_Rect& filled_rect)
{
    // Đặt màu vẽ thành black, xoá màn hình về màu black.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   // black
    SDL_RenderClear(renderer);

    // Đặt màu vẽ về trắng và vẽ hình chữ nhật
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderFillRect(renderer, &filled_rect);

    // Dùng lệnh hiển thị (đưa) hình đã vẽ ra mành hình
   //Khi thông thường chạy với môi trường bình thường ở nhà
    SDL_RenderPresent(renderer);
   //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   //SDL_UpdateWindowSurface(window);
}

SDL_Texture* utils::loadTexture(const std::string &file)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = IMG_Load(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr)
    {
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr)
		{
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else
	{
		logSDLError(std::cout, "LoadIMG");
	}
	return texture;
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), trong khi
* giữ nguyên chiều rộng và cao của ảnh
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
*/
void utils::renderTexture(SDL_Texture *tex, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), với
* chiều rộng và cao mới
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
* @param w: chiều rộng (mới)
* @param h: độ cao (mới)
*/
void utils::renderTexture(SDL_Texture *tex, int x, int y, int w, int h)
{
	// Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    // Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

bool utils::checkCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left1 = object1.x;
    int right1 = object1.x + object1.w;
    int top1 = object1.y;
    int bottom1 = object1.y + object1.h;

    int left2 = object2.x;
    int right2 = object2.x + object2.w;
    int top2 = object2.y;
    int bottom2 = object2.y + object2.h;

    if(bottom1 <= top2)
    {
        return false;
    }
    if(top1 >= bottom2)
    {
        return false;
    }
    if(right1 <= left2)
    {
        return false;
    }
    if(left1 >= right2)
    {
        return false;
    }
    return true;
}

long long int utils::updateHighScore(long long int score)
{
    long long int highScore;
    std::fstream f_highScore;
    f_highScore.open("highScore.txt", std::ios_base::in | std::ios_base::out);
    if(f_highScore.is_open())
    {
        f_highScore >> highScore;
        if(score > highScore)
        {
            highScore = score;
            f_highScore.seekp(0);
            f_highScore << highScore << std::endl;
        }
    }
    else
    {
        highScore = score;
        f_highScore << highScore << std::endl;
    }
    f_highScore.close();
    return highScore;
}

long long int utils::getHighScore()
{
    long long int highScore = 0;
    std::ifstream f_highScore;
    f_highScore.open("highScore.txt");
    if(f_highScore.is_open())
    {
        f_highScore >> highScore;
    }
    return highScore;
}

void utils::setHighScore(long long int _highScore)
{
    std::ofstream f_highScore("highScore.txt", std::ios_base::trunc);
    if(f_highScore.is_open())
    {
        f_highScore << _highScore << std::endl;
    }
}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(int screenWidth, int screenHeight)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init", true);
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr)
    {
        logSDLError(std::cout, "CreateWindow", true);
    }

    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr)
    {
        logSDLError(std::cout, "CreateRenderer", true);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}

void quitSDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


