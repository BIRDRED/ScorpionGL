#include "Scorpion.h"
#include "Image.h"
#include <iostream>

using namespace std;
// Scorpion
Scorpion::Scorpion()
{
    eyes[0] = eyes[1] = eyes[2] = 0.0;
    eyes[3] = 1.0;

    skin[0] = 0.485;
    skin[1] = 0.325;
    skin[2] = 0.19;
    skin[3] = 1.2;

    Image skinTextureBmp = Image();
    skinTextureBmp.readBMP("img/skin.bmp");
    skinTex = skinTextureBmp.toTexture();

    moveX = 0;
    moveY = 0;
    moveZ = 0;
    bodyCount = 15;
    bodyUpside = true;
    rotation = 45;

    leftSideCount = 0.0;
    rightSideCount = 0.0;
    leftSideForward = true;
    rightSideForward = false;
}

Scorpion::Scorpion(GLfloat skinColor[], GLfloat eyesColor[])
{
    moveX = 0;
    moveY = 0;
    moveZ = 0;
    bodyCount = 15;
    bodyUpside = true;
    rotation = 45;

    leftSideCount = 0.0;
    rightSideCount = 0.0;
    leftSideForward = true;
    rightSideForward = false;
}

/*void Scorpion::changeRotation( int change )
{
    rotation += change;
}*/

/*void Scorpion::move( GLfloat x, GLfloat y, GLfloat z )
{
    moveX += x;
    moveY += y;
    moveZ += z;
}*/

void Scorpion::moveClaws(float change)
{
    moveClaw += change;
    if (moveClaw > 20) moveClaw = 20;
    if (moveClaw < -20) moveClaw = -20;
}

GLfloat Scorpion::getRotation() const
{
    return rotation;
}

GLfloat Scorpion::getX() const
{
    return moveX;
}

GLfloat Scorpion::getY() const
{
    return moveY;
}

GLfloat Scorpion::getZ() const
{
    return moveZ;
}

void Scorpion::drawBody()
{

    glPushMatrix();
    
    glTranslatef(-2.6, -0.5, 0.0);
    glRotatef(bodyCount, 0, 0, 1);
    glScalef(1.7, 0.5, 1);


    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GLU_TRUE);
    glBindTexture(GL_TEXTURE_2D, skinTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 
    gluSphere(quad, 1.0, 100, 100);
    glPopMatrix();
}

