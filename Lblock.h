//
//  Lblock.h
//  Tetris
//
//  Created by Mark Rattray on 3/15/16.
//  Copyright © 2016 mrattray. All rights reserved.
//
#define _DEBUG
#ifndef Lblock_h
#define Lblock_h

//#include "main.h"
//#include "Border.h"
#include "Shape.h"
//#define GL_GLEXT_PROTOTYPES
//#include <GL/freeglut.h>


class Lblock : public Shape
{
public:
    Lblock();
    ~Lblock();
    
    void draw(int board[22][12]);
    void moveLeft(int board[22][12]);
    void moveRight(int board[22][12]);
    void dropSet(int board[22][12]);
    bool moveDown(int board[22][12]);
    void rotate(int board[22][12]);
    
private:
    bool DROP;
    bool MOVE;
    bool POSITION1; //Original position
    bool POSITION2; //Position after one 90 degree clockwise rotation
    bool POSITION3; //Position after two 90 degree clockwise rotations
    bool POSITION4; //Position after three 90 degree clockwise rotations
    int n = 1;
    
};

Lblock::Lblock()
{
    
    //These are for horizontal piece
    X1 = 7;
    Y1 = 1;
    
    X2 = 5;
    Y2 = 2;
    
    X3 = 6;
    Y3 = 2;
    
    X4 = 7;
    Y4 = 2;
    
    
    
    POSITION1 = true;
    POSITION2 = false;
    POSITION3 = false;
    POSITION4 = false;
    DROP = true;
    MOVE = false;
}

Lblock::~Lblock()
{
    
}

void Lblock::draw(int board[22][12])
{
    board[Y1][X1] = 5;
    board[Y2][X2] = 5;
    board[Y3][X3] = 5;
    board[Y4][X4] = 5;
}

void Lblock::moveLeft(int board[22][12])
{
    MOVE = false;
    
    //Move left in Position 1
    if(POSITION1 && !POSITION2 && !POSITION3 && !POSITION4)
    {
        if(board[Y1][X1-1] == 0 && board[Y2][X2-1] == 0)
        {
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            X1 -= 1;
            X2 -= 1;
            X3 -= 1;
            X4 -= 1;
        }
    }
    
    //Move left in Position 2
    if(!POSITION1 && POSITION2 && !POSITION3 && !POSITION4)
    {
        if(board[Y2][X2-1] == 0 && board[Y4][X4-1] == 0 && board[Y3][X3-1] == 0)
        {
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            X1 -= 1;
            X2 -= 1;
            X3 -= 1;
            X4 -= 1;
        }
    }
    
    //Move left in Position 3
    if(!POSITION1 && !POSITION2 && POSITION3 && !POSITION4)
    {
        if(board[Y4][X4-1] == 0 && board[Y1][X1-1] ==0)
        {
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            X1 -= 1;
            X2 -= 1;
            X3 -= 1;
            X4 -= 1;
        }
    }
    
    //Move left in Position 4
    if(!POSITION1 && !POSITION2 && !POSITION3 && POSITION4)
    {
        if(board[Y1][X1-1] == 0 && board[Y3][X3-1] == 0 && board[Y2][X2-1] == 0)
        {
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            X1 -= 1;
            X2 -= 1;
            X3 -= 1;
            X4 -= 1;
        }
    }
}

//Moves the block to the right
void Lblock::moveRight(int board[22][12])
{
    //Move right in Position 1
    if(POSITION1 && !POSITION2 && !POSITION3 && !POSITION4)
    {
        if(board[Y1][X1+1] == 0 && board[Y4][X4+1] == 0)
        {
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            X1 += 1;
            X2 += 1;
            X3 += 1;
            X4 += 1;
        }
    }
    
    //Move right in Position 2
    if(!POSITION1 && POSITION2 && !POSITION3 && !POSITION4)
    {
        if(board[Y1][X1+1] == 0 && board[Y3][X3 + 1] == 0 && board[Y2][X2+1] == 0)
        {
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            X1 += 1;
            X2 += 1;
            X3 += 1;
            X4 += 1;
        }
    }
    
    //Move right in Position 3
    if(!POSITION1 && !POSITION2 && POSITION3 && !POSITION4)
    {
        if(board[Y1][X1+1] == 0 && board[Y2][X2+1] == 0)
        {
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            X1 += 1;
            X2 += 1;
            X3 += 1;
            X4 += 1;
        }
    }
    
    //Move right in Position 4
    if(!POSITION1 && !POSITION2 && !POSITION3 && POSITION4)
    {
        if(board[Y2][X2+1] == 0 && board[Y3][X3+1] == 0 && board[Y4][X4+1] == 0)
        {
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            X1 += 1;
            X2 += 1;
            X3 += 1;
            X4 += 1;
        }
    }
}

