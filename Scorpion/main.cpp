//
//  main.cpp
//  Scorpion
//
//  Created by Gustavo Melo , Bianca e Mauricio
//  Copyright © 2019 Gustavo Melo. All rights reserved.
//

#include "declarations.h"

int main(int argc, char **argv)
{
    glutInit( &argc, argv );
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 750, 750 );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutCreateWindow( "SCORPION OPENGL" );
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyPressed );
    glutSpecialFunc( keySpecial );
    glutIdleFunc( display );
    init();
    glutMainLoop();

    return 0;
}
