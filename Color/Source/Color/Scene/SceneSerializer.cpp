#include "ColorPCH.h"
#include "SceneSerializer.h"

#include "Scene/Components.h"
#include "Utils/FileSystem.h"

#include <yaml-cpp/yaml.h>

namespace YAML
{
	template <>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();

			return true;
		}
	};
	
	template <>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();

			return true;
		}
	};
	
	template <>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();

			return true;
		}
	};
}

namespace Color
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& vector)
	{
		return out << YAML::Flow << YAML::BeginSeq << vector.x << vector.y << YAML::EndSeq;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& vector)
	{
		return out << YAML::Flow << YAML::BeginSeq << vector.x << vector.y << vector.z << YAML::EndSeq;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& vector)
	{
		return out << YAML::Flow << YAML::BeginSeq << vector.x << vector.y << vector.z << vector.w << YAML::EndSeq;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, const ECS::Entity& entity)
	{
		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << entity.ID; // Entity

		if (entity.HasComponent<NameComponent>())
		{
			out << YAML::Key << "NameComponent";
			out << YAML::BeginMap; // NameComponent

			NameComponent& nc = entity.GetComponent<NameComponent>();
			out << YAML::Key << "Name" << YAML::Value << nc.Name;

			out << YAML::EndMap; // NameComponent
		}
		
		if (entity.HasComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TransformComponent

			TransformComponent& tc = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Position" << YAML::Value << tc.Position;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Size" << YAML::Value << tc.Size;

			out << YAML::EndMap; // TransformComponent
		}

		out << YAML::EndMap; // Entity
	}

	bool SceneSerializer::Serialize(std::string_view path) const
	{
		YAML::Emitter out;
		{
			out << YAML::BeginMap; // Root
			out << YAML::Key << "Scene" << YAML::Value;
			{
				out << YAML::BeginMap; // Scene
				out << YAML::Key << "Name" << YAML::Value << m_Scene->GetName();
				out << YAML::Key << "Running" << YAML::Value << m_Scene->IsRunning();
				out << YAML::Key << "Paused" << YAML::Value << m_Scene->IsPaused();
				out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq; // Entities
				{
					for (auto&& [id, entity] : m_Scene->m_Entities)
					{
						SerializeEntity(out, entity);
					}
				}
				out << YAML::EndSeq; // Entities
				out << YAML::EndMap; // Scene
			}
			out << YAML::EndMap; // Root
		}

		return FileSystem::Write(path, out.c_str());
	}

	bool SceneSerializer::Deserialize(std::string_view path)
	{
		YAML::Node nRoot;
		try
		{
			nRoot = YAML::LoadFile(path.data());
		}
		catch (YAML::ParserException e)
		{
			CL_CORE_ERROR("Failed to load scene file '{}'\n.	{}", path, e.what());
			return false;
		}

		YAML::Node nScene = nRoot["Scene"];
		if (!nScene)
		{
			CL_CORE_ERROR("Scene file '{}' has no root node!", path);
			return false;
		}

		m_Scene->SetName(nScene["Name"].as<std::string>());
		m_Scene->SetPaused(nScene["Paused"].as<bool>());
		if (nScene["Running"].as<bool>())
		{
			m_Scene->StartRuntime();
		}
		else
		{
			m_Scene->StopRuntime();
		}
		CL_CORE_TRACE("Deserializing scene '{}'...", m_Scene->GetName());

		YAML::Node nEntities = nScene["Entities"];
		if (nEntities)
		{
			size_t unnamedIdx = 0;

			for (YAML::Node nEntity : nEntities)
			{
				ECS::EntityID id = nEntity["Entity"].as<ECS::EntityID>();

				YAML::Node nNameComponent = nEntity["NameComponent"];
				std::string name = nNameComponent ? nNameComponent["Name"].as<std::string>() : "Unnamed Deserialized Entity (" + std::to_string(unnamedIdx++) + ')';

				Entity e = m_Scene->CreateEntityWithID(id, name);
				CL_CORE_TRACE("Deserializing entity '{}':{}", name, id);

				YAML::Node nTransformComponent = nEntity["TransformComponent"];
				if (nTransformComponent)
				{
					TransformComponent& tc = e.GetComponent<TransformComponent>();
					tc.Position = nTransformComponent["Position"].as<glm::vec3>();
					tc.Rotation = nTransformComponent["Rotation"].as<glm::vec3>();
					tc.Size = nTransformComponent["Size"].as<glm::vec3>();
				}
				else
				{
					e.RemoveComponent<TransformComponent>();
				}
			}
		}

		CL_CORE_INFO("Finished scene deserialization.");
		return true;
	}
}
