#include <iostream>
#include <vector>
#include <cstdlib>   //rand, srand
#include <ctime>     //time
#include <algorithm> //max_element

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <chrono>

#include <iomanip>

#define WIDTH 50
#define HEIGHT 100
using namespace std;
const string KReset("0");
const string KNoir("30");
const string KRouge("31");
const string KVert("32");
const string KJaune("33");
const string KBleu("34");
const string KMAgenta("35");
const string KCyan("36");

void Couleur(const string &coul)
{
  cout << "\033[" << coul << "m";
}

struct termios saved_attributes;

void reset_input_mode(void)
{
  tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}
struct pos
{
  unsigned x;
  unsigned y;
};

void set_input_mode(void)
{
  struct termios tattr;
  char *name;

  /* Make sure stdin is a terminal. */
  if (!isatty(STDIN_FILENO))
  {
    fprintf(stderr, "Not a terminal.\n");
    exit(EXIT_FAILURE);
  }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr(STDIN_FILENO, &saved_attributes);
  atexit(reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr(STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON | ECHO); /* Clear ICANON and ECHO. */
  tattr.c_cc[VMIN] = 0;
  tattr.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}
void GotoXY(unsigned X, unsigned Y)
{
  cout << "\033[" << X << ';' << Y << "H";

} // gotoxy()

void ClearScreen()
{
  cout << "\033[H\033[2J";
}

void drawSnake(vector<pos> &tail)
{
  unsigned i(0);
  for (auto iter(tail.begin()); iter < tail.end(); ++iter)
  {
    ++i;
    if (iter == tail.begin())
      Couleur(KJaune);
    else
      Couleur(KVert);

    GotoXY((*iter).x, (*iter).y);
    cout << "██" << endl;
  }
}

void drawArena(const pos &apple)
{
  GotoXY(1, 1);
  cout << "┌" << endl;
  GotoXY(1, HEIGHT);
  cout << "┐" << endl;
  for (unsigned x(2); x < WIDTH; ++x)
  {
    GotoXY(x, 1);
    cout << "│" << endl;
    GotoXY(x, HEIGHT);
    cout << "│" << endl;
  }
  GotoXY(WIDTH, 1);
  cout << "└" << endl;
  GotoXY(WIDTH, HEIGHT);
  cout << "┘" << endl;
  for (unsigned y(2); y < HEIGHT; ++y)
  {
    GotoXY(1, y);
    cout << "─" << endl;
    GotoXY(WIDTH, y);
    cout << "─" << endl;
  }
}

void updateSnake(vector<pos> &tail, const unsigned &direction)
{
  cout << tail.size() << endl;
  for (unsigned i(tail.size() - 1); i > 0; --i)
  {
    tail[i] = tail[i - 1];
  }
  switch (direction)
  {
  case 0:
    tail[0].x -= 2;
    break;
  case 1:
    tail[0].y += 2;
    break;
  case 2:
    tail[0].x += 2;
    break;
  case 3:
    tail[0].y -= 2;
    break;
  default:
    break;
  }
}

int main()
{

  char c;
  double seconds(0);
  auto timer = chrono::steady_clock::now();
  set_input_mode();
  Couleur(KRouge);
  cout << "Rouge" << endl;
  Couleur(KVert);
  cout << "Vert" << endl;
  Couleur(KReset);
  cout << "Retour à la normale" << endl;
  pos apple({8, 8});
  vector<pos>
      tail(1, {5, 5});
  tail.push_back({5, 6});
  tail.push_back({5, 8});
  tail.push_back({5, 10});

  unsigned dir(1);
  while (1)
  {
    timer = chrono::steady_clock::now();
    drawArena(apple);
    updateSnake(tail, dir);
    drawSnake(tail);
    while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timer).count() < 160)
    {
      //Couleur(KReset);
      c = '_';
      read(STDIN_FILENO, &c, 1);
      //cout << c << endl;
      if (c == '\004') /* C-d */
        break;
      //GotoXY(0, 0);

      switch (c)
      {
      case 'A':
        dir = 0;
        break;
      case 'C':
        dir = 1;
        break;
      case 'B':
        dir = 2;
        break;
      case 'D':
        dir = 3;
        break;
      case ' ':
        tail.push_back({200, 200});
        break;
      default:
        break;
      }
      //cout << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timer).count() << endl;
    }

    ClearScreen();
  }

  return EXIT_SUCCESS;
}
