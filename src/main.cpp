#include "app.h"
#include "header.h"
#include "util.h"

#include "skybox.h"
#include "ground.h"
#include "model.h"
#include "particlesystem.h"
#include "camera.h"

using namespace framework;
class Test:	public Application
{
public:
	virtual void startup(double currentTime)
	{
		lastTime = currentTime;

		camera.mViewportWidth = info.windowWidth;
		camera.mViewportHeight = info.windowHeight;

		skybox.Init("../resources/");
		ground.Init();

		model.Init("../resources/Sphere.obj");
		model.SetTexture("../resources/earth.bmp");
		model.SetPosition(0.0f, 0.0f, 0.0f);

		niutou.Init("../resources/niutou.obj");
		niutou.SetTexture("../resources/niutou.bmp");
		niutou.mModelMatrix = glm::translate(-5.0f, 0.0f, 4.0f) * glm::scale(0.05f, 0.05f, 0.05f);

		ps.Init(5.0f, 5.0f, 5.0f);
	}
	virtual void render(double currentTime)
	{
		double frameTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.SwitchTo3D(projectionMatrix);
		camera.Update(frameTime, viewMatrix);

		skybox.Draw(camera.mPos.x, camera.mPos.y, camera.mPos.z, viewMatrix, projectionMatrix);
		ground.Draw(viewMatrix, projectionMatrix);
		model.Draw(camera.mPos.x, camera.mPos.y, camera.mPos.z, viewMatrix, projectionMatrix);
		niutou.Draw(camera.mPos.x, camera.mPos.y, camera.mPos.z, viewMatrix, projectionMatrix);

		camera.SwitchTo2D(projectionMatrix);
		ps.Update(frameTime);
		ps.Draw(viewMatrix, projectionMatrix);
	}
    virtual void onKey(int key, int action)
    {
		bool value = false;
		switch (action) {
			case GLFW_PRESS:
				value = true;
				break;
			case GLFW_RELEASE:
				value = false;
				break;
			case GLFW_REPEAT:
				return;
				break;
		}

		switch (key) {
			case GLFW_KEY_A:
				camera.mbMoveLeft = value;
				break;
			case GLFW_KEY_D:
				camera.mbMoveRight = value;
				break;
			case GLFW_KEY_W:
				camera.mbMoveForward = value;
				break;
			case GLFW_KEY_S:
				camera.mbMoveBack = value;
				break;
			default:
				break;
		}
    }
    virtual void onMouseButton(int button, int action)
    {
		switch (action) {
			case GLFW_PRESS:
				getMousePosition(lastMousePosX, lastMousePosY);
				rotateView = true;
				break;
			case GLFW_RELEASE:
				rotateView = false;
				break;
			default:
				break;
		}

    }

    virtual void onMouseMove(int x, int y)
    {
		if ( rotateView ) {
			float angleRotateByRight = (y - lastMousePosY)/ 1000.0f;
			float angleRotateByUp = (x - lastMousePosX) / 1000.0f;
			camera.Pitch(angleRotateByRight);
			camera.Yaw(angleRotateByUp);

			lastMousePosX = x;
			lastMousePosY = y;
		}
    }
private:
	glm::mat4 viewMatrix, projectionMatrix;

	Camera camera;
	SkyBox skybox;
	Ground ground;
	Model model, niutou;
	ParticleSystem ps;
private:
	bool rotateView;
	int lastMousePosX;
	int lastMousePosY;
private:
	double lastTime;
};

DECLARE_MAIN(Test);
