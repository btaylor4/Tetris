//
//  Square.h
//  Function Pointers
//
//  Created by Bryan Taylor on 3/18/16.
//  Copyright © 2016 Bryan Taylor. All rights reserved.
//

#ifndef Square_h
#define Square_h

#include "Shape.h"

class Square : public Shape
{
public:
    Square();
    ~Square();
    
    void draw(int board[22][12]);
    void moveLeft(int board[22][12]);
    void moveRight(int board[22][12]);
    void dropSet(int board[22][12]);
    void ghost(int board[22][12]);
    bool moveDown(int board[22][12]);
    
private:
    bool DROP;
    bool GEN;
};

Square::Square()
{
    //left top square
    X1 = 5;
    Y1 = 1;

    //right top square
    X2 = 6;
    Y2 = 1;
    
    //bottom left square
    X3 = 5;
    Y3 = 2;
    
    //bottom right square
    X4 = 6;
    Y4 = 2;
    
    DROP = false;
    GEN = false;
}

Square::~Square()
{
    
}

void Square::draw(int board[22][12])
{
    if(!GEN && (board[Y3][X3] != 0 || board[Y4][X4] != 0))
    {
        board[Y1][X1] = 1;
        board[Y2][X2] = 1;
        X1 = -1;
    }
    
    else
    {
        board[Y1][X1] = 1;
        board[Y2][X2] = 1;
        board[Y3][X3] = 1;
        board[Y4][X4] = 1;
        
        GEN = true;
    }
}

void Square::moveLeft(int board[22][12])
{
    if(DROP)
    {
        return;
    }
    
    if(X1 != 1 && (board[Y1][X1-1] != 0 || board[Y3][X3-1] != 0))
    {
        return;
    }
    
    else if(X1 != 1 && board[Y1][X1-1] == 0 && board[Y3][X3-1] == 0)
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

void Square::moveRight(int board[22][12]) //something wonky here
{
    if(DROP)
    {
        return;
    }
    
    if(X2 != 10 && (board[Y2][X2+1] != 0 || board[Y4][X4+1] != 0))
    {
        return;
    }
    
    else if(X2 != 10 && board[Y2][X2+1] == 0 && board[Y4][X4+1] == 0)
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

bool Square::moveDown(int board[22][12])
{
    if(DROP)
    {
        return false;
    }
    
    if(board[Y3+1][X3] != 0 || board[Y4+1][X4] != 0) // checks if move is even possible before continuing
    {
        if(board[Y3+1][X3] != 8 || board[Y4+1][X4] != 8)
        {
            return false;
        }
        
        else if(board[Y3+1][X3] == 8 && board[Y4+1][X4] == 8)
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
    
    else if(Y3 != 20 && Y4 != 20 && board[Y3+1][X3] == 0 && board[Y4+1][X4] == 0)
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
    
    return true;
}

void Square::dropSet(int board[22][12]) //sets piece instantly below to where ever it first collides 
{
    board[Y1][X1] = 0;
    board[Y2][X2] = 0;
    board[Y3][X3] = 0;
    board[Y4][X4] = 0;
    
    while(board[Y3+1][X3] == 0 && board[Y4+1][X4] == 0)
    {
        Y1++;
        Y2++;
        Y3++;
        Y4++;
    }
    
    DROP = true;
}

void Square::ghost(int board[22][12])
{
    /*
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
    
    while(board[Y3+C][X3] == 0 && board[Y4+C][X4] == 0 && board[Y3+C][X3] != 8 && board[Y4+C][X4] != 8)
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
     */
}

#endif /* Square_h */
