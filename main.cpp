//
//  main.cpp
//  Function Pointers
//
//  Created by Bryan Taylor on 3/11/16.
//  Copyright © 2016 Bryan Taylor. All rights reserved.
//

/////////////////////////////// NOTES //////////////////////////////////

/*
 Modeling tetris based off of a 2D array
 */

///////////////////////////////////////////////////////////////////////

#include "main.h" 

//this prints our board to the console and is used for testing
void print(int array[22][12])
{
    for(int i = 0; i < 22; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            cout << setw(2) << array[i][j];
        }
        
        cout << endl;
    }
    
    cout << endl;
}

//this function takes charge in clearing out lines if there are 10 blocks in a line
void clearLines(int board[22][12])
{
    int repeat = 0;
    int count = 0;
    int TEMPI = 20;
    bool clear = false;
    int numLines = 0;
    
    do
    {
        repeat++;
     
        for(int i = 20; i >= 1; i--)
        {
            for(int j = 1; j < 11; j++)
            {
                if(!clear)
                {
                    if(board[i][j] != 0)
                    {
                        count++;
                    }
                    
                    if(count == 10)
                    {
                        numLines++;
                        totalLines++;
                        count = 0;
                        clear = true;
                        j = 0;
                        
                        switch((int)(totalLines / 10))
                        {
                            case 1:
                                level = 2;
                                speed = 730;
                                break;
                                
                            case 2:
                                level = 3;
                                speed = 660;
                                break;
                                
                            case 3:
                                level = 4;
                                speed = 590;
                                break;
                                
                            case 4:
                                level = 5;
                                speed = 520;
                                break;
                                
                            case 5:
                                level = 6;
                                speed = 450;
                                break;
                                
                            case 6:
                                level = 7;
                                speed = 380;
                                break;
                                
                            case 7:
                                level = 8;
                                speed = 310;
                                break;
                                
                            case 8:
                                level = 9;
                                speed = 240;
                                break;
                                
                            case 9:
                                level = 10;
                                speed = 170;
                                break;
                                
                            case 10:
                                level = 9000;
                                speed = 85;
                                break;
                        }
                    }
                }
                
                else if(clear)
                {
                    TEMPI = i;
                    
                    while(i > 1)
                    {
                        board[i][j] = board[i-1][j];
                        board[i-1][j] = 0;
                        i--;
                    }
        
                    i = TEMPI;
                }
            }
            
            count = 0;
            clear = false;
        }
    } while(repeat <= 4);

    //Player class score will go here
    //class->score +=...
    switch(numLines)
    {
        case 1:
            player.increaseScore(100);
            break;
            
        case 2:
            player.increaseScore(200);
            break;
            
        case 3:
            player.increaseScore(300);
            break;
            
        case 4:
            player.increaseScore(800);
            break;
    }
    
    numLines = 0;
}

//this function takes in our keyboard inputs
void keys(int key, int w, int y) //movements need to be about the
{
    //Remember to add option to quit which is the esc key
    if(key == GLUT_KEY_UP)
    {
        //rotate method
        x->rotate(board);// rotate our shape
        x->draw(board); //draw our shape to the array
        //x->ghost(board);
        boardDraw();  //draw our shape to the screen
    }
    
    if(key == GLUT_KEY_LEFT)
    {
        //left directional key
        x->moveLeft(board); //moves our shape to the left
        x->draw(board);
        //x->ghost(board);
        boardDraw(); //draw our shape to the screen
    }
    
    if(key == GLUT_KEY_RIGHT)
    {
        //Right directional key
        x->moveRight(board); //moves our shape to the right
        x->draw(board); //draw our shape to the array
        //x->ghost(board);
        boardDraw(); //draw our shape to the screen
    }
    
    if(key == GLUT_KEY_DOWN)
    {
        //Down directional key
        x->moveDown(board); //moves the shape down
        x->draw(board); //draw our shape to the array
        boardDraw(); //draw our shape to the screen
    }
    
    if(key == 32) //space key
    {
        //set piece immediately
        x->dropSet(board); // this is wonky. when there is space beneath tiles it runs forever??
        x->draw(board);
        boardDraw(); // draw shape to screen window
    }
    
    if(key == 27) //esc key
    {
        player.addScore();
        player.exportFile();
        exit(0);
    }
}

void menuKeys(int key, int w, int y) 
{
    if(key == 127 && !lose) //delete key
    {
        drawMenu();
        menu = false;
    }
    
    if(key == 27)
    {
        exit(0);
    }
}