//Moves the block down
bool Lblock::moveDown(int board[22][12])
{
    //Move down in Position 1
    if(POSITION1){
        if(board[Y2+1][X2] != 0 || board[Y3+1][X3] != 0 || board[Y4+1][X4] != 0)
        {
#ifdef _DEBUG
            printf("moveDown Pos 1: %d returning false\n", __LINE__);
#endif
            return false;
        }
    }
    //Move down in Position 2
    else if(POSITION2)
    {
        if(board[Y4+1][X4] != 0 || board[Y1+1][X1] != 0)
        {
#ifdef _DEBUG
            printf("moveDown Pos 2: %d returning false\n", __LINE__);
           // printf("The current values[Y4][X4]: %d %d \nThe Next set of values %d %d: ", Y4, X4, (Y4+1), X4);
            
#endif
            return false;
        }
    }
    //Move down in Position 3
    else if(POSITION3)
    {
        if(board[Y2+1][X2] != 0 || board[Y1+1][X1] != 0 || board[Y3+1][X3] != 0)
        {
#ifdef _DEBUG
            printf("moveDown Pos 3: %d returning false\n", __LINE__);
#endif
            return false;
        }
    }
    //Move down in Position 4
    else if(POSITION4)
    {
        if(board[Y1+1][X1] != 0 || board[Y2+1][X2] != 0)
        {

#ifdef _DEBUG
            printf("moveDown Pos 4: %d returning false\n", __LINE__);
#endif
            return false;
        }
    }
    
    board[Y1][X1] = 0;
    board[Y2][X2] = 0;
    board[Y3][X3] = 0;
    board[Y4][X4] = 0;
    
    Y1 += 1;
    Y2 += 1;
    Y3 += 1;
    Y4 += 1;
    return true;
}

//Sets the block in place
void Lblock::dropSet(int board[22][12])
{
    int n = 1;
    
    //Drop and set into place in Position 1
    if(POSITION1)
    {
        //Clear blocks from old spaces
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while(board[Y3 + n][X3] == 0 && board[Y2 + n][X2] == 0 && board[Y4 + n][X4] == 0)
        {
            n++;
        }
        
        //Drop block the correct (maximum possible) number of times
        Y1 += n - 1;
        Y2 += n - 1;
        Y3 += n - 1;
        Y4 += n - 1;
        
        //Stop the block from dropping
        DROP = false;
    }
    
    //Drop and set into place in Position 2
    if(POSITION2)
    {
        //Clear blocks from old spaces
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while(board[Y1 + n][X1] == 0 && board[Y4 + n][X4] == 0)
        {
            n++;
        }
        
        //Drop block the correct (maximum possible) number of times
        Y1 += n - 1;
        Y2 += n - 1;
        Y3 += n - 1;
        Y4 += n - 1;
        
        //Stop the block from dropping
        DROP = false;
    }
    
    //Drop and set into place in Position 3
    if(POSITION3)
    {
        //Clear blocks from old spaces
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while(board[Y4 + n][X4] == 0 && board[Y3 + n][X3] == 0 && board[Y1 + n][X1] == 0)
        {
            n++;
        }
        
        //Drop block the correct (maximum possible) number of times
        Y1 += n - 1;
        Y2 += n - 1;
        Y3 += n - 1;
        Y4 += n - 1;
        
        //Stop the block from dropping
        DROP = false;
    }
    
    //Drop and set into place in Position 4
    if(POSITION4)
    {
        //Clear blocks from old spaces
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while(board[Y1 + n][X1] == 0 && board[Y2 + n][X2] == 0)
        {
            n++;
        }
        
        //Drop block the correct (maximum possible) number of times
        Y1 += n - 1;
        Y2 += n - 1;
        Y3 += n - 1;
        Y4 += n - 1;
        
        //Stop the block from dropping
        DROP = false;
    }
}

