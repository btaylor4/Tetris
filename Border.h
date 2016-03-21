//
//  Border.h
//  Function Pointers
//
//  Created by Bryan Taylor on 3/18/16.
//  Copyright © 2016 Bryan Taylor. All rights reserved.
//

#ifndef Border_h
#define Border_h

#define GL_GLEXT_PROTOTYPES
#include <GLUT/glut.h>

void drawBorder()
{
    glClear( GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
    
    //left border
    glBegin(GL_POLYGON);
    glColor3f(0.63, .63, .63); //grayish color
    glVertex3f(0, 0, 0.0); // bottom left corner
    glVertex3f(0, 10, 0.0); // top left corner
    glVertex3f(.3, 10, 0.0); // top right corner
    glVertex3f(.3, 0, 0.0); // bottom right corner
    glEnd();
    
    //top border
    glBegin(GL_POLYGON);
    glColor3f(0.63, .63, .63); //grayish color
    glVertex3f(0, 9.7, 0.0); // bottom left corner
    glVertex3f(0, 10, 0.0); // top left corner
    glVertex3f(4.85, 10, 0.0); // top right corner
    glVertex3f(4.85, 9.7, 0.0); // bottom right corner
    glEnd();
    
    //right border
    glBegin(GL_POLYGON);
    glColor3f(0.63, .63, .63); //grayish color
    glVertex3f(4.85, 0, 0.0); // bottom left corner
    glVertex3f(4.85, 10, 0.0); // top left corner
    glVertex3f(5.15, 10, 0.0); // top right corner
    glVertex3f(5.15, 0, 0.0); // bottom right corner
    glEnd();
    
    //bottom border
    glBegin(GL_POLYGON);
    glColor3f(0.63, .63, .63); //grayish color
    glVertex3f(0, 0, 0.0); // bottom left corner
    glVertex3f(0, .3, 0.0); // top left corner
    glVertex3f(4.85, .3, 0.0); // top right corner
    glVertex3f(4.85, 0, 0.0); // bottom right corner
    glEnd();
}
#endif /* Border_h */