void Timer(int a)
{
    if(!change) //checks to see if we are dealing with the same shape
    {
        if( nextP == NULL)
        {
            x = generatePart(board); // if the shape has set, generate a new shape
            
            if( x == NULL)
            {
                player.importFile();
                drawLose();
                lose = true;
                glutSpecialFunc(menuKeys);
                return;
            }
            
            nextP = nextPart(nextBoard);
            
            while (typeid(*x) == typeid(*nextP))
            {
                nextP = nextPart(nextBoard);
            }
        }
        
        else
        {
            x = nextP; // if the shape has set, generate a new shape
            x->draw(board);
            if(x->X1 == -1)
            {
                player.importFile();
                drawLose();
                lose = true;
                glutSpecialFunc(menuKeys);
                return;
            }
            
            nextP = nextPart(nextBoard);
            
            while (typeid(*x) == typeid(*nextP))
            {
                nextP = nextPart(nextBoard);
            }
        }

        change = true; // set change to true to not generate a new shape until the one we just generated sets
    }
    
    x->draw(board); //draw shape to board
    //x->ghost(board);
    boardDraw(); // draw shape to screen window
    
    if(x->moveDown(board)) //check if down move is available
    {
        glutTimerFunc(speed, Timer, 0);
        glutDisplayFunc(draw);
        glutSpecialFunc(keys);
        glutPostRedisplay();
    }
    
    else if(!x->moveDown(board))// if the cube reached the bottom
    {     
        change = false;
        clearLines(board);
        glutDisplayFunc(draw);
        glutSpecialFunc(keys);
        glutTimerFunc(1, Timer, 0);
        glutPostRedisplay();
    }
}

//generate the part
Shape *generatePart(int board[22][12])
{
    /*
     This method is to generate new parts
     Once you believe your classes are done, do x = new YOURSHAPE();
     Then x->draw(board) (We may not need this call since our timer function has it...
     */
    
    partsCreated++;
    
    int random = 0;
    
    //code to make choices more random
    if(partsCreated > 1)
    {
        do
        {
            srand(time(NULL));
            random = rand() % 8;
        } while(random == randChoice);
        
        randChoice = random;
    }
    
    else
    {
        srand(time(NULL));
        random = rand() % 8;
        randChoice = random;
    }
    
    switch(random) //chooses a shape at random
    {
        case 0:
            // generate Cube
            x = new Square();
            x->draw(board);
            if(x->X1 != -1)
            {
                return x;
            }
            
            else
                return NULL;
            
            break;
            
        case 1:
            //generate Line
            x = new Line();
            x->draw(board);
            if(x->X1 != -1)
            {
                return x;
            }
            
            else
                return NULL;
            
            break;
            
        case 2:
            //generate Z-block
            x = new zBlock();
            x->draw(board);
            if(x->X1 != -1)
            {
                return x;
            }
            
            else
                return NULL;
            break;
            
        case 3:
            //generate reverse Z-block
            x = new ReverseZ();
            x->draw(board);
            if(x->X1 != -1)
            {
                return x;
            }
            
            else
                return NULL;
            break;
            
        case 4:
            //generate T-block
            x = new TBlock();
            x->draw(board);
            if(x->X1 != -1)
            {
                return x;
            }
            
            else
                return NULL;
            break;
            
        case 5:
            //generate Reverse L-Block
            x = new J();
            x->draw(board);
            if(x->X1 != -1)
            {
                return x;
            }
            
            else
                return NULL;
            break;
            
        case 6:
            //generate L-block
            x = new Lblock();
            x->draw(board);
            if(x->X1 != -1)
            {
                return x;
            }
            
            else
                return NULL;
            break;
            
        case 7:
            //generate Line
            x = new Line();
            x->draw(board);
            if(x->X1 != -1)
            {
                return x;
            }
            
            else
                return NULL;
            
            break;
    }
    
    return x; // return our shape
}

//generate the next part
Shape *nextPart(int nextBoard[5][5])
{
    int random = 0;
    
    do
    {
        srand(time(NULL));
        random = rand() % 8;
    } while(random == randChoice);
    
    randChoice = random;


    switch(random) //chooses a shape at random
    {
        case 0:
            // generate Cube
            nextP = new Square();
            
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    nextBoard[i][j] = 0;
                }
            }
            
            nextBoard[1][0] = 1;
            nextBoard[1][1] = 1;
            nextBoard[2][0] = 1;
            nextBoard[2][1] = 1;
            
            return nextP;
            break;
            
        case 1:
            //generate Line
            nextP = new Line();
            
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    nextBoard[i][j] = 0;
                }
            }
            
            nextBoard[1][0] = 2;
            nextBoard[1][1] = 2;
            nextBoard[1][2] = 2;
            nextBoard[1][3] = 2;
            
            return nextP;
            break;
            
        case 2:
            //generate Z-block
            nextP = new zBlock();
            
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    nextBoard[i][j] = 0;
                }
            }
            
            nextBoard[1][0] = 3;
            nextBoard[1][1] = 3;
            nextBoard[2][1] = 3;
            nextBoard[2][2] = 3;
            
            return nextP;
            break;
            
        case 3:
            //generate reverse Z-block
            nextP = new ReverseZ();
            
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    nextBoard[i][j] = 0;
                }
            }
            
            nextBoard[1][2] = 4;
            nextBoard[1][1] = 4;
            nextBoard[2][0] = 4;
            nextBoard[2][1] = 4;
            
            return nextP;
            break;
            
        case 4:
            //generate T-block
            nextP = new TBlock();
            
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    nextBoard[i][j] = 0;
                }
            }
            
            nextBoard[1][2] = 7;
            nextBoard[2][1] = 7;
            nextBoard[2][2] = 7;
            nextBoard[2][3] = 7;
            
            return nextP;
            break;
            
        case 5:
            nextP = new J();
            
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    nextBoard[i][j] = 0;
                }
            }
            
            nextBoard[1][3] = 5;
            nextBoard[2][3] = 5;
            nextBoard[2][2] = 5;
            nextBoard[2][1] = 5;
            
            return nextP;
            break;
            
        case 6:
            //generate L-block
            nextP = new Lblock();
            
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    nextBoard[i][j] = 0;
                }
            }
            
            nextBoard[1][0] = 6;
            nextBoard[2][0] = 6;
            nextBoard[2][1] = 6;
            nextBoard[2][2] = 6;
            
            return nextP;
            break;
            
        case 7:
            //generate Line
            nextP = new Line();
            
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    nextBoard[i][j] = 0;
                }
            }
            
            nextBoard[1][0] = 2;
            nextBoard[1][1] = 2;
            nextBoard[1][2] = 2;
            nextBoard[1][3] = 2;
            
            return nextP;
            break;
    }
    
    return nextP; // return our shape
}

