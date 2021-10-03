#pragma once

#include "Feijoa/Scene/Entity.h"
#include <assimp/scene.h>
#include "Feijoa/Renderer/VertexArray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Feijoa
{
	class ModelEntity
	{
	public:
		ModelEntity(Entity* entity, const std::string& path, const glm::vec3& position, const glm::vec3& size);

	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		Ref<VertexArray> ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		Entity* m_Entity;
		std::string m_Directory;
		glm::vec3 m_Position;
		glm::vec3 m_Size = glm::vec3(1.0f);
	};
}