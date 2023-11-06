/* CSCI 200: Final Project
 *
 * Author: Jacey Jonson
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * A game modeled after the popular game tetris
 */


#ifndef BLOCK_H
#define BLOCK_H

#include "SFML/Graphics.hpp"
using namespace sf;

class Block {
    public: 
        Block();
        Block(int x, int y);
        Color defineColor();
        int getX() const;
        int getY() const;
        int getRotate() const;
        Color getColor() const;
        void setRotate(const int ROTATE);
        void setX(const int X);
        void setY(const int Y);
        void setColor(const Color COLOR);
    private:
        int x, y;
        int rotate;
        Color color;
};

#endif