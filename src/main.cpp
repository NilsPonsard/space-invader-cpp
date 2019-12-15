#include "graph/rgbcolor.h"
#include "graph/mingl.h"
#include "graph/pos.h"
#include "figs/rectangle.h"
#include "figs/triangle.h"
#include "figs/circle.h"
#include "figs/figure.h"
#include <iostream>
#include <utility>
using namespace std;
typedef pair<int, bool> keyType; // clef, spécial

int main()
{
    minGL Window;
    Window.initGlut();
    Window.initGraphic();
    Window << rectangle({0, 0}, {50, 50}, KBlack, KBlack);
    keyType key;
    while (true)
    {
        key = Window.get_key2();
        if (key.first != 0)
            cout << key.first << ':' << key.second << endl;
    }
    Window.updateGraphic();
    Window.get_key();
    return 0;
}
