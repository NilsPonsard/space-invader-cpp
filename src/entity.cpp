#include <entity.h>

Object::Object(pos position, Vstring texture)
{
    Object::position = position;
    Object::texture = texture;
}

Object::~Object()
{
}

void Object::show()
{
    GotoXY(Object::position.x, Object::position.y);
    std::cout << KBlock << std::endl;
}

const Vstring playerTexture = {
    "    ██   ",
    "██████████",
    "██████████"

};

Player::Player(pos p)
{
    Object(p, playerTexture);
}

void Player::tick()
{
    if (Player::Object::position.x + Player::speed)
    {
    }
}