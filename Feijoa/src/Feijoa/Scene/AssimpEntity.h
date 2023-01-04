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
		std::vector<Ref<Texture2D>> Textures;

		RenderMesh(const RenderMesh&) = default;
		RenderMesh(const std::vector<ModelVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Ref<Texture2D>>& textures = {})
			: Vertices(vertices), Indices(indices), Textures(textures) {}

		inline bool HasTexture() const { return !Textures.empty(); }
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
		std::vector<Ref<Texture2D>> LoadTextures(const aiMaterial* material, aiTextureType type);

		glm::vec4 GetMaterialColor(const aiMaterial* material, const char* pKey, uint32_t type, uint32_t idx);

	private:
		std::string m_Directory;
		std::vector<Ref<Texture2D>> m_Textures;
		std::vector<RenderMesh> m_Meshes;
	};
}