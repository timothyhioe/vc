#pragma once

#include "OpenGLWindow.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>
#include "Transform.h"
#include "Cube.h"

class Scene
{
public:
	Scene(OpenGLWindow* window);
	~Scene();

	bool init();
	void shutdown();
	void render(float dt);
	void update(float dt);
	OpenGLWindow* getWindow();

	void onKey(Key key, Action action, Modifier modifier);
	void onMouseMove(MousePosition mouseposition);
	void onMouseButton(MouseButton button, Action action, Modifier modifier);
	void onMouseScroll(double xscroll, double yscroll);
	void onFrameBufferResize(int width, int height);

private:
	OpenGLWindow* m_window;
	AssetManager m_assets;
    ShaderProgram* m_shader;
    GLuint vaoID, vboID;
    Transform cubeTrans;

    //Body Parts
    Transform headTransform;

    Transform torsoTransform;

    Transform upperRightArmTransform;
    Transform lowerRightArmTransform;
    Transform rightShoulderTransform;
    Transform rightElbowTransform;

    Transform upperLeftArmTransform;
    Transform lowerLeftArmTransform;
    Transform leftShoulderTransform;
    Transform leftElbowTransform;

    Transform rightLegTransform;
    Transform rightHipTransform;

    Transform leftLegTransform;
    Transform leftHipTransform;

    glm::vec3 leftShoulder = glm::vec3(-1.0f, 0.4f, 0.2f);
    glm::vec3 rightShoulder = glm::vec3(1.0f, 0.4f, 0.2f);

    glm::vec3 leftElbow = glm::vec3(-1.0f, 0.1f, 0.2f);
    glm::vec3 rightElbow = glm::vec3(1.0f, 0.1f, 0.2f);

    glm::vec3 leftHip = glm::vec3(-0.1, -0.5, 0.0);
    glm::vec3 rightHip = glm::vec3(0.1f, -0.5f, 0.0);



};

