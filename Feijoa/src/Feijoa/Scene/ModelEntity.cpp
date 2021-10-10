#include "fjpch.h"
#include "ModelEntity.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Feijoa/Scene/Components.h"
#include "Feijoa/Renderer/Renderer3D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Feijoa
{

	ModelEntity::ModelEntity(Entity* entity, const std::string& path, const glm::vec3& position, const glm::vec3& size)
		: m_Entity(entity), m_Position(position), m_Size(size)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		FJ_CORE_ASSERT(scene || scene->mRootNode || ((scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != AI_SCENE_FLAGS_INCOMPLETE), "Failed to load model!");

		m_Directory = path.substr(0, path.find_last_of("/"));
		ProcessNode(scene->mRootNode, scene);
	}

	void ModelEntity::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Entity->AddComponent<MeshComponent>(ProcessMesh(mesh, scene));
		}

		for (uint32_t i = 0; i < node->mNumChildren; i++)
			ProcessNode(node->mChildren[i], scene);
	}

	MeshComponent ModelEntity::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		ModelVertex* vertices = new ModelVertex[mesh->mNumVertices];
		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
			vertices[i] = { { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z } };
		
		std::vector<uint32_t> indicesVec;
		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j++)
				indicesVec.push_back(face.mIndices[j]);
		}

		uint32_t* indices = new uint32_t[indicesVec.size()];
		memcpy(indices, indicesVec.data(), sizeof(uint32_t) * indicesVec.size());

		return MeshComponent(vertices, mesh->mNumVertices, indices, (uint32_t)indicesVec.size());
	}

}