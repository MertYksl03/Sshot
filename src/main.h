#include <stdio.h> 

#include <SDL3/SDL.h>

#define SDL_SetRenderDrawColorStruct(renderer, color) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

// Function prototypes
int initialize_window();
uint8_t process_input(SDL_Event *event);
void update();
void render();
void QUIT();
