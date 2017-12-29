#include "particlesystem.h"
#include "util.h"

using namespace framework;

void ParticleSystem::Init(float x, float y, float z) {
	mModelMatrix = glm::translate(x, y, z);
	int particleCount = 180;
	mVertexBuffer.SetSize(particleCount);
	for (int i = 0; i < particleCount; ++i) {
		mVertexBuffer.SetPosition(i, 2.0f*cosf(float(i) * 8.0f*3.14f / 180.0f), 0.0f, 2.0f*sinf(float(i) * 8.0f*3.14f / 180.0f));
		mVertexBuffer.SetColor(i, 0.1f, 0.4f, 0.6f);
	}
	mShader.Init("../resources/particle.vs", "../resources/particle.fs");
	mShader.SetTexture("U_Texture", CreateProcedureTexture(256));
}
void ParticleSystem::Update(float deltaTime) {
	static float angle = 0.0f;
	angle += deltaTime*10.0f;
	mModelMatrix = glm::rotate(angle, 0.0f, 1.0f, 0.0f);
	for (int i = 0; i < mVertexBuffer.GetVertexCount(); ++i) {
		Vertex &vertex = mVertexBuffer.Get(i);
		vertex.normal[1] = 0.1f*i;
		if (i > 90){
			break;
		}
	}
}
void ParticleSystem::Draw(glm::mat4 & viewMatrix, glm::mat4 & projectionMatrix) {
	glEnable(GL_PROGRAM_POINT_SIZE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	mVertexBuffer.Bind();
	mShader.Bind(glm::value_ptr(mModelMatrix), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
	glDrawArrays(GL_POINTS, 0, mVertexBuffer.GetVertexCount());
	mVertexBuffer.Unbind();
	glDisable(GL_BLEND);
	glDisable(GL_PROGRAM_POINT_SIZE);
}
