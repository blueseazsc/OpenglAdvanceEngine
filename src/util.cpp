#include "util.h"
#include <SOIL.h>

namespace framework {

GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void *data /* = nullptr */) {
	GLuint object;
	glGenBuffers(1, &object);
	glBindBuffer(bufferType, object);
	glBufferData(bufferType, size, data, usage);
	glBindBuffer(bufferType, 0);
	return object;
}
std::shared_ptr<unsigned char> LoadFileContent(const char *path, int &filesize) {
	filesize = 0;

	// 要读入整个文件，必须采用二进制打开
	std::ifstream fileStream;
	fileStream.open(path, std::ios::binary);
	// 获取fileStream对应buffer对象的指针
	std::filebuf *pbuf = fileStream.rdbuf();

	// 调用buffer对象方法获取文件大小
	filesize = pbuf->pubseekoff(0, std::ios::end, std::ios::in);
	if ( filesize > 0 ) {
		pbuf->pubseekpos(0, std::ios::in);

		// 分配内存空间
		unsigned char *fileContent = new unsigned char[filesize + 1];

		// 获取文件内容
		pbuf->sgetn((char*)fileContent, filesize);

		fileContent[filesize]='\0';

		return std::shared_ptr<unsigned char>(fileContent);
	}
	return std::shared_ptr<unsigned char>();
}
unsigned char* DecodeBMP(unsigned char*bmpFileData, int&width, int&height) {
	if (0x4D42 == *((unsigned short*)bmpFileData)) {
		int pixelDataOffset = *((int*)(bmpFileData + 10));
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		unsigned char*pixelData = bmpFileData + pixelDataOffset;
		for (int i = 0; i < width*height * 3; i += 3) {
			unsigned char temp = pixelData[i];
			pixelData[i] = pixelData[i + 2];
			pixelData[i + 2] = temp;
		}
		return pixelData;
	}
	return nullptr;
}
GLuint CreateTexture2D(unsigned char*pixelData, int width, int height, GLenum type) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}
GLuint CreateTexture2DFromBMP(const char*bmpPath) {
	int nFileSize = 0;
	std::shared_ptr<unsigned char> bmpFileContent = LoadFileContent(bmpPath, nFileSize);
	if (!bmpFileContent) {
		return 0;
	}
	int bmpWidth = 0, bmpHeight = 0;
	unsigned char*pixelData = DecodeBMP(bmpFileContent.get(), bmpWidth, bmpHeight);
	if (bmpWidth == 0) {
		return 0;
	}
	GLuint texture = CreateTexture2D(pixelData, bmpWidth, bmpHeight, GL_RGB);
	return texture;
}

GLuint CreateTextureFromImage(const char *imgFilePath, bool invertY) {
	unsigned int flags = SOIL_FLAG_POWER_OF_TWO;
	if ( invertY )
		flags |= SOIL_FLAG_INVERT_Y;

	return SOIL_load_OGL_texture(imgFilePath, 0, 0, flags);
}

GLuint CreateDisplayList(std::function<void()> func) {
	GLuint displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);
	func();
	glEndList();
	return displayList;
}

GLuint CreateProcedureTexture(int size) {
	unsigned char *imageData = new unsigned char[size*size * 4];
	float halfSize = (float)size / 2.0f;
	float maxDistance = sqrtf(halfSize*halfSize + halfSize*halfSize);
	float centerX = halfSize;
	float centerY = halfSize;
	for (int y = 0; y < size; ++y) {
		for (int x = 0; x < size; ++x) {
			int currentPixelOffset = (x + y*size) * 4;
			imageData[currentPixelOffset] = 255;
			imageData[currentPixelOffset + 1] = 255;
			imageData[currentPixelOffset + 2] = 255;
			float deltaX = (float)x - centerX;
			float deltaY = (float)y - centerY;
			float distance = sqrtf(deltaX*deltaX + deltaY*deltaY);
			float alpha = powf(1.0f - (distance / maxDistance), 8.0f);
			alpha = alpha > 1.0f ? 1.0f : alpha;
			imageData[currentPixelOffset + 3] = (unsigned char)(alpha*255.0f);
		}
	}
	GLuint texture = CreateTexture2D(imageData, size, size, GL_RGBA);
	delete[] imageData;
	return texture;
}

}

