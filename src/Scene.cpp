#include "Scene.hpp"

Scene::Scene(std::string fileName)
{
	// import scene
	Assimp::Importer importer;
	std::string scene_file = std::string(std::filesystem::current_path().generic_string()).append("/../res/").append(fileName);
	const aiScene* scene = importer.ReadFile(scene_file,
		aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType | aiProcess_PreTransformVertices);
	// If the import failed, report it
	if (!scene) {
		std::cerr << "Importing of 3D scene failed: " << importer.GetErrorString() << std::endl;
	}
	else {
		std::cout << "Import of '" << fileName << "' at: " << scene_file << " successfull" << std::endl;
	}
	// init scene
	this->processMeshes(scene);
	this->processLights(scene);
	this->processCamera(scene);
}

Scene::Scene(const Scene& scene) {
	this->camera = std::make_unique<Camera>(*(scene.camera));
	this->light = std::make_unique<PointLight>(*(scene.light));
	for (auto& m : scene.meshes) {
		this->meshes.push_back(std::make_unique<Mesh>(*(m)));
	}
	

}

Scene::~Scene() {
	this->meshes.clear();
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
}

void Scene::processCamera(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumCameras; i++) {
		aiVector3D point = scene->mCameras[i]->mPosition;
		aiVector3D look = scene->mCameras[i]->mLookAt;
		glm::vec3 position = glm::vec3(point.x, point.y, point.z);
		glm::vec3 lookAt = glm::vec3(look.x, look.y, look.z);
		this->camera = std::make_unique<Camera>(position, lookAt);
	}
}

void Scene::processMeshes(const aiScene* scene) {
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		std::vector<float> vertices;
		aiMesh* aiMesh = scene->mMeshes[i];
		aiColor4D* aiColor = aiMesh->mColors[0];
		glm::vec4 objColor(aiColor->r, aiColor->g, aiColor->b, aiColor->a);
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

		// ------ here hard coded what mash 1 & 2 get as values, 
		//		  can be done differently if scene file contains such values
		const float speed = (i == 0) ? 0.01f : -0.03f;

		// create and save mash
		this->meshes.push_back(std::make_unique<Mesh>(vertices, indices, speed, glm::vec3(.0f, 1.0f, .0f), objColor));
	}
	std::cout << "Num meshes: " << this->meshes.size() << std::endl;
}

void Scene::processLights(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumLights; i++) {
		aiColor3D color = scene->mLights[i]->mColorDiffuse;
		aiVector3D point = scene->mLights[i]->mPosition;
		glm::vec3 lightCol = glm::vec3(color.r, color.g, color.b);
		glm::vec3 lightPos = glm::vec3(point.x, point.y, point.z);
		this->light = std::make_unique<PointLight>(lightPos, lightCol);
	}

}

const aiScene* Scene::loadScene(std::string fileName) {
	// Create an instance of the Importer class
	Assimp::Importer importer;
	std::string scene_file = std::string(std::filesystem::current_path().generic_string()).append("/../res/").append(fileName);
	const aiScene* scene = importer.ReadFile(scene_file,
		aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType | aiProcess_PreTransformVertices);
	// If the import failed, report it
	if (!scene) {
		std::cerr << "Importing of 3D scene failed: " << importer.GetErrorString() << std::endl;
	}
	else {
		std::cout << "Import of '" << fileName << "' at: " << scene_file << " successfull" << std::endl;
	}
	return scene;
}