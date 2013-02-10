#include <stdio.h>
#include <SDL/SDL.h>

SDL_Surface *imgload(char *string)
{
    SDL_Surface *loadedimage = NULL;
    loadedimage = SDL_LoadBMP(string);
    if (loadedimage != NULL){
        SDL_Surface *optimizedimage = NULL;
        optimizedimage = SDL_DisplayFormat(loadedimage);
        SDL_FreeSurface(loadedimage);
        return optimizedimage;
    }
    return NULL;
}



int main (int argc, char * argv[])
{
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Surface *message = NULL;
    message = imgload("/Users/keysi/Documents/SDL"\
            "/Platformer/Platformer/lenna.bmp");
    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
    SDL_BlitSurface(message,NULL,screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(2024);
    SDL_FreeSurface(message);
    SDL_Quit();
    return 0;
}

