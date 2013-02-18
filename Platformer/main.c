#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <stdbool.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480
#define SCREEN_BPP  32

SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;

SDL_Event event;

SDL_Surface *load_image(char *string)
{
    SDL_Surface *loadedimage = NULL;
    loadedimage = IMG_Load(string);
    SDL_Surface *optimizedimage = NULL;
    if (loadedimage != NULL){
        optimizedimage = SDL_DisplayFormat(loadedimage);
        SDL_FreeSurface(loadedimage);
                
    }
    return optimizedimage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
        return false;    
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL ){
        return false;    
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Event test", NULL );
    
    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the image
    image = load_image( "/Users/keysi/Documents/SDL/"
                       "Platformer/Platformer/character.png" );
    
    //If there was an error in loading the image
    if( image == NULL ){
        return false;    
    }
    
    //If everything loaded fine
    return true;    
}

void clean_up()
{
    //Free the image
    SDL_FreeSurface( image );
    //Quit SDL
    SDL_Quit();    
}

int main (int argc, char * argv[])
{
    bool quit = false;
    //Initialize
    if( init() == false )
        return 1;    
    if( load_files() == false )
        return 1;    
    //Apply the surface to the screen
    apply_surface( 0, 0, image, screen );
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
        return 1;    
    while( quit == false ){
        while( SDL_PollEvent( &event ) ){
            //If the user has Xed out the window
            if( event.type == SDL_QUIT ){
                //Quit the program
                quit = true;
            }   
        }
    }
    clean_up();
    return 0;
}

