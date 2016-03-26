//
//  J.h
//  Function Pointers
//
//  Created by Bethany Willis on 3/20/16.
//  Copyright © 2016 Bethany Willis. All rights reserved.
//

#ifndef J_h
#define J_h

#include "main.h"
#include "Border.h"
#include "Shape.h"
#define GL_GLEXT_PROTOTYPES
#include <GLUT/glut.h>


class J : public Shape
{
public:
    J();
    ~J();

    void draw(int board[22][12]);
    void moveLeft(int board[22][12]);
    void moveRight(int board[22][12]);
    void dropSet(int board[22][12]);
    bool moveDown(int board[22][12]);

private:
    bool ROTATE1;
    bool ROTATE2;
    bool ROTATE3;
    bool ROTATE4;

};

J::J()
{
    /*
    These are for horizontal piece
    X1 = 6;
    Y1 = 1;

    X2 = 6;
    Y2 = 2;

    X3 = 7;
    Y3 = 2;

    X4 = 8;
    Y4 = 2;
    */

    X1 = 6;
    Y1 = 0;

    X2 = 6;
    Y2 = 1;

    X3 = 6;
    Y3 = 2;

    X4 = 5;
    Y4 = 2;

    ROTATE1 = true;
}

J::~J()
{

}

void J::draw(int board[22][12])
{
    board[Y1][X1] = 2;
    board[Y2][X2] = 2;
    board[Y3][X3] = 2;
    board[Y4][X4] = 2;
}

void J::moveLeft(int board[22][12])
{
    if(!ROTATE1)
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

    else if (ROTATE1)
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

void J::moveRight(int board[22][12])
{
    if(!ROTATE1)
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

    else if(ROTATE1)
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

bool J::moveDown(int board[22][12])
{
    if(!ROTATE1) //if the piece has not rotated
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

    else if(ROTATE1)
    {
        if(board[Y4+1][X4] != 0)
        {
            return false;
        }

        else if(Y4 != 20 && board[Y4+1][X4] == 0)
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

void J::dropSet(int board[22][12]) // not working fully
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

void J::rotate(int board[22][12]) // rotates piece to the right 90 degrees
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

    if(!ROTATE1)
    {
        //checking if the first block can move
        if(board[Y1-1][X1] != 0 || board[Y1-1][X1+1] != 0)
        {
            return;
        }

        //second block will not change

        //check the third block movement
        else if(board[Y3+1][X3] != 0 || board[Y3+1][X3-1] != 0)
        {
            return;
        }

        //checking fourth block movement
        else if(board[Y4-1][X4] != 0 || board[Y4-2][X4] != 0 || board[Y4-1][X4-1] != 0 || board[Y4-2][X4-2])
        {
            return;
        }

        else if(board[Y1-1][X1+1] == 0 && board[Y3+1][X3-1] == 0 && board[Y4+2][X4-2] == 0)
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
    }

    else if(ROTATE1)
    {
        if(board[Y1][X1-1] != 0 || board[Y1+1][X1-1] != 0)
        {
            return;
        }

        //second block will not change

        //check the third block movement
        else if(board[Y3][X3+1] != 0 || board[Y3+1][X3+1] != 0)
        {
            return;
        }

        //checking fourth block movement
        else if(board[Y4][X4+1] != 0 || board[Y4][X4+2] != 0 || board[Y4-1][X4+1] != 0 || board[Y4-2][X4+2])
        {
            return;
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
}

#endif /* J_h */