//graphics for our board
void boardDraw()
{
    string s = "Score: ";
    string t = "Lines: ";
    string l = "Level: ";
    string h = "High Score: ";
    
    s += to_string(player.getScore());
    t += to_string(totalLines);
    l += to_string(level);
    h += to_string(player.getHighScore());
    
    //This method takes care of drawing our shapes in our window
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    
    drawBorder();
    drawText(s,h, t, l);
    
    //for the next piece
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            switch(nextBoard[i][j])
            {
                case 1:
                    glBegin(GL_POLYGON);
                    glColor3f(1, 1, 0); //color of our block
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 2:
                    glBegin(GL_POLYGON);
                    glColor3f(0, 1, 1);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 3:
                    glBegin(GL_POLYGON);
                    glColor3f(1, 0, 0);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 4:
                    glBegin(GL_POLYGON);
                    glColor3f(0, 1, 0);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 5:
                    glBegin(GL_POLYGON);
                    glColor3f(1, .4, 0);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 6:
                    glBegin(GL_POLYGON);
                    glColor3f(0, .4, 1);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 7:
                    glBegin(GL_POLYGON);
                    glColor3f(.63, .13, .95);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
            }
        }
    }

    for(int i = 1; i < 21; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            switch(board[i][j])
            {
                case 1: //if a square block
                    glBegin(GL_POLYGON);
                    glColor3f(1, 1, 0); //color of our block
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 2: // if a line block
                    glBegin(GL_POLYGON);
                    glColor3f(0, 1, 1); //cyan
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 3: // if a z block
                    glBegin(GL_POLYGON);
                    glColor3f(1, 0, 0); // red
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 4: //if a reverse z block(s block)
                    glBegin(GL_POLYGON);
                    glColor3f(0, 1, 0); //green
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 5: // if a L block
                    glBegin(GL_POLYGON);
                    glColor3f(1, .4, 0); //orange
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 6: //if a reverse L block
                    glBegin(GL_POLYGON);
                    glColor3f(0, .4, 1); //blue
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 7: // if a t block
                    glBegin(GL_POLYGON);
                    glColor3f(.63, .13, .95); //purple
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 8: //ghost color
                    glEnable(GL_BLEND);
                    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    glBegin(GL_POLYGON);
                    glColor4f(1, 1, 1, .3); //transparent grey
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
            }
        }
    }
    
    glutSwapBuffers();
}

//draw the score, highscore, tiles cleared, and level
void drawText(string s, string h, string t, string l)
{
    string N = "NEXT:";
    
    glLoadIdentity();
    glColor3f(1, 0, 0);
    glRasterPos3f(5.5, 5,0);
    
    for (int i = 0; i < s.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s.at(i));
    }
    
    glColor3f(0, 1, 0);
    glRasterPos3f(5.5, 4,0);
    for (int i = 0; i < h.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, h.at(i));
    }
    
    glColor3f(0, .4, 1);
    glRasterPos3f(5.5, 3,0);
    for (int i = 0; i < t.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, t.at(i));
    }
    
    glColor3f(1, 0, 1);
    glRasterPos3f(5.5, 2,0);
    for (int i = 0; i < l.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, l.at(i));
    }
    
    //Text for Next
    glColor3f(1, 1, 1);
    glRasterPos3f(5.5, 9.4, 0);
    for (int i = 0; i < N.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, N.at(i));
    }
}

//draw the help settings
void drawHelp()
{
    string A = "UP: Rotate Piece";
    string B = "DOWN: Move The Piece Down";
    string C = "LEFT: Move Piece Left";
    string D = "RIGHT: Move Piece Right";
    string E = "ESC: Exit The Program";
    string F = "DEL: Back To Main Menu";
    
    string phrases[6] = {A, B, C, D, E, F};
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPushMatrix();
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glColor3f(0, 1, 0);
    
    for(int i = 0; i < 6; i++)
    {
        glRasterPos3f(2, 7-i,0);
        for(int j = 0; j < phrases[i].length(); j++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, phrases[i][j]);
        }
    }
    
    glutSwapBuffers();
}

//draw lose screen
void drawLose()
{
    string lose = "YOU LOSE! PRESS ESC TO CLOSE!";
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPushMatrix();
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glColor3f(0, 1, 0);
    glRasterPos3f(3, 5,0);
    
    for (int i = 0; i < lose.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lose.at(i));
    }
    
    glutSwapBuffers();
}

