#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Static class for different color values
class Color
{
public:
	Color();
	~Color();

	static glm::vec3 Red;
	static glm::vec3 Green;
	static glm::vec3 Blue;
	static glm::vec3 Yellow;
	static glm::vec3 Purple;
	static glm::vec3 Cyan;
	static glm::vec3 White;
	static glm::vec3 Black;
};
#endif