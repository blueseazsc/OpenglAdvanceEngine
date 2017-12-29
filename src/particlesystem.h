#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "header.h"
#include "vertexbuffer.h"
#include "shader.h"
namespace framework {

class ParticleSystem {
public:
	void Init(float x,float y,float z);
	void Draw(glm::mat4 & viewMatrix,glm::mat4 & projectionMatrix);
	void Update(float deltaTime);
protected:
	VertexBuffer mVertexBuffer;
	Shader mShader;
	glm::mat4 mModelMatrix;
};
}
#endif
