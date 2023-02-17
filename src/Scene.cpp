#include "Scene.hpp"

Scene::Scene(const aiScene* scene)
{
	this->processMeshes(scene);
	this->processLights(scene);
	this->processCamera(scene);
}

Scene::~Scene() {
	//delte meshes
	for (auto* n : this->meshes)
	{
		delete n;
	}
	//delete camera
	auto c = this->camera.release();
	delete c;
	//delete light
	auto l = this->light.release();
	delete l;
}

void Scene::render(Shader& shader)
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->render(shader);
	}
}

void Scene::setUniforms(Shader& shader)
{
	light->setUniforms(shader);
	camera->setUniforms(shader);
	shader.setUniform("u_objectCol", glm::vec3(1.f, .5f, .32f));
}

void Scene::processCamera(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumCameras; i++) {
		aiVector3D point = scene->mCameras[i]->mPosition;
		glm::vec3 position = glm::vec3(point.x, point.y, point.z);
		this->camera = std::make_unique<Camera>(position);
	}
}

void Scene::processMeshes(const aiScene* scene) {
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		std::vector<float> vertices;
		aiMesh* aiMesh = scene->mMeshes[i];
		for (unsigned int j = 0; j < aiMesh->mNumVertices; j++) {
			// TODO: Copy the vertex data into the vector "vertices"
			for (int z = 0; z < 6; z++) {
				switch (z) {
					case 0:vertices.push_back(aiMesh->mVertices[j].x); break;
					case 1:vertices.push_back(aiMesh->mVertices[j].y); break;
					case 2:vertices.push_back(aiMesh->mVertices[j].z); break;
					case 3:vertices.push_back(aiMesh->mNormals[j].x); break;
					case 4:vertices.push_back(aiMesh->mNormals[j].y); break;
					case 5:vertices.push_back(aiMesh->mNormals[j].z); break;
				}
			}
			
		}
		
		std::vector<uint32_t> indices;
		for (unsigned int k = 0; k < aiMesh->mNumFaces; k++) {
			aiFace& face = aiMesh->mFaces[k];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		std::cout << "Num vertices (& normals): " << vertices.size() << std::endl;
		std::cout << "Num incides: " << indices.size() << std::endl;
		Mesh2* customMesh = new Mesh2(vertices, indices);
		this->meshes.push_back(customMesh);
	}
	std::cout << "Num meshes: " << this->meshes.size() << std::endl;
}

void Scene::processLights(const aiScene* scene)
{
	// TODO: Implement
	// 
	// Tip: Unique pointer are initialized as follows:
	for (int i = 0; i < scene->mNumLights; i++) {
		aiColor3D color = scene->mLights[i]->mColorDiffuse;
		aiVector3D point = scene->mLights[i]->mPosition;
		glm::vec3 lightCol = glm::vec3(color.r, color.g, color.b);
		glm::vec3 lightPos = glm::vec3(point.x, point.y, point.z);
		this->light = std::make_unique<PointLight>(lightPos, lightCol);
	}
	
}
