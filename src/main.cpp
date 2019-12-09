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
#include <entity.h>

#define WIDTH 50
#define HEIGHT 100

using namespace std;

const string KBlock("██");
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
  //char *name;

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

void boucle()
{
  char c = '_';
  auto timer = chrono::steady_clock::now();

  while (true)
  {
    timer = chrono::steady_clock::now();
    /*
     * Affichage des éléments
     */
    while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timer).count() < 100)
    {
      /*
       * commandes
       */

      c = '_';
      read(STDIN_FILENO, &c, 1);
      if (c == '\004') /* C-d */
        break;
      switch (c)
      {
      case ' ':
        cout << "espace" << endl;
        break;
      case 'A':
        cout << "Haut" << endl;
        break;
      case 'C':
        cout << "Droite" << endl;
        break;
      case 'B':
        cout << "Bas" << endl;
        break;
      case 'D':
        cout << "Gauche" << endl;
        break;
      default:
        break;
      }
      //cout << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - timer).count() << endl;
    }

    ClearScreen();
  }
}

int main()
{
  srand(time(NULL));
  set_input_mode();
  boucle();

  return EXIT_SUCCESS;
}
