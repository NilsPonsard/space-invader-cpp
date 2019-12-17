/*
    @file: main.cpp
    @brief : point d'entrée du jeu
*/

#include "graph/rgbcolor.h"
#include "graph/mingl.h"
#include "graph/pos.h"
#include "figs/rectangle.h"
#include "figs/triangle.h"
#include "figs/circle.h"
#include "figs/figure.h"
#include <iostream>
#include <utility>
#include <chrono>

#define WIDTH 800
#define HEIGHT 600
#define PIXELSIZE 20

using namespace std;
//typedef pair<int, bool> keyType; // clef, spécial
const keyType UP({101, true});
const keyType DOWN({103, true});
const keyType LEFT({100, true});
const keyType RIGHT({102, true});
const keyType ESCAPE({27, false});

const unsigned frameRate(60);
const unsigned frameTime(1000 / frameRate);

typedef vector<int> pixelArray;
typedef vector<pixelArray> pixelMatrix;

const pixelMatrix playerPixels = {
    {0, 0, 1, 0, 0},
    {1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1}};

struct position
{
    int x;
    int y;
};

// affichage de rectangle sans faire crash
void drawRectClipping(minGL &Window, position posStart, position posEnd, const RGBcolor col)
{
    int height = Window.getWindowHeight();
    int width = Window.getWindowWidth();
    posStart.y = (-1 * posStart.y + height);
    posEnd.y = (-1 * posEnd.y + height);
    posStart.x = min(posStart.x, width);
    posStart.x = max(posStart.x, 0);
    posStart.y = min(posStart.y, height);
    posStart.y = max(posStart.y, 0);
    posEnd.x = min(posEnd.x, width);
    posEnd.x = max(posEnd.x, 0);
    posEnd.y = min(posEnd.y, height);
    posEnd.y = max(posEnd.y, 0);
    Window << rectangle({posStart.x, posStart.y}, {posEnd.x, posEnd.y}, col, col);
}
void drawPlayer(minGL &Window, position pos)
{
    for (int j(0); j < playerPixels.size(); ++j)
    {
        for (int i(0); i < playerPixels[j].size(); ++i)
        {
            if (playerPixels[j][i] != 0)
                drawRectClipping(Window, {pos.x + i * PIXELSIZE, pos.y + j * PIXELSIZE}, {pos.x + (i + 1) * PIXELSIZE, pos.y + (j + 1) * PIXELSIZE}, KBlack);
        }
    }
}

int main()
{
    cout << frameTime << endl;
    int x = 0;
    int y = 0;
    auto timer = chrono::steady_clock::now();
    minGL Window(WIDTH, HEIGHT, "jeu");
    Window.initGlut();
    Window.initGraphic();
    keyType key;
    bool boucle(true);
    //Window.fullScreen();

    Window.setBgColor(KGreen);
    while (boucle) // boucle du jeu
    {
        timer = chrono::steady_clock::now();
        Window.clearScreen();
        // gestion de l'affichage
        //cout << Window.keydown[RIGHT] << endl;
        if (Window.keydown[ESCAPE]) // stopper si la touche échap est pressée
            boucle = false;
        if (Window.keydown[RIGHT])
            x += 5;
        if (Window.keydown[LEFT])
            x -= 5;
        if (Window.keydown[DOWN])
            y += 5;
        if (Window.keydown[UP])
            y -= 5;
        drawPlayer(Window, {x, y});

        Window.updateGraphic();

        while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timer).count() < frameTime)
        {
            /*
            key = Window.get_key2();
            if (key.first != 0)
                cout << key.first << " : " << key.second << endl;*/
        }
    }
    return 0;
}
