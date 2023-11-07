/* CSCI 200: SFML-TETRIS-GAME
 *
 * Author: Jacey Jonson
 *
 * A game modeled after the popular game tetris using SFML
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

