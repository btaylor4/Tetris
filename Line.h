//
//  Line.h
//  Function Pointers
//
//  Created by Bryan Taylor on 3/18/16.
//  Copyright © 2016 Bryan Taylor. All rights reserved.
//


#ifndef Line_h
#define Line_h

#include "Shape.h"


class Line : public Shape
{
public:
    Line();
    ~Line();
    
    void draw(int board[22][12]);
    void moveLeft(int board[22][12]);
    void moveRight(int board[22][12]);
    void dropSet(int board[22][12]);
    void rotate(int board[22][12]);
    void ghost(int board[22][12]);
    bool moveDown(int board[22][12]);
    
private:
    bool DROP;
    bool ROTATE1;
    bool ROTATE2;
    bool ROTATE3;
    bool GHOST;
    bool GEN;
    
};

Line::Line()
{
    //These coordinates are to generate the part horizontally
    X1 = 5;
    Y1 = 1;
    
    X2 = 6;
    Y2 = 1;
    
    X3 = 7;
    Y3 = 1;
    
    X4 = 8;
    Y4 = 1;
    
    ROTATE1 = false;
    ROTATE2 = false;
    ROTATE3 = false;
    DROP = false;
    GEN = false;
}

Line::~Line()
{
    
}

void Line::draw(int board[22][12])
{
    if(!GEN && (board[Y1][X1] != 0 || board[Y2][X2] != 0 || board[Y3][X3] != 0 || board[Y4][X4] != 0))
    {
        X1 = -1;
    }
    
    else
    {
        board[Y1][X1] = 2;
        board[Y2][X2] = 2;
        board[Y3][X3] = 2;
        board[Y4][X4] = 2;
        
        GEN = true;
    }
}

void Line::moveLeft(int board[22][12])
{
    if(DROP)
    {
        return;
    }
    
    if(!ROTATE1 && !ROTATE2 && !ROTATE3) //position 1
    {
        if(board[Y1][X1-1] != 0)
        {
            return;
        }
        
        else if(X1 != 1 && board[Y1][X1-1] == 0)
        {
            X1 = X1 - 1;
            board[Y1][X1+1] = 0;
            
            X2 = X2 - 1;
            board[Y2][X2+1] = 0;
            
            X3 = X3 - 1;
            board[Y3][X3+1] = 0;
            
            X4 = X4 - 1;
            board[Y4][X4+1] = 0;
        }
    }
    
    else if (ROTATE1 && !ROTATE2 && !ROTATE3) //position 2
    {
        if(board[Y1][X1-1] != 0 || board[Y2][X2-1] != 0 || board[Y3][X3-1] != 0 || board[Y4][X4-1] != 0)
        {
            return;
        }
        
        else if(X1 != 1 && board[Y1][X1-1] == 0 && board[Y2][X2-1] == 0 && board[Y3][X3-1] == 0 && board[Y4][X4-1] == 0)
        {
            X1 = X1 - 1;
            board[Y1][X1+1] = 0;
            
            X2 = X2 - 1;
            board[Y2][X2+1] = 0;
            
            X3 = X3 - 1;
            board[Y3][X3+1] = 0;
            
            X4 = X4 - 1;
            board[Y4][X4+1] = 0;
        }
    }
    
    else if (ROTATE1 && ROTATE2 && !ROTATE3) //position 3
    {
        if(board[Y4][X4-1] != 0)
        {
            return;
        }
        
        else if(X4 != 1 && board[Y4][X4-1] == 0)
        {
            X1 = X1 - 1;
            board[Y1][X1+1] = 0;
            
            X2 = X2 - 1;
            board[Y2][X2+1] = 0;
            
            X3 = X3 - 1;
            board[Y3][X3+1] = 0;
            
            X4 = X4 - 1;
            board[Y4][X4+1] = 0;
        }
    }
    
    else if (ROTATE1 && ROTATE2 && ROTATE3) //position 4
    {
        if(board[Y1][X1-1] != 0 || board[Y2][X2-1] != 0 || board[Y3][X3-1] != 0 || board[Y4][X4-1] != 0)
        {
            return;
        }
        
        else if(X1 != 1 && board[Y1][X1-1] == 0 && board[Y2][X2-1] == 0 && board[Y3][X3-1] == 0 && board[Y4][X4-1] == 0)
        {
            X1 = X1 - 1;
            board[Y1][X1+1] = 0;
            
            X2 = X2 - 1;
            board[Y2][X2+1] = 0;
            
            X3 = X3 - 1;
            board[Y3][X3+1] = 0;
            
            X4 = X4 - 1;
            board[Y4][X4+1] = 0;
        }
    }
}