void Scorpion::drawTail()
{
    float radius = 0.3; //radius to apply in all of the tail
    float scaleX = 1.6;
    float scaleY = 1;
    float scaleZ = 1;
    float upY = 0.2;

    glPushMatrix();
    glTranslatef(-0.7, -0.2, 0);
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidSphere(radius, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidSphere(radius, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, 0.2, 0);
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidSphere(radius, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, 0.6, 0);
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidSphere(radius, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, 0.9, 0);
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidSphere(radius, 100, 100);
    glPopMatrix();
}

void Scorpion::legPartsLeft(GLfloat x, GLdouble y)
{
    glPushMatrix();
    glTranslatef(-0.5, 0.0, 0.0);
    glutSolidSphere(0.1, 10, 10);
    glRotatef(x, 0, 0, 1);
    glPushMatrix();
    glTranslatef(0.22, -0.6, 0.0);
    glRotatef(110, 0, 0, 1);
    glScalef(3.7, 0.2, 0.2);
    glutSolidSphere(y, 50, 50);
    glPopMatrix();
    glPopMatrix();
}

void Scorpion::legPartsRight(GLfloat x, GLdouble y)
{
    glPushMatrix();
    glTranslatef(0.5, 0.0, 0.0);
    glutSolidSphere(0.1, 10, 10);

    glRotatef(x, 0, 0, 1);

    glPushMatrix();
    glTranslatef(-0.22, -0.6, 0.0);
    glRotatef(-110, 0, 0, 1);
    glScalef(3.7, 0.2, 0.2);
    glutSolidSphere(y, 50, 50);
    glPopMatrix();
    glutSolidSphere(0.1, 10, 10);

    glPopMatrix();
}

void Scorpion::drawLegsLeft()
{
    // PRIMEIRA PATA ESQUERDA
    glPushMatrix();
    glTranslatef(-3.8, -0.8, 0.1);
    glRotatef(leftSideCount, 1, 0, 1);
    glRotatef(80.0 + leftSideCount, 0, 1, 0);
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(-30, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glRotatef(leftSideCount * 1.1, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0.22, -0.6, 0.0);
    glRotatef(110, 0, 0, 1);
    glScalef(2, 0.4, 0.4);
    glutSolidSphere(0.3, 30, 30);
    glRotatef(moveClaw, 0, 1, 0);

    // first claw
    glPushMatrix();
    glTranslatef(-0.3, -0.3, 0.0);
    glScalef(0.4, 0.4, 0.4);
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();

    //second claw
    glPushMatrix();
    glTranslatef(-0.3, -0.3, 0.2);
    glScalef(0.4, 0.4, 0.4);
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
    
    
    //SEGUNDA PATA ESQUERDA
    glPushMatrix();
    glTranslatef(-3.4, -0.2, 0.8);
    glRotatef(leftSideCount, 1, 0, 1);
    glRotatef(80.0 + leftSideCount, 0, 1, 0);
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(-30, 0, 0, 1);
    
    glPushMatrix();
    glScalef(3, 0.4, 0.4);
    glutSolidSphere(0.2, 50, 50);
    glPopMatrix();
    legPartsLeft(leftSideCount * 1.1,0.2);
    glPopMatrix();
    
    //TERCEIRA PATA ESQUERDA
    glPushMatrix();
    glTranslatef(-2.8, -0.2, 0.8);
    glRotatef(leftSideCount, 1, 0, 1);
    glRotatef(80.0 + leftSideCount, 0, 1, 0);
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(-30, 0, 0, 1);
    glPushMatrix();
    glScalef(3, 0.4, 0.4);
    glutSolidSphere(0.2, 50, 50);
    glPopMatrix();
    legPartsLeft(leftSideCount * 1.1,0.2);
    glPopMatrix();
    
    
    //QUARTA PATA ESQUERDA
    glPushMatrix();
    glTranslatef(-2.2, -0.2, 0.8);
    glRotatef(leftSideCount, 1, 0, 1);
    glRotatef(80.0 + leftSideCount, 0, 1, 0);
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(-30, 0, 0, 1);
    glPushMatrix();
    glScalef(3, 0.4, 0.4);
    glutSolidSphere(0.2, 50, 50);
    glPopMatrix();
    legPartsLeft(leftSideCount * 1.1,0.2);
    glPopMatrix();
    
    //QUINTA PATA ESQUERDA
    //    glPushMatrix();
    //    glTranslatef(-1.6, -0.2, 0.8);
    //
    //    glRotatef(leftSideCount, 1, 0, 1);
    //
    //    glRotatef(80.0 + leftSideCount, 0, 1, 0);
    //    glTranslatef(-0.5, 0.0, 0.0);
    //    glRotatef(-30, 0, 0, 1);
    //
    //    glPushMatrix();
    //    glScalef(3, 0.4, 0.4);
    //    glutSolidSphere(0.2, 50, 50);
    //    glPopMatrix();
    //    legPartsLeft(leftSideCount * 1.1,0.2);
    //    glPopMatrix();
}

void Scorpion::drawLegsRight()
{
    glPushMatrix();
    glTranslatef(-3.8, -0.8, -0.8);
    glRotatef(leftSideCount, 1, 0, 1);
    glRotatef(80.0 + leftSideCount, 0, 1, 0);
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef(-30, 0, 0, 1);
    glRotatef(90, 1, 0, 0);
    glRotatef(leftSideCount * 1.1, 0, 0, 1);
    glPushMatrix();
    glTranslatef(0.22, -0.6, 0.0);
    glRotatef(110, 0, 0, 1);
    glScalef(2, 0.4, 0.4);
    glutSolidSphere(0.3, 30, 30);
    glRotatef(moveClaw, 0, 1, 0);
    // garras
    glPushMatrix();
    glTranslatef(-0.3, -0.3, 0.0);
    glScalef(0.4, 0.4, 0.4);
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.3, -0.3, 0.2);
    glScalef(0.4, 0.4, 0.4);
    glutSolidSphere(0.3, 30, 30);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // SEGUNDA PATA DIREITA
    glPushMatrix();
    glTranslatef(-3.4, -0.2, -0.8);
    glRotatef(-rightSideCount, 1, 0, 1);
    
    glRotatef(80.0 + rightSideCount, 0, 1, 0);
    glTranslatef(0.5, 0.0, 0.0);
    
    glRotatef(30, 0, 0, 1);
    
    glPushMatrix();
    glScalef(3, 0.4, 0.4);
    glutSolidSphere(0.2, 50, 50);
    glPopMatrix();
    legPartsRight(-rightSideCount * 1.1,0.2);
    glPopMatrix();
    
    // TERCEIRA PATA DIREITA
    glPushMatrix();
    glTranslatef(-2.8, -0.2, -0.8);
    glRotatef(-rightSideCount, 1, 0, 1);
    
    glRotatef(80.0 + rightSideCount, 0, 1, 0);
    glTranslatef(0.5, 0.0, 0.0);
    
    glRotatef(30, 0, 0, 1);
    
    glPushMatrix();
    glScalef(3, 0.4, 0.4);
    glutSolidSphere(0.2, 50, 50);
    glPopMatrix();
    legPartsRight(-rightSideCount * 1.1,0.2);
    glPopMatrix();
    
    // QUARTA PATA DIREITA
    glPushMatrix();
    glTranslatef(-2.2, -0.2, -0.8);
    glRotatef(-rightSideCount, 1, 0, 1);
    
    glRotatef(80.0 + rightSideCount, 0, 1, 0);
    glTranslatef(0.5, 0.0, 0.0);
    
    glRotatef(30, 0, 0, 1);
    
    glPushMatrix();
    glScalef(3, 0.4, 0.4);
    glutSolidSphere(0.2, 50, 50);
    glPopMatrix();
    legPartsRight(-rightSideCount * 1.1,0.2);
    glPopMatrix();
    // QUINTA PATA DIREITA
    //    glPushMatrix();
    //    glTranslatef(-1.6, -0.2, -0.8);
    //    glRotatef(-rightSideCount, 1, 0, 1);
    //
    //    glRotatef(80.0 + rightSideCount, 0, 1, 0);
    //    glTranslatef(0.5, 0.0, 0.0);
    //
    //    glRotatef(30, 0, 0, 1);
    //
    //    glPushMatrix();
    //    glScalef(3, 0.4, 0.4);
    //    glutSolidSphere(0.2, 50, 50);
    //    glPopMatrix();
    //    legPartsRight(-rightSideCount * 1.1,0.2);
    //    glPopMatrix();
}

void Scorpion::moveLeftLegs()
{
    if (leftSideForward)
    {
        leftSideCount += 3;
        if (leftSideCount >= 15)
            leftSideForward = false;
    }
    else
    {
        leftSideCount -= 3;
        if (leftSideCount <= -15)
            leftSideForward = true;
    }
}

void Scorpion::moveRightLegs()
{
    if (rightSideForward)
    {
        rightSideCount += 3;
        if (rightSideCount >= 15)
            rightSideForward = false;
    }
    else
    {
        rightSideCount -= 3;
        if (rightSideCount <= -15)
            rightSideForward = true;
    }
}

void Scorpion::moveBody()
{
    if (bodyUpside)
    {
        bodyCount += 1;
        if (bodyCount >= 25)
            bodyUpside = false;
    }
    else
    {
        bodyCount -= 1;
        if (bodyCount <= 15)
            bodyUpside = true;
    }
}

void Scorpion::drawScorpion()
{
    glPushMatrix();
    glTranslatef(moveX + 0.2, -1.0, moveZ - 10);
    glRotatef(rotation, 0, 1, 0);
    // TODO Isso é o que colore o bicho
    glMaterialfv(GL_FRONT, GL_DIFFUSE, skin);

    drawBody();
    drawTail();
    drawLegsLeft();
    drawLegsRight();
    glPopMatrix();
}
