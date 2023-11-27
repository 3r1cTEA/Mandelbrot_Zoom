#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>

#include <iostream>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

int screen_width{ 1080 };
int screen_height{ 1080 };

int num_frames{ 0 };
float last_time{ 0.0f };

float center_x{ 0.0f };
float center_y{ 0.0f };
float zoom{ 1.0 };
// Vertices coordinates
GLfloat vertices[] =
{
    -1.0f, -1.0f, -0.0f,    // Lower left corner
    1.0f,   1.0f, -0.0f,    // Lower right corner
    -1.0f,  1.0f, -0.0f,    // Upper corner
    1.0f, -1.0f, -0.0f      // Inner left
    
};

// Indices for vertices order
GLuint indices[] =
{
   0, 1, 2,
    0, 3, 1
};

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}
 
void countFPS()
{
    double current_time = glfwGetTime();
    num_frames++;
    if (current_time - last_time >= 1.0)
    {
        std::cout << 1000.0 / num_frames << "ms / frame\n";
        num_frames = 0;
        last_time += 1.0;
    }
}

void process_input(GLFWwindow * window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        center_y = center_y + 0.005f * zoom;
        if (center_y > 1.0f)
        {
            center_y = 1.0f;
    }
    }
 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        center_y = center_y - 0.005f * zoom;
        if (center_y < -1.0f)
        {
            center_y = -1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        center_x = center_x - 0.005f * zoom;
        if (center_x < -1.0f)
        {
            center_x = -1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        center_x = center_x + 0.005f * zoom;
        if (center_x > 1.0f)
        {
            center_x = 1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        zoom = zoom * 1.02f;
        if (zoom > 1.0f)
        {
            zoom = 1.0f;
        }
    }
 
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        zoom = zoom * 0.98f;
        if (zoom < 0.00001f)
        {
            zoom = 0.00001f;
        }
    }
}

int main(void)
{
    // Initialize GLFW
    glfwInit();

    //Set OpenGL version in GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Set CORE profile in GLFW
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //set GLFW window, 800 x 800
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "MyOpenGL", NULL, NULL);
    if (window== NULL)
    {
        std::cout << "Failed to create GFLW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD to configure OpenGL
    gladLoadGL();

    //set viewport for OpenGL in the window
    glViewport(0, 0, screen_width, screen_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Generates Shader object using shaders defualt.vert and default.frag
    Shader shaderProgram("res/default.vert", "res/default.frag");

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkVBO(VBO1, 0);
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    



    while(!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        process_input(window);
        shaderProgram.Activate();
        shaderProgram.set_float("zoom", zoom);
        shaderProgram.set_float("center_x", center_x);
        shaderProgram.set_float("center_y", center_y);
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}