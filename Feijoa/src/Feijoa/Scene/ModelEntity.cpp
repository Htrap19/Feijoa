#include "fjpch.h"
#include "ModelEntity.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Feijoa/Scene/Components.h"

namespace Feijoa
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
	};

	ModelEntity::ModelEntity(Entity* entity, const std::string& path, const glm::vec3& position, const glm::vec3& size)
		: m_Entity(entity), m_Position(position), m_Size(size)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		FJ_CORE_ASSERT((scene || scene->mRootNode || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != AI_SCENE_FLAGS_INCOMPLETE), "Failed to load model!");

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

	Ref<VertexArray> ModelEntity::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		Ref<VertexArray> vertexArray = VertexArray::Create();

		std::vector<Vertex> vertices;
		vertices.reserve(mesh->mNumVertices);
		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
		{
			glm::vec3 position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
			glm::vec2 texCoord = glm::vec2(0.0f);
			if (mesh->mTextureCoords[0])
				texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position)
				* glm::scale(glm::mat4(1.0f), m_Size);

			glm::vec3 pos = glm::vec3(glm::vec4(position, 1.0f) * model);

			vertices.push_back({ pos, texCoord });
		}

		std::vector<uint32_t> indices;
		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(sizeof(Vertex) * vertices.size());
		vertexBuffer->SetData(vertices.data(), sizeof(Vertex) * vertices.size());
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), indices.size());

		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

		return vertexArray;
	}

}