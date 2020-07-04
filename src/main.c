#include <math.h> // using for sin and cos 
#include <SDL.h> // graphics lib

#define PI 3.141592653

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct vec2
{
	float x; 
	float y;
};

float plasma_efect(float x, float y, float time)
{
	//variables to collect sin and cos data 
	float v1, v2, v3;
	struct vec2 coor; 
	
	x = -0.05f + (float)x / SCREEN_WIDTH;
	y = -0.05f + (float)y / SCREEN_HEIGHT;
	
	v1 = sin(x * 10 + time);
	v2 = sin(10 * (x * sin(time / 2) + y *cos(time / 3)) + time);
	
	coor.x = x + 0.05f * sin(time / 5);
	coor.y = y + 0.05f * cos(time / 3);
	v3 = sin(sqrt(100 * (coor.x * coor.x + coor.y * coor.y) + 1) + time);
	
	return (v1 + v2 +v3);
}

int main(int argc, char **argv)
{
	//variables used in the while loop
	float time = 0;
	float value = 0;
	int x, y; //omg 0.o
	//variables used in the while loop
	
	
	//for displaying surafecs >.> 
	SDL_Surface *surface = NULL;
	uint8_t *keys = NULL; //keyboard inter... -_-
	//forgot to create pixel buffer lmao
	Uint32 *pixels = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0){ return -1;}
	//this is the display/window
	surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_NOFRAME);
	//getting key events/states 
	keys = SDL_GetKeyState(NULL);
	
	pixels = (Uint32 *) surface->pixels;
	while(1)
	{
		if (keys[SDLK_ESCAPE]) {break;}
		
		//time/seconds since the app started
		time = SDL_GetTicks() * 0.0025f;
		
		for(x = 0; x < surface->w; ++x)
		{
			for(y = 0; y < surface->h; ++y)
			{
				value = plasma_efect(x, y, time);
				
				//ploting pixel
				pixels[x + surface->w * y] = SDL_MapRGB(surface->format, 10 * (sin(value * PI)), 
				                                                         10 * (cos(value * PI)),
																	     0);
			}
		}
		
		//use another surface to create double buffer 
		//to prevent tearing 
		SDL_Flip(surface);
		
		//pump state/events
		SDL_PumpEvents();
	}
	
	//quit SDL 
	SDL_Quit();
	
	//SUCCESS
	return 0;
}