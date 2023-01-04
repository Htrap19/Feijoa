#pragma once

#include "Feijoa/Scene/Entity.h"
#include "Feijoa/Renderer/VertexArray.h"
#include "Feijoa/Renderer/Texture.h"
#include "Feijoa/Renderer/Renderer3D.h"

#include <assimp/scene.h>
#include <glm/glm.hpp>

namespace Feijoa
{
	struct RenderMesh
	{
		std::vector<ModelVertex> Vertices;
		std::vector<uint32_t> Indices;
		Ref<Texture2D> Texture;

		inline bool HasTexture() const { return Texture != nullptr ; }
	};

	class AssimpEntity
	{
	public:
		AssimpEntity(const std::string& path);

		inline std::vector<RenderMesh>& GetMeshes() { return m_Meshes; }
		inline const std::vector<RenderMesh>& GetMeshes() const { return m_Meshes; }

	protected:
		void ProcessNode(aiNode* node, const aiScene* scene);
		RenderMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		Ref<Texture2D> AssimpEntity::LoadTexture(const aiMaterial* material, aiTextureType type, uint32_t idx);

	private:
		std::string m_Directory;
		std::vector<RenderMesh> m_Meshes;
	};
}