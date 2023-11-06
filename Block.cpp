/* CSCI 200: Final Project
 *
 * Author: Jacey Jonson
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * A game modeled after the popular game tetris
 */


#include "Block.h"

Block::Block () {
    x = 0;
    y = 0;
}

Block::Block(int x, int y){
    this->x = x;
    this->y = y;
}

Color Block::defineColor(){
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    color = Color(r, g, b);
    return color;
}

int Block::getX() const{
    return x;
}

int Block::getY() const {
    return y;
}

int Block::getRotate() const{
    return rotate;
}

Color Block::getColor() const{
    return color;
}

void Block::setRotate(const int ROTATE){
    this->rotate = ROTATE;
}

void Block::setX(const int X){
    x = X;
}

void Block::setY(const int Y){
    y = Y;
}

void Block::setColor(const Color COLOR){
    color = COLOR;
}

