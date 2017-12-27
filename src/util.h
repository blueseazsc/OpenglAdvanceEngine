#ifndef UTILS_H
#define UTILS_H

#include "header.h"

namespace framework {

GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void *data = nullptr);

std::shared_ptr<unsigned char> LoadFileContent(const char *path, int &filesize);
unsigned char* DecodeBMP(unsigned char*bmpFileData, int&width, int&height);
GLuint CreateTexture2D(unsigned char*pixelData, int width, int height, GLenum type);
GLuint CreateTexture2DFromBMP(const char *bmpPath);

GLuint CreateTextureFromImage(const char *imgFilePath, bool invertY = true);
GLuint CreateDisplayList(std::function<void()> func);

GLuint CreateProcedureTexture(int size);

}
#endif
