/* CSCI 200: SFML-TETRIS-GAME
 *
 * Author: Jacey Jonson
 *
 * A game modeled after the popular game tetris using SFML
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