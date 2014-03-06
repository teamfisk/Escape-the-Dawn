#ifndef AABB_h__
#define AABB_h__

#include <GL/glew.h>
//#define GLFW_INCLUDE_GLU
//#include <GLFW/glfw3.h>
//#include <glext.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AABB
{
public:
	AABB(glm::vec3, glm::vec3);
	void CreateBB(void);

	
private:
	glm::vec3 origin;
	glm::vec3 volumeVector; //The vector that defines the volume of the BB, it goes from one corner to the opposite one

};
#endif // !AABB_h__
