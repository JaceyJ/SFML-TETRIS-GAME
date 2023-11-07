/* CSCI 200: SFML-TETRIS-GAME
 *
 * Author: Jacey Jonson
 *
 * A game modeled after the popular game tetris using SFML
 */

#include "MoveBlocks.h"

//=== CONSTANT VALUES ===========================================================================================
int BOX_SIZE;
int WIDTH;
int HEIGHT;
int BUFFERX;
int BUFFERY;
int STARTING_X; 
int STARTING_Y;

void setMoveBlocksConstants(const int BOX_SIZE_, const int WIDTH_, const int HEIGHT_, const int BUFFERX_, const int BUFFERY_, const int STARTING_X_, const int STARTING_Y_){
    BOX_SIZE = BOX_SIZE_;
    WIDTH = WIDTH_;
    HEIGHT = HEIGHT_;
    BUFFERX = BUFFERX_;
    BUFFERY = BUFFERY_;
    STARTING_X = STARTING_X_;
    STARTING_Y = STARTING_Y_;
}
//=============================================================================================================

// ======= DRAWING =====================================================================================================
void drawGrid(RenderWindow& window){
    //draw larger rect around whole thing to give illusion of a thicker outline on the borders
    RectangleShape outline;
    outline.setPosition(BUFFERX, BUFFERY);
    outline.setSize(Vector2f(WIDTH, HEIGHT));
    outline.setFillColor(Color :: Black);
    outline.setOutlineColor(Color :: White);
    outline.setOutlineThickness(2);
    window.draw(outline);
    //Height: 20 blocks -- Width: 10 blocks
    //draws individual blocks to form the background grid for the tetris game
    for(int i = 0; i < HEIGHT; i = i + BOX_SIZE){
        for(int j = 0; j < WIDTH; j = j + BOX_SIZE){
            RectangleShape box;
            box.setPosition(j + BUFFERX, i + BUFFERY);
            box.setSize(Vector2f(BOX_SIZE, BOX_SIZE));
            box.setFillColor(Color :: Black);
            box.setOutlineColor(Color :: White);
            box.setOutlineThickness(-1);
            window.draw(box); 
        }
    }
}

void drawBlocks(vector<Block*>& block, RenderWindow& window){
    //take in a vector of the active blocks and draw them --> this function doesn't care about block 
    //relationship with eachother, just focuses on individual blocks
    Block* thisBlock;
    for(unsigned int i = 0; i < block.size(); i++){
        thisBlock = block.at(i);
        RectangleShape box;
        box.setPosition(thisBlock->getX(), thisBlock->getY());
        box.setSize(Vector2f(BOX_SIZE, BOX_SIZE));
        box.setFillColor(block.at(i)->getColor()); 
        box.setOutlineColor(Color :: Black);
        box.setOutlineThickness(-2);
        window.draw(box);
    }
}

//=============================================================================================================================

//=== BLOCK MANIPULATIONS =====================================================================================================
void moveBlock(vector<Block*>& currBlock, const int X){
    //for every block piece, sets the x position to the current position + the x translation
    for(unsigned int i = 0; i < currBlock.size(); i++){
        currBlock.at(i)->setX(currBlock.at(i)->getX() + X); 
    }
}

void rotateBlock(vector<char**>& rotations, vector<Block*>& currBlock, vector<Block*>& placed){
    //store the value of the x and y coordinates of the orgin block
    int orginX = currBlock.at(0)->getX();
    int orginY = currBlock.at(0)->getY();
    int rCurr = currBlock.at(0)->getRotate();
    //get the index from rotations of the current block 
    int rNew;
    if(rCurr >= 3){
        rNew = 0;
    } else {
        rNew = rCurr + 1;
    }
    //if the block can rotate without going out of bounds 
    
        //clear currBlock and set new blocks
        getCurrentBlock(rotations.at(rNew), currBlock, orginX, orginY);
        shiftInBounds(currBlock, placed);
        for(unsigned int i = 0; i < currBlock.size(); i++){
            currBlock.at(i)->setRotate(rNew);
        }
    
}

void shiftInBounds(vector<Block*>& currBlock, vector<Block*>& placed){
    int shift;
    if(canMove(currBlock, 0, placed)){
        return;
    } else {
        if(currBlock.at(0)->getX() > (WIDTH + BUFFERX)/2){
            shift = -BOX_SIZE;
        } else {
           shift = BOX_SIZE;
        }
        while(!canMove(currBlock, 0, placed)){
            moveBlock(currBlock, shift);
        }
        
    }
}

void instantPlace(vector<Block*>& currBlock, const vector<Block*>& placed){
    while(moveDown(currBlock, placed)){
        for(unsigned int i = 0; i < currBlock.size(); i++){
            currBlock.at(i)->setY(currBlock.at(i)->getY() + BOX_SIZE);
        }
    }
}

//=========================================================================================================================

//=== NEW BLOCKS ==========================================================================================================