void Line::moveRight(int board[22][12])
{
    if(DROP)
    {
        return;
    }
    
    if(!ROTATE1 && !ROTATE2 && !ROTATE3) //position 1
    {
        if(board[Y4][X4+1] != 0)
        {
            return;
        }
        
        else if(X4 != 11 && board[Y4][X4+1] == 0)
        {
            X1 = X1 + 1;
            board[Y1][X1-1] = 0;
            
            X2 = X2 + 1;
            board[Y2][X2-1] = 0;
            
            X3 = X3 + 1;
            board[Y3][X3-1] = 0;
            
            X4 = X4 + 1;
            board[Y4][X4-1] = 0;
        }
    }
    
    else if(ROTATE1 && !ROTATE2 && !ROTATE3) //position 2
    {
        if(board[Y4][X4+1] != 0 || board[Y3][X3+1] != 0 || board[Y2][X2+1] != 0 || board[Y1][X1+1] != 0)
        {
            return;
        }
        
        else if(X4 != 11 && board[Y4][X4+1] == 0 && board[Y3][X3+1] == 0 && board[Y2][X2+1] == 0 && board[Y1][X1+1] == 0)
        {
            X1 = X1 + 1;
            board[Y1][X1-1] = 0;
            
            X2 = X2 + 1;
            board[Y2][X2-1] = 0;
            
            X3 = X3 + 1;
            board[Y3][X3-1] = 0;
            
            X4 = X4 + 1;
            board[Y4][X4-1] = 0;
        }
    }
    
    else if(ROTATE1 && ROTATE2 && !ROTATE3) //position 3
    {
        if(board[Y1][X1+1] != 0)
        {
            return;
        }
        
        else if(X1 != 11 && board[Y1][X1+1] == 0)
        {
            X1 = X1 + 1;
            board[Y1][X1-1] = 0;
            
            X2 = X2 + 1;
            board[Y2][X2-1] = 0;
            
            X3 = X3 + 1;
            board[Y3][X3-1] = 0;
            
            X4 = X4 + 1;
            board[Y4][X4-1] = 0;
        }
    }
    
    else if(ROTATE1 && ROTATE2 && ROTATE3) //position 4
    {
        if(board[Y4][X4+1] != 0 || board[Y3][X3+1] != 0 || board[Y2][X2+1] != 0 || board[Y1][X1+1] != 0)
        {
            return;
        }
        
        else if(X4 != 11 && board[Y4][X4+1] == 0 && board[Y3][X3+1] == 0 && board[Y2][X2+1] == 0 && board[Y1][X1+1] == 0)
        {
            X1 = X1 + 1;
            board[Y1][X1-1] = 0;
            
            X2 = X2 + 1;
            board[Y2][X2-1] = 0;
            
            X3 = X3 + 1;
            board[Y3][X3-1] = 0;
            
            X4 = X4 + 1;
            board[Y4][X4-1] = 0;
        }
    }
}

