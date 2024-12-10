#pragma once

#include "OpenGLWindow.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>
#include "Transform.h"
#include "Cube.h"
#include "CubewithNormals.h"

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
    GLuint vaoID, vboID, iboID;

    float m_time;
    Transform* cubeTrans;

    //P2.3
    glm::vec3 rainbowColor;
    //Instanzen fuer die Transformationen des Roboters
    Transform cubeTransform;
    Transform headSkalierung, bodySkalierung, legSkalierung, armSkalierung;
    Transform headTrans, bodyTrans, legRightTrans, legLeftTrans, armTopLeftTrans, armBotLeftTrans, armTopRightTrans, armBotRightTrans;
    Transform headRot, bodyRot, legRightRot, legLeftRot, armTopLeftRot, armBotLeftRot, armTopRightRot, armBotRightRot;

    Transform robotSkalierung, robotRotate, robotTrans;

    glm::mat4 m_viewMatrix; // Ma trận ViewMatrix cho camera
    glm::vec3 m_cameraPos;  // Vị trí camera
    glm::vec3 m_cameraTarget; // Điểm mà camera nhìn vào
    glm::vec3 m_cameraUp; // Vector chỉ hướng lên của camera
    Transform lightTransform; // Transformation für die Lichtquelle
    glm::vec3 lightColor;     // Farbe der Lichtquelle
    glm::vec3 lightPosition;  // Position der Lichtquelle
};




