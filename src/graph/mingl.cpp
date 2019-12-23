#include <map>

#include "mingl.h"

using namespace std;
using namespace nsUtil;

//astuce pour faire passer les handlers en fonction static dans initGraphic ()
namespace
{
map<int, minGL *> anyWindow;

template <typename T, T oHandler>
struct callBackBuilder;

template <typename Obj, typename... Arg, void (Obj::*oHandler)(Arg...)>
struct callBackBuilder<void (Obj::*)(Arg...), oHandler>
{
    static void callback(Arg... arg)
    {
        int current_id = glutGetWindow();
        //cout << "window [" << current_id << "] handler call" << endl;
        auto it = anyWindow.find(current_id);
        if (it != anyWindow.end())
        {
            (it->second->*oHandler)(arg...);
        }
    }
};
} // namespace

#define BIND_CALLBACK(HANDLER) callBackBuilder<decltype(HANDLER), HANDLER>::callback

minGL::minGL(const unsigned &Width, const unsigned &Height, const std::string &Name) : windowWidth(Width),
                                                                                       windowHeight(Height),
                                                                                       windowName(Name)
{
    screenBuffer.resize(Width * Height * 3);
    // initGlut();
    // initGraphic();
}

minGL::~minGL()
{
    auto it = anyWindow.find(glutWindowId);
    if (it != anyWindow.end())
        anyWindow.erase(it);
    stopGaphic();
}

void minGL::updateGraphic()
{
    glutPostRedisplay();
    glutMainLoopEvent();
}

void minGL::clearScreen() throw(myexception)
{
    for (unsigned i(0); i < windowWidth; ++i)
        for (unsigned j(0); j < windowHeight; ++j)
            setPixel(pos(i, j), bgColor);
}
void minGL::setBgColor(const RGBcolor &color)
{
    bgColor = color;
}

void minGL::fullScreen()
{
    unsigned height = windowHeight;
    unsigned width = windowWidth;
    glutFullScreen();
    //glutSetupVideoResizing;
}

void minGL::setPixel(const pos &pos_, const RGBcolor &col) throw(PixelException)
{

    //if (pos_.abs > windowWidth) throw myexception (kErrTooRight);
    //if (pos_.ord > windowHeight) throw myexception (kErrTooHight);
    if (pos_.abs > windowWidth)
        throw PixelException(pos_, col, "Pixel too right");
    if (pos_.ord > windowHeight)
        throw PixelException(pos_, col, "Pixel too high");

    screenBuffer[3 * (pos_.ord * windowWidth + pos_.abs) + 0] = col.Red;
    screenBuffer[3 * (pos_.ord * windowWidth + pos_.abs) + 1] = col.Green;
    screenBuffer[3 * (pos_.ord * windowWidth + pos_.abs) + 2] = col.Blue;
}
void minGL::setPixel2(const pos &pos_, const RGBcolor &col)
{
    /*
        @brief  setPixel, but safe for memory without exceptions, don't draw what is outside the screen
        @author Nils Ponsard$
    */
    if (pos_.abs > windowWidth)
        return;
    if (pos_.ord > windowHeight)
        return;

    screenBuffer[3 * (pos_.ord * windowWidth + pos_.abs) + 0] = col.Red;
    screenBuffer[3 * (pos_.ord * windowWidth + pos_.abs) + 1] = col.Green;
    screenBuffer[3 * (pos_.ord * windowWidth + pos_.abs) + 2] = col.Blue;
}

keyType minGL::get_key()
{
    glutMainLoopEvent();
    keyType key;
    while (keyboardBuffer.size() == 0)
    {
        glutMainLoopEvent();
    }
    key = keyboardBuffer.front();
    keyboardBuffer.pop();
    return (key);
}

/*
    get_key2() ajouté par Nils Ponsard
    permet d'obtenir une touche préssée (sinon le caractère '_' est envoyé)
*/
keyType minGL::get_key2()
{
    glutMainLoopEvent();
    keyType key(0, false);
    if (keyboardBuffer.size() != 0)
    {
        key = keyboardBuffer.front();
        keyboardBuffer.pop();
    }
    return (key);
}

//static void minGL::initGlut()
//{
//    int tmp=0;
//    glutInit(&tmp, NULL);

//}

void minGL::initGraphic()
{

    // Initialisation GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(int(windowWidth), int(windowHeight));
    glutInitWindowPosition(200, 100);

    glutWindowId = glutCreateWindow(windowName.c_str());
    anyWindow[glutWindowId] = this;

    // Initialisation handlers
    glutReshapeFunc(BIND_CALLBACK(&minGL::callReshape));
    glutDisplayFunc(BIND_CALLBACK(&minGL::callDisplay));
    glutKeyboardFunc(BIND_CALLBACK(&minGL::callKeyboard));
    glutKeyboardUpFunc(BIND_CALLBACK(&minGL::callKeyboardUp));
    glutSpecialFunc(BIND_CALLBACK(&minGL::callKeyboardSpecial));
    glutSpecialUpFunc(BIND_CALLBACK(&minGL::callKeyboardUpSpecial));

    // Efface ecran
    clearScreen();

    // Un tour de boucle pour lancer l'affichage
    glutMainLoopEvent();
}

void minGL::stopGaphic()
{
    glutDestroyWindow(glutWindowId);
    glutMainLoopEvent();
}

void minGL::callReshape(int h, int w)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLfloat(windowWidth), 0.0, GLfloat(windowHeight));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, h, w);
}

void minGL::callDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0, 0);
    glDrawPixels(windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, &screenBuffer[0]);
    glFlush();
}

void minGL::callKeyboard(unsigned char k, int x, int y)
{
    //cout << x << ':' << y << ':' << int(key) << endl;
    keyType key(k, false);
    keydown[key] = true;
    keyboardBuffer.push(key);
    // cout << int (key) << endl;
}
void minGL::callKeyboardUp(unsigned char k, int x, int y)
{
    keyType key(k, false);
    keydown[key] = false;
}

void minGL::callKeyboardSpecial(int k, int x, int y)
{
    //cout << x << ':' << y << ':' << k << endl;
    keyType key(k, true);
    keydown[key] = true;
    keyboardBuffer.push(key);
}
void minGL::callKeyboardUpSpecial(int k, int x, int y)
{
    keyType key(k, true);
    keydown[key] = false;
}

unsigned minGL::getWindowWidth() const
{
    return windowWidth;
}

unsigned minGL::getWindowHeight() const
{
    return windowHeight;
}