bool Line::moveDown(int board[22][12])
{
    if(DROP)
    {
        return false;
    }
    
    if(!ROTATE1 && !ROTATE2 && !ROTATE3) //first position
    {
        if(board[Y1+1][X1] != 0 || board[Y2+1][X2] != 0 || board[Y3+1][X3] != 0 || board[Y4+1][X4] != 0)
        {
            if(board[Y1+1][X1] != 8 || board[Y2+1][X2] != 8 || board[Y3+1][X3] != 8 || board[Y4+1][X4] != 8)
            {
                return false;
            }
            
            else if(board[Y1+1][X1] == 8 && board[Y2+1][X2] == 8 && board[Y3+1][X3] == 8 && board[Y4+1][X4] == 8)
            {
                Y1 = Y1 + 1;
                board[Y1-1][X1] = 0;
                
                Y2 = Y2 + 1;
                board[Y2-1][X2] = 0;
                
                Y3 = Y3 + 1;
                board[Y3-1][X3] = 0;
                
                Y4 = Y4 + 1;
                board[Y4-1][X4] = 0;
                
                return true;
            }
        }
        
        else if(Y1 != 20 && board[Y1+1][X1] == 0 && board[Y2+1][X2] == 0 && board[Y3+1][X3] == 0 && board[Y4+1][X4] == 0)
        {
            Y1 = Y1 + 1;
            board[Y1-1][X1] = 0;
            
            Y2 = Y2 + 1;
            board[Y2-1][X2] = 0;
            
            Y3 = Y3 + 1;
            board[Y3-1][X3] = 0;
            
            Y4 = Y4 + 1;
            board[Y4-1][X4] = 0;
        }
        
        return true;
    }
    
    else if(ROTATE1 && !ROTATE2 && !ROTATE3)
    {
        if(board[Y4+1][X4] != 0 && board[Y4+1][X4] != 8)
        {
            return false;
        }
        
        else if(Y4 != 20 && (board[Y4+1][X4] == 0 || board[Y4+1][X4] == 8))
        {
            Y1 = Y1 + 1;
            board[Y1-1][X1] = 0;
            
            Y2 = Y2 + 1;
            board[Y2-1][X2] = 0;
            
            Y3 = Y3 + 1;
            board[Y3-1][X3] = 0;
            
            Y4 = Y4 + 1;
            board[Y4-1][X4] = 0;
        }
        
        return true;
    }
    
    else if(ROTATE1 && ROTATE2 && !ROTATE3) //third position
    {
        if(board[Y1+1][X1] != 0 || board[Y2+1][X2] != 0 || board[Y3+1][X3] != 0 || board[Y4+1][X4] != 0)
        {
            return false;
        }
        
        else if(Y1 != 20 && board[Y1+1][X1] == 0 && board[Y2+1][X2] == 0 && board[Y3+1][X3] == 0 && board[Y4+1][X4] == 0)
        {
            Y1 = Y1 + 1;
            board[Y1-1][X1] = 0;
            
            Y2 = Y2 + 1;
            board[Y2-1][X2] = 0;
            
            Y3 = Y3 + 1;
            board[Y3-1][X3] = 0;
            
            Y4 = Y4 + 1;
            board[Y4-1][X4] = 0;
        }
        
        return true;
    }
    
    else if(ROTATE1 && ROTATE2 && ROTATE3) //fourth position
    {
        if(board[Y1+1][X1] != 0 && board[Y1+1][X1] != 8)
        {
            return false;
        }
        
        else if(Y1 != 20 && (board[Y1+1][X1] == 0 || board[Y1+1][X1] == 8))
        {
            Y1 = Y1 + 1;
            board[Y1-1][X1] = 0;
            
            Y2 = Y2 + 1;
            board[Y2-1][X2] = 0;
            
            Y3 = Y3 + 1;
            board[Y3-1][X3] = 0;
            
            Y4 = Y4 + 1;
            board[Y4-1][X4] = 0;
        }
        
        return true;
    }
    
    return true;
}

void Line::dropSet(int board[22][12]) // not working fully
{
    board[Y1][X1] = 0;
    board[Y2][X2] = 0;
    board[Y3][X3] = 0;
    board[Y4][X4] = 0;
    
    while(board[Y1+1][X1] == 0 && board[Y4+1][X4] == 0 && board[Y2+1][X2] == 0 && board[Y3+1][X3] == 0)
    {
        Y1++;
        Y2++;
        Y3++;
        Y4++;
    }
    
    DROP = true;
}

