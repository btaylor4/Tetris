//
// zBlock.h
//
// Class for the zBlock in Tetris
//
// Eric Daff™

#ifndef zBlock_h
#define zBlock_h

#include "Shape.h"

class zBlock : public Shape
{
public:
    zBlock();
    ~zBlock();
    
    void draw(int board[22][12]);
    void moveLeft(int board[22][12]);
    void moveRight(int board[22][12]);
    void dropSet(int board[22][12]);
    bool moveDown(int board[22][12]);
    void rotate(int board[22][12]);
    
private:
    bool DROP;
    bool p1;
    bool p2;
    bool p3;
    bool p4;
    bool GEN;
    int n = 1;
};

// Constructor
zBlock::zBlock()
{
    // Top left square
    X1 = 4;
    Y1 = 1;
    
    // Top middle square
    X2 = 5;
    Y2 = 1;
    
    // Bottom middle square
    X3 = 5;
    Y3 = 2;
    
    // Far Right square
    X4 = 6;
    Y4 = 2;
    
    DROP = true;
    
    p1 = true;
    p2 = false;
    p3 = false;
    p4 = false;
    GEN = false;
}

// Destructor
zBlock::~zBlock()
{
    
}

// Draw the block onto the board
void zBlock::draw(int board[22][12])
{
    if(!GEN && (board[Y1][X1] != 0 || board[Y2][X2] != 0 || board[Y3][X3] != 0 || board[Y4][X4] != 0))
    {
        X1 = -1;
    }
    
    else
    {
        board[Y1][X1] = 3;
        board[Y2][X2] = 3;
        board[Y3][X3] = 3;
        board[Y4][X4] = 3;
        GEN = true;
    }
}

