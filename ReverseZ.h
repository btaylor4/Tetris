//
//  J.h
//  Function Pointers
//
// Rahul Patel

#include "Shape.h"

class ReverseZ : public Shape
{
public:
    ReverseZ();
    ~ReverseZ();
    
    void draw(int board[22][12]);
    void moveLeft(int board[22][12]);
    void moveRight(int board[22][12]);
    void dropSet(int board[22][12]);
    void rotate(int board[22][12]);
    bool moveDown(int board[22][12]);
    
private:
    bool r1;
    bool r2;
    bool r3;
    bool r4;
    bool DROP;
    bool GEN;
};

ReverseZ::ReverseZ()
{
    X1 = 4;
    Y1 = 2;
    
    X2 = 5;
    Y2 = 2;
    
    X3 = 5;
    Y3 = 1;
    
    X4 = 6;
    Y4 = 1;
    
    r1 = true;
    r2 = false;
    r3 = false;
    r4 = false;
    DROP = false;
    GEN = false;
}

ReverseZ::~ReverseZ()
{
    
}

void ReverseZ::draw(int board[22][12])
{
    if(!GEN && (board[Y1][X1] != 0 || board[Y2][X2] != 0 || board[Y3][X3] != 0 || board[Y4][X4] != 0))
    {
        X1 = -1;
    }
    
    else
    {
        board[Y1][X1] = 4;
        board[Y2][X2] = 4;
        board[Y3][X3] = 4;
        board[Y4][X4] = 4;
        GEN = true;
    }
}

void ReverseZ::moveLeft(int board[22][12])
{
    if(DROP)
    {
        return;
    }
    
    if (r1)
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
    
    else if (r2)
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
    
    else if (r3)
    {
        if (board[Y2][X2 - 1] == 0 && board[Y4][X4 - 1] == 0)
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
    
    else if (r4)
    {
        if (board[Y1][X1 - 1] == 0 && board[Y3][X3 - 1] == 0 && board[Y4][X4 - 1] == 0)
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

void ReverseZ::moveRight(int board[22][12])
{
    if(DROP)
    {
        return;
    }
    
    if (r1)
    {
        if (board[Y4][X4 + 1] == 0 && board[Y2][X2 + 1] == 0)
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
    
    else if (r2)
    {
        if (board[Y1][X1 + 1] == 0 && board[Y3][X3 + 1] == 0 && board[Y4][X4 + 1] == 0)
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
    
    else if (r3)
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
    
    else if (r4)
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
}

bool ReverseZ::moveDown(int board[22][12])
{
    if(DROP)
    {
        return false;
    }
    
    if (r1)
    {
        if (board[Y1 + 1][X1] == 0 && board[Y2 + 1][X2] == 0 && board[Y4 + 1][X4] == 0)
        {
            Y2 += 1;
            board[Y2 - 1][X2] = 0;
            
            Y3 += 1;
            board[Y3 - 1][X3] = 0;
            
            Y1 += 1;
            board[Y1 - 1][X1] = 0;
            
            Y4 += 1;
            board[Y4 - 1][X4] = 0;
            
            return true;
        }
        
        else
            return false;
    }
    
    else if (r2)
    {
        if (board[Y2 + 1][X2] == 0 && board[Y4 + 1][X4] == 0)
        {
            Y2 += 1;
            board[Y2 - 1][X2] = 0;
            
            Y3 += 1;
            board[Y3 - 1][X3] = 0;
            
            Y1 += 1;
            board[Y1 - 1][X1] = 0;
            
            Y4 += 1;
            board[Y4 - 1][X4] = 0;
            
            return true;
        }
        
        else
            return false;
    }
    
    else if (r3)
    {
        if (board[Y1 + 1][X1] == 0 && board[Y3 + 1][X3] == 0 && board[Y4 + 1][X4] == 0)
        {
            Y2 += 1;
            board[Y2 - 1][X2] = 0;
            
            Y3 += 1;
            board[Y3 - 1][X3] = 0;
            
            Y1 += 1;
            board[Y1 - 1][X1] = 0;
            
            Y4 += 1;
            board[Y4 - 1][X4] = 0;
            
            return true;
        }
        
        else
            return false;
    }
    
    else if (r4)
    {
        if (board[Y1 + 1][X1] == 0 && board[Y3 + 1][X3] == 0)
        {
            Y2 += 1;
            board[Y2 - 1][X2] = 0;
            
            Y3 += 1;
            board[Y3 - 1][X3] = 0;
            
            Y1 += 1;
            board[Y1 - 1][X1] = 0;
            
            Y4 += 1;
            board[Y4 - 1][X4] = 0;
            
            return true;
        }
        
        else
            return false;
    }
    return true;
}

void ReverseZ::dropSet(int board[22][12])
{
    board[Y1][X1] = 0;
    board[Y2][X2] = 0;
    board[Y3][X3] = 0;
    board[Y4][X4] = 0;
    
    while (board[Y1 + 1][X1] == 0 && board[Y2 + 1][X2] == 0 && board[Y3 + 1][X3] == 0 && board[Y4 + 1][X4] == 0)
    {
        Y1++;
        Y2++;
        Y3++;
        Y4++;
    }
    
    DROP = true;
}

void ReverseZ::rotate(int board[22][12])
{
    if(DROP)
    {
        return;
    }
    
    if (r1)
    {
        if (board[Y1 - 1][X1] != 0)
        {
            return;
        }
        
        else if (board[Y3 + 1][X3 + 1] != 0)
        {
            return;
        }
        
        else if (board[Y4 + 2][X4] != 0)
        {
            return;
        }
        
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        X1 += 1;
        Y1 -= 1;
        X3 += 1;
        Y3 += 1;
        Y4 += 2;
        
        r1 = false;
        r2 = true;
        r3 = false;
        r4 = false;
    }
    
    else if (r2)
    {	
        if (board[Y1][X1 + 1] != 0)
        {
            return;
        }
        
        else if (board[Y3 + 1][X3 - 1] != 0)
        {
            return;
        }
        
        else if (board[Y4][X4 - 2] != 0)
        {
            return;
        }
        
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        X1 += 1;
        Y1 += 1;
        X3 -= 1;
        Y3 += 1;
        X4 -= 2;
        
        r1 = false;
        r2 = false;
        r3 = true;
        r4 = false;
    }
    
    else if (r3)
    {
        if (board[Y1 + 1][X1] != 0)
        {
            return;
        }
        
        else if (board[Y3 - 1][X3 - 1] != 0)
        {
            return;
        }
        
        else if (board[Y4 - 2][X4] != 0)
        {
            return;
        }
        
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        X1 -= 1;
        Y1 += 1;
        X3 -= 1;
        Y3 -= 1;
        Y4 -= 2;
        
        r1 = false;
        r2 = false;
        r3 = false;
        r4 = true;
    }
    
    else if (r4)
    {
        if (board[Y1][X1 - 1] != 0)
        {
            return;
        }
        
        else if (board[Y3 - 1][X3 + 1] != 0)
        {
            return;
        }
        
        else if (board[Y4][X4 + 2] != 0)
        {
            return;
        }
        
        board[Y1][X1] = 0;
        board[Y2][X2] = 0;
        board[Y3][X3] = 0;
        board[Y4][X4] = 0;
        
        X1 -= 1;
        Y1 -= 1;
        X3 += 1;
        Y3 -= 1;
        X4 += 2;
        
        r1 = true;
        r2 = false;
        r3 = false;
        r4 = false;
    }
}