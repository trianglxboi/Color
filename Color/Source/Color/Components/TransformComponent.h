#pragma once

#include "Core/Base.h"

#include <glm/glm.hpp>

namespace Color
{
	struct TransformComponent
	{
		CL_COMPONENT_ID("TransformComponent");

		// Only the X and Y components of the position are used in a 2D environment.
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };

		// The Z component of the rotation is used as the rotation in a 2D environment.
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };

		// Only the X and Y components of the size are used in a 2D environment.
		glm::vec3 Size     = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent& operator=(const TransformComponent&) = default;

		TransformComponent(const glm::vec3& position, const glm::vec3& rotation = {}, const glm::vec3& size = glm::vec3(1.0f));
		TransformComponent(const glm::vec2& position, float rotation, const glm::vec2& size = glm::vec2(1.0f));

		glm::mat4 CalculateTransformMatrix2D() const;
		glm::mat4 CalculateTransformMatrix3D() const;
	};
}
