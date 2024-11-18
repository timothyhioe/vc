#include "Scene.h"
#include <AssetManager.h>
#include <iostream>
#include "Cube.h"

using namespace std;

Scene::Scene(OpenGLWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
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

		/*
		 * ************
		 * Place your code here!
		 * ************
		 */
        \

        //generate and activate vbo
        glGenBuffers(1, &vboID); //vbo ID generieren
        glBindBuffer(GL_ARRAY_BUFFER, vboID); //korrekter vbo Buffer aktivieren
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), &cubeVert, GL_STATIC_DRAW);

        //generate and activate vao
        glGenVertexArrays(1, &vaoID); //vao ID generieren
        glBindVertexArray(vaoID);

        //describe vbo in the vao
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr); // Position, 5 floats(2 for position and 3 for color)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float))); //color, 2 as the offset
        glEnableVertexAttribArray(1);

        //generate and bin ibo
        GLuint iboID;
        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);

        //unbind vao
        glBindVertexArray(0);

        cubeTrans.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        cubeTrans.setScale(glm::vec3(1.0f));

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        cout << "Scene initialization done\n";
        return true;
	}
	catch (std::exception& ex)
	{
	    throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
	}
}


void Scene::render(float dt)
{

    /*
    * ************
    * Place your code here!
    * ************
    */

    m_shader->use();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //remove trailing effect from the rotating cube

    cubeTrans.rotate(glm::vec3(0.0f, dt, 0.0f)); // Rotate around Y-axis
    cubeTrans.rotate(glm::vec3(dt, 0.0f, 0.0f)); // Rotate around X-axis

    m_shader->setUniform("model", cubeTrans.getMatrix(), false);

    glBindVertexArray(vaoID);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); // cube has 36 indices

    glBindVertexArray(0);


}

void Scene::update(float dt)
{

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
