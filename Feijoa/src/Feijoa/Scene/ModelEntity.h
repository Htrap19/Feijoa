#pragma once

#include "Feijoa/Scene/Entity.h"
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include "Feijoa/Renderer/VertexArray.h"

namespace Feijoa
{
	struct MeshComponent;
	struct MeshContainerComponent;
	struct ModelVertex;

	class ModelEntity
	{
	public:
		ModelEntity(Entity* entity, const std::string& path, const glm::vec3& position, const glm::vec3& size);

		inline glm::vec3 GetPosition() const { return m_Position; }
		inline glm::vec3 GetSize() const { return m_Size; }

	protected:
		void ProcessNode(aiNode* node, const aiScene* scene);
		MeshComponent ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		Entity* m_Entity;
		std::string m_Directory;
		glm::vec3 m_Position, m_Size;
		MeshContainerComponent* m_MeshContainer;
	};
}