#ifndef MODEL_H
#define MODEL_H

#include "header.h"
#include "shader.h"
#include "vertexbuffer.h"

namespace framework {

class Model {
public:
	glm::mat4 mModelMatrix;
public:
	void Init(const char *modelPath);
	void SetTexture(const char *imagePath);
	void SetPosition(float x, float y, float z);
	void Draw(float cameraX, float cameraY, float cameraZ, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
	void SetAmbientMaterial(float r, float g, float b, float a);
	void SetDiffuseMaterial(float r, float g, float b, float a);
	void SetSpecularMaterial(float r, float g, float b, float a);
protected:
	VertexBuffer mVertexBuffer;
	Shader mShader;
};

}
#endif