// Move the block left
void zBlock::moveLeft(int board[22][12])
{
    if(!DROP)
    {
        return;
    }
    
    if (p1)
    {
        if (board[Y1][X1 - 1] == 0 && board[Y3][X3 - 1] == 0)
        {
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
    else if (p2)
    {
        if (board[Y3][X3 - 1] == 0 && board[Y4][X4 - 1] == 0 && board[Y1][X1 - 1] == 0)
        {
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
    else if (p3)
    {
        if (board[Y4][X4 - 1] == 0 && board[Y2][X2 - 1] == 0)
        {
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
    else if (p4)
    {
        if (board[Y1][X1 - 1] == 0 && board[Y2][X2 - 1] == 0 && board[Y4][X4 - 1] == 0)
        {
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

// Move the block down
bool zBlock::moveDown(int board[22][12])
{
    if(!DROP)
    {
        return false;
    }
    
    if (p1)
    {
        if (board[Y3 + 1][X3] != 0 || board[Y4 + 1][X4] != 0 || board[Y1 + 1][X1] != 0)
        {
            return false;
        }
    }
    else if (p2)
    {
        if (board[Y4 + 1][X4] != 0 || board[Y2 + 1][X2] != 0)
        {
            return false;
        }
    }
    else if (p3)
    {
        if (board[Y4 + 1][X4] != 0 || board[Y2 + 1][X2] != 0 || board[Y1 + 1][X1] != 0)
        {
            return false;
        }
    }
    else if (p4)
    {
        if (board[Y3 + 1][X3] != 0 || board[Y1 + 1][X1] != 0)
        {
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

// Moves the block right
void zBlock::moveRight(int board[22][12])
{
    if(!DROP)
    {
        return;
    }
    
    if (p1)
    {
        if (board[Y4][X4 + 1] == 0)
        {
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
    else if (p2)
    {
        if (board[Y1][X1 + 1] == 0 && board[Y2][X2 + 1] == 0 && board[Y4][X4 + 1] == 0)
        {
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
    else if (p3)
    {
        if (board[Y1][X1 + 1] == 0 && board[Y3][X3 + 1] == 0)
        {
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
    else if (p4)
    {
        if (board[Y3][X3 + 1] == 0 && board[Y4][X4 + 1] == 0 && board[Y1][X1 + 1] == 0)
        {
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

// Sets the block into the board permanently
void zBlock::dropSet(int board[22][12])
{
    n = 1;
    if (p1)
    {
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while (board[Y3 + n][X3] == 0 && board[Y4 + n][X4] == 0 && board[Y1 + n][X1] == 0)
        {
            n++;
        }
        
        Y1 += n - 1;
        Y2 += n - 1;
        Y3 += n - 1;
        Y4 += n - 1;
        
        DROP = false;
    }
    
    else if (p2)
    {
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while (board[Y4 + n][X4] == 0 && board[Y2 + n][X2] == 0)
        {
            n++;
        }
        
        Y1 += n - 1;
        Y2 += n - 1;
        Y3 += n - 1;
        Y4 += n - 1;
        
        DROP = false;
    }
    
    else if (p3)
    {
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while (board[Y2 + n][X2] == 0 && board[Y4 + n][X4] == 0 && board[Y1 + n][X1] == 0)
        {
            n++;
        }
        
        Y1 += n - 1;
        Y2 += n - 1;
        Y3 += n - 1;
        Y4 += n - 1;
        
        DROP = false;
    }
    
    else if (p4)
    {
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        while (board[Y3 + n][X3] == 0 && board[Y1 + n][X1] == 0)
        {
            n++;
        }
        
        Y1 += n - 1;
        Y2 += n - 1;
        Y3 += n - 1;
        Y4 += n - 1;
        
        DROP = false;
    }
}

// Rotates the block
void zBlock::rotate(int board[22][12])
{
    if(!DROP)
    {
        return;
    }
    
    if (p1)
    {
        // Check if the 4th block has a clear path
        if (board[Y4 + 1][X4] != 0 || board[Y4 + 1][X4 - 1] != 0)
        {
            return;
        }
        // Check if the 2nd block has a clear path
        else if (board[Y2][X2 + 1] != 0)
        {
            return;
        }
        // Check if the
        else if (board[Y1][X1 + 2] != 0)
        {
            return;
        }
        // Delete previous drawing
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        // Rotate shape
        X1 += 2;
        X2 += 1;
        Y2 += 1;
        X4 -= 1;
        Y4 += 1;
        
        // Change booleans for position
        p1 = false;
        p2 = true;
        p3 = false;
        p4 = false;
    }
    else if (p2)
    {
        // Check if the 1st block has a clear path
        if (board[Y1 + 2][X1] != 0)
        {
            return;
        }
        
        else if (board[Y2 + 1][X2] != 0)
        {
            return;
        }
        
        else if (board[Y4][X4 - 1] != 0 || board[Y4 - 1][X4 - 1] != 0)
        {
            return;
        }
        // Delete previous drawing
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        // Rotate block
        Y1 += 2;
        X2 -= 1;
        Y2 += 1;
        X4 -= 1;
        Y4 -= 1;
        
        // Change booleans for position
        p1 = false;
        p2 = false;
        p3 = true;
        p4 = false;
    }
    
    else if (p3)
    {
        // Check if the 1st block has a clear path
        if (board[Y1 + 1][X1] != 0)
        {
            return;
        }
        // Check if the 2nd block has a clear path
        else if (board[Y2][X2 - 1] != 0)
        {
            return;
        }
        // Check if the 4th block has a clear path
        else if (board[Y4 - 1][X4] != 0 || board[Y4 - 1][X4 + 1] != 0)
        {
            return;
        }
        
        // Delete previous drawing
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        // Rotate block
        X1 -= 2;
        X2 -= 1;
        Y2 -= 1;
        X4 += 1;
        Y4 -= 1;
        
        // Change booleans for position
        p1 = false;
        p2 = false;
        p3 = false;
        p4 = true;
    }
    
    else if (p4)
    {
        // Check if the 1st block has a clear path
        if (board[Y1 - 2][X1] != 0)
        {
            return;
        }
        // Check if the 2nd block has a clear path
        else if (board[Y2 - 1][X2] != 0)
        {
            return;
        }
        // Check if the 4th block has a clear path
        else if (board[Y4][X4 + 1] != 0 || board[Y4 + 1][X4 + 1] != 0)
        {
            return;
        }
        // Delete previous drawing
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        // Rotate block
        Y1 -= 2;
        X2 += 1;
        Y2 -= 1;
        X4 += 1;
        Y4 += 1;
        
        // Change booleans for position
        p1 = true;
        p2 = false;
        p3 = false;
        p4 = false;
    }
}
#endif