//main menu screen
void drawMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPushMatrix();
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    string o1 = "Play!";
    string o2 = "Help?";
    string o3 = "Highscore";
    string o4 = "Exit.";
    
    //TETRIS TITLE
    //Letter T
    title[0][0] = 3;
    title[0][1] = 3;
    title[0][2] = 3;
    title[1][1] = 3;
    title[2][1] = 3;
    title[3][1] = 3;
    title[4][1] = 3;
    
    //Letter E
    title[0][4] = 5;
    title[1][4] = 5;
    title[2][4] = 5;
    title[3][4] = 5;
    title[4][4] = 5;
    title[0][5] = 5;
    title[2][5] = 5;
    title[4][5] = 5;
    
    //Letter T
    title[0][7] = 1;
    title[0][8] = 1;
    title[0][9] = 1;
    title[1][8] = 1;
    title[2][8] = 1;
    title[3][8] = 1;
    title[4][8] = 1;
    
    //Letter R
    title[0][11] = 6;
    title[0][12] = 6;
    title[0][13] = 6;
    title[1][11] = 6;
    title[2][11] = 6;
    title[3][11] = 6;
    title[4][11] = 6;
    title[1][13] = 6;
    title[2][12] = 6;
    title[4][13] = 6;
    title[3][13] = 6;
    
    //Letter I
    title[0][15] = 4;
    title[2][15] = 4;
    title[3][15] = 4;
    title[4][15] = 4;
    
    //Letter S
    title[0][17] = 7;
    title[0][18] = 7;
    title[0][19] = 7;
    title[1][17] = 7;
    title[2][18] = 7;
    title[3][19] = 7;
    title[4][19] = 7;
    title[4][18] = 7;
    title[4][17] = 7;
    
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            switch(title[i][j])
            {
                case 1:
                    glBegin(GL_POLYGON);
                    glColor3f(1, 1, 0); //color of our block yellow
                    glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 3:
                    glBegin(GL_POLYGON);
                    glColor3f(1, 0, 0); //color of our block red
                    glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 4:
                    glBegin(GL_POLYGON);
                    glColor3f(0, .4, 1); //color of our block blue
                    glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 5:
                    glBegin(GL_POLYGON);
                    glColor3f(1, .4, 0); //color of our block orange
                    glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 6:
                    glBegin(GL_POLYGON);
                    glColor3f(0, 1, 0); //color of our block green
                    glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 7:
                    glBegin(GL_POLYGON);
                    glColor3f(.63, .13, .95); // purple
                    glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
            }
        }
    }
    
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            switch(nextBoard[i][j])
            {
                case 1:
                    glBegin(GL_POLYGON);
                    glColor3f(1, 1, 0); //color of our block
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 2:
                    glBegin(GL_POLYGON);
                    glColor3f(0, 1, 1);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 3:
                    glBegin(GL_POLYGON);
                    glColor3f(1, 0, 0);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 4:
                    glBegin(GL_POLYGON);
                    glColor3f(0, 1, 0);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 5:
                    glBegin(GL_POLYGON);
                    glColor3f(1, .4, 0);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 6:
                    glBegin(GL_POLYGON);
                    glColor3f(0, .4, 1);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 7:
                    glBegin(GL_POLYGON);
                    glColor3f(.63, .13, .95);
                    glVertex3f(7.5 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(7.9 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(7.9 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(7.5 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
            }
        }
    }

    //Box for Play
    glLoadIdentity();
    glColor3f(1, 0, 0);
    glRasterPos3f(4.4, 6,0);
    
    //left edge of box
    glBegin(GL_POLYGON);
    glVertex3f(3.65, 5.74, 0.0); // bottom left corner
    glVertex3f(3.65, 6.5, 0.0); // top left corner
    glVertex3f(3.8, 6.5, 0.0); // top right corner
    glVertex3f(3.8, 5.74, 0.0); // bottom right corner
    glEnd();
    
    //right edge of box
    glBegin(GL_POLYGON);
    glVertex3f(5.7, 5.74, 0.0); // bottom left corner
    glVertex3f(5.7, 6.5, 0.0); // top left corner
    glVertex3f(5.85, 6.5, 0.0); // top right corner
    glVertex3f(5.85, 5.74, 0.0); // bottom right corner
    glEnd();
    
    for (int i = 0; i < o1.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o1.at(i));
    }
    
    //Box for Help
    glColor3f(0, 1, 0);
    glRasterPos3f(4.4, 4,0);
    
    //left edge of box
    glBegin(GL_POLYGON);
    glVertex3f(3.65, 3.74, 0.0); // bottom left corner
    glVertex3f(3.65, 4.5, 0.0); // top left corner
    glVertex3f(3.8, 4.5, 0.0); // top right corner
    glVertex3f(3.8, 3.74, 0.0); // bottom right corner
    glEnd();
    
    //right edge of box
    glBegin(GL_POLYGON);
    glVertex3f(5.7, 3.74, 0.0); // bottom left corner
    glVertex3f(5.7, 4.5, 0.0); // top left corner
    glVertex3f(5.85, 4.5, 0.0); // top right corner
    glVertex3f(5.85, 3.74, 0.0); // bottom right corner
    glEnd();
    
    for (int i = 0; i < o2.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o2.at(i));
    }
    
    //Box for Highscore
    glColor3f(0, .4, 1);
    glRasterPos3f(4.15, 5,0);
    
    //left edge of box
    glBegin(GL_POLYGON);
    glVertex3f(3.65, 4.74, 0.0); // bottom left corner
    glVertex3f(3.65, 5.5, 0.0); // top left corner
    glVertex3f(3.8, 5.5, 0.0); // top right corner
    glVertex3f(3.8, 4.74, 0.0); // bottom right corner
    glEnd();
    
    //right edge of box
    glBegin(GL_POLYGON);
    glVertex3f(5.7, 4.74, 0.0); // bottom left corner
    glVertex3f(5.7, 5.5, 0.0); // top left corner
    glVertex3f(5.85, 5.5, 0.0); // top right corner
    glVertex3f(5.85, 4.74, 0.0); // bottom right corner
    glEnd();
    
    for (int i = 0; i < o3.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o3.at(i));
    }
    
    //Box for Exit
    glColor3f(1, 0, 1);
    glRasterPos3f(4.4, 3,0);
    
    //left edge of box
    glBegin(GL_POLYGON);
    glVertex3f(3.65, 2.74, 0.0); // bottom left corner
    glVertex3f(3.65, 3.5, 0.0); // top left corner
    glVertex3f(3.8, 3.5, 0.0); // top right corner
    glVertex3f(3.8, 2.74, 0.0); // bottom right corner
    glEnd();
    
    //right edge of box
    glBegin(GL_POLYGON);
    glVertex3f(5.7, 2.74, 0.0); // bottom left corner
    glVertex3f(5.7, 3.5, 0.0); // top left corner
    glVertex3f(5.85, 3.5, 0.0); // top right corner
    glVertex3f(5.85, 2.74, 0.0); // bottom right corner
    glEnd();
    for (int i = 0; i < o4.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o4.at(i));
    }
    
    glutSwapBuffers();
}

