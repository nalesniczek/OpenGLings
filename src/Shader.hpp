#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
    public:
        //the program ID
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath){
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try{
                //opening files of vertex and fragment shader
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                //now this gives stringstream conent of vertex and frgamnet shader
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                //converting stream into string who knows why
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch(std::ifstream::failure& e){
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            }
            //I have no idea why we have changed it into string and now we change it into fucking char
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();
            
            //compiling shaders
            //vertex shader
            unsigned int vertex, fragment;
            vertex = glCreateShader(GL_VERTEX_SHADER);
            //nevermind now I know because glShaderSource get as 3rd argument char*
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            checkCompileErrors(vertex, "VERTEX");
            //fragment shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            checkCompileErrors(fragment, "FRAGMENT");
            //geanerating ID for shader program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);
            checkCompileErrors(ID, "PROGRAM");
            //after linking shader program with it's shaders deleting shaders 
            glDeleteShader(vertex);
            glDeleteShader(fragment);

        }
        //function to use shader
        void use(){
            glUseProgram(ID);
        } 
        void setBool(const std::string &name, bool value) const{
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }
        void setInt(const std::string &name, int value) const{
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setFloat(const std::string &name, float value) const{
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }

    private:
        void checkCompileErrors(unsigned int shader, std::string type){
            int success;
            char infoLog[1024];
            if(type != "PROGRAM"){
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if(!success){
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout <<  "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
            else{
                glGetShaderiv(shader, GL_LINK_STATUS, &success);
                if(!success){
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout <<  "ERROR::SHADER_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
        }
};

#endif