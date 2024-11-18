#include "Scene.h"
#include <AssetManager.h>
#include <iostream>
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

        float vertices[] = {-0.5, -0.5, 0.0, 0.0, 1.0, //first 2 for position, last 3 for rgb color
                            0.5, -0.5, 0.0, 0.0, 1.0,
                            0.5, 0.5, 0.0, 1.0, 0.0,
                            0.0, 1.0, 1.0, 0.0, 0.0,
                            -0.5, 0.5, 0.0, 1.0, 0.0};

        int indices[] = {0, 1, 2,
                         0, 2, 4,
                         4, 2, 3};


        float T_vertices[] = { -0.16, -1.0, 1.0, 0.0, 0.0, //0
                               0.16, -1.0, 0.0, 1.0, 0.0, //1
                               0.16, 0.5, 0.0, 0.0, 1.0, //2
                               -0.16, 0.5, 1.0, 0.0, 0.0, //3
                               -1.0, 0.5, 0.0, 1.0, 0.0, //4
                               -1.0, 0.83, 0.0, 0.0, 1.0, //5
                               1.0, 0.5, 0.0, 1.0, 0.0, //6
                               1.0, 0.83, 1.0, 0.0, 0.0 //7
        };

        int T_indices[] = {0, 1, 2,
                           0, 2, 3,
                           6, 5, 4,
                           5, 6, 7
                           };

		/*
		 * ************
		 * Place your code here!
		 * ************
		 */
        \

        //generate and activate vbo
        glGenBuffers(1, &vboID); //vbo ID generieren
        glBindBuffer(GL_ARRAY_BUFFER, vboID); //korrekter vbo Buffer aktivieren
        glBufferData(GL_ARRAY_BUFFER, sizeof(T_vertices), &T_vertices, GL_STATIC_DRAW);

        //generate and activate vao
        glGenVertexArrays(1, &vaoID); //vao ID generieren
        glBindVertexArray(vaoID);

        //describe vbo in the vao
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr); // Position, 5 floats(2 for position and 3 for color)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float))); //color, 2 as the offset
        glEnableVertexAttribArray(1);

        //generate and bin ibo
        GLuint iboID;
        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T_indices), T_indices, GL_STATIC_DRAW);

        //unbind vao
        glBindVertexArray(0);

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

    glBindVertexArray(vaoID);

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);

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