void draw()
{
 
}

void pass(int x, int y)
{
    if(!playing && !menu)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glPushMatrix();
        glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        string o1 = "Play!";
        string o2 = "Help?";
        string o3 = "Highscore";
        string o4 = "Exit.";
        
        //TETRIS TITLE
        //Letter T
        title[0][0] = 3;
        title[0][1] = 3;
        title[0][2] = 3;
        title[1][1] = 3;
        title[2][1] = 3;
        title[3][1] = 3;
        title[4][1] = 3;
        
        //Letter E
        title[0][4] = 5;
        title[1][4] = 5;
        title[2][4] = 5;
        title[3][4] = 5;
        title[4][4] = 5;
        title[0][5] = 5;
        title[2][5] = 5;
        title[4][5] = 5;
        
        //Letter T
        title[0][7] = 1;
        title[0][8] = 1;
        title[0][9] = 1;
        title[1][8] = 1;
        title[2][8] = 1;
        title[3][8] = 1;
        title[4][8] = 1;
        
        //Letter R
        title[0][11] = 6;
        title[0][12] = 6;
        title[0][13] = 6;
        title[1][11] = 6;
        title[2][11] = 6;
        title[3][11] = 6;
        title[4][11] = 6;
        title[1][13] = 6;
        title[2][12] = 6;
        title[4][13] = 6;
        title[3][13] = 6;
        
        //Letter I
        title[0][15] = 4;
        title[2][15] = 4;
        title[3][15] = 4;
        title[4][15] = 4;
        
        //Letter S
        title[0][17] = 7;
        title[0][18] = 7;
        title[0][19] = 7;
        title[1][17] = 7;
        title[2][18] = 7;
        title[3][19] = 7;
        title[4][19] = 7;
        title[4][18] = 7;
        title[4][17] = 7;
        
        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 20; j++)
            {
                switch(title[i][j])
                {
                    case 1:
                        glBegin(GL_POLYGON);
                        glColor3f(1, 1, 0); //color of our block yellow
                        glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                        glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                        glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                        glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                        glEnd();
                        break;
                        
                    case 3:
                        glBegin(GL_POLYGON);
                        glColor3f(1, 0, 0); //color of our block red
                        glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                        glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                        glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                        glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                        glEnd();
                        break;
                        
                    case 4:
                        glBegin(GL_POLYGON);
                        glColor3f(0, .4, 1); //color of our block blue
                        glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                        glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                        glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                        glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                        glEnd();
                        break;
                        
                    case 5:
                        glBegin(GL_POLYGON);
                        glColor3f(1, .4, 0); //color of our block orange
                        glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                        glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                        glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                        glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                        glEnd();
                        break;
                        
                    case 6:
                        glBegin(GL_POLYGON);
                        glColor3f(0, 1, 0); //color of our block green
                        glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                        glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                        glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                        glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                        glEnd();
                        break;
                        
                    case 7:
                        glBegin(GL_POLYGON);
                        glColor3f(.63, .13, .95); // purple
                        glVertex3f(0.85 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top left corner
                        glVertex3f(1.25 + .45 * (j-1), 8.97 - .47 * (i-1), 0.0); // top right corner
                        glVertex3f(1.25 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom right corner
                        glVertex3f(0.85 + .45 * (j-1), 8.57 - .47 * (i-1), 0.0); // bottom left corner
                        glEnd();
                        break;
                }
            }
        }
        
        if(y <= 265 && y >= 220 && x >=301 && x <= 483 && !playing) //&& !playing
        {
            //Box for Play
            glLoadIdentity();
            
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1, 0, 0, .3);
            glRasterPos3f(4.4, 6,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 5.74, 0.0); // bottom left corner
            glVertex3f(3.65, 6.5, 0.0); // top left corner
            glVertex3f(3.8, 6.5, 0.0); // top right corner
            glVertex3f(3.8, 5.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 5.74, 0.0); // bottom left corner
            glVertex3f(5.7, 6.5, 0.0); // top left corner
            glVertex3f(5.85, 6.5, 0.0); // top right corner
            glVertex3f(5.85, 5.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o1.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o1.at(i));
            }
            
            //Box for Help
            glColor3f(0, 1, 0);
            glRasterPos3f(4.4, 4,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 3.74, 0.0); // bottom left corner
            glVertex3f(3.65, 4.5, 0.0); // top left corner
            glVertex3f(3.8, 4.5, 0.0); // top right corner
            glVertex3f(3.8, 3.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 3.74, 0.0); // bottom left corner
            glVertex3f(5.7, 4.5, 0.0); // top left corner
            glVertex3f(5.85, 4.5, 0.0); // top right corner
            glVertex3f(5.85, 3.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o2.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o2.at(i));
            }
            
            //Box for Highscore
            glColor3f(0, .4, 1);
            glRasterPos3f(4.15, 5,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 4.74, 0.0); // bottom left corner
            glVertex3f(3.65, 5.5, 0.0); // top left corner
            glVertex3f(3.8, 5.5, 0.0); // top right corner
            glVertex3f(3.8, 4.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 4.74, 0.0); // bottom left corner
            glVertex3f(5.7, 5.5, 0.0); // top left corner
            glVertex3f(5.85, 5.5, 0.0); // top right corner
            glVertex3f(5.85, 4.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o3.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o3.at(i));
            }
            
            //Box for Exit
            glColor3f(1, 0, 1);
            glRasterPos3f(4.4, 3,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 2.74, 0.0); // bottom left corner
            glVertex3f(3.65, 3.5, 0.0); // top left corner
            glVertex3f(3.8, 3.5, 0.0); // top right corner
            glVertex3f(3.8, 2.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 2.74, 0.0); // bottom left corner
            glVertex3f(5.7, 3.5, 0.0); // top left corner
            glVertex3f(5.85, 3.5, 0.0); // top right corner
            glVertex3f(5.85, 2.74, 0.0); // bottom right corner
            glEnd();
            for (int i = 0; i < o4.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o4.at(i));
            }
        }
        
        //show highscore
        else if(y <= 330 && y >= 280 && x >=301 && x <= 483)
        {
            //Box for Play
            glLoadIdentity();
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor3f(1, 0, 0);
            glRasterPos3f(4.4, 6,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 5.74, 0.0); // bottom left corner
            glVertex3f(3.65, 6.5, 0.0); // top left corner
            glVertex3f(3.8, 6.5, 0.0); // top right corner
            glVertex3f(3.8, 5.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 5.74, 0.0); // bottom left corner
            glVertex3f(5.7, 6.5, 0.0); // top left corner
            glVertex3f(5.85, 6.5, 0.0); // top right corner
            glVertex3f(5.85, 5.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o1.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o1.at(i));
            }
            
            //Box for Help
            glColor3f(0, 1, 0);
            glRasterPos3f(4.4, 4,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 3.74, 0.0); // bottom left corner
            glVertex3f(3.65, 4.5, 0.0); // top left corner
            glVertex3f(3.8, 4.5, 0.0); // top right corner
            glVertex3f(3.8, 3.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 3.74, 0.0); // bottom left corner
            glVertex3f(5.7, 4.5, 0.0); // top left corner
            glVertex3f(5.85, 4.5, 0.0); // top right corner
            glVertex3f(5.85, 3.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o2.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o2.at(i));
            }
            
            //Box for Highscore
            glColor4f(0, .4, 1, .3);
            glRasterPos3f(4.15, 5,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 4.74, 0.0); // bottom left corner
            glVertex3f(3.65, 5.5, 0.0); // top left corner
            glVertex3f(3.8, 5.5, 0.0); // top right corner
            glVertex3f(3.8, 4.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 4.74, 0.0); // bottom left corner
            glVertex3f(5.7, 5.5, 0.0); // top left corner
            glVertex3f(5.85, 5.5, 0.0); // top right corner
            glVertex3f(5.85, 4.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o3.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o3.at(i));
            }
            
            //Box for Exit
            glColor3f(1, 0, 1);
            glRasterPos3f(4.4, 3,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 2.74, 0.0); // bottom left corner
            glVertex3f(3.65, 3.5, 0.0); // top left corner
            glVertex3f(3.8, 3.5, 0.0); // top right corner
            glVertex3f(3.8, 2.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 2.74, 0.0); // bottom left corner
            glVertex3f(5.7, 3.5, 0.0); // top left corner
            glVertex3f(5.85, 3.5, 0.0); // top right corner
            glVertex3f(5.85, 2.74, 0.0); // bottom right corner
            glEnd();
            for (int i = 0; i < o4.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o4.at(i));
            }
        }
        
        //show help
        else if(y <= 390 && y >= 345 && x >=301 && x <= 483)
        {
            //Box for Play
            glLoadIdentity();
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor3f(1, 0, 0);
            glRasterPos3f(4.4, 6,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 5.74, 0.0); // bottom left corner
            glVertex3f(3.65, 6.5, 0.0); // top left corner
            glVertex3f(3.8, 6.5, 0.0); // top right corner
            glVertex3f(3.8, 5.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 5.74, 0.0); // bottom left corner
            glVertex3f(5.7, 6.5, 0.0); // top left corner
            glVertex3f(5.85, 6.5, 0.0); // top right corner
            glVertex3f(5.85, 5.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o1.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o1.at(i));
            }
            
            //Box for Help
            glColor4f(0, 1, 0, .3);
            glRasterPos3f(4.4, 4,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 3.74, 0.0); // bottom left corner
            glVertex3f(3.65, 4.5, 0.0); // top left corner
            glVertex3f(3.8, 4.5, 0.0); // top right corner
            glVertex3f(3.8, 3.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 3.74, 0.0); // bottom left corner
            glVertex3f(5.7, 4.5, 0.0); // top left corner
            glVertex3f(5.85, 4.5, 0.0); // top right corner
            glVertex3f(5.85, 3.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o2.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o2.at(i));
            }
            
            //Box for Highscore
            glColor3f(0, .4, 1);
            glRasterPos3f(4.15, 5,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 4.74, 0.0); // bottom left corner
            glVertex3f(3.65, 5.5, 0.0); // top left corner
            glVertex3f(3.8, 5.5, 0.0); // top right corner
            glVertex3f(3.8, 4.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 4.74, 0.0); // bottom left corner
            glVertex3f(5.7, 5.5, 0.0); // top left corner
            glVertex3f(5.85, 5.5, 0.0); // top right corner
            glVertex3f(5.85, 4.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o3.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o3.at(i));
            }
            
            //Box for Exit
            glColor3f(1, 0, 1);
            glRasterPos3f(4.4, 3,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 2.74, 0.0); // bottom left corner
            glVertex3f(3.65, 3.5, 0.0); // top left corner
            glVertex3f(3.8, 3.5, 0.0); // top right corner
            glVertex3f(3.8, 2.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 2.74, 0.0); // bottom left corner
            glVertex3f(5.7, 3.5, 0.0); // top left corner
            glVertex3f(5.85, 3.5, 0.0); // top right corner
            glVertex3f(5.85, 2.74, 0.0); // bottom right corner
            glEnd();
            for (int i = 0; i < o4.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o4.at(i));
            }
        }
        
        //exit the game
        else if(y <= 470 && y >= 400 && x >=301 && x <= 483)
        {
            //Box for Play
            glLoadIdentity();
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor3f(1, 0, 0);
            glRasterPos3f(4.4, 6,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 5.74, 0.0); // bottom left corner
            glVertex3f(3.65, 6.5, 0.0); // top left corner
            glVertex3f(3.8, 6.5, 0.0); // top right corner
            glVertex3f(3.8, 5.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 5.74, 0.0); // bottom left corner
            glVertex3f(5.7, 6.5, 0.0); // top left corner
            glVertex3f(5.85, 6.5, 0.0); // top right corner
            glVertex3f(5.85, 5.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o1.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o1.at(i));
            }
            
            //Box for Help
            glColor3f(0, 1, 0);
            glRasterPos3f(4.4, 4,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 3.74, 0.0); // bottom left corner
            glVertex3f(3.65, 4.5, 0.0); // top left corner
            glVertex3f(3.8, 4.5, 0.0); // top right corner
            glVertex3f(3.8, 3.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 3.74, 0.0); // bottom left corner
            glVertex3f(5.7, 4.5, 0.0); // top left corner
            glVertex3f(5.85, 4.5, 0.0); // top right corner
            glVertex3f(5.85, 3.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o2.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o2.at(i));
            }
            
            //Box for Highscore
            glColor3f(0, .4, 1);
            glRasterPos3f(4.15, 5,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 4.74, 0.0); // bottom left corner
            glVertex3f(3.65, 5.5, 0.0); // top left corner
            glVertex3f(3.8, 5.5, 0.0); // top right corner
            glVertex3f(3.8, 4.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 4.74, 0.0); // bottom left corner
            glVertex3f(5.7, 5.5, 0.0); // top left corner
            glVertex3f(5.85, 5.5, 0.0); // top right corner
            glVertex3f(5.85, 4.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o3.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o3.at(i));
            }
            
            //Box for Exit
            glColor4f(1, 0, 1, .3);
            glRasterPos3f(4.4, 3,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 2.74, 0.0); // bottom left corner
            glVertex3f(3.65, 3.5, 0.0); // top left corner
            glVertex3f(3.8, 3.5, 0.0); // top right corner
            glVertex3f(3.8, 2.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 2.74, 0.0); // bottom left corner
            glVertex3f(5.7, 3.5, 0.0); // top left corner
            glVertex3f(5.85, 3.5, 0.0); // top right corner
            glVertex3f(5.85, 2.74, 0.0); // bottom right corner
            glEnd();
            for (int i = 0; i < o4.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o4.at(i));
            }
        }
        
        else
        {
            //Box for Play
            glLoadIdentity();
            glColor3f(1, 0, 0);
            glRasterPos3f(4.4, 6,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 5.74, 0.0); // bottom left corner
            glVertex3f(3.65, 6.5, 0.0); // top left corner
            glVertex3f(3.8, 6.5, 0.0); // top right corner
            glVertex3f(3.8, 5.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 5.74, 0.0); // bottom left corner
            glVertex3f(5.7, 6.5, 0.0); // top left corner
            glVertex3f(5.85, 6.5, 0.0); // top right corner
            glVertex3f(5.85, 5.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o1.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o1.at(i));
            }
            
            //Box for Help
            glColor3f(0, 1, 0);
            glRasterPos3f(4.4, 4,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 3.74, 0.0); // bottom left corner
            glVertex3f(3.65, 4.5, 0.0); // top left corner
            glVertex3f(3.8, 4.5, 0.0); // top right corner
            glVertex3f(3.8, 3.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 3.74, 0.0); // bottom left corner
            glVertex3f(5.7, 4.5, 0.0); // top left corner
            glVertex3f(5.85, 4.5, 0.0); // top right corner
            glVertex3f(5.85, 3.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o2.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o2.at(i));
            }
            
            //Box for Highscore
            glColor3f(0, .4, 1);
            glRasterPos3f(4.15, 5,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 4.74, 0.0); // bottom left corner
            glVertex3f(3.65, 5.5, 0.0); // top left corner
            glVertex3f(3.8, 5.5, 0.0); // top right corner
            glVertex3f(3.8, 4.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 4.74, 0.0); // bottom left corner
            glVertex3f(5.7, 5.5, 0.0); // top left corner
            glVertex3f(5.85, 5.5, 0.0); // top right corner
            glVertex3f(5.85, 4.74, 0.0); // bottom right corner
            glEnd();
            
            for (int i = 0; i < o3.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o3.at(i));
            }
            
            //Box for Exit
            glColor3f(1, 0, 1);
            glRasterPos3f(4.4, 3,0);
            
            //left edge of box
            glBegin(GL_POLYGON);
            glVertex3f(3.65, 2.74, 0.0); // bottom left corner
            glVertex3f(3.65, 3.5, 0.0); // top left corner
            glVertex3f(3.8, 3.5, 0.0); // top right corner
            glVertex3f(3.8, 2.74, 0.0); // bottom right corner
            glEnd();
            
            //right edge of box
            glBegin(GL_POLYGON);
            glVertex3f(5.7, 2.74, 0.0); // bottom left corner
            glVertex3f(5.7, 3.5, 0.0); // top left corner
            glVertex3f(5.85, 3.5, 0.0); // top right corner
            glVertex3f(5.85, 2.74, 0.0); // bottom right corner
            glEnd();
            for (int i = 0; i < o4.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, o4.at(i));
            }
        }
        
        glutSwapBuffers();
    }
}

