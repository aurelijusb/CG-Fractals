Fractals example
================

Fractals created using affine transformations.

Transformations
---------------

Transormation vector:

    T = Scale (x,y) Rotate (x, y) Translate (x, y)


Contractions (by output):

    T1 T2
    T3 T4


Contractions (attributes):

     T1 = (0.5, 1,  180, 180,  0.5, 1)
     T2 = (-0.5, 0.5,  90, 90,  0.5, 0.5)
     T3 = (0.5, 0.5,  180, 180,  1, 1)
     T4 = (0.5, 0.5,  0, 0,  0.5, 0)

P_(k+1) = T1(P_k) U .. U T4(P_k)

Compilation
-----------

Libraries
 * OpenGl
 * Free GLUT

To compile program::

    gcc src/main.c -lGL -lGLU -lglut -o U2Aurelijus
  
