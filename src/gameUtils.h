
#ifndef GUTILS_H
#define GUTILS_H
#include <vector>
#include <iostream>
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
};

#endif