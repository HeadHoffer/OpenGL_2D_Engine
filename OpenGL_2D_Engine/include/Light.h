#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Color.h>

class Light
{
public:
	//The color of the light
	glm::vec3 Ambient = glm::vec3(0.05f, 0.05f, 0.05f);

	//Diffusion value of the light
	glm::vec3 Diffuse = glm::vec3(0.5f, 0.5f, 0.5f);

	//The reflection strength of the light
	glm::vec3 Specular = Color::White;
};

class WorldLight : public Light
{
public:
	//Position in world space
	glm::vec3 Position;

	//Related to how far the light travels
	float Constant = 1.0f;
	//Related to how far the light travels
	float Linear = 0.045f; //0.09f;
	//Related to how far the light travels
	float Quadratic = 0.0072f; //0.032f;
};

class DirLight : public Light
{
public:
	//Direction of the light
	glm::vec3 Direction;

	//Constructs a new Directional Light Source
	DirLight(glm::vec3 direction, glm::vec3 color = glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3 specular = Color::White)
	{
		Direction = direction;
		Ambient = color;
		Diffuse = diffuse;
		Specular = specular;
	}
};

class SpotLight : public WorldLight
{
public:
	//Direction of the light
	glm::vec3 Direction;

	//Inner light cone
	float CutOff;

	//Outer light cone
	float OuterCutOff;

	//Constructs a new Spotlight
	SpotLight(glm::vec3 position, glm::vec3 direction, float cutoff, float outercutoff, 
		glm::vec3 color = glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3 specular = Color::White, 
		float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
	{
		Position = position;
		Direction = direction;
		CutOff = cutoff;
		OuterCutOff = outercutoff;
		Ambient = color;
		Diffuse = diffuse;
		Specular = specular;
		Constant = constant;
		Linear = linear;
		Quadratic = quadratic;
	}
};

class PointLight : public WorldLight
{
public:
	//Constructs a new point light
	PointLight(glm::vec3 position,
		glm::vec3 color = glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3 specular = Color::White, 
		float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
	{
		Position = position;
		Ambient = color;
		Diffuse = diffuse;
		Specular = specular;
		Constant = constant;
		Linear = linear;
		Quadratic = quadratic;
	}
};
#endif