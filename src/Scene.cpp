#include "Scene.hpp"

Scene::Scene(const aiScene* scene)
{
	this->processMeshes(scene);
	this->processLights(scene);
}

//TODO delete vetor meshes

void Scene::render(Shader& shader)
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->render(shader);
	}
}

void Scene::setUniforms(Shader& shader)
{
	light->setUniforms(shader);
}

const glm::vec3& Scene::getCameraPos()
{
	return this->cameraPosition;
}

void Scene::processMeshes(const aiScene* scene) {
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		std::vector<float> vertices;
		aiMesh* aiMesh = scene->mMeshes[i];
		for (unsigned int j = 0; j < aiMesh->mNumVertices; j++) {
			// TODO: Copy the vertex data into the vector "vertices"
			for (int z = 0; z < 3; z++) {
				if (j == 0) {
					vertices.push_back(aiMesh->mVertices[j].x);
				}
				else if (j == 1) {
					vertices.push_back(aiMesh->mVertices[j].y);
				}
				else {
					vertices.push_back(aiMesh->mVertices[j].z);
				}
			}
			
		}
		
		std::vector<uint32_t> indices;
		for (unsigned int k = 0; k < aiMesh->mNumFaces; k++) {
			aiFace& face = aiMesh->mFaces[k];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		std::cout << "Num incides: " << indices.size() << std::endl;
		std::cout << "Num vertices: " << vertices.size() << std::endl;
		Mesh2* customMesh = new Mesh2(vertices, indices);
		this->meshes.push_back(customMesh);
	}
}

void Scene::processLights(const aiScene* scene)
{
	// TODO: Implement
	// 
	// Tip: Unique pointer are initialized as follows:
	for (int i = 0; i < scene->mNumLights; i++) {
		aiColor3D color = scene->mLights[i]->mColorAmbient;
		aiVector3D point = scene->mLights[i]->mPosition;
		glm::vec3 lightCol = glm::vec3(color.r, color.g, color.b);
		glm::vec3 lightPos = glm::vec3(point.x, point.y, point.z);
		this->light = std::make_unique<PointLight>(lightPos, lightCol);
	}
	
}