void getCurrentBlock(char** BLOCK, vector<Block*>& currBlock, const int START_X, const int START_Y){  
    currBlock.clear();
    stack<int*> st; //stores coordinates
    stack<int*> past; //stores the coordinates to which block the new block should be related to
    stack<int> index;
    int startX;
    int startY = 0;
    bool isVisited[4][4];
    //finds the starting index of the block
    for(int i = 0; i < 4; i++){ //there is always at least 1 block piece in the top row
        if(BLOCK[0][i] == 'X'){
            startX = i;
            break;
        }
    }
    int start[2] = {startY, startX};
    st.push(start);
    past.push(start);
    index.push(0);
    //uses dfs to search the 2d array and add all the blocks
    while(!st.empty()){
        int* curr = st.top();
        int x = curr[1];
        int y = curr[0];
        int* prev = past.top();
        st.pop();
        past.pop();
        
        //mark the current cell as visited
        isVisited[y][x] = true;
        addBlock(currBlock, prev[1], x, prev[0], y, START_X, START_Y, index.top());
        index.pop();
        
        //push all adjacent cells 
        int adjRow[4] = {1, -1, 0, 0};
        int adjCol[4] = {0, 0, 1, -1};
        for(int i = 0; i < 4; i++){
            int* temp = new int[2];
            temp[0] = y + adjRow[i];
            temp[1] = x + adjCol[i];
            int* addPast = new int[2];
            addPast[0] = y;
            addPast[1] = x;
            if(valid(y + adjRow[i], x + adjCol[i], 4, 4)){
                if(BLOCK[temp[0]][temp[1]] == 'X' && !isVisited[y + adjRow[i]][x + adjCol[i]]){
                    st.push(temp);
                    past.push(addPast);
                    index.push(currBlock.size() - 1);
                }
            }
        }
    }
    //set all blocks to a random color
    Color blockColor = currBlock.at(0)->defineColor();
    for(unsigned int i = 1; i < currBlock.size(); i++){
        currBlock.at(i)->setColor(blockColor);
    }
}

bool valid(const int ROW, const int COL, const int R_MAX, const int C_MAX){
    if(ROW < 0 || COL < 0 || ROW >= R_MAX || COL >= C_MAX){
        return false;
    }
    return true;
}

//=================================================================================================================
void addBlock(vector<Block*>& currBlock, const int PREV_X, const int X, const int PREV_Y, const int Y, const int START_X, const int START_Y, const int INDEX){
    if(currBlock.size() == 0){
            Block* orgin = new Block(START_X, START_Y);
            currBlock.push_back(orgin);
    } else {
        //if not the first block, add the other blocks in relation to the last added block
        Block* next;
        if(PREV_X == X){ 
            if(PREV_Y < Y) { //add down
                next = new Block(currBlock.at((INDEX))->getX(), currBlock.at(INDEX)->getY() + BOX_SIZE);
            } else { //add up
                next = new Block(currBlock.at((INDEX))->getX(), currBlock.at(INDEX)->getY() - BOX_SIZE);
            }
         } else if(PREV_Y == Y){
            if(PREV_X < X) { //add right
                next = new Block(currBlock.at((INDEX))->getX() + BOX_SIZE, currBlock.at(INDEX)->getY());
            } else {
                next = new Block(currBlock.at((INDEX))->getX() - BOX_SIZE, currBlock.at(INDEX)->getY());
            }
        }
        currBlock.push_back(next);
    }
}

char** newBlock(vector<char**>& rotations, vector<vector<char**>> allBlocks){
    rotations.clear();
    //gets a random number for the new block
    int iRand = rand() % (allBlocks.size() - 1) + 1;
    rotations = allBlocks.at(iRand);
    //color = colors.at(iRand);
    return rotations.at(0); //return the original rotation of the new block
}

void setPlaced(vector<Block*>& currBlock, vector<Block*>& placed){
    for(unsigned int i = 0; i < currBlock.size(); i++){
        placed.push_back(currBlock.at(i));
    }
}

void setRotations(vector<Block*>& currBlock){
    for(unsigned int i = 0; i < currBlock.size(); i++){
        currBlock.at(i)->setRotate(0);
    }
}
//=========================================================================================================================

//=== VALID POSITION CHECKS ===============================================================================================
bool moveDown(const vector<Block*>& currBlock, const vector<Block*>& placed){
   //find the lowest y value to check against bounds
   int maxY = 0;
   for(unsigned int i = 0; i < currBlock.size(); i++){
        if(currBlock.at(i)->getY() > maxY){
            maxY = currBlock.at(i)->getY();
        }
   }
   //check to make sure won't go past bottom 
    if(maxY + BOX_SIZE >= HEIGHT + BUFFERY){
        return false;
    }
    //check to make sure it won't hit any placed blocks
    for(unsigned int i = 0; i < currBlock.size(); i++){
        for(unsigned int j = 0; j < placed.size(); j++){
            if(currBlock.at(i)->getY() + BOX_SIZE >= placed.at(j)->getY() && currBlock.at(i)->getX() == placed.at(j)->getX()){
                return false;
            }
        }
    }
    return true;
}

bool canMove(const vector<Block*>& currBlock, const int X, const vector<Block*>& placed){
    //makes sure the block will not move out of bounds from the grid
    for(unsigned int i = 0; i < currBlock.size(); i++){
        if(currBlock.at(i)->getX() + X < BUFFERX || currBlock.at(i)->getX() + X > WIDTH + BUFFERX - BOX_SIZE){
            return false;
        }
        //checks if movement will run into any already placed blocks
        for(unsigned int j = 0; j < placed.size(); j++){
            if(currBlock.at(i)->getY() == placed.at(j)->getY() && currBlock.at(i)->getX() + X == placed.at(j)->getX()){
                return false;
            }
        }
    }
    return true;
}

bool endGame(const vector<Block*>& placed){
    for(unsigned int i = 0; i < placed.size(); i++){
        if(placed.at(i)->getY() >= BUFFERY + BOX_SIZE){
            return true;
        }
    }
    return false;
}

