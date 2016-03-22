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
    bool moveDown(int board[22][12]);
    
private:
    bool MOVE;
    bool ROTATE1;
    bool RDOWN;
    
};

Line::Line()
{
    X1 = 5;
    Y1 = 2;
    
    X2 = 6;
    Y2 = 2;
    
    X3 = 7;
    Y3 = 2;
    
    X4 = 8;
    Y4 = 2;
    
    MOVE = false;
    ROTATE1 = false;
}

Line::~Line()
{
    
}

void Line::draw(int board[22][12])
{
    board[Y1][X1] = 2;
    board[Y2][X2] = 2;
    board[Y3][X3] = 2;
    board[Y4][X4] = 2;
}

void Line::moveLeft(int board[22][12])
{
    if(X1 != 1 && board[Y1][X1-1] == 0)
    {
        X1 = X1 - 1;
        board[Y1][X1+1] = 0;
        MOVE = true;
    }
    
    if(X2 != 1 && MOVE)
    {
        X2 = X2 - 1;
        board[Y2][X2+1] = 0;
    }
    
    if(X3 != 1 && MOVE)
    {
        X3 = X3 - 1;
        board[Y3][X3+1] = 0;
        MOVE = true;
    }
    
    if(X4 != 1 && MOVE)
    {
        X4 = X4 - 1;
        board[Y4][X4+1] = 0;
    }
    
    MOVE = false;
}

void Line::moveRight(int board[22][12])
{
    if(X4 != 11 && board[Y4][X4+1] == 0)
    {
        X4 = X4 + 1;
        board[Y4][X4-1] = 0;
        MOVE = true;
    }
    
    if(X3 != 11 && MOVE)
    {
        X3 = X3 + 1;
        board[Y3][X3-1] = 0;
    }
    
    if(X2 != 11 && MOVE)
    {
        X2 = X2 + 1;
        board[Y2][X2-1] = 0;
    }
    
    if(X1 != 11 && MOVE)
    {
        X1 = X1 + 1;
        board[Y1][X1-1] = 0;
    }
    
    MOVE = false;
}

bool Line::moveDown(int board[22][12])
{
    if(!ROTATE1) //if the piece has not rotated
    {
        if(board[Y1+1][X1] != 0 || board[Y2+1][X2] != 0 || board[Y3+1][X3] != 0 || board[Y4+1][X4] != 0)
        {
            return false;
        }
        
        if(Y1 != 20 && board[Y1+1][X1] == 0 && board[Y2+1][X2] == 0 && board[Y3+1][X3] == 0 && board[Y4+1][X4] == 0)
        {
            Y1 = Y1 + 1;
            board[Y1-1][X1] = 0;
            MOVE = true;
        }
        
        if(Y2 != 20 && board[Y2+1][X2] == 0 && MOVE)
        {
            Y2 = Y2 + 1;
            board[Y2-1][X2] = 0;
        }
        
        if(Y3 != 20 && board[Y3+1][X3] == 0 && MOVE)
        {
            Y3 = Y3 + 1;
            board[Y3-1][X3] = 0;
            MOVE = true;
        }
        
        if(Y4 != 20 && board[Y4+1][X4] == 0 && MOVE)
        {
            Y4 = Y4 + 1;
            board[Y4-1][X4] = 0;
        }
        
        MOVE = false;
        
        return true;
    }
    
    else if(ROTATE1)
    {
        if(board[Y4+1][X4] != 0)
        {
            return false;
        }
        
        if(Y4 != 20 && board[Y4+1][X4] == 0)
        {
            Y4 = Y4 + 1;
            board[Y4-1][X4] = 0;
            MOVE = true;
        }
        
        if(Y3 != 20 && MOVE)
        {
            Y3 = Y3 + 1;
            board[Y3-1][X3] = 0;
        }
        
        if(Y1 != 20 && MOVE)
        {
            Y1 = Y1 + 1;
            board[Y1-1][X1] = 0;
        }
        
        if(Y2 != 20 && MOVE)
        {
            Y2 = Y2 + 1;
            board[Y2-1][X2] = 0;
        }
        
        MOVE = false;
        
        return true;
    }
    
    return true;
}

void Line::dropSet(int board[22][12]) // not working
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
}

void Line::rotate(int board[22][12]) // rotates piece to the right 90 degrees
{
    /*
     check first block move:
     board[Y1-1][X1] == 0 && board[Y1-1][X1] == 0
     
     second block is stationary 
     
     check third block movement:
     board[Y3+1][X3] == 0 && board[Y3+1][X3-1] == 0
     
     check last block movement
     board[Y4+1][X4] == 0 && board[Y4+2][X4] == 0&& board[Y4+1][X4-1] == 0
     
     */
    if(!ROTATE1 && (board[Y1-1][X1+1] != 0 || board[Y3+1][X3-1] != 0 || board[Y4+2][X4-2] != 0))
    {
        return;
    }
    
    else if(ROTATE1 && (board[Y1+1][X1-1] != 0 || board[Y3-1][X3+1] != 0 || board[Y4-2][X4+2] != 0))
    {
        return;
    }
    
    //if piece has not rotated yet
    if(board[Y1-1][X1+1] == 0 && board[Y3+1][X3-1] == 0 && board[Y4+2][X4-2] == 0 && !ROTATE1)
    {
        Y1 = Y1 - 1;
        X1 = X1 + 1;
        board[Y1+1][X1-1] = 0;
        
        Y3 = Y3 + 1;
        X3 = X3 - 1;
        board[Y3-1][X3+1] = 0;
        
        Y4 = Y4 + 2;
        X4 = X4 - 2;
        board[Y4-2][X4+2] = 0;
        
        ROTATE1 = true;
    }
    
    else if(board[Y1+1][X1-1] == 0 && board[Y3-1][X3+1] == 0 && board[Y4-2][X4+2] == 0 && ROTATE1)
    {
        Y1 = Y1 + 1;
        X1 = X1 - 1;
        board[Y1-1][X1+1] = 0;
        
        Y3 = Y3 - 1;
        X3 = X3 + 1;
        board[Y3+1][X3-1] = 0;
        
        Y4 = Y4 - 2;
        X4 = X4 + 2;
        board[Y4+2][X4-2] = 0;
        
        ROTATE1 = false;
    }
}

#endif /* Line_h */
