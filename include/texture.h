#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glut.h>
#include <fstream>

class Texture
{
public:
    Texture (){ /* Empty */};
    Texture (const char* _filename);
    void activeTex(void);
    void setFileName(const char* _filename);

private:
    const char* filename;
    int width,height;
    GLuint texid1=-777;

    unsigned char * readPPM(const char* filename);

    GLuint loadTex(const char *c);

    void putImage(void);
};

#endif