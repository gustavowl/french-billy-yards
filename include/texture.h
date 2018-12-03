#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glut.h>
#include <fstream>

struct Image
{
    unsigned char* pixels = NULL;
    int width;
    int height;
    int numChannels;
};

class Texture
{
    public:
    Texture ();
    ~Texture ();

    void loadTexture (void);

    void readPPM (const char* filename);

    GLuint texName;
    Image image;
};

#endif