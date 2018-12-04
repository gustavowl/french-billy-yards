#include "texture.h"
Texture::Texture (const char* _filename){ this->setFileName(_filename); }
void Texture::setFileName (const char* _filename){ 
    filename = _filename; 
    texid1 = this->loadTex(filename);
    printf("DEPOIS %d",texid1);
    this->activeTex();
}

unsigned char * Texture::readPPM(const char* filename) {
    FILE *arq = fopen(filename, "r");
    char format[3];
    int max;
    unsigned char* pixels =NULL;
    if(arq != NULL){
        fscanf(arq, "%s %d %d %d\n", format, &width, &height, &max);
        pixels= (unsigned char *) malloc(sizeof(unsigned char)*width*height*3);
        fread(pixels, sizeof(unsigned char), width*height*3, arq);
        fclose(arq);
        printf("IMAGEM LIDA COM SUCESSO! PATH= %s",filename);
        return pixels;
    }
    printf("IMAGEM NAO ENCONTRADA! PATH= %s",filename);
    return NULL;
}

GLuint Texture::loadTex(const char *c){
    unsigned char *data = this->readPPM(c);
    GLuint texid;
    printf("ANTES %d",texid1);
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    free(data);
    return texid;
}

void Texture::activeTex(void){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //printf("TEXTURA ATIVADA %d",texid1);
}