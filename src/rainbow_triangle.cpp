/*this file contains program before creating Shaderclass,
 so everything is in one place like shaders's source code and compiling them
*/

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void shader_compile_error(unsigned int shader);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float timeValue;
float greenValue;
int vertexColorLocation;

//vertex shader
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos, 1.0f);\n"
" ourColor = aColor;\n"
"}\0";

 //fragment shader
 const char *fragmentShaderSource = "#version 330 core\n"
 "out vec4 FragColor;\n"
 "in vec3 ourColor;\n"
 "void main()\n"
 "{\n"
 " FragColor = vec4(ourColor, 1.0f);\n"
 "}\0";


int main(){

    //vertcies 
    float vertices[] ={
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,//top
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//bottomleft
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f//bottomright

    };

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



    //compiling shaders

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    //checking if compilation of vertex shader was correct
    shader_compile_error(vertexShader);
    shader_compile_error(fragmentShader);


    //creating sahder program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


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


        //using shader program
        // timeValue = glfwGetTime();
        // greenValue = (sin(timeValue * 10.0f) / 2.0f) + 0.5f;
        // vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.2f, 1.0f);

        glUseProgram(shaderProgram);
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
void shader_compile_error(unsigned int shader){
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}