void Line::rotate(int board[22][12]) // rotates piece to the right 90 degrees
{
    if(DROP)
    {
        return;
    }
    
    if(!ROTATE1 && !ROTATE2 && !ROTATE3) //original piece (This is working)
    {
        //checking if the first block can move
        if(board[Y1-1][X1] != 0 || board[Y1-1][X1+1] != 0 || board[Y1-1][X1+2] != 0)
        {
            return;
        }
        
        //check the third block movement
        else if(board[Y3+1][X3] != 0)
        {
            return;
        }
        
        //checking fourth block movement
        else if(board[Y4+1][X4] != 0 || board[Y4+2][X4] != 0 || board[Y4+2][X4-1] != 0)
        {
            return;
        }
        
        else if(board[Y1-1][X1+2] == 0 && board[Y3+1][X3] == 0 && board[Y4+2][X4-1] == 0)
        {
            Y1 = Y1 - 1;
            X1 = X1 + 2;
            board[Y1+1][X1-2] = 0;
            
            X2 = X2 + 1;
            board[Y2][X2-1] = 0;
            
            Y3 = Y3 + 1;
            board[Y3-1][X3] = 0;
            
            Y4 = Y4 + 2;
            X4 = X4 - 1;
            board[Y4-2][X4+1] = 0;
            
            ROTATE1 = true;
        }
    }
    
    else if(ROTATE1 && !ROTATE2 && !ROTATE3) //piece is in second position (Looking good)
    {
        //check top block in vertical line
        if(board[Y1][X1+1] != 0 || board[Y1+1][X1+1] != 0 || board[Y1+2][X1+1] != 0)
        {
            return;
        }
        
        //check the third block movement
        else if(board[Y3][X3-1] != 0)
        {
            return;
        }
        
        //checking fourth block movement
        else if(board[Y4][X4-1] != 0 || board[Y4][X4-2] != 0 || board[Y4-1][X4-1] != 0 || board[Y4-1][X4-2] != 0)
        {
            return;
        }
        
        //board[Y1+1][X1-1] == 0 && board[Y3-1][X3+1] == 0 && board[Y4-2][X4+2] == 0 && ROTATE1
        else if(board[Y4-1][X4-2] == 0 && board[Y3][X3-1] == 0 && board[Y1+2][X1+1] == 0)
        {
            Y1 = Y1 + 2;
            X1 = X1 + 1;
            board[Y1-2][X1-1] = 0;
            
            Y2 = Y2 + 1;
            board[Y2-1][X2] = 0;
            
            X3 = X3 - 1;
            board[Y3][X3+1] = 0;
            
            Y4 = Y4 - 1;
            X4 = X4 - 2;
            board[Y4+1][X4+2] = 0;
            
            ROTATE2 = true;
        }
    }

    else if(ROTATE1 && ROTATE2 && !ROTATE3) // piece is in third position
    {
        //check top block in vertical line
        if(board[Y4-1][X4] != 0 || board[Y4-2][X4] != 0 || board[Y4-1][X4-1] != 0 || board[Y4-2][X4-1] != 0)
        {
            return;
        }
        
        //check the third block movement
        else if(board[Y3+1][X3] != 0)
        {
            return;
        }
        
        //checking fourth block movement
        else if(board[Y1+1][X1] != 0 || board[Y1+1][X1-1] != 0 || board[Y1+1][X1-2] != 0)
        {
            return;
        }
        
        //board[Y1+1][X1-1] == 0 && board[Y3-1][X3+1] == 0 && board[Y4-2][X4+2] == 0 && ROTATE1
        else if(board[Y1+1][X1-2] == 0 && board[Y3+1][X3] == 0 && board[Y4-2][X4+1] == 0)
        {
            Y4 = Y4 - 2;
            X4 = X4 + 1;
            board[Y4+2][X4-1] = 0;
            
            X2 = X2 - 1;
            board[Y2][X2+1] = 0;
            
            Y3 = Y3 - 1;
            board[Y3+1][X3] = 0;
            
            Y1 = Y1 + 1;
            X1 = X1 - 2;
            board[Y1-1][X1+2] = 0;

            ROTATE3 = true;
        }
    }
    
    else if(ROTATE1 && ROTATE2 && ROTATE3) //piece is in second position
    {
        //checking if the first block can move
        if(board[Y4][X4+1] != 0 || board[Y4][X4+2] != 0 || board[Y4+1][X4+1] != 0 || board[Y4+1][X4+2] != 0)
        {
            return;
        }
        
        //check the third block movement
        else if(board[Y3][X3+1] != 0)
        {
            return;
        }
        
        //checking fourth block movement
        else if(board[Y1][X1-1] != 0 || board[Y1-1][X1-1] != 0 || board[Y1-2][X1-1] != 0)
        {
            return;
        }
        
        else if(board[Y4+1][X4+2] == 0 && board[Y3][X3+1] == 0 && board[Y1-2][X1-1] == 0)
        {
            Y4 = Y4 + 1;
            X4 = X4 + 2;
            board[Y4-1][X4-2] = 0;
            
            Y2 = Y2 - 1;
            board[Y2+1][X2] = 0;
            
            X3 = X3 + 1;
            board[Y3][X3-1] = 0;
            
            Y1 = Y1 - 2;
            X1 = X1 - 1;
            board[Y1+2][X1+1] = 0;
            
            ROTATE1 = false;
            ROTATE2 = false;
            ROTATE3 = false;
        }
    }
}

