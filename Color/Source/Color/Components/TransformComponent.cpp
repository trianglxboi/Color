#include "ColorPCH.h"
#include "TransformComponent.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Color
{
	TransformComponent::TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& size)
		: Position(position), Rotation(rotation), Size(size)
	{
	}

	TransformComponent::TransformComponent(const glm::vec2& position, float rotation, const glm::vec2& size)
		: Position{position.x, position.y, 0.0f}, Rotation{0.0f, 0.0f, rotation}, Size{size.x, size.y, 0.0f}
	{
	}

	glm::mat4 TransformComponent::CalculateTransformMatrix2D() const
	{
		return glm::translate(glm::mat4(1.0f), Position) * glm::toMat4(glm::qua(Rotation)) * glm::scale(glm::mat4(1.0f), Size);
	}

	glm::mat4 TransformComponent::CalculateTransformMatrix3D() const
	{
		return glm::translate(glm::mat4(1.0f), { Position.x, Position.y, 0.0f }) * glm::rotate(glm::mat4(1.0f), Rotation.z, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 0.0f });
	}
}
