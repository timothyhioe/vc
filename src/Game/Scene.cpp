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

        //aufgabe 2.2
//        cubeTrans.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
//        cubeTrans.setScale(glm::vec3(1.0, 1.0, 1.0));

        //aufgabe 2.3
        //initialize body parts position and scale

        // torso
        torsoTransform.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));  // torso on the center
        torsoTransform.setScale(glm::vec3(1.0f, 2.0f, 0.5f));     // torso scaling

        // head
        headTransform.setPosition(glm::vec3(0.0f, 1.4f, 0.0f));  // head above torso
        headTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));     // head scaling

        // upper left arm
        upperLeftArmTransform.setPosition(glm::vec3(-0.7f, 0.25f, 0.2f));  // upper left arm position
        upperLeftArmTransform.setScale(glm::vec3(0.2f, 0.4f, 0.2f));     // arm scaling

        // lower left arm
        lowerLeftArmTransform.setPosition(glm::vec3(0.0f, -1.1f, 0.2f)); // position lower left arm
        lowerLeftArmTransform.setScale(glm::vec3(0.2f, 0.5f, 0.15f));

        // upper right arm
        upperRightArmTransform.setPosition(glm::vec3(0.7f, 0.25f, 0.2f));
        upperRightArmTransform.setScale(glm::vec3(0.2f, 0.4f, 0.2f));

        // lower right arm
        lowerRightArmTransform.setPosition(glm::vec3(0.0f, -1.1f, 0.2f));
        lowerRightArmTransform.setScale(glm::vec3(0.25f, 0.4f, 0.2f));

        // left leg
        leftLegTransform.setPosition(glm::vec3(-0.3f, -0.8f, 0.0f)); // position left leg
        leftLegTransform.setScale(glm::vec3(0.45f, 0.45f, 0.2f));    // leg width and length

        // right leg
        rightLegTransform.setPosition(glm::vec3(0.3f, -0.8f, 0.0f));
        rightLegTransform.setScale(glm::vec3(0.45f, 0.45f, 0.2f));




        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearDepth(1.0f);


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


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //remove trailing effect from the animation

    //aufgabe 2.2

//    cubeTrans.rotate(glm::vec3(0.0f, dt, 0.0f)); // Rotate around Y-axis
//    cubeTrans.rotate(glm::vec3(dt, 0.0f, 0.0f)); // Rotate around X-axis

