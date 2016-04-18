//
//  Lblock.h
//  Tetris
//
//  Created by Chris Perreault on 4/17/16.
//  Copyright © 2016 Chris Perreault. All rights reserved.
//

#ifndef Lblock_h
#define Lblock_h


#include "main.h"
#include "Border.h"
#include "Shape.h"
#define GL_GLEXT_PROTOTYPES
#include <GLUT/glut.h>

class LBlock : public Shape{
    
public:
    LBlock();
    ~LBlock();
    
    void draw(int board[22][12]); //Complete, untested
    void moveLeft(int board[22][12]); //Complete, untested
    void moveRight(int board[22][12]); //Complete, untested
    void dropSet(int board[22][12]);
    bool moveDown(int board[22][12]);  //Complete, untested
    void rotate(int board[22][12]);  //Complete, untested
    
private:
    //int X1, Y1, X2, Y2, X3, Y3, X4, Y4;
    bool DROP;  //Says the block can drop
    //bool MOVE;
    bool POSITION1; //Original L shaped position
    bool POSITION2; //Position after one 90 degree clockwise rotation
    bool POSITION3; //Position after two 90 degree clockwise rotations
    bool POSITION4; //Position after three 90 degree clockwise rotations
};

//----------CONSTRUCTOR CODE-----------

LBlock::LBlock(){
    
    //Top square
    X1 = 6;
    Y1 = 2;
    
    //Middle square
    X2 = 6;
    Y2 = 3;
    
    //Bottom left square
    X3 = 6;
    Y3 = 4;
    
    //Bottom right square
    X4 = 7;
    Y4 = 4;
    
    POSITION1 = true; //Block starts in Position 1: L shape
    POSITION2 = false;
    POSITION3 = false;
    POSITION4 = false;
    DROP = true;
}

//----------DESTRUCTOR CODE------------

LBlock::~LBlock(){
    
}

//----------FUNCTION CODE--------------

//Draws the blocks on the board
void LBlock::draw(int board[22][12]){   //*****COMPLETE*****
    board[Y1][X1] = 4;
    board[Y2][X2] = 4;
    board[Y3][X3] = 4;
    board[Y4][X4] = 4;
}

