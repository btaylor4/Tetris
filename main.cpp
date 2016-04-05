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

void clearLines(int board[22][12])
{
    int repeat = 0;
    int count = 0;
    int TEMPI = 0;
    bool clear = false;
    int numLines = 0;
   
    do
    {
        repeat++;
        
        for(int i = 20; i >= 0; i--)
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
                        count = 0;
                        clear = true;
                        j = 0;
                    }
                }
                
                else if(clear)
                {
                    TEMPI = i;
                    
                    while(i != 0)
                    {
                        board[i][j] = board[i-1][j];
                        board[i-1][j] = 0;
                        i--;
                    }
        
                    i = TEMPI;
                    
                    count ++;
                    
                    if(count == 10)
                    {
                        count = 0;
                        clear = false;
                    }
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
            score+= 100;
            break;
            
        case 2:
            score+= 200;
            break;
            
        case 3:
            score+= 300;
            break;
            
        case 4:
            score+= 800;
            break;
    }
}

//this function takes in our keyboard inputs
void keys(int key, int w, int y) //movements need to be about the
{
    //Remember to add option to quit which is the esc key
    if(key == GLUT_KEY_UP)
    {
        //rotate method
        x->rotate(board);// rotate our shape
        //x->ghost(board);
        x->draw(board); //draw our shape to the array
        boardDraw();  //draw our shape to the screen
    }
    
    if(key == GLUT_KEY_LEFT)
    {
        //left directional key
        x->moveLeft(board); //moves our shape to the left
        //x->ghost(board);
        x->draw(board);
        boardDraw(); //draw our shape to the screen
    }
    
    if(key == GLUT_KEY_RIGHT)
    {
        //Right directional key
        x->moveRight(board); //moves our shape to the right
        //x->ghost(board);
        x->draw(board); //draw our shape to the array
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
        exit(0);
    }
}

void Timer(int a)
{
    if(!change) //checks to see if we are dealing with the same shape
    {
        x = generatePart(board); // if the shape has set, generate a new shape
        change = true; // set change to true to not generate a new shape until the one we just generated sets
    }
    
    if( x == NULL)
    {
        char choice =' ';
        boardDraw();
        cout << "Game over" << endl;
        cout << "Wish to play again?" << endl;
        cin >> choice;
        
        if( choice == 'Y')
        {
            for(int i = 1; i < 21; i++)
            {
                for(int j = 1; j < 11; j++)
                {
                    board[i][j] = 0;
                }
            }
            
            boardDraw();
            x = generatePart(board);
            change = true;
            speed = 1000;
        }
        
        else if (choice == 'N')
            exit(0);
    }
    
    x->draw(board); //draw shape to board
    boardDraw(); // draw shape to screen window
    
    if(x->moveDown(board)) //check if down move is available
    {
        cout << "Score: " << score << endl;
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
        glutTimerFunc(.1, Timer, 0);
        glutPostRedisplay();
    }    
}

Shape *generatePart(int board[22][12])
{
    
    /*
     This method is to generate new parts
     Once you believe your classes are done, do x = new YOURSHAPE();
     Then x->draw(board) (We may not need this call since our timer function has it...
     */
    int random = 0;
    
    partsCreated++;
    
    if(partsCreated > 5)
    {
        speed -= 50;
        partsCreated = 0;
    }

    //code to make choices more random
    if(partsCreated > 1)
    {
        do
        {
            srand(time(NULL));
            random = rand() % 6;
        } while(random == randChoice);
        
        randChoice = random;
    }
    
    else
    {
        srand(time(NULL));
        random = rand() % 6;
        randChoice = random;
    }
    
    switch(random) //chooses a shape at random
    {
        case 0:
            // generate Cube
            x = new Square();
            
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
            return x;
            break;
            
        case 3:
            //generate reverse Z-block
            x = new ReverseZ();
            x->draw(board);
            return x;
            break;
            
        case 4:
            //generate T-block
            x = new TBlock();
            x->draw(board);
            return x;
            break;
            
        case 5:
            //generate Reverse L-Block
            x = new J();
            x->draw(board);
            return x;
            break;
            
        case 6:
            //generate L-block
            break;
    }
    
    return x; // return our shape
}

void boardDraw()
{
    //This method takes care of drawing our shapes in our window
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    drawBorder();

    for(int i = 1; i < 21; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            switch(board[i][j])
            {
                case 1: //if a square block
                    glMatrixMode(GL_MODELVIEW);
                    glPushMatrix();
                    glLoadIdentity();
                    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
                    
                    glBegin(GL_POLYGON);
                    glColor3f(1, 1, 0); //color of our block
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 2: // if a line block
                    glMatrixMode(GL_MODELVIEW);
                    glPushMatrix();
                    glLoadIdentity();
                    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
                    
                    
                    glBegin(GL_POLYGON);
                    glColor3f(0, 1, 1);
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 3: // if a z block
                    glMatrixMode(GL_MODELVIEW);
                    glPushMatrix();
                    glLoadIdentity();
                    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
                    
                    glBegin(GL_POLYGON);
                    glColor3f(1, 0, 0);
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 4: //if a reverse z block(s block)
                    glMatrixMode(GL_MODELVIEW);
                    glPushMatrix();
                    glLoadIdentity();
                    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
                    
                    glBegin(GL_POLYGON);
                    glColor3f(0, 1, 0);
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 5: // if a L block
                    glMatrixMode(GL_MODELVIEW);
                    glPushMatrix();
                    glLoadIdentity();
                    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
                    
                    glBegin(GL_POLYGON);
                    glColor3f(1, 1, 0);
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 6: //if a reverse L block
                    glMatrixMode(GL_MODELVIEW);
                    glPushMatrix();
                    glLoadIdentity();
                    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
                    
                    glBegin(GL_POLYGON);
                    glColor3f(0, 0, 1);
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 7: // if a t block
                    glMatrixMode(GL_MODELVIEW);
                    glPushMatrix();
                    glLoadIdentity();
                    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
                    
                    glBegin(GL_POLYGON);
                    glColor3f(.63, .13, .95);
                    glVertex3f(.35 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top left corner
                    glVertex3f(.75 + .45 * (j-1), 9.67 - .47 * (i-1), 0.0); // top right corner
                    glVertex3f(.75 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom right corner
                    glVertex3f(.35 + .45 * (j-1), 9.27 - .47 * (i-1), 0.0); // bottom left corner
                    glEnd();
                    break;
                    
                case 8: //ghost color
                    glEnable(GL_BLEND);
                    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glMatrixMode(GL_MODELVIEW);
                    glPushMatrix();
                    glLoadIdentity();
                    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
                    
                    glBegin(GL_POLYGON);
                    glColor4f(1, 1, 1, .3);
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

void draw()
{
 
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv); //initializes our window
    glutInitWindowSize(825,625); //sets our window size
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //sets the display mode
    glutCreateWindow("Tetris"); //The title of our window
    
    Timer(0); // our Main timer function
    glutMainLoop();
    
    return 0;
}
