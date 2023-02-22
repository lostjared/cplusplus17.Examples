#include"window.hpp"
#include"SDL.h"
#include"SDL_ttf.h"
#include<iostream>
#include<vector>

namespace game {

    struct SDL_RenderObject : public RenderObject {
         SDL_Window *window = NULL;
         SDL_Renderer *ren = NULL;
         std::vector<SDL_Surface *> surfaces;
         std::vector<TTF_Font *> fonts;
         SDL_Texture *tex = NULL;
         SDL_Surface *surface = NULL;
         int width = 0, height = 0;
    
         ~SDL_RenderObject() {
            release_images();

            TTF_Quit();
            SDL_Quit();
         }

        void release_images() {
            for(int i = 0; i < surfaces.size(); ++i) {
                SDL_FreeSurface(surfaces[i]);
                std::cout << "released image index: [" << i << "]\n";
            }
            if(!surfaces.empty())
                surfaces.erase(surfaces.begin(), surfaces.end());

            for(int i = 0; i< fonts.size(); ++i) {
                TTF_CloseFont(fonts[i]);
                std::cout << "released font index: [" << i << "]\n";
            }

            if(!fonts.empty()) 
                fonts.erase(fonts.begin(), fonts.end());
            
        }

        void drawAt(int image, int x, int y) override {
            SDL_Rect rc = { x, y, surfaces[image]->w, surfaces[image]->h };
            SDL_BlitSurface(surfaces[image], 0, surface, &rc);
        }

        void drawAtRect(int image, int x, int y, int w, int h) override {
            SDL_Rect rc = { x, y, w, h };
            SDL_BlitSurface(surfaces[image], 0, surface, &rc);
        }

        void drawAtRect(int image, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
            SDL_Rect rc = { x1, y1, w1, h1 };
            SDL_Rect rc2 = { x2, y2, w2, h2 };
            SDL_BlitSurface(surfaces[image], &rc, surface, &rc2);
        }
        
        void printText(int font, int x, int y, const std::string &text, const Color &col) override {
            SDL_Color col_s = { col.r, col.g, col.b };
            SDL_Surface *surf = TTF_RenderText_Solid(fonts[font], text.c_str(), col_s);
            SDL_Rect rc = { x, y, surf->w, surf->h };
            SDL_BlitSurface(surf, 0, surface, &rc);
            SDL_FreeSurface(surf);
        }
        
        int loadImage(const std::string &text) override {
            SDL_Surface *surface = SDL_LoadBMP(text.c_str());
            if(!surface) {
                std::cerr << "Error could not load surface: " << text << "\n";
                SDL_Quit();
                exit(EXIT_FAILURE);
            }
            surfaces.push_back(surface);
            int index = surfaces.size()-1;
            std::cout << "loaded image [" << text << "] at index: [" << index << "]\n";
            return index;
        }

        int loadFont(const std::string &text, int size) override {
            TTF_Font *font = TTF_OpenFont(text.c_str(), size);
            if(!font) {
                std::cerr << "Error could not load font: " << text << "\n" << SDL_GetError() << "\n";
                TTF_Quit();
                SDL_Quit();
                exit(EXIT_FAILURE);
            }
            fonts.push_back(font);
            int index = fonts.size()-1;
            std::cout << "loaded font [" << text << "] at index: [" << index << "]\n";
            return index;
        }

        void update() {

        }

        bool init(const std::string &text, int w, int h) {
            if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                std::cerr << "Error initaliziing SDL\n";
                return false;
            }

            TTF_Init();

            window = SDL_CreateWindow(text.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
            if(!window) {
                std::cerr << "Error creating window: " << SDL_GetError() << "...\n";
                TTF_Quit();
                SDL_Quit();
                return false;
            }
            ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(!ren) {
                std::cerr << "Error creating Renderer: " << SDL_GetError() << "\n";
                TTF_Quit();
                SDL_Quit();
                return false;
            }

            tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 1280, 720);

            if(!tex) {
                std::cerr << "Could not create texture: " << SDL_GetError() << "\n";
                TTF_Quit();
                SDL_Quit();
                return false;
            }

            surface = SDL_CreateRGBSurfaceFrom(NULL, 1280, 720, 32, w*4, 0x00FF0000, 0x0000FF00,0x000000FF,0xFF000000);

            if(!surface) {
                std::cerr << "Could not create main surface: " << SDL_GetError() << "\n";
                TTF_Quit();
                SDL_Quit();
                return false;
            }

            width = w;
            height = h;
            return true;
        }

        unsigned int getTicks() override {
            return static_cast<unsigned int>(SDL_GetTicks());
        }

        bool keyDown(const Key &c) override {
            const Uint8 *keys = SDL_GetKeyboardState(0);
            switch(c) {
                case Key::KEY_LEFT:
                if(keys[SDL_SCANCODE_LEFT]) return true; 
                break;
                case Key::KEY_RIGHT:
                if(keys[SDL_SCANCODE_RIGHT]) return true;
                break;
                case Key::KEY_UP:
                if(keys[SDL_SCANCODE_UP]) return true;
                break;
                case Key::KEY_DOWN:
                if(keys[SDL_SCANCODE_DOWN]) return true;
                break;
                default:
                return false;
            }
            return false;
        }

    };

    bool Window::active;
    GameObject *Window::current_object = nullptr;
    SDL_RenderObject render_object;

    bool Window::createWindow(const std::string &text, int w, int h) {
        return render_object.init(text, w, h);
    }

    void Window::setObject(GameObject *obj) {
        Window::current_object = obj;
    }

    void Window::init_object(GameObject *obj) {
        obj->init(&render_object);
    }
    int Window::loop() {

        if(current_object == nullptr) {
            std::cerr << "Error must initalize a game object.\n";
            return EXIT_FAILURE;
        }

        SDL_Event e;
        active = true;
        while (active) {
            SDL_RenderClear(render_object.ren);          
            SDL_LockTexture(render_object.tex, 0, &render_object.surface->pixels, &render_object.surface->pitch);
            current_object->draw(&render_object);
            SDL_UnlockTexture(render_object.tex);
            SDL_Rect rc = { 0, 0, render_object.width, render_object.height };
            SDL_RenderCopy(render_object.ren, render_object.tex, 0, &rc);
            SDL_RenderPresent(render_object.ren);
    
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                    active = false;
                    break;
                    case SDL_KEYDOWN:
                        if(e.key.keysym.sym == SDLK_ESCAPE)
                            active = false;
                        current_object->keydown(e.key.keysym.sym);
                    break;
                    case SDL_KEYUP:
                        current_object->keyup(e.key.keysym.sym);
                    break;
                }
            }

        }
        return EXIT_SUCCESS;
    }
}