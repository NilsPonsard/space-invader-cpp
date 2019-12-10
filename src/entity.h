
#include <gameUtils.h>

#ifndef ENTITY_H
#define ENTITY_H

typedef std::vector<std::string> Vstring;

class Object
{
private:
    Vstring texture;

public:
    pos position;
    Object(pos position, Vstring texture);
    ~Object();
    void show();
};

class Player : public Object
{
private:
public:
    unsigned direction;
    int speed;
    Player(pos p);
    ~Player();
    void tick();
};

class Alien1 : public Object
{
private:
public:
    Alien1(pos p);
    ~Alien1();
};
#endif
