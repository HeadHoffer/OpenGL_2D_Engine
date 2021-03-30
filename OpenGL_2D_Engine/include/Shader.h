#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Light.h>

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(std::string vertexPath, std::string fragmentPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        const char* vPath = vertexPath.c_str();
        const char* fPath = fragmentPath.c_str();

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vShaderFile.open(vPath);
            fShaderFile.open(fPath);
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        //Vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        //Fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        //Shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        //Print linking errors if they occur
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        //Clean up shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() 
    {
        glUseProgram(ID);
    }

    // Utility uniform functions
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setPointLight(const PointLight& light) const
    {
        setVec3("pointLight.position", light.Position);
        setVec3("pointLight.ambient", light.Ambient);
        setVec3("pointLight.diffuse", light.Diffuse);
        setVec3("pointLight.specular", light.Specular);
        setFloat("pointLight.constant", light.Constant);
        setFloat("pointLight.linear", light.Linear);
        setFloat("pointLight.quadratic", light.Quadratic);
    }
    // ------------------------------------------------------------------------
    void setDirLight(const DirLight& light) const
    {
        setVec3("dirLight.direction", light.Direction);
        setVec3("dirLight.ambient", light.Ambient);
        setVec3("dirLight.diffuse", light.Diffuse);
        setVec3("dirLight.specular", light.Specular);
    }
    // ------------------------------------------------------------------------
    void SetSpotLight(const SpotLight& light) const
    {
        setVec3("spotLight.position", light.Position);
        setVec3("spotLight.direction", light.Direction);
        setVec3("spotLight.ambient", light.Ambient);
        setVec3("spotLight.diffuse", light.Diffuse);
        setVec3("spotLight.specular", light.Specular);
        setFloat("spotLight.constant", light.Constant);
        setFloat("spotLight.linear", light.Linear);
        setFloat("spotLight.quadratic", light.Quadratic);
        setFloat("spotLight.cutOff", light.CutOff);
        setFloat("spotLight.outerCutOff", light.OuterCutOff);
    }

    void SetPointLights(const std::vector<PointLight>& lights) const
    {
        for (int i = 0; i < lights.size(); i++)
        {
            std::string name = "pointLights[" + std::to_string(i) + (std::string)"].";
            setVec3(name + "position", lights[i].Position);
            setVec3(name + "ambient", lights[i].Ambient);
            setVec3(name + "diffuse", lights[i].Diffuse);
            setVec3(name + "specular", lights[i].Specular);
            setFloat(name + "constant", lights[i].Constant);
            setFloat(name + "linear", lights[i].Linear);
            setFloat(name + "quadratic", lights[i].Quadratic);
        }
    }
};

#endif