void Line::ghost(int board[22][12])
{
    /*
    if((!ROTATE1 && !ROTATE2 && !ROTATE3) || (ROTATE1 && ROTATE2 && !ROTATE3))
    {
        int C = 1;
        
        for(int i = 1; i < 21; i++)
        {
            for(int j = 1; j < 11; j++)
            {
                if(board[i][j] == 8)
                {
                    board[i][j] = 0;
                }
            }
        }
        
        while(board[Y1+C][X1] == 0 && board[Y4+C][X4] == 0 && board[Y2+C][X2] == 0 && board[Y3+C][X3] == 0)
        {
            C++;
        }
        
        if(C > 1)
        {
            board[Y1+C-1][X1] = 8;
            board[Y2+C-1][X2] = 8;
            board[Y3+C-1][X3] = 8;
            board[Y4+C-1][X4] = 8;
        }
    }
    
    else if(ROTATE1 && !ROTATE2 && !ROTATE3)
    {
        int C = 1;
        
        for(int i = 1; i < 21; i++)
        {
            for(int j = 1; j < 11; j++)
            {
                if(board[i][j] == 8)
                {
                    board[i][j] = 0;
                }
            }
        }
        
        while(board[Y4+C][X4] == 0)
        {
            C++;
        }
        
        if(C > 1)
        {
            board[Y1+C-1][X1] = 8;
            board[Y2+C-1][X2] = 8;
            board[Y3+C-1][X3] = 8;
            board[Y4+C-1][X4] = 8;
        }
    }
    
    else if(ROTATE1 && ROTATE2 && ROTATE3)
    {
        int C = 1;
        
        for(int i = 1; i < 21; i++)
        {
            for(int j = 1; j < 11; j++)
            {
                if(board[i][j] == 8)
                {
                    board[i][j] = 0;
                }
            }
        }
        
        while(board[Y1+C][X1] == 0)
        {
            C++;
        }
        
        if(C > 1)
        {
            board[Y1+C-1][X1] = 8;
            board[Y2+C-1][X2] = 8;
            board[Y3+C-1][X3] = 8;
            board[Y4+C-1][X4] = 8;
        }
    }
     */
}

#endif /* Line_h */