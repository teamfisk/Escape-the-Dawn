#ifndef Camera_h__
#define Camera_h__

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera
{
public:
	Camera(float yFOV, float aspectRatio, float nearClip, float farClip);

	glm::vec3 Forward();
	glm::vec3 Right();
	glm::mat4 Orientation();

	float AspectRatio() const { return m_AspectRatio; }
	void AspectRatio(float val);

	glm::vec3 Position() const { return m_Position; }
	void Position(glm::vec3 val);

	float Pitch() const { return m_Pitch; }
	void Pitch(float val);
	float Yaw() const { return m_Yaw; }
	void Yaw(float val);

	glm::mat4 ProjectionMatrix() const { return m_ProjectionMatrix; }
	void ProjectionMatrix(glm::mat4 val) { m_ProjectionMatrix = val; }

	glm::mat4 ViewMatrix() const { return m_ViewMatrix; }
	void ViewMatrix(glm::mat4 val) { m_ViewMatrix = val; }

private:
	void UpdateProjectionMatrix();
	void UpdateViewMatrix();

	float m_FOV;
	float m_AspectRatio;
	float m_NearClip;
	float m_FarClip;

	glm::vec3 m_Position;
	float m_Pitch;
	float m_Yaw;

	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
};

#endif // Camera_h__