//mouse click events
void button(int button, int state, int x, int y)
{
    if(!playing)
    {
        if(button == GLUT_RIGHT_BUTTON || button == GLUT_LEFT_BUTTON)
        {
            if(state == GLUT_UP)
            {
                if(y <= 265 && y >= 220 && x >=301 && x <= 483 && !playing) //&& !playing
                {
                    //only do music if on mac
#ifndef _WIN32
                    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
                    
                    //initalize Mixer API
                    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );
                    
                    //Song is not originally mine: https://www.youtube.com/watch?v=E8FQBjVlERk
                    song = Mix_LoadMUS( "/Users/Bryan/Desktop/College/Computer Engineering /All Programmin'/C++ COP 3503/Tetris-Master/Tetris-Master/beat.mp3" );
                    
                    if( Mix_PlayingMusic() == 0 )
                    {
                        //Play the music
                        Mix_PlayMusic(song, -1);
                    }
#endif
                    
                    //play game
                    playing = true;
                    
                    //Play Game
                    Timer(0);
                }
                
                //show highscore
                else if(y <= 330 && y >= 280 && x >=301 && x <= 483)
                {
                    menu = true;
                    player.displayScores();
                    glutSpecialFunc(menuKeys);
                }
                
                //show help
                else if(y <= 390 && y >= 345 && x >=301 && x <= 483)
                {
                    menu = true;
                    drawHelp();
                    glutSpecialFunc(menuKeys);
                }
                
                //exit the game
                else if(y <= 470 && y >= 400 && x >=301 && x <= 483)
                {
                    exit(0);
                }
            }
        }
    }
}

void reshape(int w, int h)
{
    glutReshapeWindow(825,625);
}

int main(int argc, char * argv[])
{
    string name = "";
    bool correct = false;
    
    do
    {
        cout << "Enter your name with no spaces: " << endl;
        getline(cin, name);
        
        for(int i = 0; i < name.length(); i++)
        {
            if(name[i] == ' ')
            {
                correct = false;
                break;
            }
            
            correct = true;
        }
    } while(!correct);
    
    name += ":";
    player.setName(name);
    player.importFile();
    
    glutInit(&argc, argv); //initializes our window
    glutInitWindowSize(825,625); //sets our window size
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //sets the display mode
    glutCreateWindow("Tetris"); //The title of our window
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(drawMenu);
    glutMouseFunc(button);
    
    glutPassiveMotionFunc(pass);
    glutMainLoop();

    return 0;
}

//adding comments to reach 2000
//yeah
//there it is