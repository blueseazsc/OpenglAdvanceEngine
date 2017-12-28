#include "app.h"
#include "header.h"
#include "util.h"

#include "ground.h"

using namespace framework;
class Test:	public Application
{
public:
	virtual void startup(double currentTime)
	{
		lastTime = currentTime;

		projectionMatrix = glm::perspective(60.f, (float)info.windowWidth / (float)info.windowHeight, 0.1f, 1000.f);

		ground.Init();
	}
	virtual void render(double currentTime)
	{
		double frameTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ground.Draw(viewMatrix, projectionMatrix);
	}
private:
	double lastTime;

	glm::mat4 viewMatrix, projectionMatrix;

	Ground ground;
};

DECLARE_MAIN(Test);
