#pragma once

#include "Project/Project.h"

namespace Color
{
	class ProjectSerializer
	{
	public:
		ProjectSerializer(const Ref<Project>& project);

		bool Serialize(std::string_view filepath) const;
		bool Deserialize(std::string_view filepath);
	private:
		Ref<Project> m_Project;
	};
}
