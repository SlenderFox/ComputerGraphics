#include "Camera.h"

Camera::Camera()
	: m_worldTransform(glm::mat4()),
	m_viewTransform(glm::mat4()),
	m_projectionTransform(glm::mat4()),
	m_projectionView(glm::mat4())
{
}

Camera::~Camera()
{
}

void Camera::setPerspective(const float pFov, const float pAspectRatio, const float pNear, const float pFar)
{
	m_projectionTransform = glm::perspective(pFov, pAspectRatio, pNear, pFar);
}

void Camera::setLookAt(const glm::vec3 pFrom, const glm::vec3 pTo, const glm::vec3 pUp)
{
	m_viewTransform = glm::lookAt(pFrom, pTo, pUp);
	m_worldTransform = glm::inverse(m_viewTransform);
}

void Camera::setPosition(const glm::vec3 pPosition)
{
	m_worldTransform = glm::mat4(m_worldTransform[0], m_worldTransform[1], m_worldTransform[2], glm::vec4(pPosition, m_worldTransform[3][3]));
	m_viewTransform = glm::inverse(m_worldTransform);
}

void Camera::setRotation(glm::mat3 pRotations)
{
	m_worldTransform[0] = glm::vec4(pRotations[0], 0);
	m_worldTransform[1] = glm::vec4(pRotations[1], 0);
	m_worldTransform[2] = glm::vec4(pRotations[2], 0);
	m_viewTransform = glm::inverse(m_worldTransform);
}

void Camera::updateProjectionViewTransform()
{
	m_projectionView = m_projectionTransform * m_viewTransform;
}