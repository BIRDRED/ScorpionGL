#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>

#endif

enum SkyboxSides
{
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    SURFACE,
    TEMP_TEXTURE
};

struct Scenery
{
    GLdouble camera_x;
    GLdouble camera_y;
    GLdouble camera_z;
    GLdouble center_x;
    GLdouble center_y;
    GLdouble center_z;
    GLdouble position_x;
    GLdouble position_y;
    GLdouble position_z;
    GLdouble look_down;
    GLfloat ambientLight[4];
    GLfloat diffuse[4];
    GLfloat mat_specular[4];
    GLfloat light_position[4];
    GLfloat fog_color[4];
    GLfloat fog_density;
    //sterowanie oúwietleniem
    GLfloat lightAmbientLevel;
    GLfloat lightDiffuseLevel;
    GLfloat light_position_change;
    
    
    Scenery()
    {
        camera_x = 0;
        camera_y = 0.3;
        camera_z = 0;
        center_x = camera_x;
        center_y = camera_y;
        center_z = camera_z - 1;
        position_x = camera_x;
        position_y = camera_y;
        position_z = camera_z;
        look_down = 0.2;
        
        ambientLight[0] = 1.0f;
        ambientLight[1] = 1.0f;
        ambientLight[2] = 1.0f;
        ambientLight[3] = 2.0f;
        
        diffuse[0] = 1.0f;
        diffuse[1] = 1.0f;
        diffuse[2] = 1.0f;
        diffuse[3] = 1.0f;
        
        mat_specular[0] = 1.0f;
        mat_specular[1] = 1.0f;
        mat_specular[2] = 1.0f;
        mat_specular[3] = 1.0f;
        
        light_position[0] = 0.0f;
        light_position[1] = 10.0f;
        light_position[2] = 0.0f;
        light_position[3] = 1.0f;
        
        //sterowanie oúwietleniem
        lightAmbientLevel = 2.0;
        lightDiffuseLevel = 1.5;
        light_position_change = 1.0;
        
        fog_color[0] = 0.33f;
        fog_color[1] = 0.33f;
        fog_color[2] = 0.33f;
        fog_color[3] = 1.0f;
        
        fog_density = 0.1f;
    }
    
    void changeAmbientLevel( float lvl )
    {
        lightAmbientLevel += lvl;
        if ( lightAmbientLevel <= 0 )
            lightAmbientLevel = 2.0;
        else if ( lightAmbientLevel >= 2.0 )
            lightAmbientLevel = 2.0;
        
        GLfloat ambient[] =
        {
            ambientLight[0] * lightAmbientLevel,
            ambientLight[1] * lightAmbientLevel,
            ambientLight[2] * lightAmbientLevel,
            ambientLight[3] * lightAmbientLevel
        };
        
        glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
    }
    
    void changeDiffuseLevel( float lvl )
    {
        lightDiffuseLevel += lvl;
        if ( lightDiffuseLevel <= 0 )
            lightDiffuseLevel = 2.0;
        else if ( lightDiffuseLevel >= 2.0 )
            lightDiffuseLevel = 2.0;
        
        GLfloat newDiffuse[] =
        {
            diffuse[0] * lightDiffuseLevel,
            diffuse[1] * lightDiffuseLevel,
            diffuse[2] * lightDiffuseLevel,
            diffuse[3] * lightDiffuseLevel
        };
        
        glLightfv( GL_LIGHT1, GL_DIFFUSE, newDiffuse );
    }
    
    void changeFogDensity( float lvl )
    {
        fog_density += lvl;
        if ( fog_density <= 0.0 )
            fog_density = 0.0;
        
        if ( fog_density >= 1.0 )
            fog_density = 1.0;
        
        glFogf( GL_FOG_DENSITY, fog_density );
    }
    
};

struct Point
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    Point( GLfloat x1, GLfloat y1, GLfloat z1 ) : x( x1 ), y( y1 ), z( z1 ) {}
};

void display();
void reshape( GLsizei w, GLsizei h );
void keyPressed( unsigned char key, int x, int y );
void keySpecial( int key, int x, int y );
void init();
void displayObjects();
void surface( const Point& p );
void draw( const Point& p1, const Point& p2, const Point& p3, const Point& p4, int texture );
void changeDiffuseLevel( float lvl );
#endif
