#include "app.h"
#include "header.h"
#include "util.h"

#include "shader.h"
#include "vertexbuffer.h"

using namespace framework;
class Test:	public Application
{
public:
	virtual void startup(double currentTime)
	{
		lastTime = currentTime;

		ProjectionMatrix = glm::perspective(60.f, (float)info.windowWidth / (float)info.windowHeight, 0.1f, 1000.f);

		vertexBuffer.SetSize(3);
		vertexBuffer.SetPosition(0, -0.5f, 0.5f, -0.2f);
		vertexBuffer.SetTexcoord(0, -1.0f, 0.0f);
		vertexBuffer.SetPosition(1, 0.5f, 0.5f, -0.2f);
		vertexBuffer.SetTexcoord(1, 2.0f, 0.0f);
		vertexBuffer.SetPosition(2, 0.0f, -0.5f, -0.2f);
		vertexBuffer.SetTexcoord(2, 0.5f, 2.0f);
		
		shader.Init("../resources/triangle.vs", "../resources/triangle.fs");
		shader.SetTexture("U_Texture", "../resources/head.png");
	}
	virtual void render(double currentTime)
	{
		double frameTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vertexBuffer.Bind();
		shader.Bind(glm::value_ptr(ModelMatrix), glm::value_ptr(ViewMatrix), glm::value_ptr(ProjectionMatrix));
		glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.GetVertexCount());
		vertexBuffer.Unbind();
	}
private:
	double lastTime;

	glm::mat4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	VertexBuffer vertexBuffer;
	Shader shader;
};

DECLARE_MAIN(Test);
