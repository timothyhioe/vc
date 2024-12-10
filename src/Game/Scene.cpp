#include "Scene.h"
#include <AssetManager.h>

Scene::Scene(OpenGLWindow * window) :
        m_window(window),
        m_time(0.0f)
{
    assert(window != nullptr);;
}

Scene::~Scene()
{}

bool Scene::init()
{
    try
    {
        //Load shader
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();

        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertWithNormals), cubeVertWithNormals, GL_STATIC_DRAW);

        // b) Tạo VAO
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);
 //2.3.1
        // c) Kết nối các thuộc tính
        // Position: die erste 3 (x,y,z)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Normals die naechste 3 nx, ny, nz (normalen)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Colors: 3 float (r, g, b) (farbe)
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);


        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearDepth(1.0);

        //P2.2
        //cubeTrans = new Transform;
        lightTransform = Transform();
        glBindVertexArray(0);
        // Thiết lập ánh sáng
        std::cout << "Scene initialization done\n";
        return true;
    }
    catch (std::exception& ex)
    {
        throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
    }
}

void Scene::render(float dt)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_shader->use();

    m_cameraPos = glm::vec3(0.0f, 2.0f, 3.0f); // Camera  x: von link nach ract, y von oben nach unten , z : fern
    m_cameraTarget = glm::vec3(-3.0f, 0.0f, 0.0f); //Betrachtung, X:von link nacht recht, y oben nach unten, z: fern
    m_cameraUp = glm::vec3(-0.0f, 2.0f, -0.0f); //Upvektor

    // view Matrix erstellt
    m_viewMatrix = glm::lookAt(m_cameraPos, m_cameraTarget, m_cameraUp);
    m_shader->setUniform("view", m_viewMatrix,false);

    //fov : camera sehen kann
    glm::mat4 m_projection = glm::perspective(glm::radians(90.0f), 16.0f/9.0f, 0.01f, 100.0f);
    //90 grad damit bleibt in zentrum, am rand verzerrt, nahe von 0.01 wird abgeschnitten, >100 wird ausgeblendet
    m_shader->setUniform("projection", m_projection,false);

    lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // Licht Weiss
    lightPosition = glm::vec3(0.0f, 2.0f, 0.5f); // x: rechts oder links, y: unter oder ober, z: near oder far
    lightTransform.setPosition(lightPosition);
    lightTransform.setScale(glm::vec3(0.2f, 0.3f, 0.2f));
    glm::mat4 lightModel = lightTransform.getMatrix(); // setze licht durch die kleine cube

    lightTransform.rotate(glm::vec3(0.0f, 1.0f * dt, 0.0f));
    m_shader->setUniform("lightPos",lightPosition);
    m_shader->setUniform("lightColor",lightColor);
    m_shader->setUniform("viewPos",m_cameraPos);
    m_shader->setUniform("emissiveColor", glm::vec3(1.0f, 1.0f, 1.0f)); // lich fur kleine cube
    m_shader->setUniform("model", lightModel, false);

    // Hiển thị nguồn sáng (cube nhỏ)
    glBindVertexArray(vaoID);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Cube chính
    glBindVertexArray(vaoID);
    cubeTransform.rotate(glm::vec3(0.5*dt,0.5*dt,0.5*dt));
    glm::mat4 model = cubeTransform.getMatrix();
    m_shader->setUniform("model", model, false);
    m_shader->setUniform("emissiveColor", glm::vec3(0.0f, 0.0f, 0.0f)); // cube to không phát sáng
    glDrawArrays(GL_TRIANGLES, 0, 36); // 36 đỉnh (6 mặt * 2 tam giác * 3 đỉnh)
    //glBindVertexArray(0);
}

void Scene::update(float dt)
{
    m_time += dt;
}

OpenGLWindow * Scene::getWindow()
{
    return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}
void Scene::shutdown()
{

}
