//
//  Square.h
//  Function Pointers
//
//  Created by Bryan Taylor on 3/18/16.
//  Copyright © 2016 Bryan Taylor. All rights reserved.
//

#ifndef Square_h
#define Square_h

#include "main.h"
#include "Border.h"
#include "Shape.h"
#define GL_GLEXT_PROTOTYPES
#include <GLUT/glut.h>


class Square : public Shape
{
public:
    Square();
    ~Square();
    
    void draw(int board[22][12]);
    void moveLeft(int board[22][12]);
    void moveRight(int board[22][12]);
    void dropSet(int board[22][12]);
    bool moveDown(int board[22][12]);
    
private:
    bool DROP;
    bool MOVE;
    
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
    
    MOVE = false;
    DROP = true;
}

Square::~Square()
{
    
}

void Square::draw(int board[22][12])
{
    board[Y1][X1] = 1;
    board[Y2][X2] = 1;
    board[Y3][X3] = 1;
    board[Y4][X4] = 1;
}

void Square::moveLeft(int board[22][12])
{
    if(X1 != 1 && board[Y1][X1-1] == 0)
    {
        X1 = X1 - 1;
        board[Y1][X1+1] = 0;
        MOVE = true;
    }
    
    if(X3 != 1 && MOVE)
    {
        X3 = X3 - 1;
        board[Y3][X3+1] = 0;
    }

    if(X2 != 1 && MOVE)
    {
        X2 = X2 - 1;
        board[Y2][X2+1] = 0;
    }

    
    if(X4 != 1 && MOVE)
    {
        X4 = X4 - 1;
        board[Y4][X4+1] = 0;
    }
    
    MOVE = false;
}

void Square::moveRight(int board[22][12]) //something wonky here
{
    if(X2 != 10 && board[Y2][X2+1] == 0 && board[Y4][X4+1] == 0)
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
    if(board[Y3+1][X3] != 0 || board[Y4+1][X4] != 0)
    {
        return false;
    }
    
    else if(Y3 != 20 && board[Y3+1][X3] == 0 && board[Y4+1][X4] == 0)
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
    
    else if(Y4 != 20 && board[Y4+1][X4] == 0 && board[Y3+1][X3] == 0)
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

void Square::dropSet(int board[22][12])
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
    
    DROP = false;
}

#endif /* Square_h */
