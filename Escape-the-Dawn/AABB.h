#ifndef AABB_h__
#define AABB_h__

#include <glm/glm.hpp>

struct AABB
{
	AABB(glm::vec3 origin, glm::vec3 volumeVector) 
		: Origin(origin), VolumeVector(volumeVector) { }
	
	glm::vec3 Origin;
	glm::vec3 VolumeVector; //The vector that defines the volume of the BB, it goes from the origin to a corner
};

#endif // !AABB_h__
