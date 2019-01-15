#ifndef Scorpion_H
#define Scorpion_H

#include "declarations.h"

class Scorpion
{
  public:
    Scorpion();
    Scorpion(GLfloat skinColor[], GLfloat eyesColor[]);
    //void changeRotation(int change);
    //void move( GLfloat x, GLfloat y, GLfloat z );
    void drawScorpion();
    void moveLeftLegs();
    void moveRightLegs();
    void moveBody();
    GLfloat getRotation() const;
    GLfloat getX() const;
    GLfloat getY() const;
    GLfloat getZ() const;

  private:
    GLfloat eyes[4];
    GLfloat skin[4];
    GLfloat moveX;
    GLfloat moveY;
    GLfloat moveZ;
    GLfloat rotation;
    GLuint skinTex;
    

    bool leftSideForward;
    bool rightSideForward;

    GLfloat leftSideCount;
    GLfloat rightSideCount;

    void drawEyes();
    void drawBody();
    void drawTail();
    void drawLegsleft();
    void drawLegsright();

    void legPartsLeft(GLfloat,GLdouble);

    void legPartsRight(GLfloat,GLdouble);

    GLfloat bodyCount;

    bool bodyUpside;
};

#endif
