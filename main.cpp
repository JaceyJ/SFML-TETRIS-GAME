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
#include "MoveBlocks.h"
using namespace sf;

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <stack>
#include <ctime>
#include <random>
using namespace std;


/**
* @brief reads in the file containing tetris blocks and rotations
* @param fileIn the ifstream for reading the file
* @param colors a vector containing the set colors of all blocks
* @return all blocks and all rotations in a vector
*/
vector<vector<char**>> readFile(ifstream& fileIn, vector<int*>& colors);


//=== CONSTANTS ==========================================================================
const int BOX_SIZE = 25;
const int WIDTH = BOX_SIZE * 10;
const int HEIGHT = BOX_SIZE * 20;
const int BUFFERX = 100;
const int BUFFERY = 75;
const int STARTING_X = BUFFERX + (BOX_SIZE ) * 4; 
const int STARTING_Y = BUFFERY;
//========================================================================================

int main() {
    // create a window
    RenderWindow window( VideoMode(640, 640), "SFML Test" );
    //implements constants to other classes
    setMoveBlocksConstants(BOX_SIZE, WIDTH, HEIGHT, BUFFERX, BUFFERY, STARTING_X, STARTING_Y);
    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // perform any file processing once before draw loop begins

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // create an event object once to store future events
    Event event;
    Clock clock;
    float speed = 1.0;
    srand(time(0));
    rand();
    
    vector<vector<char**>> allBlocks;
    vector<Block*> currBlock;
    vector<Block*> placed;
    vector<char**> rotations;
    vector<int*> colors;
    bool keepMoving = true;
    ifstream fileIn;
    allBlocks = readFile(fileIn, colors);
    //get the first 
    getCurrentBlock(newBlock(rotations, allBlocks), currBlock, STARTING_X, STARTING_Y);
    setRotations(currBlock);
    //use this one for testing specific blocks
    // while the window is open
    while( window.isOpen() ) {
        // clear any existing contents
        window.clear();

        /////////////////////////////////////
        // BEGIN DRAWING HERE
        drawGrid(window);
        drawBlocks(currBlock, window);
        drawBlocks(placed, window);
        //  END  DRAWING HERE
        /////////////////////////////////////
         
        // display the current contents of the window
        window.display();
        
        if(clock.getElapsedTime().asSeconds() > speed){
        for(unsigned int i = 0; i < currBlock.size(); i++){
            currBlock.at(i)->setY(currBlock.at(i)->getY() + BOX_SIZE);
            if(!moveDown(currBlock, placed)){
                keepMoving = false;
            }
        }
        if(!keepMoving){
            setPlaced(currBlock, placed);
            char** temp = newBlock(rotations, allBlocks);
            getCurrentBlock(temp, currBlock, STARTING_X, STARTING_Y);
            setRotations(currBlock);
            keepMoving = true;
        }
        clock.restart();
    }
        /////////////////////////////////////
        // BEGIN EVENT HANDLING HERE
        // check if any events happened since the last time checked
        while( window.pollEvent(event) ) {
            // if event type corresponds to pressing window X
            if(event.type == Event::Closed) {
                // tell the window to close
                window.close();
            }
             if ((event.type == Event::KeyReleased)){
                speed = 1.0;
             }
            // check addition event types to handle additional events
           if (Keyboard::isKeyPressed(Keyboard::Left)){
                // left key is pressed: move our character
                if(canMove(currBlock, -BOX_SIZE, placed)){
                    moveBlock(currBlock, -BOX_SIZE);
                }
            } else if(Keyboard::isKeyPressed(Keyboard::Right)){
                if(canMove(currBlock, BOX_SIZE, placed)){
                    moveBlock(currBlock, BOX_SIZE);
                }  
            } else if(Keyboard::isKeyPressed(Keyboard::Up)){ //automatically place block at location
                //might have to add bounds?
                rotateBlock(rotations, currBlock, placed);
            } else if(Keyboard::isKeyPressed(Keyboard::Down)){
                speed = 0.1;
            } else if(Keyboard::isKeyPressed(Keyboard::Space)){
                /*
                instantPlace(currBlock, placed);
                setPlaced(currBlock, placed);
                getCurrentBlock(newBlock(rotations, allBlocks), currBlock, STARTING_X, STARTING_Y);
                setRotations(currBlock);  */

            }

        
        //  END  EVENT HANDLING HERE
     }   /////////////////////////////////////
    }

    return 0;
}

vector<vector<char**>> readFile (ifstream& fileIn, vector<int*>& colors){
    //vector containing all overarching shapes --> array of 2d arrays with each shape and all rotations
        fileIn.open("data/blocks.txt"); 
        if(fileIn.fail()){
            cout << "Failed to Open" << endl;
        }
        
        string x;
        queue<string> file;
        vector<char**> blockGroup;
        vector<vector<char**>> allBlocks;
        //create a new 2D arry to store rotation
        char** arr = new char*[4];
        for(int i = 0; i < 4; i++){
            arr[i] = new char[4];
        }

        while(!fileIn.eof()){
           fileIn >> x;
           file.push(x);
        }
        
        while(file.size() > 1){ //{color, row1, row2, row3, row4}
                //get the color from the list
                int* newColor = new int[3];
                newColor[0] = stoi(file.front());
                file.pop();
                newColor[1] = stoi(file.front());
                file.pop();
                newColor[2] = stoi(file.front());
                file.pop();
               
                colors.push_back(newColor);
                //read in the next 4 rotations
                for(int i = 0; i < 4; i++){
                    char** arr = new char*[4];
                    for(int i = 0; i < 4; i++){
                        arr[i] = new char[4];
                    }
                    
                    for(int i = 0; i < 4; i++){ //reads in 4 lines 
                        x = file.front(); 
                        file.pop();
                        for(unsigned int j = 0; j < x.size(); j++){ //reads individual components of lines
                            arr[i][j] = x.at(j);
                        }
                    }
                    //add the array to the block group
                    
                    blockGroup.push_back(arr);
                }

                //add the blockGroup of all 4 rotations to the list with all blocks
                
                allBlocks.push_back(blockGroup);
                blockGroup.clear();
        }
        return allBlocks;
        
}