//Rotates the block
void Lblock::rotate(int board[22][12])
{
    if(POSITION1)
    {
        /*This block's rotations happen on the 3rd block, so there are no movements for
         the 3rd block on rotations*/
        
        //Initial series of checks make sure no blocks are occupying the area it will rotate into
        
        //Check proLblockected rotation path for 1st block
        if(board[Y1+2][X1] != 0)
        {
            return;
        }
        
        //Check proLblockected rotation path for 2nd block
        else if(board[Y2-1][X2+1] !=0)
        {
            return;
        }
        
        //Check proLblockected rotation path for 4th block
        else if(board[Y4+1][X4-1] != 0) // || board[Y4 + 1][X4] != 0)
        {
            return;
        }
        
        //Remove blocks from old positions
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        //Block 1
        Y1 += 2;
        //X2 += 1;
        
        //Block 2
        Y2 -= 1;
        X2 += 1;
        
        //Block 3 (Y3, X3) stays in place
        
        
        //Block 4
        Y4 += 1;
        X4 -= 1;
        
        POSITION1 = false;
        POSITION2 = true; //Lets program know that the block is in the 2nd position
    }
    
    else if(POSITION2)
    {
        //Check proLblockected rotation for 1st block
        if(board[Y1+2][X1] != 0)
        {
            return;
        }
        
        //Check proLblockected rotation for 2nd block
        else if(board[Y2-1][X2+1] != 0)
        {
            return;
        }
        
        //Check proLblockected rotation for 4th block
        else if(board[Y4][X4-1] != 0 || board[Y1-1][X1-1] != 0)
        {
            return;
        }
        
        //Remove blocks from old positions
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        //Block 1
        X1 -= 2;
       // Y1 -= 2;
        
        //Block 2
        Y2 += 1;
        X2 += 1;
        
        //3rd block stays in place
        
        //Block 4
        Y4 -= 1;
        X4 -= 1;
        
        POSITION2 = false;  //Lets the program know that the block is in the 3rd position
        POSITION3 = true;
    }
    
    else if(POSITION3)
    {
        //Check proLblockected rotation for 1st block
        if(board[Y1][X1-2] != 0)
        {
            return;
        }
        
        //Check proLblockected rotation for 3rd block
        else if(board[Y2+1][X2-1] != 0)
        {
            return;
        }
        
        //Chekc proLblockected rotation for 4th block
        else if(board[Y4-1][X4] != 0 || board[Y4-1][X4+1] != 0)
        {
            return;
        }
        
        //Remove blocks from old positions
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        //Block 1
        //X1 -= 2;
        Y1 -= 2;
        
        //Block 2
        Y2 += 1;
        X2 -= 1;
        
        //Block 3 stays in place
        
        //Block 4
        Y4 -= 1;
        X4 += 1;
        
        POSITION3 = false;
        POSITION4 = true; //Lets the program know that the block is in the 4th position
    }
    
    else if(POSITION4)
    {
        //Check proLblockected rotation for 1st block
        if(board[Y1-2][X1] != 0)
        {
            return;
        }
        
        //check the 2nd blocks movement
        else if(board[Y2-1][X2-1] != 0)
        {
            return;
        }
        
        //checking fourth block movement
        else if(board[Y4][X4+1] != 0 || board[Y4+1][X4+1] != 0)
        {
            return;
        }
        
        //Remove blocks from old positions
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        //Block 1
        //Y1 += 1;
        X1 +=2;
        
        //Block 2
        Y2 -= 1;
        X2 -= 1;
        
        //Block 3 stays in place
        
        //Block 4
        Y4 += 1;
        X4 += 1;
        
        //Lets the program know that the block is back in position 1
        POSITION1 = true;
        POSITION4 = false;
    }
}

#endif /* Lblock_h */