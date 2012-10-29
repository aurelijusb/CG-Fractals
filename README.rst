Fractals example
================

Functionality
---------------

 * Draw fractals using affine transformation
 * Animate interations (1 big image to meny pixel size images)
 * Random based (chaos game) fractal painting
 * Different colors for each transformation


Usage
-----

 * [Enter] - swith between random/transformation based drawing.
 * [Space] - iterate affine transformations


Transformations
---------------

Transormation vector:

    T = Scale (x,y) Rotate (x, y) Translate (x, y)


Contractions (by output):

    T1 T2
    T3 T4


Contractions (attributes):

     T1 = (0.25, 0.25, 180, 180,  0.5,   1)
     T2 = (-0.5,  0.5,  90,  90,  0.5, 0.5)
     T3 = ( 0.5,  0.5, 180, 180,    1,   1)
     T4 = (0.5, 0.5,     0,   0,  0.5,   0)

P_(k+1) = T1(P_k) U .. U T4(P_k)


Compilation
-----------

Libraries
 * OpenGl
 * Free GLUT
 * Math

To compile program::

    gcc src/main.c -lGL -lGLU -lglut -lm -o U2Aurelijus
  
  
References
----------

 * http://uosis.mif.vu.lt/~rimask/destymas/kompiuterine-grafika-ps/2-uzd/
 * http://classes.yale.edu/fractals/
 * http://chaos4.phy.ohiou.edu/~thomas/fractal/game.html
 * A. Lenkevičius, J. Matickas „KOMPIUTERINĖ GRAFIKA“. Technologija, Kaunas, 2004.
 * http://www.eecis.udel.edu/~chandra/640/Spring05/lecture4.ppt
