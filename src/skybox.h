#ifndef SKYBOX_H
#define SKYBOX_H

#include "shader.h"
#include "vertexbuffer.h"

namespace framework {

class SkyBox {
public:
	void Init(const char *imageDir);
	void InitFront(const char *imageDir);
	void InitBack(const char *imageDir);
	void InitLeft(const char *imageDir);
	void InitRight(const char *imageDir);
	void InitTop(const char *imageDir);
	void InitBottom(const char *imageDir);
	void Draw(float cameraX,float cameraY,float cameraZ, glm::mat4 &V, glm::mat4&P);
protected:
	Shader mShader[6];
	VertexBuffer mVertexBuffer[6];
};

}
#endif
