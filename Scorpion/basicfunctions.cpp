#include "declarations.h"
#include "Image.h"
#include "Scorpion.h"

using namespace std;

const float PI = 3.14;

Scorpion scorpion;
Scenery scene;

GLuint texture[10];

float angleXZ = -90;
float angleYZ = 90;

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(scene.position_x, scene.position_y, scene.position_z, scene.position_x + scene.center_x, scene.position_y - scene.look_down, scene.position_z + scene.center_z, 0, 1, 0);
    displayObjects();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
    if (h > 0 && w > 0)
    {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, (GLfloat)w / (GLfloat)h, 1, 100.0f);
        glMatrixMode(GL_MODELVIEW);
    }
}

void keyPressed(unsigned char key, int x, int y)
{
    float quant = 0.2;
    switch (key)
    {
    
        case 'r':
            scorpion.moveRightLegsCrap();
            break;
        
        case 'l':
            scorpion.moveLeftLegsCrap();
            break;
            
        case 'a':
            scorpion.moveLeftLegs2();
            break;
            
        case 'z':
            scorpion.moveRightLegs2();
            break;
        
        case 's':
            scorpion.moveLeftLegs3();
            break;
            
        case 'x':
            scorpion.moveRightLegs3();
            break;
            
        case 'd':
            scorpion.moveLeftLegs4();
            break;
            
        case 'c':
            scorpion.moveRightLegs4();
            break;
            
        
    //MOVIMENTOS DA CAMERA
        
    case 'q':
        scene.center_z -= quant * cos(angleXZ * PI / 180);
        scene.center_x += quant * sin(angleXZ * PI / 180);
        //angleXZ -= 1;
        break;
            
    case 'e':
        scene.center_z += quant * cos(angleXZ * PI / 180);
        scene.center_x -= quant * sin(angleXZ * PI / 180);
        //angleXZ += 1;
        break;

    case 'w':
        scene.position_x += quant * sin(angleXZ * PI / 180);
        scene.position_y += quant * cos(angleYZ * PI / 180);
        scene.position_z += quant * sin(angleXZ * PI / 180);
        break;

    case 'y':
        scene.position_x -= quant * sin(angleXZ * PI / 180);
        scene.position_y -= quant * cos(angleYZ * PI / 180);
        scene.position_z -= quant * sin(angleXZ * PI / 180);
        break;
    
    //MOVIMENTOS DA GARRA
    case 'o':
        scorpion.moveClaws(-1);
        break;

    case 'p':
        scorpion.moveClaws(1);
        break;
    };
}

void keySpecial(int key, int x, int y)
{
    float quant = 0.13;
    GLfloat moveX = quant * cos(scorpion.getRotation() * PI / 180);
    GLfloat moveZ = quant * sin(scorpion.getRotation() * PI / 180);

    switch (key)
    {
    case GLUT_KEY_UP:
        if (scorpion.getX() - moveX > -37.5 && scorpion.getX() - moveX < 47 && scorpion.getZ() + moveZ < 56.5 && scorpion.getZ() + moveZ > -27)
        {
            //scorpion.move( -moveX, 0.0, moveZ );
            scene.position_x -= moveX;
            scene.position_z += moveZ;
        }
        scorpion.moveLeftLegsCrap();
        scorpion.moveLeftLegs2();
        scorpion.moveLeftLegs3();
        scorpion.moveLeftLegs4();
            
        scorpion.moveRightLegsCrap();
        scorpion.moveRightLegs2();
        scorpion.moveRightLegs3();
        scorpion.moveRightLegs4();
        scorpion.moveBody();

        break;

    case GLUT_KEY_DOWN:
        if (scorpion.getX() + moveX > -37.5 && scorpion.getX() + moveX < 47 && scorpion.getZ() - moveZ < 56.5 && scorpion.getZ() - moveZ > -27)
        {
            //scorpion.move( moveX, 0.0, -moveZ );
            scene.position_x += moveX;
            scene.position_z -= moveZ;
        }
        scorpion.moveLeftLegsCrap();
        scorpion.moveLeftLegs2();
        scorpion.moveLeftLegs3();
        scorpion.moveLeftLegs4();
            
        scorpion.moveRightLegsCrap();
        scorpion.moveRightLegs2();
        scorpion.moveRightLegs3();
        scorpion.moveRightLegs4();
        scorpion.moveBody();
        break;

    case GLUT_KEY_LEFT:
        //scorpion.changeRotation( 4 );
            scorpion.moveLeftLegsCrap();
            scorpion.moveLeftLegs2();
            scorpion.moveLeftLegs3();
            scorpion.moveLeftLegs4();
            
            scorpion.moveRightLegsCrap();
            scorpion.moveRightLegs2();
            scorpion.moveRightLegs3();
            scorpion.moveRightLegs4();
        scorpion.moveBody();
        break;

    case GLUT_KEY_RIGHT:
        //scorpion.changeRotation( -4 );
            scorpion.moveLeftLegsCrap();
            scorpion.moveLeftLegs2();
            scorpion.moveLeftLegs3();
            scorpion.moveLeftLegs4();
            
            scorpion.moveRightLegsCrap();
            scorpion.moveRightLegs2();
            scorpion.moveRightLegs3();
            scorpion.moveRightLegs4();
        scorpion.moveBody();
        break;
    }
}

