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

void onKeyPress(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(1);
        break;
        case ' ':
            if (currentNum < 6) {
                currentNum++;
            } else {
                currentNum = 0;
            }
            glutPostRedisplay();
        break;
    }
}

void drawTriangle() {
    glBegin( GL_TRIANGLES );
		glVertex3f( 1.0, 0.0, 0.0 );
		glVertex3f( 0.0, 1.0, 0.0 );
		glVertex3f( 0.0, 0.0, 0.0 );
    glEnd();
}

void drawFractal(int num) {
    switch(num) {
    case 0:
        drawTriangle();
        break;
    default:
        glPushMatrix();
            glScalef(0.5,0.5,1.0);
            drawFractal(num - 1);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.5,0.0,0.0);
            glScalef(0.5,0.5,1.0);
            drawFractal(num - 1);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0,0.5,0.0);
            glScalef(0.5,0.5,0.5);
            drawFractal(num - 1);
        glPopMatrix();
        break;
    }
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
    glLoadIdentity();
    glTranslatef(-1, -1, 0);
    glColor3f( 1.0, 1.0, 1.0 );	
    
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

    return 1;
}
