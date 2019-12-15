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

using namespace std;
typedef pair<int, bool> keyType; // clef, spécial

struct position
{
    int x;
    int y;
};

// affichage de rectangle sans faire crash
void drawRectClipping(minGL &Window, position posStart, position posEnd, const RGBcolor col)
{
    posStart.y = (-1 * posStart.y + HEIGHT);
    posEnd.y = (-1 * posEnd.y + HEIGHT);
    posStart.x = min(posStart.x, WIDTH);
    posStart.x = max(posStart.x, 0);
    posStart.y = min(posStart.y, HEIGHT);
    posStart.y = max(posStart.y, 0);
    posEnd.x = min(posEnd.x, WIDTH);
    posEnd.x = max(posEnd.x, 0);
    posEnd.y = min(posEnd.y, HEIGHT);
    posEnd.y = max(posEnd.y, 0);
    Window << rectangle({posStart.x, posStart.y}, {posEnd.x, posEnd.y}, col, col);
}

int main()

{
    int x = 0;
    int y = 0;
    auto timer = chrono::steady_clock::now();
    minGL Window(WIDTH, HEIGHT, "jeu");
    Window.initGlut();
    Window.initGraphic();
    keyType key;
    bool boucle(true);
    while (boucle) // boucle du jeu
    {
        Window.clearScreen();
        timer = chrono::steady_clock::now();
        // gestion de l'affichage
        drawRectClipping(Window, {x, y}, {x + 50, y + 50}, KBlack);

        Window.updateGraphic();

        while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timer).count() < 100)
        {
            key = Window.get_key2();
            //gestion des commandes
            if (key.first != 0) // si une touche a été pressée
            {
                cout << key.first << ':' << key.second << endl;
                if (key.first == 27 && key.second == false) // stopper si la touche échap est pressée
                    boucle = false;
                if (key.first == 102 && key.second == true)
                    x += 20;
            }
        }
    }
    return 0;
}
