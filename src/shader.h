#ifndef SHADER_H
#define SHADER_H

#include "glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        unsigned int ID;        
        
        Shader(const char* vertexPath, const char* fragmentPath)
        {
            std::string vertexShaderSource = readShaderSource(vertexPath);
            std::string fragmentShaderSource = readShaderSource(fragmentPath);

            unsigned int vertexShader, fragmentShader;
            
            vertexShader = createShader("VERTEX", vertexShaderSource);
            checkCompileErrors(vertexShader, "VERTEX");

            fragmentShader = createShader("FRAGMENT", fragmentShaderSource);
            checkCompileErrors(fragmentShader, "FRAGMENT");

            ID = glCreateProgram();
            glAttachShader(ID, vertexShader);
            glAttachShader(ID, fragmentShader);
            glLinkProgram(ID);
            checkCompileErrors(ID, "PROGRAM");

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        void use()
        {
            glUseProgram(ID);
        }

        void setFloat(const std::string &name, float value)
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }

    private:
        std::string readShaderSource(std::string filePath)
        {
            std::ifstream file(filePath);
            std::string contents((std::istreambuf_iterator<char>(file)), 
            std::istreambuf_iterator<char>());
            return contents;
        }

        unsigned int createShader(const char* shaderType, std::string shaderSource)
        {
            unsigned int shader;

            if(shaderType == "VERTEX")
                shader = glCreateShader(GL_VERTEX_SHADER);
            else
                shader = glCreateShader(GL_FRAGMENT_SHADER);
            
            glShaderSource(shader, 1, (const GLchar *const *) &shaderSource, NULL);
            glCompileShader(shader);

            return shader;
        }

        void checkCompileErrors(unsigned int shader, std::string type)
        {
            int success;
            char infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
        }
};

#endif