#include "Image.h"
#include <iomanip>

void Image::readBMP(char *filename)
{
    int i;
    FILE *f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    width = *(int *)&info[18];
    height = *(int *)&info[22];

    int size = 3 * width * height;
    data = new unsigned char[size];              // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for (i = 0; i < size; i += 3)
    {
        unsigned char tmp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = tmp;
    }

    width = width;
    height = height;
}


GLuint Image::toTexture()
{

    GLuint textureId;
    glGenTextures(1, &textureId);            //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,    //Always GL_TEXTURE_2D
                 0,                //0 for now
                 GL_RGB,           //Format OpenGL uses for image
                 width, height,    //Width and height
                 0,                //The border of the image
                 GL_RGB,           //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 data); //The actual pixel data

    return textureId; //Returns the id of the texture
}
