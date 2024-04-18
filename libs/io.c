#include "io.h"
#include <SDL2/SDL_ttf.h>

static SDL_Window *window;
static SDL_Renderer *rend;
static TTF_Font *font;
static int screen_width, screen_height;
static const Uint8* keyboard_state;

void io_init(int w, int h)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    window = SDL_CreateWindow("Tanks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
    rend = SDL_CreateRenderer(window, -1, 0);
    font = TTF_OpenFont("font.ttf", 12);
    keyboard_state = SDL_GetKeyboardState(0);
    screen_width = w;
    screen_height = h;
}

void io_quit(void)
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int io_dialog(const char *message, const char *options)
{
    int btns_len = 1, options_len;
    for (options_len = 0; options[options_len] != 0; ++options_len)
    {
        btns_len += options[options_len] == '|';
    }
    char *buffer = malloc(options_len);
    strcpy(buffer, options);

    SDL_MessageBoxButtonData *btns = malloc(sizeof(SDL_MessageBoxButtonData) * btns_len);
    char *buffer_ptr = buffer;
    for (int i = 0; i < btns_len; ++i)
    {
        btns[i].buttonid = i;
        btns[i].flags = 0;
        btns[i].text = buffer_ptr;
        if (i != btns_len - 1)
        {
            buffer_ptr = strchr(buffer_ptr, '|') + 1;
            buffer_ptr[-1] = '\0';
        }
    }

    SDL_MessageBoxData box;
    box.buttons = btns;
    box.colorScheme = 0;
    box.flags = 0;
    box.message = message;
    box.numbuttons = btns_len;
    box.title = message;
    box.window = 0;
    
    int selected = 0;
    SDL_ShowMessageBox(&box, &selected);
    free(buffer);
    free(btns);

    return selected >= 0 && selected < options_len ? selected : 0;
}

bool io_loop(void)
{
    SDL_Delay(50);
    return !SDL_QuitRequested();
}

void io_message(const char *message)
{
    SDL_ShowSimpleMessageBox(0, message, message, 0);
}

bool io_click(void)
{
    return SDL_GetMouseState(0, 0) == SDL_BUTTON_LEFT;
}

void io_mouse_position(int *x, int *y)
{
    SDL_GetMouseState(x, y);
}


void io_arrows(int *x, int *y)
{
    *x = keyboard_state[SDL_SCANCODE_RIGHT] - keyboard_state[SDL_SCANCODE_LEFT];
    *y = keyboard_state[SDL_SCANCODE_DOWN] - keyboard_state[SDL_SCANCODE_UP];
}

void io_draw_clear(void)
{
    SDL_SetRenderDrawColor(rend, 245, 250, 255, 255);
    SDL_RenderClear(rend);
}

void io_draw_update(void)
{
    SDL_RenderPresent(rend);
}

static const int xp_bar_height = 10;

void io_draw_fighter(int x, int y, int w, int h, int r, int g, int b, float life)
{
    SDL_Rect fighter_rect = {x, y + xp_bar_height, w, h};
    SDL_SetRenderDrawColor(rend, r, g, b, 255);
    SDL_RenderFillRect(rend, &fighter_rect);

	if (life < 1.0)
	{
        SDL_Rect green_rect = {x, y + xp_bar_height, (int)(w * life), 2};
        SDL_SetRenderDrawColor(rend, 10, 190, 0, 255);
        SDL_RenderFillRect(rend, &green_rect);
        SDL_Rect red_rect = {x + green_rect.w, y + xp_bar_height, w - green_rect.w, 2};
        SDL_SetRenderDrawColor(rend, 190, 10, 0, 255);
        SDL_RenderFillRect(rend, &red_rect);
	}
}

void io_draw_xp(int level, float xp)
{
    SDL_Rect area_rect = {0, 0, screen_width, xp_bar_height};
    SDL_SetRenderDrawColor(rend, 190, 190, 190, 255);
    SDL_RenderFillRect(rend, &area_rect);

    SDL_Rect xp_rect = {0, 0, (int)(screen_width * xp), xp_bar_height};
    SDL_SetRenderDrawColor(rend, 100, 255, 0, 255);
    SDL_RenderFillRect(rend, &xp_rect);

    char text_buf[256];
    snprintf(text_buf, 256, "Level: %d", level);
    SDL_Color black = {0, 0, 0, 255};
    SDL_Surface *surface = TTF_RenderText_Blended(font, text_buf, black);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_Rect text_rect = {0, 10, 100, 20};
    text_rect.x += (text_rect.w - surface->w) / 2;
    text_rect.y += (text_rect.h - surface->h) / 2;
    text_rect.w = surface->w;
    text_rect.h = surface->h;
    SDL_RenderCopy(rend, texture, 0, &text_rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
