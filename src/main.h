#ifndef MAIN_H
#define MAIN_H

#include <stdio.h> 

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "mouse.h"
#include "buttons.h"

#define SDL_SetRenderDrawColorStruct(renderer, color) SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

// Function prototypes
bool initialize_window();
bool process_input(SDL_Event *event, Button **buttons);
void update();
void render();
void QUIT();

#endif // MAIN_H