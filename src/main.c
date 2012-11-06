/**
 * Computer graphics, task 2. 
 * Affine fractals.
 * 
 * @author Aurelijus Banelis
 */

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define PI 3.14159265

/*
 * Contractions
 */
#define N 4             //      T1            T2         T3            T4
GLfloat scale[N][2]     = {{-0.25, 0.25}, {-0.5, 0.5}, {0.5, 0.5}, {0.5, 0.5}};
GLfloat rotation[N]     = {          180,          90,        180,          0};
GLfloat translate[N][2] = {{ 0.25,    1}, { 0.5, 0.5}, {  1,   1}, {0.5,   0}};
GLfloat colours[N][3]   = {{0.5, 1, 0.5}, {0, 1,   1}, {1,0,   1}, {1,1,   0}};


/*
 * Global variables
 */
int currentDepth = 0;
enum MODE {transformationBased, randomBased} currentMode = randomBased;

/*
 * Interaction
 */
void onKeyPress(unsigned char key, int keyX, int keyY) {
    switch (key) {
        case KEY_ESCAPE:
        case 'q':
            exit(1);
        break;
        case KEY_ENTER:
            if (currentMode == randomBased) {
                currentMode = transformationBased;
            } else {
                currentMode = randomBased;
            }
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


/*
 * Fractal from single element
 */
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


/*
 * Drawing fractal using affine transforamtions
 */
void drawFractalAffine(int depth) {
    if (depth > 0) {
        /* Parts of fractal:    T1 T2
         *                      T3 T2
         * 
         * Coordinate system: ^y
         *                    |
         *                    +--->x
         * 
         * Order convention: T(R(S(v)))
         */

        int i;
        for (i = 0; i < N; i++) {
            glPushMatrix();
                glTranslatef(translate[i][0], translate[i][1], 0);
                glRotatef(rotation[i], 0, 0, 1);
                glScalef(scale[i][0], scale[i][1], 1);
                glColor3f(colours[i][0], colours[i][1], colours[i][2]);
                drawFractalAffine(depth - 1);
            glPopMatrix();
        }
    } else {
        drawPicture();
    }
}


/*
 * Drawing fractal using chaos game
 */
void drawFractalRandom() {
    GLfloat p[2] = {0.5,0.5};
    int max = 50000;
    int i, j;
    for (i = 0; i < max; i++) {
        j = rand()%4;
        
        
        /*     / x'\   / s_x*cos(r)  -s_x*sin(r)  t_x \   / x \
         * p = | y'| = | s_x*sin(r)   s_y*cos(r)  t_y | x | y |
         *     \ 1 /   \     0             0       1  /   \ 1 /
         */
        float x = p[0];
        float y = p[1];
        float r = rotation[j] * PI / 180;
        float Sx = scale[j][0];
        float Sy = scale[j][1];
        float Tx = translate[j][0];
        float Ty = translate[j][1];
        p[0] = ( x * Sx * cos(r) ) + (-y * Sy * sin(r)) + Tx;
        p[1] = ( x * Sx * sin(r) ) + ( y * Sy * cos(r)) + Ty;
        
        glColor3f(colours[j][0], colours[j][1], colours[j][2]);
        glBegin(GL_POINTS);
            glVertex2fv(p); 
        glEnd();
    }
}


/*
 * Main drawing loop
 */
void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (currentMode == randomBased) {
        drawFractalRandom();
    } else {
        drawFractalAffine(currentDepth);    
    }
    
    glutSwapBuffers();
}


/*
 * Initial view configurations
 */
void init() {
    glMatrixMode(GL_PROJECTION);
    glTranslatef(-1, -1, 0);
    glScalef(2, 2, 0);
    glMatrixMode(GL_MODELVIEW);
}


/*
 * Initiating OpenGl
 */
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