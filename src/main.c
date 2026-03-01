#include "main.h"

#define TITLE "SSHot" // Window title(may be changed later)
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_FRect current_rect = {0, 0, 0, 0};
bool is_drawing = false;
float start_x, start_y;


int main(void) {
    if (!initialize_window()) {
        return 1; // Exit with error code if initialization fails
    }
    uint8_t is_running = true;
    SDL_Event event;    

    while (is_running) {
        is_running = process_input(&event);
        update();
        render();
    }

    QUIT();
    
    return 0;
}

int initialize_window() {
    if (SDL_Init(SDL_INIT_VIDEO) != true) {
           fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
           return false;
    }
    
    if (SDL_CreateWindowAndRenderer(TITLE,DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer) != true) {
        fprintf(stderr, "Error creating window and renderer: %s\n", SDL_GetError());
        return false;
    }

    if (window == NULL || renderer == NULL) {
        fprintf(stderr, "Error creating window or renderer: %s\n", SDL_GetError());
        return false;
    }

    if (SDL_SetRenderVSync(renderer, 1) != true) {
        fprintf(stderr, "Error enabling VSync: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

uint8_t process_input(SDL_Event *event) {
    while (SDL_PollEvent(event))
        {
            switch (event->type)
            {
              case SDL_EVENT_QUIT:
                    return false;
                    break;
                case SDL_EVENT_KEY_UP:
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (event->key.key == SDLK_ESCAPE || event->key.key == SDLK_Q) {
                        return false;
                    }   
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event->button.button == SDL_BUTTON_LEFT) {
                    is_drawing = true;
                    start_x = event->button.x;
                    start_y = event->button.y;
                    // Initialize rect at click point
                    current_rect.x = start_x;
                    current_rect.y = start_y;
                    current_rect.w = 0;
                    current_rect.h = 0;
                }
                break;

            case SDL_EVENT_MOUSE_MOTION:
                if (is_drawing) {
                    // Calculate width/height based on current mouse pos
                    current_rect.w = event->motion.x - start_x;
                    current_rect.h = event->motion.y - start_y;
                }
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (event->button.button == SDL_BUTTON_LEFT) {
                    is_drawing = false;
                    // Handle "negative" dragging (dragging up/left)
                    if (current_rect.w < 0) {
                        current_rect.x += current_rect.w;
                        current_rect.w = -current_rect.w;
                    }
                    if (current_rect.h < 0) {
                        current_rect.y += current_rect.h;
                        current_rect.h = -current_rect.h;
                    }
                }
                break;
                    break;
            }
        }

    return true;
}

void update() {
    return;
}

void render() {
    // Clear the screen with a color (e.g., black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (is_drawing || (current_rect.w != 0 && current_rect.h != 0)) {
        // Draw the fill (Semi-transparent Blue)
        // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        // SDL_SetRenderDrawColor(renderer, 0, 120, 255, 100);
        // SDL_RenderFillRect(renderer, &current_rect);

        // Draw the outline (Bright Blue)
        SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
        SDL_RenderRect(renderer, &current_rect);
    }

    // Present the rendered frame to the screen
    SDL_RenderPresent(renderer);
    return;
}

void QUIT() { 
    // Destroy renderer, window and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}