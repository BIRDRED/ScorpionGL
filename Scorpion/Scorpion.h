//
//  scorpion.h
//  Scorpion
//
//  Created by Gustavo Melo , Bianca e Mauricio
//  Copyright © 2019 Gustavo Melo. All rights reserved.
//

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
    void moveClaws(float change);
    void drawScorpion();
    
    void moveLeftLegsCrap();
    void moveLeftLegs2();
    void moveLeftLegs3();
    void moveLeftLegs4();

    void moveRightLegsCrap();
    void moveRightLegs2();
    void moveRightLegs3();
    void moveRightLegs4();

    void moveBody();

    GLfloat getRotation() const;
    GLfloat getX() const;
    GLfloat getY() const;
    GLfloat getZ() const;
    
    
    
    bool leftSideForward;
    bool leftSideForward2;
    bool leftSideForward3;
    bool leftSideForward4;

    
    bool rightSideForward;
    bool rightSideForward2;
    bool rightSideForward3;
    bool rightSideForward4;


  private:
    GLfloat eyes[4];
    GLfloat skin[4];
    GLfloat moveX;
    GLfloat moveY;
    GLfloat moveZ;
    GLfloat rotation;
    GLuint skinTex;
    GLfloat moveClaw;
    
    void drawEyes();
    void drawBody();
    void drawTail();
    void drawLegsLeft();
    void drawLegsRight();
    
    
    GLfloat leftCount;
    GLfloat leftSideCount;
    GLfloat leftSideCount2;
    GLfloat leftSideCount3;
    GLfloat leftSideCount4;
    
    GLfloat rightCount;
    GLfloat rightSideCount;
    GLfloat rightSideCount2;
    GLfloat rightSideCount3;
    GLfloat rightSideCount4;

    void legPartsLeft(GLfloat,GLdouble);

    void legPartsRight(GLfloat,GLdouble);

    GLfloat bodyCount;

    bool bodyUpside;
};

#endif
