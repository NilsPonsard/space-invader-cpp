#include <entity.h>

Object::Object(pos position)
{
    Object::position = position;
}

Object::~Object()
{
}

void Object::show()
{
    GotoXY(Object::position.x, Object::position.y);
    std::cout << KBlock << std::endl;
}

Entity::Entity()
{
}

Entity::~Entity()
{
}

player::player(/* args */)
{
}

player::~player()
{
}
void player::show()
{
}
void player::tick()
{
}