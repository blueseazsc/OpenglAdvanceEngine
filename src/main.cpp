#include "app.h"
#include "header.h"
#include "util.h"

#include "ground.h"
#include "model.h"

using namespace framework;
class Test:	public Application
{
public:
	virtual void startup(double currentTime)
	{
		lastTime = currentTime;

		projectionMatrix = glm::perspective(60.f, (float)info.windowWidth / (float)info.windowHeight, 0.1f, 1000.f);

		ground.Init();

		model.Init("Res/Sphere.obj");
		model.SetTexture("Res/earth.bmp");
		model.SetPosition(0.0f, 0.0f, 0.0f);
	}
	virtual void render(double currentTime)
	{
		double frameTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ground.Draw(viewMatrix, projectionMatrix);
		model.Draw(0.0f,0.0f,0.0f, viewMatrix, projectionMatrix);
	}
private:
	double lastTime;

	glm::mat4 viewMatrix, projectionMatrix;

	Ground ground;
	Model model;
};

DECLARE_MAIN(Test);
