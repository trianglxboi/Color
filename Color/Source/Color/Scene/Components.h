#pragma once

#include "Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Color
{
	struct NameComponent
	{
		CL_COMPONENT_ID("NameComponent");

		std::string Name;

		NameComponent() = default;
		NameComponent(const NameComponent&) = default;
		NameComponent& operator=(const NameComponent&) = default;

		NameComponent(std::string_view name)
			: Name(name) { }
	};

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

		TransformComponent(const glm::vec3& position, const glm::vec3& rotation = {}, const glm::vec3& size = glm::vec3(1.0f))
			: Position(position), Rotation(rotation), Size(size) { }

		TransformComponent(const glm::vec2& position, float rotation, const glm::vec2& size = glm::vec2(1.0f))
			: Position{ position.x, position.y, 0.0f }, Rotation{ 0.0f, 0.0f, rotation }, Size{ size.x, size.y, 0.0f } { }

		glm::mat4 CalculateTransformMatrix2D() const
		{
			return glm::translate(glm::mat4(1.0f), Position) * glm::toMat4(glm::qua(Rotation)) * glm::scale(glm::mat4(1.0f), Size);
		}

		glm::mat4 CalculateTransformMatrix3D() const
		{
			return glm::translate(glm::mat4(1.0f), { Position.x, Position.y, 0.0f }) *
				   glm::rotate(glm::mat4(1.0f), Rotation.z, { 0.0f, 0.0f, 1.0f }) *
				   glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 0.0f });
		}
	};
}
