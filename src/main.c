/**
 * Computer graphics, task 2. 
 * Affine fractals.
 * 
 * @author Aurelijus Banelis
 */

#include <GL/gl.h>
#include <GL/glut.h>
#define KEY_ESCAPE 27

int currentDepth = 0;

void onKeyPress(unsigned char key, int keyX, int keyY) {
    switch (key) {
        case KEY_ESCAPE:
        case 'q':
            exit(1);
        break;
        case ' ':
            if (currentDepth < 9) {
                currentDepth++;
            } else {
                currentDepth = 0;
            }
        break;
    }
    glutPostRedisplay();
}

void drawPicture() {
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

void drawFractal(int depth) {
    switch(depth) {
    case 0:
        drawPicture();
        break;
    default:
        /* Parts of fractal:    T1 T2
         *                      T3 T2
         * 
         * Coordinate system: ^y
         *                    |
         *                    +--->x
         * 
         * Order convention: T(R(S(v)))
         */
        
        glColor3f( 0.5, 1, 0.5 );  //T1
        glPushMatrix();
            glTranslatef(0.5, 1, 0);
            glRotatef(180, 0, 0, 1);
            glScalef(0.25, 0.25, 1);
            drawFractal(depth - 1);
        glPopMatrix();
                
        glColor3f( 0.0, 1.0, 1.0 );	//T2
        glPushMatrix();
            glTranslatef(0.5, 0.5, 1);
            glRotatef(90, 0, 0, 1);
            glScalef(-0.5, 0.5, 1);
            drawFractal(depth - 1);
        glPopMatrix();
        
        glColor3f( 1.0, 1.0, 0.0 );	//T3
        glPushMatrix();
            glTranslatef(1, 1, 0);
            glRotatef(180, 0, 0, 1);
            glScalef(0.5, 0.5, 1);
            drawFractal(depth - 1);
        glPopMatrix();
        
        glColor3f( 1.0, 0.0, 1.0 );	//T4
        glPushMatrix();
            glTranslatef(0.5, 0, 0);
            glScalef(0.5, 0.5, 1);
            drawFractal(depth - 1);
        glPopMatrix();
        break;
    }
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glTranslatef(-1, -1, 0);
    glScalef(2, 2, 0);
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawFractal(currentDepth);
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // Init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA);
    glutInitWindowPosition(1000,500);
    glutInitWindowSize(320,320);
    glutCreateWindow("U2");    
    init();
    
    // Register callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(onKeyPress);

    // Enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}
