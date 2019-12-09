
#include <gameUtils.h>

#ifndef ENTITY_H
#define ENTITY_H

typedef std::vector<std::string> Vstring;

class Object
{
private:
    pos position;

public:
    Object(pos position);
    ~Object();
    void show();
};

class Entity : Object
{
private:
public:
    Entity(pos position);
    ~Entity();
    void tick();
};

class player : Entity
{
private:
    /* data */
public:
    player();
    ~player();
    void show();
    void tick();
};
#endif
