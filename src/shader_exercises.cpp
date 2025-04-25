#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);



const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main(){

    //vertcies 
    float vertices[] ={
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,//top
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//bottomleft
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f//bottomright

    };
    float offset = 0.5f;

    // unsigned int indicies[] ={
    //     0, 1, 3,
    //     1, 2, 3
    // }; 

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    if(!glfwInit()){
        std::cout << "Failed to initiate glfw!\n"; 
    }

    //window creating
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "First OpenGL Window By me", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //resizes the window 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);

    Shader ourShader("C:/Users/Bartek/OpenGl_working_space/src/shader_vs_ex.txt","C:/Users/Bartek/OpenGl_working_space/src/shader_fs_ex.txt");


    //linking buffers
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    //binding VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //binding EBO
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);


    //location attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);




    while(!glfwWindowShouldClose(window)){
        //input
        processInput(window);

        //rendering commands
        glClearColor(0.6f, 0.1f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


    
        ourShader.use();
        ourShader.setFloat("xOffset", offset);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);


        //swapbuffer
        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