void init()
{
    glClearDepth(1.0f);
    // perspectiva
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glDepthFunc(GL_LEQUAL);
    // textura do escorpiao
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_AUTO_NORMAL);
    glClearColor(0.3474, 0.3474, 0.3052, 1.0);
    glAlphaFunc(GL_GREATER, 0.0f);

    // alpha
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);

    // texture
    Image skinTextureBmp = Image();
    skinTextureBmp.readBMP("img/rock.bmp");
    texture[SURFACE] = skinTextureBmp.toTexture();
    Image skyTextureBmp = Image();
    skyTextureBmp.readBMP("img/sky.bmp");
    texture[BACK] = skyTextureBmp.toTexture();
    texture[LEFT] = skyTextureBmp.toTexture();
    texture[RIGHT] = skyTextureBmp.toTexture();

    // lightning
    glMaterialfv(GL_FRONT, GL_SPECULAR, scene.mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 90.0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, scene.ambientLight);
    glLightfv(GL_LIGHT0, GL_POSITION, scene.light_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, scene.diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, scene.light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);

    // fog
    glHint(GL_FOG_HINT, GL_NICEST);
    glFogfv(GL_FOG_COLOR, scene.fog_color);
    glFogf(GL_FOG_DENSITY, scene.fog_density);
    glFogf(GL_FOG_MODE, GL_EXP);
    glEnable(GL_FOG);
}

void displayObjects()
{
    //surface
    for (int i = 0; i < 30; ++i)
        for (int j = 0; j < 30; ++j)
        {
            Point p(j * 3 - 40, -2.3f, i * 3 - 40);
            surface(p);
        }
    //back
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            Point p(i * 80 - 40, j * 80 - 40, -40);
            back(p);
        }
    //left
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            Point p(-40, j * 80 - 40, -40);
            left(p);
        }
    //right
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            Point p(3000, j * 80 - 40, -40);
            right(p);
        }
    GLfloat skin[] = {1, 1, 0, 1.2};
    GLfloat eyes[] = {0.0, 0.0, 0.0, 1.0};

    scorpion.drawScorpion();
}

void surface(const Point &p)
{
    Point p1 = p, p2 = p, p3 = p, p4 = p;
    p1.x += 3;
    p2.x += 3;
    p2.z += 3;
    p4.z += 3;
    draw(p1, p2, p3, p4, texture[SURFACE]);
}

void back(const Point &p)
{
    Point p1 = p, p2 = p, p3 = p, p4 = p;
    p1.x += 80;
    p2.x += 80;
    p2.y += 80;
    p4.y += 80;
    draw(p1, p2, p3, p4, texture[BACK]);
}

void right(const Point &p)
{
    Point p1 = p, p2 = p, p3 = p, p4 = p;
    p1.y += 80;
    p2.y += 80;
    p2.z += 80;
    p4.z += 80;
    draw(p1, p2, p3, p4, texture[BACK]);
}

void left(const Point &p)
{
    Point p1 = p, p2 = p, p3 = p, p4 = p;
    p1.y += 80;
    p2.y += 80;
    p2.z += 80;
    p4.z += 80;
    draw(p1, p2, p3, p4, texture[BACK]);
}

void draw(const Point &p1, const Point &p2, const Point &p3, const Point &p4, int texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(1, 0);
    glVertex3f(p1.x, p1.y, p1.z);
    glTexCoord2f(1, 1);
    glVertex3f(p2.x, p2.y, p2.z);
    glTexCoord2f(0, 0);
    glVertex3f(p3.x, p3.y, p3.z);
    glTexCoord2f(0, 1);
    glVertex3f(p4.x, p4.y, p4.z);
    glEnd();
}
