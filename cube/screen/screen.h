#ifndef CUBE2_SCREEN_H
#define CUBE2_SCREEN_H

#include "../canvas.h"

class Screen {
public:
    virtual void draw(Canvas *canvas, float elapsed) = 0;

    virtual bool isEmpty() = 0;
};


#endif //CUBE2_SCREEN_H
