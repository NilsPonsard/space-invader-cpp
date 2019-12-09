#include <vector>
#include <iostream>

#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#ifndef GUTILS_H
#define GUTILS_H

const std::string KBlock("██");
const std::string KReset("0");
const std::string KNoir("30");
const std::string KRouge("31");
const std::string KVert("32");
const std::string KJaune("33");
const std::string KBleu("34");
const std::string KMAgenta("35");
const std::string KCyan("36");

void set_input_mode(void);
void reset_input_mode(void);
void Couleur(const std::string &coul);
void GotoXY(unsigned X, unsigned Y);
void ClearScreen();

struct pos
{
    int x;
    int y;
};

class termTexture
{
private:
    std::vector<std::string> content;

public:
    termTexture(/* args */);
    ~termTexture();
    void show();
};

#endif