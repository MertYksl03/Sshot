#ifndef MOUSE_H
#define MOUSE_H

#include <SDL3/SDL.h>

#include "buttons.h"

void mouse_left_button_down(SDL_Event *event, bool *is_drawing, bool *is_dragging, float *start_x, float *start_y, SDL_FRect *current_rect , Button *buttons[]);
void mouse_motion(SDL_Event *event, bool *is_drawing, bool *is_dragging, float *start_x, float *start_y, SDL_FRect *current_rect);
void mouse_left_button_up(SDL_Event *event, bool *is_drawing, bool *is_dragging, float *start_x, float *start_y, SDL_FRect *current_rect, SDL_FRect *save_button_rect, SDL_FRect *copy_button_rect);

#endif // MOUSE_H