//
//  Shape.h
//  Function Pointers
//
//  Created by Bryan Taylor on 3/18/16.
//  Copyright © 2016 Bryan Taylor. All rights reserved.
//

#ifndef Shape_h
#define Shape_h

class Shape
{
public:
    virtual void draw(int board[22][12]){}
    virtual void rotate(int board[22][12]){}
    virtual void moveLeft(int board[22][12]){}
    virtual void moveRight(int board[22][12]){}
    virtual void dropSet(int board[22][12]){}
    virtual void ghost(int board[22][12]){}
    virtual bool moveDown(int board[22][12]){return true;}

    //Coordinates
    int X1;
    int Y1;
    
    int X2;
    int Y2;
    
    int X3;
    int Y3;
    
    int X4;
    int Y4;
    
    bool DROP;
};

#endif /* Shape_h */