/**
 * Kompiuterinės grafikos 2 užduotis. 
 * Fraktalai.
 * 
 * @author Aurelijus Banelis
 */

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

int currentNum = 0;
int d = 0;

void onKeyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(1);
        break;
        case 'd':
            if (d < 360) {
                d += 10;
            } else {
                d -= 360;
            }
        break;
        case ' ':
            if (currentNum < 12) {
                currentNum++;
            } else {
                currentNum = 0;
            }
        break;
    }
    glutPostRedisplay();
}

void drawTriangle() {
    glBegin(GL_QUADS);
        glVertex3f( 0.3, 0.2, 0.0 );
        glVertex3f( 0.6, 1.0, 0.0 );
        glVertex3f( 0.8, 1.0, 0.0 );
        glVertex3f( 1.0, 0.2, 0.0 );
        
        glVertex3f( 0.0, 0.0, 0.0 );
        glVertex3f( 1.0, 0.0, 0.0 );
        glVertex3f( 1.0, 0.2, 0.0 );
        glVertex3f( 0.0, 0.2, 0.0 );

    glEnd();
}

void drawFractal(int num) {
    switch(num) {
    case 0:
        drawTriangle();
        break;
    default:
        /*     T2
         *  T3 T1
         */
        glColor3f( 1.0, 0.0, 1.0 );	
        glPushMatrix();
            glTranslatef(0.5, 0, 0);
            glScalef(0.5, 0.5, 1);
            drawFractal(num - 1);
        glPopMatrix();
        
        glColor3f( 0.0, 1.0, 1.0 );	
        glPushMatrix();
            glTranslatef(1, 1, 0);
            glScalef(0.5, 0.5, 1);
            glRotatef(180, 0, 0, 1);
            drawFractal(num - 1);
        glPopMatrix();
        glColor3f( 1.0, 1.0, 0.0 );	
        glPushMatrix();
            glScalef(-0.5, 0.5, 1);
            glRotatef(270, 0, 0, 1);
            glTranslatef(-1, -1, 0);
            drawFractal(num - 1);
        glPopMatrix();
        break;
    }
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
    glLoadIdentity();
    glTranslatef(-1, -1, 0);
    glScalef(2, 2, 0);

    drawFractal(currentNum);
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // Init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA);
    glutInitWindowPosition(1000,500);
    glutInitWindowSize(320,320);
    glutCreateWindow("U2");    
    
    // Register callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(onKeyPress);

    // Enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}
