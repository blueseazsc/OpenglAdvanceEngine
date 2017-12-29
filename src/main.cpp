#include "app.h"
#include "header.h"
#include "util.h"

#include "skybox.h"
#include "ground.h"
#include "model.h"
#include "particlesystem.h"

using namespace framework;
class Test:	public Application
{
public:
	virtual void startup(double currentTime)
	{
		lastTime = currentTime;

		cameraPos = glm::vec3(10.0f, 10.0f, 10.0f);

		viewMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		projectionMatrix = glm::perspective(60.f, (float)info.windowWidth / (float)info.windowHeight, 0.1f, 1000.f);

		skybox.Init("../resources/");
		ground.Init();

		model.Init("../resources/Sphere.obj");
		model.SetTexture("../resources/earth.bmp");
		model.SetPosition(0.0f, 0.0f, 0.0f);

		niutou.Init("../resources/niutou.obj");
		niutou.SetTexture("../resources/niutou.bmp");
		niutou.mModelMatrix = glm::translate(-5.0f, 0.0f, 4.0f) * glm::scale(0.05f, 0.05f, 0.05f);

		ps.Init(0.0f, 0.0f, 0.0f);
	}
	virtual void render(double currentTime)
	{
		double frameTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox.Draw(cameraPos.x, cameraPos.y, cameraPos.z, viewMatrix, projectionMatrix);
		ground.Draw(viewMatrix, projectionMatrix);
		model.Draw(cameraPos.x, cameraPos.y, cameraPos.z, viewMatrix, projectionMatrix);
		niutou.Draw(cameraPos.x, cameraPos.y, cameraPos.z, viewMatrix, projectionMatrix);

		// ps.Update(frameTime);
		ps.Draw(viewMatrix, projectionMatrix);
	}
private:
	double lastTime;

	glm::mat4 viewMatrix, projectionMatrix;
	glm::vec3 cameraPos;

	SkyBox skybox;
	Ground ground;
	Model model, niutou;
	ParticleSystem ps;
};

DECLARE_MAIN(Test);
