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
    for(int i = 0; i < 22; i ++)
    {
        for(int j = 0; j < 12; j ++)
        {
            cout << setw(2) << array[i][j];
        }
        
        cout << endl;
    }
    
    cout << endl;
}

//this function takes in our keyboard inputs
void keys(int key, int w, int y) //movements need to be about the
{
    //Remember to add option to quit which is the esc key
    if(key == GLUT_KEY_UP && x->DROP)
    {
        //rotate method
        x->rotate(board); // rotate our shape
        x->draw(board); //draw our shape to the array
        boardDraw();  //draw our shape to the screen
    }
    
    else if(key == GLUT_KEY_LEFT && x->DROP)
    {
        //left directional key
        x->moveLeft(board); //moves our shape to the left
        x->draw(board); //draw our shape to the array
        boardDraw(); //draw our shape to the screen
    }
    
    else if(key == GLUT_KEY_RIGHT && x->DROP)
    {
        //Right directional key
        x->moveRight(board); //moves our shape to the right
        x->draw(board); //draw our shape to the array
        boardDraw(); //draw our shape to the screen
    }
    
    else if(key == GLUT_KEY_DOWN /*&& x->DROP*/)
    {
        //Down directional key
        x->moveDown(board); //moves the shape down
        x->draw(board); //draw our shape to the array
        boardDraw(); //draw our shape to the screen
    }
    
    else if (key == 32) //space key
    {
        //set piece immediately
        x->dropSet(board); // this is wonky. when there is space beneath tiles it runs forever??
        x->draw(board);
        boardDraw();
    }
}

void Timer(int a)
{
    /*
     some where along the line if I drop the line block on top of a square, if the right block is the one touching it will
     not recreate a part...
     */

    if(!change) //checks to see if we are dealing with the same shape
    {
        x = generatePart(board); // if the shape has set, generate a new shape
        change = true; // set change to true to not generate a new shape until the one we just generated sets
    }
    
    //Drop variable to set to true so that we cannot move once we drop set
    //if this is not here it will not work for some reason
    x->DROP = true;
    
    //display board to console for testing
    print(board);
    x->draw(board); //draw shape to board
    print(board);
    boardDraw(); // draw shape to screen window
    
    if(typeid(*x) == typeid(Square)) //if we are dealing with a sqare block (C++ version of java instanceof)
    {
        //board[x->Y4+1][x->X4] == 0 && board[x->Y3+1][x->X3] == 0
        if(x->moveDown(board)) //check if down move is available
        {
            glutDisplayFunc(draw);
            glutSpecialFunc(keys);
            glutTimerFunc(speed, Timer, 0);
            glutPostRedisplay();
        }
        
        //if(board[x->Y4+1][x->X4] != 0 || board[x->Y3+1][x->X3] != 0)
        else if(!x->moveDown(board))// if the cube reached the bottom
        {
            change = false;
            glutDisplayFunc(draw);
            glutTimerFunc(1, Timer, 0);
            glutPostRedisplay();
        }
    }
    
    else if(typeid(*x) == typeid(Line)) //if we are dealing with a line block
    {
        //this will only work for a line right now and square
         //&& board[x->Y4+1][x->X4] == 0 && board[x->Y3+1][x->X3] == 0
        if(x->moveDown(board))
        {
            glutTimerFunc(speed, Timer, 0);
            glutDisplayFunc(draw);
            glutSpecialFunc(keys);
            glutPostRedisplay();
        }
        
        // generate and draw soon after
        else if(!x->moveDown(board))
        {
            change = false;
            glutTimerFunc(1, Timer, 0);
            glutDisplayFunc(draw);
            glutPostRedisplay();
        }
    }
}

Shape *generatePart(int board[22][12])
{
    /*
     This method is to generate new parts
     Once you believe your classes are done, do x = new YOURSHAPE();
     Then x->draw(board) (We may not need this call since our timer function has it...
     */
    
    partsCreated++;
    
    /*
    if(partsCreated > 1) //use this logic to speed up process for levels
    {
        partsCreated = 0;
        speed = 1000;
    }
     */
    
    srand(time(NULL));

    int random = rand() % 2; // numbers 0 to 1
    
    switch(1) //chooses a shape at random
    {
        case 0:
            // generate Cube
            x = new Square();
            x->draw(board);
            return x;
            break;
            
        case 1:
            //generate Line
            x = new Line();
            x->draw(board);
            return x;
            break;
            
        case 2:
            //generate Z-block
            break;
            
        case 3:
            //generate reverse Z-block
            break;
            
        case 4:
            //generate L-block
            break;
            
        case 5:
            //generate Reverse L-Block
            break;
            
        case 6:
            //generate T-block
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
                    
                case 3:
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
                    
                case 4:
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
                    
                case 5:
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
                    
                case 6:
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
                    
                case 7:
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
    
    /*
     This is for music but may not work.  Since it is not essential to testing, 
     I commented this and the necessary includes out so it will not crash your program
     
     CODE:

    //With curtosy from Lazy Foo Productions
    //initialize SDL
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    
    //initalize Mixer API
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );
    
    //This will not work for people not using my folder
    //make sure you change the path if you are using a differnet system and folder
    song = Mix_LoadMUS( "/Users/Bryan/Desktop/College/Computer Engineering /All Programmin'/C++ COP 3503/Function Pointers/Function Pointers/beat.mp3" );
    
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic(song, -1);
    }
     */
    
    Timer(0); // our Main timer function
    glutMainLoop();
    
    return 0;
}
