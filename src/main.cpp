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
#include <gameUtils.h>

#define WIDTH 50
#define HEIGHT 100

using namespace std;

void boucle()
{
  Object test({6, 6});
  char c = '_';
  auto timer = chrono::steady_clock::now();

  while (true)
  {
    timer = chrono::steady_clock::now();
    /*
     * Affichage des éléments
     *
     */
    test.show();
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
