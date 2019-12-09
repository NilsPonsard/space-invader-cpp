
#ifndef ENTITY_H
#define ENTITY_H

class Object
{
private:
    pos position;

public:
    Object(pos position);
    ~Object();
};

class entity
{
private:
public:
    entity();
    ~entity();
    void show();
    void tick();
};

class player : entity
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
