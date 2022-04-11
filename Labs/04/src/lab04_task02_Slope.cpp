#include "lab04_tasks.hpp"

using namespace cv;
using namespace std;


Slope::Slope(Point pt)
{
    first = new Point(pt.x, pt.y);
    last = NULL;
    XoverY = true;
}

void Slope::setLast(Point pt)
{
    last = new Point(pt.x, pt.y);
    value();
}

float Slope::value()
{
    if (last == NULL)
        return 0.0F;

    int deltaX = last->x - first->x;
    int deltaY = last->y - first->y;

    if (abs(deltaX) > abs(deltaY))
    {
        XoverY = false;
        return (float)deltaY / (float)deltaX;
    }
    else
    {
        XoverY = true;
        return (float)deltaX / (float)deltaY;
    }

    return 0.0;
}

int Slope::getLastX()
{
    if (last == NULL)
        return first->x;
    else
        return last->x;
}

int Slope::getLastY()
{
    if (last == NULL)
        return first->y;
    else
        return last->y;
}

bool Slope::isXoverY()
{
    return XoverY;
}