//    m_shader->setUniform("model", cubeTrans.getMatrix(), false);


    //glBindVertexArray(vaoID);

    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); // cube has 36 indices




    //aufgabe 2.3

    // setup view and projection matrices
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)); // Position the camera
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f); // Perspective projection

    // Pass the matrices to the shader
    m_shader->setUniform("view", view, false);
    m_shader->setUniform("project", projection, false);


    //animation
    float timeValue = glfwGetTime();
    float speed = 3.5f;
    float maxAngle = 0.5f;         // maximum rotation angle
    float swingAngle = maxAngle * glm::sin(timeValue * speed); // animate between -maxAngle and +maxAngle

    // rotation for 3d look
    glm::mat4 rotateAroundPivot = glm::rotate(glm::mat4(1), glm::radians(-30.0f), glm::vec3(0, 1, 0));

    float red = (sin(timeValue) + 1.0f) / 2.0f; //  between 0 and 1
    float green = (sin(timeValue + glm::radians(120.0f)) + 1.0f) / 2.0f; // offset +120 for green
    float blue = (sin(timeValue + glm::radians(240.0f)) + 1.0f) / 2.0f; //  offset + 240 for blue

    // draw the torso
    glm::mat4 torso = torsoTransform.getMatrix() * rotateAroundPivot;
    m_shader->setUniform("color", glm::vec3(red, green, blue));
    m_shader->setUniform("model", torso , false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);  // Draw torso

    // draw the head
    glm::mat4 head = headTransform.getMatrix() * torso; //connect head to torso
    head = glm::scale(head, glm::vec3(1.2, 0.5, 1.0));
    m_shader->setUniform("model", head, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);  // Draw head

    // draw upper left arm
    float armSwingAngle = maxAngle * glm::sin(timeValue * speed + glm::pi<float>()); // opposite of legs
    glm::quat leftArmRotation = glm::angleAxis(glm::radians(armSwingAngle), glm::vec3(1, 0, 0));
    glm::mat4 upperLeftArm = torso * upperLeftArmTransform.getMatrix(); // connect to torso
    upperLeftArmTransform.rotateAroundPoint(leftShoulder, leftArmRotation);
    upperLeftArm = upperLeftArm * upperLeftArmTransform.getMatrix();
    upperLeftArm = glm::scale(upperLeftArm, glm::vec3(10.0, 2.0, 3.0));
    m_shader->setUniform("model", upperLeftArm, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    //draw lower left arm
    float maxLowerAngle = 0.3f;
    float delayFactor = 0.05f;
    float lowerArmSwingAngle = maxLowerAngle * glm::sin(timeValue * speed + glm::pi<float>() - delayFactor); // add some delay

    glm::mat4 lowerLeftArm = upperLeftArm;
    glm::quat lowerArmRotation = glm::angleAxis(glm::radians(lowerArmSwingAngle), glm::vec3(1, 0, 0.0));
    lowerLeftArmTransform.rotateAroundPoint(leftElbow, lowerArmRotation); // connect to the upper arm swinging animation
    lowerLeftArm = lowerLeftArm * lowerLeftArmTransform.getMatrix();
    lowerLeftArm = glm::scale(lowerLeftArm, glm::vec3(5.0, 2.0, 5.0));
    m_shader->setUniform("model", lowerLeftArm, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    // draw upper right arm
    float rightArmSwing = maxAngle * glm::sin((timeValue * speed) - delayFactor);
    glm::quat rightArmRotation = glm::angleAxis(glm::radians(rightArmSwing), glm::vec3(1, 0, 0));
    glm::mat4 upperRightArm = torso * upperRightArmTransform.getMatrix();
    upperRightArmTransform.rotateAroundPoint(rightShoulder, rightArmRotation);
    upperRightArm = upperRightArm * upperRightArmTransform.getMatrix();
    upperRightArm = glm::scale(upperRightArm, glm::vec3(10.0, 2.0, 3.0));
    m_shader->setUniform("model", upperRightArm, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    //draw lower right arm

    float lowerRightSwing = maxLowerAngle * glm::sin((timeValue * speed)  - delayFactor);
    glm::mat4 lowerRightArm = upperRightArm;
    glm::quat lowerRightArmRotation = glm::angleAxis(glm::radians(lowerRightSwing), glm::vec3(1, 0, 0));
    lowerRightArmTransform.rotateAroundPoint(rightElbow, lowerRightArmRotation);
    lowerRightArm = lowerRightArm * lowerRightArmTransform.getMatrix();
    lowerRightArm = glm::scale(lowerRightArm, glm::vec3(4.0, 2.0, 5.0));
    m_shader->setUniform("model", lowerRightArm, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);


    // Draw the left leg
    glm::mat4 leftLeg = torso; // attatch leg to torso
    glm::quat legRotation = glm::angleAxis(glm::radians(swingAngle), glm::vec3(1, 0, 0));
    leftLegTransform.rotateAroundPoint(leftHip, legRotation);
    leftLeg = leftLeg * leftLegTransform.getMatrix(); // Recalculate the final transformation
    leftLeg = glm::scale(leftLeg, glm::vec3(1.0, 1.0, 1.0));
    m_shader->setUniform("model", leftLeg, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    // Draw the right leg
    float rightSwingAngle = maxAngle * glm::sin(timeValue *  speed + glm::pi<float>()); // opposite of left leg swing
    glm::mat4 rightLeg = torso; // attatch leg to torso
    glm::quat rightLegRotation = glm::angleAxis(glm::radians(rightSwingAngle), glm::vec3(1, 0, 0));
    rightLegTransform.rotateAroundPoint(rightHip, rightLegRotation);
    rightLeg = rightLeg * rightLegTransform.getMatrix();
    rightLeg = glm::scale(rightLeg, glm::vec3(1.0, 1.0, 1.0));
    m_shader->setUniform("model", rightLeg, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);






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
