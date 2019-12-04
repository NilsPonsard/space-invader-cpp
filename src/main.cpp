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
  GotoXY(apple.x, apple.y);
  Couleur(KRouge);
  cout << "██" << endl;
}
void dead(vector<pos> &tail)
{
  ClearScreen();
  Couleur(KReset);
  cout << "vous avez perdu, score : " << tail.size() << endl;
  exit(0);
}

void updateSnake(vector<pos> &tail, const unsigned &direction, pos &apple)
{

  if (tail[0].x == apple.x && tail[0].y == apple.y)
  {
    tail.push_back({0, 0});
    unsigned x;
    unsigned y;
    x = (rand() % (WIDTH - 2) + 2) / 2;
    y = (rand() % (HEIGHT - 2) + 2) / 2;
    apple = {x * 2, y * 2};
  }

  cout << tail.size() << endl;
  for (unsigned i(tail.size() - 1); i > 0; --i)
  {
    tail[i] = tail[i - 1];
  }
  switch (direction)
  {
  case 0:
    tail[0].x -= 1;
    break;
  case 1:
    tail[0].y += 2;
    break;
  case 2:
    tail[0].x += 1;
    break;
  case 3:
    tail[0].y -= 2;
    break;
  default:
    break;
  }
  if (tail[0].x < 2 || tail[0].x > WIDTH - 2)
    dead(tail);
  if (tail[0].y < 2 || tail[0].y > HEIGHT - 2)
    dead(tail);
  for (auto iter(tail.begin() + 3); iter < tail.end(); ++iter)
  {
    if ((*iter).x == tail[0].x && (*iter).y == tail[0].y)
      dead(tail);
  }
}

int main()
{
  srand(time(NULL));
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
  vector<pos> tail;
  tail.push_back({6, 4});
  tail.push_back({6, 6});
  tail.push_back({6, 8});
  tail.push_back({6, 10});

  unsigned dir(1);
  unsigned tempdir(1);
  while (1)
  {
    timer = chrono::steady_clock::now();
    drawArena(apple);
    updateSnake(tail, dir, apple);
    drawSnake(tail);
    tempdir = dir;
    while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timer).count() < 100)
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
        if (dir != 2)
          tempdir = 0;
        break;
      case 'C':
        if (dir != 3)

          tempdir = 1;
        break;
      case 'B':
        if (dir != 0)
          tempdir = 2;
        break;
      case 'D':
        if (dir != 1)
          tempdir = 3;
        break;
      default:
        break;
      }
      //cout << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timer).count() << endl;
    }
    dir = tempdir;

    ClearScreen();
  }

  return EXIT_SUCCESS;
}
