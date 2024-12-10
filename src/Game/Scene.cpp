#include "Scene.h"
#include <AssetManager.h>
#include <iostream>
#include "Cube.h"
#include "CubeWithNormals.h"

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
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertWithNormals), &cubeVertWithNormals, GL_STATIC_DRAW);

        //generate and activate vao
        glGenVertexArrays(1, &vaoID); //vao ID generieren
        glBindVertexArray(vaoID);

        //describe vbo in the vao
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr); // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float))); // normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float))); // Colors
        glEnableVertexAttribArray(2);

        // GENERATE LIGHT SOURCE
        glGenBuffers(1, &lightVboID); // generate and activate VBO and upload data
        glBindBuffer(GL_ARRAY_BUFFER, lightVboID); //binding
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), cubeVert, GL_STATIC_DRAW);

        // generate and activate VAO
        glGenVertexArrays(1, &lightVaoID); // generate ID
        glBindVertexArray(lightVaoID); //binding

        // describe VBO in the VAO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // IBO
        glGenBuffers(1, &lightIboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightIboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);


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

        // light source
        lightSourceTransform.setPosition(glm::vec3(1.0f, 1.0f, 1.0f)); // initialize light source
        lightSourceTransform.setScale(glm::vec3(1.0f, 1.0f, 1.0f));


        glBindVertexArray(0); //Unbind VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind VBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind EBO

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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //remove trailing effect from the animation

    // Enable backface culling
    glEnable(GL_CULL_FACE); // Enable face culling
    glFrontFace(GL_CCW); // Define front faces as counter-clockwise
    glCullFace(GL_BACK); // Cull back faces

    // Enable Depth Test (2.3.3)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); //Using GL_LESS with glClearDepth(1.0f)
    glClearDepth(1.0f);


    //aufgabe 2.3

    // setup view and projection matrices
    float aspectRatio = static_cast<float>(m_window->getWindowHeight()) / static_cast<float>(m_window->getWindowWidth()); // Height / width so that it don't appear stretched
    glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector);// Position the camera
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f); // Perspective projection

    // Pass the matrices to the shader
    m_shader->setUniform("view", view, false);
    m_shader->setUniform("project", projection, false);


    //animation
    float timeValue = glfwGetTime();
    float speed = 3.0f;
    float maxAngle = 0.5f;         // maximum rotation angle
    float swingAngle = maxAngle * glm::sin(timeValue * speed); // animate between -maxAngle and +maxAngle

    // rotation for 3d look
    glm::mat4 rotateAroundPivot = glm::rotate(glm::mat4(1), glm::radians(-50.0f), glm::vec3(0, 1, 0));

    float red = (sin(timeValue) + 1.0f) / 2.0f; //  between 0 and 1
    float green = (sin(timeValue + glm::radians(120.0f)) + 1.0f) / 2.0f; // offset +120 for green
    float blue = (sin(timeValue + glm::radians(240.0f)) + 1.0f) / 2.0f; //  offset + 240 for blue

    // draw the torso
    glm::mat4 torso = torsoTransform.getMatrix() * rotateAroundPivot;
    m_shader->setUniform("color", glm::vec3(red, green, blue));
    m_shader->setUniform("model", torso , false);
    m_shader->setUniform("objectType", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);  // Draw torso

    // draw the head
    glm::mat4 head = headTransform.getMatrix() * torso; //connect head to torso
    head = glm::scale(head, glm::vec3(1.2, 0.5, 1.0));
    m_shader->setUniform("model", head, false);
    m_shader->setUniform("objectType", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);  // Draw head

    // draw upper left arm
    float armSwingAngle = maxAngle * glm::sin(timeValue * speed + glm::pi<float>()); // opposite of legs
    glm::quat leftArmRotation = glm::angleAxis(glm::radians(armSwingAngle), glm::vec3(1, 0, 0));
    glm::mat4 upperLeftArm = torso * upperLeftArmTransform.getMatrix(); // connect to torso
    upperLeftArmTransform.rotateAroundPoint(leftShoulder, leftArmRotation);
    upperLeftArm = upperLeftArm * upperLeftArmTransform.getMatrix();
    upperLeftArm = glm::scale(upperLeftArm, glm::vec3(10.0, 2.0, 3.0));
    m_shader->setUniform("model", upperLeftArm, false);
    m_shader->setUniform("objectType", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

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
    m_shader->setUniform("objectType", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // draw upper right arm
    float rightArmSwing = maxAngle * glm::sin((timeValue * speed) - delayFactor);
    glm::quat rightArmRotation = glm::angleAxis(glm::radians(rightArmSwing), glm::vec3(1, 0, 0));
    glm::mat4 upperRightArm = torso * upperRightArmTransform.getMatrix();
    upperRightArmTransform.rotateAroundPoint(rightShoulder, rightArmRotation);
    upperRightArm = upperRightArm * upperRightArmTransform.getMatrix();
    upperRightArm = glm::scale(upperRightArm, glm::vec3(10.0, 2.0, 3.0));
    m_shader->setUniform("model", upperRightArm, false);
    m_shader->setUniform("objectType", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //draw lower right arm

    float lowerRightSwing = maxLowerAngle * glm::sin((timeValue * speed)  - delayFactor);
    glm::mat4 lowerRightArm = upperRightArm;
    glm::quat lowerRightArmRotation = glm::angleAxis(glm::radians(lowerRightSwing), glm::vec3(1, 0, 0));
    lowerRightArmTransform.rotateAroundPoint(rightElbow, lowerRightArmRotation);
    lowerRightArm = lowerRightArm * lowerRightArmTransform.getMatrix();
    lowerRightArm = glm::scale(lowerRightArm, glm::vec3(4.0, 2.0, 5.0));
    m_shader->setUniform("model", lowerRightArm, false);
    m_shader->setUniform("objectType", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // Draw the left leg
    glm::mat4 leftLeg = torso; // attatch leg to torso
    glm::quat legRotation = glm::angleAxis(glm::radians(swingAngle), glm::vec3(1, 0, 0));
    leftLegTransform.rotateAroundPoint(leftHip, legRotation);
    leftLeg = leftLeg * leftLegTransform.getMatrix(); // Recalculate the final transformation
    leftLeg = glm::scale(leftLeg, glm::vec3(1.0, 1.0, 1.0));
    m_shader->setUniform("model", leftLeg, false);
    m_shader->setUniform("objectType", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Draw the right leg
    float rightSwingAngle = maxAngle * glm::sin(timeValue *  speed + glm::pi<float>()); // opposite of left leg swing
    glm::mat4 rightLeg = torso; // attatch leg to torso
    glm::quat rightLegRotation = glm::angleAxis(glm::radians(rightSwingAngle), glm::vec3(1, 0, 0));
    rightLegTransform.rotateAroundPoint(rightHip, rightLegRotation);
    rightLeg = rightLeg * rightLegTransform.getMatrix();
    rightLeg = glm::scale(rightLeg, glm::vec3(1.0, 1.0, 1.0));
    m_shader->setUniform("model", rightLeg, false);
    m_shader->setUniform("objectType", 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // draw lightsource
    glBindVertexArray(lightVaoID);

    float radius = 5.0f;

    //Circular rotation
    float lightSpeed = 2.0f;
    float x = radius * glm::cos(timeValue * lightSpeed);
    float z = radius * glm::sin(timeValue * lightSpeed);
    glm::vec3 animatedPosition = glm::vec3(x, 10.0f, z);
//    glm::mat4 lightSource = glm::translate(lightSourceTransform.getMatrix(), lightSourceTransform.getPosition());
    glm::mat4 lightSource = glm::translate(lightSourceTransform.getMatrix(), animatedPosition);
    lightSource = glm::scale(lightSource, glm::vec3(1.0, 1.0, 1.0));
    glm::vec3 lightColor = glm::vec3 (1.0f, 1.0f, 1.0f);

    m_shader->setUniform("model", lightSource, false);
    m_shader->setUniform("objectType", 1);
    m_shader->setUniform("lightPos", animatedPosition);
//    m_shader->setUniform("lightPos", lightSourceTransform.getPosition());
    m_shader->setUniform("lightColor", lightColor);

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
