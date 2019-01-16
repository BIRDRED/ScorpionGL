#include <GL/glut.h>

class Image
{
  public:
    int width;
    int height;
    unsigned char *data;
    void readBMP(char *filename);
    GLuint toTexture();
};