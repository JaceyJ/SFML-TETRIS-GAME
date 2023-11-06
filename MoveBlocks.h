/* CSCI 200: Final Project
 *
 * Author: Jacey Jonson
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * A game modeled after the popular game tetris
 */

#include <SFML/Graphics.hpp>
#include "Block.h"
using namespace sf;

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <stack>
#include <ctime>
#include <random>
using namespace std;


//=== DRAWING ===========================================================================================
/**
* @brief draws the background grid for the tetris game
* @param window the render window that the grid is draw onto
*/
void drawGrid(RenderWindow& window);

/**
* @brief draws the cluster of blocks for both placed block and current block
* @param active a vector containing squares that make up the blocks
* @param window the render window the blocks are drawn onto
*/
void drawBlocks(vector<Block*>& active, RenderWindow& window);
//=========================================================================================================

//=== BLOCK MANIPULATIONS==================================================================================
/**
* @brief moves the block to the left or right depending on user input
* @param currBlock the current cluster of blocks to be manipulated
* @param X the amount the current block will be translated
*/
void moveBlock(vector<Block*>& currBlock, const int X);
/**
* @brief sets the current block to the new rotated version 
* @param rotations a list containing all rotations for the current block pattern
* @param currBlock vector containing the current block
*/
void rotateBlock(vector<char**>& rotations, vector<Block*>& currBlock, vector<Block*>& placed);
/**
* @brief instantly moves the block in the y direction as far as possible 
* @param currBlock vector containing the current block
* @param placed a vector containing all placed blocks on the screen
*/

void shiftInBounds(vector<Block*>& currBlock, vector<Block*>& placed);

void instantPlace(vector<Block*>& currBlock, const vector<Block*>& placed);
//==========================================================================================================

//=== NEW BLOCKS ===========================================================================================
/**
* @brief uses dfs to find the placement of the blocks in the current shape
* @param BLOCK 2D array containing the orientation and layout of the block in text form
* @param currBlock vector containing the current block
* @param START_X the initial x coordinate that the first piece of the block will be displayed at
* @param START_Y the initial y coordinate that the first piece of the block will be displayed at

*/
void getCurrentBlock(char** BLOCK, vector<Block*>& currBlock, const int START_X, const int START_Y);
/**
* @brief used in the dfs search to see if the index searched would be out of bounds
* @param ROW the current row
* @param COL the current column
* @param R_MAX the number of rows in the 2D array
* @param C_MAX the number of cols in the 2D array
* @return true if the index is in bounds
*/
bool valid(const int ROW, const int COL, const int R_MAX, const int C_MAX);

/**
* @brief adds a block to the current block list in relation to the block before it
* @param currBlock the current cluster of blocks to be manipulated
* @param PREV_X the x value of the previous block
* @param PREV_Y the y value of the previous block
* @param Y the y value of the current block 
* @param X the x value of the current block
* @param START_X the x value of the starting position
* @param START_Y the y value of the starting position
* @param INDEX the index of the block piece in the current block list
*/
void addBlock(vector<Block*>& currBlock, const int PREV_X, const int X, const int PREV_Y, const int Y, const int START_X, const int START_Y, const int INDEX);
/**
* @brief randomly assigns a new block 2D array
* @param rotations vector containing all rotations for the current block
* @param allBlocks a vector containing every block and every rotation
* @return the first rotation of the new random block
*/
char** newBlock(vector<char**>& rotations, vector<vector<char**>> allBlocks);
/**
* @brief sets all parts of the current block to be placed 
* @param currBlock vector containing the current block
* @param placed vector containing all placed blocks on screen
*/
void setPlaced(vector<Block*>& currBlock, vector<Block*>& placed);
/**
* @brief sets the current rotation to be 0 for all part of the current block
* @param currBlock vector containing the current block
*/
void setRotations(vector<Block*>& currBlock);
//==========================================================================================================

//=== VALID POSITION CHECKS ================================================================================
/**
* @brief checks if the current block can move down based on previously placed blocks and the bottom of the grid
* @param currBlock the current cluster of blocks to be manipulated
* @param placed a vector containing blocks that have already been placed
* @return true if the current block is able to move down
*/
bool moveDown(const vector<Block*>& currBlock, const vector<Block*>& placed);
/**
* @brief checks if the current block can move in the x direction
* @param currBlock the current cluster of blocks to be manipulated
* @param X how much the block translates in the x direction
* @return true if the current block is able to move 
*/
bool canMove(const vector<Block*>& currBlock, const int X, const vector<Block*>& placed);
/**
* @brief checks if the current block can move in the x direction
* @param currBlock the current cluster of blocks to be manipulated
* @param X how much the block translates in the x direction
* @return true if the current block is able to move 
*/

bool endGame(const vector<Block*>& placed);
/**
* @brief sets the const values determined in the main in this class
*/
void setMoveBlocksConstants(const int BOX_SIZE, const int WIDTH, const int HEIGHT, const int BUFFERX, const int BUFFERY, const int STARTING_X, const int STARTING_Y);




