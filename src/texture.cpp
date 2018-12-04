#include "texture.h"

Texture::Texture ()
{
}

Texture::~Texture ()
{
    if(image.pixels != NULL)
        free(image.pixels);
}

void Texture::loadTexture (void)
{
    if(image.pixels!= NULL){

        glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, 
                        image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                        image.pixels);
    }
}

void Texture::readPPM(const char* filename) {
    FILE *arq = fopen(filename, "r");
    char format[3];
    int max;
    if(arq != NULL){
        fscanf(arq, "%s %d %d %d\n", format, &image.width, &image.height, &max);
        image.pixels = (unsigned char *) malloc(sizeof(unsigned char)*image.width*image.height*3);
        fread(image.pixels, sizeof(unsigned char), image.width*image.height*3, arq);
        fclose(arq);
        printf("IMAGEM LIDA COM SUCESSO! PATH= %s\n",filename);
    }
}
