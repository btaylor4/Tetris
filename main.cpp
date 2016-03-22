//
//  main.cpp
//  Function Pointers
//
//  Created by Bryan Taylor on 3/11/16.
//  Copyright © 2016 Bryan Taylor. All rights reserved.
//

/////////////////////////////// NOTES //////////////////////////////////
/*
 window size is 825 x 625 (x-length, y-length)
 
 draw function takes floats 0-10
 
 if we had x and y as coordinates in our window pane (0,0) would be the bottom left corner.
 (10,10) would be top right corner
 
 Border number is .3 in length in x direction, so 24.75 pixels in the x direction
 Shapes are going to be .2 away from the border so .3 + .2 =
 
 If each square is .4, then in the square = 33 pixels * 10pieces = at least 330 pixels across for playing space
    -this does not include the distance between every square in the same shape
 
 Where to Place border according to above numbers:
    -825 - 330 = 495 + 24.75 = 519.75(this will be the left edge of our left border)
    -Then + 24.75 = 544.5 (this will be the right edge of our left border)
 
 How far do we want the distance between our border and our shapes (will x and y be the same)?
    -I am thinking .2
 How far do we want the distance between our spaces between each square in our shape
 
 Objects: Inheritance
 Data fields: string for the type, 4 i coordinates, 4 j coordinates, function which is overriden
 
 if each square is .4 in the x direction is 33 pixels * 10pieces = at least 330 pixels across for space
 825 - 330 = 495(this will be the left edge of our left border.
 */
///////////////////////////////////////////////////////////////////////

#include "main.h" 

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

void keys(int key, int w, int y) //movements need to be about the
{
    if(key == GLUT_KEY_UP && x->DROP)
    {
        //rotate method
        x->rotate(board);
        x->draw(board);
        boardDraw(); 
    }
    
    else if(key == GLUT_KEY_LEFT && x->DROP)
    {
        //left directional key
        x->moveLeft(board);
        x->draw(board);
        boardDraw();
    }
    
    else if(key == GLUT_KEY_RIGHT && x->DROP)
    {
        //Right directional key
        x->moveRight(board);
        x->draw(board);
        boardDraw();
    }
    
    else if(key == GLUT_KEY_DOWN /*&& x->DROP*/)
    {
        //Down directional key
        x->moveDown(board);
        x->draw(board);
        boardDraw();
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

    if(!change)
    {
        x = generatePart(board);
        change = true;
    }
    
    x->DROP = true;
    
    print(board);
    x->draw(board);
    print(board);
    boardDraw();
    
    if(typeid(*x) == typeid(Square)) //if we are dealing with a sqare block
    {
        //board[x->Y4+1][x->X4] == 0 && board[x->Y3+1][x->X3] == 0
        if(x->moveDown(board))
        {
            glutDisplayFunc(draw);
            glutSpecialFunc(keys);
            glutTimerFunc(500, Timer, 0);
            glutPostRedisplay();
        }
        
        //if(board[x->Y4+1][x->X4] != 0 || board[x->Y3+1][x->X3] != 0)
        // if the cube reached the bottom
        else if(!x->moveDown(board))
        {
            free(x);
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
            free(x);
            change = false;
            glutTimerFunc(1, Timer, 0);
            glutDisplayFunc(draw);
            glutPostRedisplay();
        }
    }
}

Shape *generatePart(int board[22][12])
{
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
    
    switch(random)
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
    
    return x;
}

void boardDraw()
{
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
                    glColor3f(1, 1, 0);
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
    glutInit(&argc, argv);
    glutInitWindowSize(825,625);
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tetris");
    
    
    //glutTimerFunc(200, NULL, 0);
    
    //With curtosy from Lazy Foo Productions
    //initialize SDL
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    
    //initalize Mixer API
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );
    
    song = Mix_LoadMUS( "/Users/Bryan/Desktop/College/Computer Engineering /All Programmin'/C++ COP 3503/Function Pointers/Function Pointers/beat.mp3" );
    
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic(song, -1);
    }
    
    Timer(0);
    glutMainLoop();
    
    return 0;
}
