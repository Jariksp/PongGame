#include <SDL.h>
#include <sstream>
#include <iostream>

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 800;

const int BALL_X = SCREEN_WIDTH/2;
const int BALL_Y = SCREEN_HEIGHT/2;



SDL_Window* gwindow;
SDL_Surface* gScreen = NULL;
SDL_Event ocur;

Uint32 white;


SDL_Rect PlayerPaddle; 
SDL_Rect AIPaddle;
SDL_Rect Ball;
SDL_Rect Center;


int xVel, yVel;

bool PointInRect(int x, int y, SDL_Rect rec)
{

	if (x > rec.x && y > rec.y && x < rec.x + rec.w && y < rec.y + rec.h)
		return true;
	else return false;

}

bool CheckCollission(SDL_Rect r1, SDL_Rect r2)
{
	if (PointInRect(r1.x, r1.y, r2) == true || PointInRect(r1.x + r1.w, r1.y, r2) == true || PointInRect(r1.x, r1.y + r1.h, r2) == true || PointInRect(r1.x + r1.w, r1.y + r1.h, r2) == true)
		return true;
	else return false;

}


int GetRandomNumber(int high, int low)
{
	return rand() % high + low;
}

void ResetBall()
{
	Ball.x = BALL_X;
	Ball.y = BALL_Y;
	
	xVel = GetRandomNumber(1, 1);
	yVel = GetRandomNumber(1, 1);
}

void LoadGame()
{
	SDL_Init;

	gwindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gScreen = SDL_GetWindowSurface(gwindow);

	Center.x = SCREEN_WIDTH/2 - 3;
	Center.y = 0;
	Center.h = SCREEN_HEIGHT;
	Center.w = 6;

	PlayerPaddle.x = 100;
	PlayerPaddle.y = SCREEN_HEIGHT / 2 - PlayerPaddle.x;
	PlayerPaddle.h = 130;
	PlayerPaddle.w = 40;

	AIPaddle.x = 1500;
	AIPaddle.y = SCREEN_HEIGHT / 2 - PlayerPaddle.x;
	AIPaddle.h = 130;
	AIPaddle.w = 40;

	Ball.x = BALL_X;
	Ball.y = BALL_Y;
	Ball.w = 30;
	Ball.h = 30;



	white = SDL_MapRGB(gScreen-> format, 0xFF, 0xFF, 0xFF);

	srand(time_t(NULL));

	ResetBall();


}


void DrawScreen()
{
	SDL_FillRect(gScreen, NULL, 0);
	SDL_FillRect(gScreen, &Center, white);
	SDL_FillRect(gScreen, &PlayerPaddle, white);
	SDL_FillRect(gScreen, &AIPaddle, white);
	SDL_FillRect(gScreen, &Ball, white);

	SDL_UpdateWindowSurface(gwindow);

}



void Logic(SDL_Event ocur)
{


	if (ocur.key.keysym.sym == 'w')
		PlayerPaddle.y -= 20;


	if (ocur.key.keysym.sym == 's')
		PlayerPaddle.y += 20;
	
	if (PlayerPaddle.y < 1)
		PlayerPaddle.y = 1;

	if (PlayerPaddle.y + PlayerPaddle.h >799)
		PlayerPaddle.y = 800 - PlayerPaddle.h;
	

	if (AIPaddle.y + 0.2 * AIPaddle.h > Ball.y + 0.2 * Ball.h)
		AIPaddle.y -= 1;

	if (AIPaddle.y + 0.2 * AIPaddle.h < Ball.y + 0.2 * Ball.h)
		AIPaddle.y += 1;

	if (AIPaddle.y < 1)
		AIPaddle.y = 1;

	if (AIPaddle.y + AIPaddle.h > 799)
		AIPaddle.y = 800 - AIPaddle.h;
	

	Ball.x += xVel;
	Ball.y += yVel;


	if (Ball.y < 1 || Ball.y + Ball.h > 799)
		yVel = -yVel;

	if (Ball.x < 2 || Ball.x + Ball.w > 1598)
		ResetBall();

		
	if (CheckCollission(Ball, PlayerPaddle) == true)
		xVel = -xVel;

	if (CheckCollission(Ball, AIPaddle) == true)
		xVel = -xVel;
		
}

int main(int argv, char* argc[]) 
{

	bool running = true;

	LoadGame();

	while (running)
	{
		SDL_PollEvent(&ocur);

		if (ocur.type == SDL_QUIT)
			running = false;

		if (ocur.key.keysym.sym == SDLK_ESCAPE)
			running = false;

		Logic(ocur);
		DrawScreen();


	}
	SDL_Quit();


	return 0;
}
