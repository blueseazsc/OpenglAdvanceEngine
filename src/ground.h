#ifndef GROUND_H
#define GROUND_H

#include "header.h"
#include "shader.h"
#include "vertexbuffer.h"

namespace framework {

class Ground {
public:
	void Init();
	void Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
	void SetAmbientMaterial(float r, float g, float b, float a);
	void SetDiffuseMaterial(float r, float g, float b, float a);
	void SetSpecularMaterial(float r, float g, float b, float a);
protected:
	VertexBuffer mVertexBuffer;
	Shader mShader;
	glm::mat4 mModelMatrix;
};

}
#endif
