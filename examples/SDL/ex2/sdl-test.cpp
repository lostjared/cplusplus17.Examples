#include"SDL.h"
#include<iostream>
#include "cmd-switch.hpp"

int main(int argc, char **argv) {
    int width=1280, height=720;
    try {
        cmd::ArgumentList<std::string> argz(argc, argv);
        std::string w,h;
        argz.require("--width", w, "window width");
        argz.require("--height", h, "Window height");
        width = atoi(w.c_str());
        height = atoi(h.c_str());
    } catch(cmd::ArgExcep<std::string> &e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    
    if(width < 640 || height < 480) {
        std::cout << "error: minimum is 640x480...\n defaulting..\n";
        width = 640;
        height = 480;
    }
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }
    
    SDL_Window *window = SDL_CreateWindow("Hello World Random Pixels", 0, 0, width, height, SDL_WINDOW_SHOWN);
    if(!window) {
        std::cerr << "Error creating window..\n";
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(ren == 0) {
        std::cout << SDL_GetError() << "\n";
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    SDL_Surface *card = SDL_LoadBMP("cardback.bmp");
    if(!card) {
        std::cerr << "Could not load card..\n";
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Texture *tex_card = SDL_CreateTextureFromSurface(ren,card);
    
    bool active = true;
    SDL_Event e;
    
    while(active) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) active = false;
                    break;
                case SDL_QUIT:
                    active = false;
                    break;
            }
        }
        
        SDL_RenderClear(ren);
        SDL_Rect rc1 = { 0, 0, card->w, card->h };
        SDL_RenderCopy(ren, tex_card, 0, &rc1);
        SDL_RenderPresent(ren);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyTexture(tex_card);
    SDL_FreeSurface(card);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
