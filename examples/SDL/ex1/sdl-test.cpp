#include"SDL.h"
#include<iostream>
#include "cmd-switch.hpp"

void rand_pixels(SDL_Texture *tex, SDL_Surface *surface) {
    SDL_LockTexture(tex, 0, &surface->pixels, &surface->pitch);
    for(unsigned int i = 0; i < surface->w; ++i) {
        for(unsigned int z = 0; z < surface->h; ++z) {
            unsigned int *ptr = (unsigned int *)surface->pixels+ (i+z*surface->w);
            *ptr = SDL_MapRGB(surface->format, rand()%255, rand()%255, rand()%255);
        }
    }
    SDL_UnlockTexture(tex);
}

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
    
    SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    
    if(!tex) {
        std::cerr << "Error creating texture..\n";
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(NULL, width, height, 32, 0, 0x00FF0000, 0x0000FF00,0x000000FF,0xFF000000);
    
    if(!surface) {
        std::cerr << "Error creating surface\n";
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
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
        rand_pixels(tex, surface);
        SDL_RenderCopy(ren, tex, 0, 0);
        SDL_RenderPresent(ren);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyTexture(tex);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    SDL_Quit();
    return 0;
}