//Moves the block to the left
void LBlock::moveLeft(int board[22][12]){   //*****COMPLETE, UNTESTED*****
    
    //Move left in Position 1
    if(POSITION1 && !POSITION2 && !POSITION3 && !POSITION4)
    {
        if(board[Y1][X1-1] != 0)
        {
            return;
        }
        else if(board[Y2][X2-1] != 0){
            return;
        }
        else if(board[Y3][X3-1] != 0){
            return;
        }
        
        else if(X1 != 1 && X2 != 1 && X3 != 1 && board[Y1][X1-1] == 0 && board[Y2][X2-1] == 0 && board[Y3][X3-1] == 0)
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
    if(!POSITION1 && POSITION2 && !POSITION3 && !POSITION4){
        if(board[Y3][X3-1] != 0){
            return;
        }
        else if(board[Y4][X4-1] != 0){
            return;
        }
        else if(X3 != 1 && X4 != 1 && board[Y3][X3-1] == 0 && board[Y4][X4-1] == 0){
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
    if(!POSITION1 && !POSITION2 && POSITION3 && !POSITION4){
        if(board[Y1][X1-1] != 0){
            return;
        }
        if(board[Y2][X2-1] != 0){
            return;
        }
        else if(board[Y4][X4-1] != 0){
            return;
        }
        else if(X4 != 1 && board[Y4][X4-1] == 0 && board[Y2][X2-1] == 0 && board[Y1][X1-1] == 0){
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
    if(!POSITION1 && !POSITION2 && !POSITION3 && POSITION4){
        if(board[Y1][X1-1] != 0){
            return;
        }
        else if(board[Y2][X2-1] != 0){
            return;
        }
        else if(board[Y4][X4-1] != 0){
            return;
        }
        else if(X1 != 1 && board[Y1][X1-1] == 0 && board[Y2][X2-1] == 0 && board[Y4][X4-1] == 0){
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
void LBlock::moveRight(int board[22][12]){  //*****COMPLETE, UNTESTED*****
    
    //Move right in Position 1
    if(POSITION1 && !POSITION2 && !POSITION3 && !POSITION4)
    {
        if(board[Y1][X1+1] != 0)
        {
            return;
        }
        else if(board[Y2][X2+1] != 0){
            return;
        }
        else if(board[Y4][X4+1] != 0){
            return;
        }
        
        else if(X4 != 11 && board[Y4][X4+1] == 0 && board[Y2][X2+1] == 0 && board[Y1][X1+1] == 0)
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
    if(!POSITION1 && POSITION2 && !POSITION3 && !POSITION4){
        if(board[Y1][X1+1] != 0){
            return;
        }
        else if(board[Y4][X4+1] != 0){
            return;
        }
        else if(X1 != 11 && board[Y1][X1+1] == 0 && board[Y4][X4+1] == 0){
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
    if(!POSITION1 && !POSITION2 && POSITION3 && !POSITION4){
        if(board[Y3][X3+1] != 0){
            return;
        }
        else if(board[Y2][X2+1] != 0){
            return;
        }
        else if(board[Y1][X1+1] != 0){
            return;
        }
        else if(X1 != 11 && X2 != 11 && X3 != 11 && board[Y3][X3+1] == 0 && board[Y2][X2+1] == 0 && board[Y1][X1+1] == 0){
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
    
    //Move left in Position 4
    if(!POSITION1 && !POSITION2 && !POSITION3 && POSITION4){
        if(board[Y3][X3+1] != 0){
            return;
        }
        else if(board[Y4][X4+1] != 0){
            return;
        }
        else if(X3 != 11 && X4 != 11 && board[Y3][X3+1] == 0 && board[Y4][X4+1] == 0){
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

//Sets the block in place
void LBlock::dropSet(int board[22][12]){   //*****COMPLETE, UNTESTED*****
    int n = 1;
    
    //Drop and set into place in Position 1
    if(POSITION1){
        
        //Clear blocks from old spaces
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while(board[Y3 + n][X3] == 0 && board[Y4 + n][X4] == 0){
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
    if(POSITION2){
        //Clear blocks from old spaces
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while(board[Y1 + n][X1] == 0 && board[Y2 + n][X2] && board[Y4 + n][X4] == 0){
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
    if(POSITION3){
        //Clear blocks from old spaces
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while(board[Y4 + n][X4] == 0 && board[Y1 + n][X1] == 0){
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
    if(POSITION4){
        //Clear blocks from old spaces
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while(board[Y1 + n][X1] == 0 && board[Y2 + n][X2] == 0 && board[Y3 + n][X3] == 0){
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

//Moves the block down
bool LBlock::moveDown(int board[22][12]){   //*****COMPLETE, UNTESTED*****
    
    //Move down in Position 1
    if(POSITION1){
        if(board[Y3+1][X3] != 0 || board[Y4+1][X4] != 0){
            return false;
        }
        else if(Y3 != 20 && Y4 != 20 && board[Y3+1][X3] == 0 && board[Y4+1][X4] == 0){
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            Y1 += 1;
            Y2 += 1;
            Y3 += 1;
            Y4 += 1;
        }
    }
    //Move down in Position 2
    else if(POSITION2){
        if(board[Y1+1][X1] != 0 || board[Y2+1][X2] != 0 || board[Y4+1][X4]){
            return false;
        }
        else if(Y1 != 20 && Y2 != 20 && Y4 != 20 && board[Y1+1][X1] == 0 && board[Y2+1][X2] == 0 && board[Y4+1][X4] == 0){
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            Y1 += 1;
            Y2 += 1;
            Y3 += 1;
            Y4 += 1;
        }
    }
    //Move down in Position 3
    else if(POSITION3){
        if(board[Y4+1][X4] != 0 || board[Y1+1][X1] != 0){
            return false;
        }
        else if(Y4 != 20 && Y1 != 20 && board[Y4+1][X4] == 0 && board[Y1+1][X1] == 0){
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            Y1 += 1;
            Y2 += 1;
            Y3 += 1;
            Y4 += 1;
        }
    }
    //Move down in Position 4
    else if(POSITION4){
        if(board[Y1+1][X1] != 0 || board[Y2+1][X2] != 0 || board[Y3+1][X3] != 0){
            return false;
        }
        else if(Y1 != 20 && Y2 != 20 && Y3 != 20 && board[Y1+1][X1] == 0 && board[Y3+1][X3] == 0){
            //Remove blocks from their previous locations
            board[Y1][X1] = 0;
            board[Y2][X2] = 0;
            board[Y3][X3] = 0;
            board[Y4][X4] = 0;
            
            Y1 += 1;
            Y2 += 1;
            Y3 += 1;
            Y4 += 1;
        }
    }
    
    return true;
}

//Rotates the block
void LBlock::rotate(int board[22][12]){ //*****COMPLETE, UNTESTED*****
    
    if(POSITION1 && !POSITION2 && !POSITION3 && !POSITION4){ //If block is in original L position
        /*Block order as follows:   /1/
                                    /2/
                                    /3/ /4/    */
        /*This block's rotations happen on the middle block (2nd block), so there are no movements for
         the 2nd block on rotations*/
        
        //Initial series of checks make sure no blocks are occupying the area it will rotate into
        
        //Check projected rotation path for 1st block
        if(board[Y1][X1+1] != 0 || board[Y1+1][X1+1] != 0){
            return;
        }
        
        //Check projected rotation path for 3rd block
        else if(board[Y3][X3-1] != 0 || board[Y3-1][X3-1] != 0){
            return;
        }
        
        //Check projected rotation path for 4th block - No check for Y4, X4-1 because it is occupied by block 3
        else if(board[Y4][X4-2] != 0){
            return;
        }
        
        //Remove blocks from old positions
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        //Block 1
        Y1 += 1;
        X1 += 1;
        
        //Block 2
        
        
        //Block 3
        Y3 -= 1;
        X3 -= 1;
        
        //Block 4
        X4 -= 2;
        
        //Redraw the blocks in their new positions
        /*board[Y1][X1] = 7;
         board[Y2][X2] = 7;
         board[Y3][X3] = 7;
         board[Y4][X4] = 7;*/
        
        POSITION1 = false;
        POSITION2 = true; //Lets program know that the block is in the 2nd position
    }
    
    else if(!POSITION1 && POSITION2 && !POSITION3 && !POSITION4){ /*The block is in the 2nd position:
                                                                   /3/ /2/ /1/
                                                                   /4/          */
        //Check projected rotation for 1st block
        if(board[Y1+1][X1] != 0 || board[Y1+1][X1-1] != 0){
            return;
        }
        
        //Check projected rotation for 3rd block
        else if(board[Y3-1][X3] != 0 || board[Y3-1][X3+1] != 0){
            return;
        }
        
        //Check projected rotation for 4th block - No check for Y4-1, X4 because it is occupied by block 3
        else if(board[Y4-2][X4] != 0){
            return;
        }
        
        //Remove blocks from old positions
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        //Block 1
        Y1 += 1;
        X1 -= 1;
        
        //2nd block stays in place
        
        //Block 3
        Y3 -= 1;
        X3 += 1;
        
        //Block 4
        Y4 -= 2;
        
        //Redraw the blocks in their new positions
        /*board[Y1][X1] = 7;
         board[Y2][X2] = 7;
         board[Y3][X3] = 7;
         board[Y4][X4] = 7;*/
        
        POSITION2 = false;  //Lets the program know that the block is in the 3rd position
        POSITION3 = true;
    }
    
    else if(!POSITION1 && !POSITION2 && POSITION3 &&!POSITION4){ /*Block is in 3rd position:
                                                                  /4/ /3/
                                                                      /2/
                                                                      /1/   */
        
        //Check projected rotation for 1st block
        if(board[Y1][X1-1] != 0 || board[Y1-1][X1-1] != 0){
            return;
        }
        
        //Check projected rotation for 3rd block
        else if(board[Y3][X3+1] != 0 || board[Y3+1][X3+1] != 0){
            return;
        }
        
        //Check projected rotation for 4th block - No check for Y4, X4+1 because it is occupied by block 3
        else if(board[Y4][X4+2] != 0){
            return;
        }
        
        //Remove blocks from old positions
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        //Block 1
        Y1 -= 1;
        X1 -= 1;
        
        //Block 2 stays in place
        
        //Block 3
        Y3 += 1;
        X3 += 1;
        
        //Block 4
        X4 += 2;
        
        //Redraw the blocks in their new positions
        /*board[Y1][X1] = 7;
         board[Y2][X2] = 7;
         board[Y3][X3] = 7;
         board[Y4][X4] = 7;*/
        
        POSITION3 = false;
        POSITION4 = true; //Lets the program know that the block is in the 4th position
    }
    
    else if(!POSITION1 && !POSITION2 && !POSITION3 && POSITION4){  /*The block is in the 4th position:
                                                                           /4/
                                                                   /1/ /2/ /3/  */
        
        //Check projected rotation for 1st block
        if(board[Y1-1][X1] != 0 || board[Y1-1][X1+1] != 0)
        {
            return;
        }
        
        //check the third block movement
        else if(board[Y3+1][X3] != 0 || board[Y3+1][X3-1] != 0)
        {
            return;
        }
        
        //checking fourth block movement - No check for Y4+1, X4 because it is occupied by block 3
        else if(board[Y4+2][X4] != 0)
        {
            return;
        }
        
        //Remove blocks from old positions
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        //Block 1
        Y1 -= 1;
        X1 += 1;
        
        //Block 2 stays in place
        
        //Block 3
        Y3 += 1;
        X3 -= 1;
        
        //Block 4
        Y4 += 2;
        
        //Redraw the blocks in their new positions
        /*board[Y1][X1] = 7;
         board[Y2][X2] = 7;
         board[Y3][X3] = 7;
         board[Y4][X4] = 7;*/
        
        //Lets the program know that the block is back in position 1
        POSITION1 = true;
        POSITION4 = false;
    }
}


#endif /* Lblock_h */
