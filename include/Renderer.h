#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h"
#include <SDL2/SDL.h>
#include <string>
#include <utility>

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(const char* title, int width, int height);
    void draw(Game& game);
    void cleanup();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
    int tileSize;

    // Camera view settings
    int viewSizeX;
    int viewSizeY;

    // Drawing functions
    void drawBoard(Board& board, Player& player);
    void drawUI(Player& player);
    void drawTile(std::pair<int,int> pos, char tile, Color color, int screenX, int screenY);
    void setDrawColor(Color color);
    void drawRect(int x, int y, int w, int h, bool filled = true);
    void drawText(const std::string& text, int x, int y);
};

#endif //RENDERER_H