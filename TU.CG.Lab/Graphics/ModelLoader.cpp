#include "ModelLoader.hpp"

#include <assimp/postprocess.h>
#include <filesystem>

#include "TextureCache.hpp"

namespace Graphics
{
	std::unique_ptr<Model> ModelLoader::Load(
		const std::string& modelFilePath, TextureCache& textureCache)
	{
		Assimp::Importer importer;

		constexpr auto flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals |
			aiProcess_FlipUVs;

		const auto scene = importer.ReadFile(modelFilePath, flags);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			const auto errorMessage = "Could not load model: " +
				modelFilePath + " Error: " + importer.GetErrorString();

			throw std::exception(errorMessage.c_str());
		}

		const auto modelDirectory = std::filesystem::path(modelFilePath)
			.parent_path()
			.string();

		std::vector<Mesh> meshes;
		meshes.reserve(scene->mNumMeshes);

		ProcessNode(scene->mRootNode, scene, meshes, modelDirectory, textureCache);

		return std::make_unique<Model>(std::move(meshes));
	}

	void ModelLoader::ProcessNode(
		const aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes,
		const std::string& modelDirectory, TextureCache& textureCache)
	{
		for (unsigned i = 0; i < node->mNumMeshes; ++i)
		{
			const auto assimpMesh = scene->mMeshes[node->mMeshes[i]];

			auto ourMesh = ProcessMesh(
				assimpMesh, scene, modelDirectory, textureCache);

			meshes.push_back(std::move(ourMesh));
		}

		for (unsigned i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(
				node->mChildren[i], scene, meshes,
				modelDirectory, textureCache);
		}
	}

	Mesh ModelLoader::ProcessMesh(
		aiMesh* mesh, const aiScene* scene, const std::string& modelDirectory,
		TextureCache& textureCache)
	{
		std::vector<Vertex> vertices;
		vertices.reserve(mesh->mNumVertices);

		std::vector<unsigned> indices;
		std::vector<Texture> textures;

		for (unsigned i = 0; i < mesh->mNumVertices; ++i)
		{
			auto vertex = Vertex();

			const auto position = mesh->mVertices[i];
			const auto normal = mesh->mNormals[i];

			vertex.Position = glm::vec3(
				position.x, position.y, position.z);

			vertex.Normal = glm::vec3(
				normal.x, normal.y, normal.z);

			if (mesh->mTextureCoords[0])
			{
				const auto texCoords = mesh->mTextureCoords[0][i];

				vertex.TexCoords = glm::vec2(
					texCoords.x, texCoords.y);
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f);
			}

			vertices.push_back(vertex);
		}

		for (unsigned i = 0; i < mesh->mNumFaces; ++i)
		{
			const auto face = mesh->mFaces[i];

			for (unsigned j = 0; j < face.mNumIndices; ++j)
				indices.push_back(face.mIndices[j]);
		}

		auto material = scene->mMaterials[mesh->mMaterialIndex];

		auto diffuseMaps = LoadMaterialTextures(
			material, aiTextureType_DIFFUSE, modelDirectory, textureCache);

		auto specularMaps = LoadMaterialTextures(
			material, aiTextureType_SPECULAR, modelDirectory, textureCache);

		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> ModelLoader::LoadMaterialTextures(
		const aiMaterial* mat, aiTextureType type,
		const std::string& modelDirectory, TextureCache& textureCache)
	{
		const unsigned textureCount = mat->GetTextureCount(type);

		std::vector<Texture> textures;
		textures.reserve(textureCount);

		for (unsigned i = 0; i < textureCount; ++i)
		{
			aiString texturePath;
			mat->GetTexture(type, i, &texturePath);

			auto texture = textureCache.GetTexture(
				modelDirectory + "/" + texturePath.C_Str());

			textures.push_back(texture);
		}

		return textures;
	}
}
