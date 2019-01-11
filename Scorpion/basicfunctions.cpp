#include "declarations.h"
#include "Scorpion.h"


const float PI = 3.14;

Scorpion spider;
Scenery scene;

GLuint texture[10];

float angleXZ = -90;
float angleYZ = 90;


void display()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_TEXTURE_2D );
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    gluLookAt( scene.position_x, scene.position_y, scene.position_z, scene.position_x + scene.center_x, scene.position_y - scene.look_down, scene.position_z + scene.center_z, 0, 1, 0 );
    displayObjects();
    glPopMatrix();
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void reshape( GLsizei w, GLsizei h )
{
    if ( h > 0 && w > 0 ) {
        glViewport( 0, 0, w, h );
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective( 60, (GLfloat)w / (GLfloat)h, 1, 100.0f );
        glMatrixMode( GL_MODELVIEW );
    }
}

void keyPressed( unsigned char key, int x, int y )
{
    float quant = 0.2;
    switch ( key )
    {
            //obrÛt wokÛ≥ osi kamery
        case 'q':
            scene.center_z -= quant * cos( angleXZ * PI / 180 );
            scene.center_x += quant * sin( angleXZ * PI / 180 );
            //angleXZ -= 1;
            break;
            //obrÛt wokÛ≥ osi kamery
        case 'e':
            scene.center_z += quant * cos( angleXZ * PI / 180 );
            scene.center_x -= quant * sin( angleXZ * PI / 180 );
            //angleXZ += 1;
            break;
            
            // klawisze WSAD - ruch po osi Z
        case 'w':
            scene.position_x += quant * sin( angleXZ * PI / 180 );
            scene.position_y += quant * cos( angleYZ * PI / 180 );
            scene.position_z += quant * sin( angleXZ * PI / 180 );
            break;
            
        case 's':
            scene.position_x -= quant * sin( angleXZ * PI / 180 );
            scene.position_y -= quant * cos( angleYZ * PI / 180 );
            scene.position_z -= quant * sin( angleXZ * PI / 180 );
            break;
            
        case 'a':
            scene.position_z -= quant*cos( angleXZ * PI / 180 );
            scene.position_x += quant*sin( angleXZ * PI / 180 );
            break;
            
        case 'd':
            scene.position_z += quant*cos( angleXZ * PI / 180 );
            scene.position_x -= quant*sin( angleXZ * PI / 180 );
            break;
            
            // rf - kamera po osi Y
        case 'r':
            scene.position_y += 0.4;
            break;
            
        case 'f':
            if ( scene.position_y > 0.0 )
                scene.position_y -= 0.4;
            break;
            
            // tg - nachylenie gÛra-dÛ≥
        case 't':
            scene.look_down += 0.1;
            break;
            
        case 'g':
            scene.look_down -= 0.1;
            break;
            
            // sterowanie úwiat≥em
        case 'm':
            scene.changeAmbientLevel( -0.1 );
            break;
            
        case 'n':
            scene.changeDiffuseLevel( -0.1 );
            break;
            
        case 'o':
            scene.changeFogDensity( 0.1 );
            break;
            
        case 'p':
            scene.changeFogDensity(-0.1);
            break;
    };
}

void keySpecial( int key, int x, int y )
{
    float quant = 0.13;
    GLfloat moveX = quant * cos( spider.getRotation() * PI / 180 );
    GLfloat moveZ = quant * sin( spider.getRotation() * PI / 180 );
    
    switch ( key )
    {
        case GLUT_KEY_UP:
            //warunek øeby pajπk nie wychodzi≥ poza planszÍ
            if ( spider.getX()-moveX > -37.5 && spider.getX()-moveX < 47 && spider.getZ()+moveZ < 56.5 && spider.getZ()+moveZ > -27)
            {
                //spider.move( -moveX, 0.0, moveZ );
                scene.position_x -= moveX;
                scene.position_z += moveZ;
            }
            spider.moveLeftLegs();
            spider.moveRightLegs();
            spider.moveBody();
            
            break;
            
        case GLUT_KEY_DOWN:
            // warunek øeby pajπk nie wychodzi≥ poza planszÍ
            if ( spider.getX() + moveX > -37.5 && spider.getX() + moveX < 47 && spider.getZ() - moveZ < 56.5 && spider.getZ() - moveZ > -27 )
            {
                //spider.move( moveX, 0.0, -moveZ );
                scene.position_x += moveX;
                scene.position_z -= moveZ;
            }
            spider.moveLeftLegs();
            spider.moveRightLegs();
            spider.moveBody();
            break;
            
        case GLUT_KEY_LEFT:
            //spider.changeRotation( 4 );
            spider.moveLeftLegs();
            spider.moveRightLegs();
            spider.moveBody();
            break;
            
        case GLUT_KEY_RIGHT:
            //spider.changeRotation( -4 );
            spider.moveLeftLegs();
            spider.moveRightLegs();
            spider.moveBody();
            break;
    }
    
}

void init()
{
    glClearDepth( 1.0f );
    //perspektywa
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glDepthFunc( GL_LEQUAL );
    //wlaczanie tekstur
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_AUTO_NORMAL );
    glClearColor( 0.3474, 0.3474, 0.3052, 1.0 );
    glAlphaFunc( GL_GREATER, 0.0f );
    
    //wlaczanie kanalu alpha
    glEnable( GL_ALPHA_TEST );
    glEnable( GL_DEPTH_TEST );
    
    //wczytywanie tekstur
    //texture[SURFACE] = SOIL_load_OGL_texture( "rock.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT );
    
    //ustawienia oswietlenia
    glMaterialfv( GL_FRONT, GL_SPECULAR, scene.mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 90.0 );
    glLightfv( GL_LIGHT0, GL_AMBIENT, scene.ambientLight );
    glLightfv( GL_LIGHT0, GL_POSITION, scene.light_position );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, scene.diffuse );
    glLightfv( GL_LIGHT1, GL_POSITION, scene.light_position );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glShadeModel( GL_SMOOTH );
    
    glHint( GL_FOG_HINT, GL_NICEST );
    
    glFogfv( GL_FOG_COLOR, scene.fog_color );
    
    glFogf( GL_FOG_DENSITY, scene.fog_density );
    
    glFogf( GL_FOG_MODE, GL_EXP );
    
    glEnable( GL_FOG );
    
}

void displayObjects()
{
    //pod≥oøe
    for ( int i = 0; i < 30; ++i )
        for ( int j = 0; j < 30; ++j )
        {
            Point p( j * 3 - 40, -2.3f, i * 3 - 40 );
            surface( p );
        }
    
    GLfloat skin[] = { 1, 1, 0, 1.2 };
    GLfloat eyes[] = { 0.0, 0.0, 0.0, 1.0 };
    
    spider.drawScorpion();
}

void surface( const Point& p )
{
    Point p1 = p, p2 = p, p3 = p, p4 = p;
    p1.x += 3;
    p2.x += 3;
    p2.z += 3;
    p4.z += 3;
    draw( p1, p2, p3, p4, texture[SURFACE] );
}

void draw( const Point& p1, const Point& p2, const Point& p3, const Point& p4, int texture )
{
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glBegin( GL_TRIANGLE_STRIP );
    glTexCoord2f( 1, 0 ); glVertex3f( p1.x, p1.y, p1.z );
    glTexCoord2f( 1, 1 ); glVertex3f( p2.x, p2.y, p2.z );
    glTexCoord2f( 0, 0 ); glVertex3f( p3.x, p3.y, p3.z );
    glTexCoord2f( 0, 1 ); glVertex3f( p4.x, p4.y, p4.z );
    glEnd();
}
