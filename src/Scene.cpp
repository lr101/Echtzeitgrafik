#include "Scene.hpp"

Scene::Scene(std::string fileName, const GLfloat rot_per_frame, const glm::vec3 rot_mat)
{
	this->rot_per_frame_ = rot_per_frame;
	this->rot_mat_ = rot_mat;

	// import scene
	Assimp::Importer importer;
	std::string scene_file = std::string(std::filesystem::current_path().generic_string()).append("/../res/").
		append(fileName);
	const aiScene* scene = importer.ReadFile(scene_file,
	                                         aiProcess_CalcTangentSpace | aiProcess_Triangulate |
	                                         aiProcess_JoinIdenticalVertices |
	                                         aiProcess_SortByPType | aiProcess_PreTransformVertices);
	// If the import failed, report it
	if (!scene)
	{
		std::cerr << "Importing of 3D scene failed: " << importer.GetErrorString() << std::endl;
	}
	else
	{
		std::cout << "Import of '" << fileName << "' at: " << scene_file << " successfull" << std::endl;
	}
	// init scene
	this->processMeshes(scene);
	this->processLights(scene);
	this->processCamera(scene);
}

Scene::Scene(const Scene& scene)
{
	this->rot_per_frame_ = scene.rot_per_frame_;
	this->rot_mat_ = scene.rot_mat_;
	this->camera_ = std::make_unique<Camera>(*(scene.camera_));
	this->light = std::make_unique<PointLight>(*(scene.light));
	for (auto& m : scene.meshes)
	{
		this->meshes.push_back(std::make_unique<Mesh>(*(m)));
	}
}

Scene::~Scene()
{
	this->meshes.clear();
}

void Scene::render(Shader& shader)
{
	const glm::mat4 tmp_mat_model = glm::rotate(this->mat_model_, this->rot_amount_, this->rot_mat_);
	this->rot_amount_ = glm::radians(this->rot_per_frame_ + glm::degrees(this->rot_amount_));
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->render(shader, tmp_mat_model);
		this->light->apply_mat(shader, tmp_mat_model);
	}
}

void Scene::setUniforms(Shader& shader)
{
	light->setUniforms(shader);
	camera_->setUniforms(shader);
}

void Scene::processCamera(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumCameras; i++)
	{
		aiVector3D point = scene->mCameras[i]->mPosition;
		aiVector3D look = scene->mCameras[i]->mLookAt;
		auto position = glm::vec3(point.x, point.y, point.z);
		auto lookAt = glm::vec3(look.x, look.y, look.z);
		this->camera_ = std::make_unique<Camera>(position, lookAt);
	}
}

void Scene::processMeshes(const aiScene* scene)
{
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		std::vector<float> vertices;
		// TODO: Names are shit
		aiMesh* aiMesh = scene->mMeshes[i];
		aiColor4D* aiColor = aiMesh->mColors[0];
		glm::vec4 objColor(aiColor->r, aiColor->g, aiColor->b, aiColor->a);
		for (unsigned int j = 0; j < aiMesh->mNumVertices; j++)
		{
			// TODO: Copy the vertex data into the vector "vertices"
			for (int z = 0; z < 6; z++)
			{
				switch (z)
				{
				case 0: vertices.push_back(aiMesh->mVertices[j].x);
					break;
				case 1: vertices.push_back(aiMesh->mVertices[j].y);
					break;
				case 2: vertices.push_back(aiMesh->mVertices[j].z);
					break;
				case 3: vertices.push_back(aiMesh->mNormals[j].x);
					break;
				case 4: vertices.push_back(aiMesh->mNormals[j].y);
					break;
				case 5: vertices.push_back(aiMesh->mNormals[j].z);
					break;
				}
			}
		}

		std::vector<uint32_t> indices;
		for (unsigned int k = 0; k < aiMesh->mNumFaces; k++)
		{
			aiFace& face = aiMesh->mFaces[k];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		std::cout << "Num vertices (& normals): " << vertices.size() << std::endl;
		std::cout << "Num incides: " << indices.size() << std::endl;

		// create and save mash
		this->meshes.push_back(std::make_unique<Mesh>(vertices, indices, objColor));
	}
	std::cout << "Num meshes: " << this->meshes.size() << std::endl;
}

void Scene::processLights(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumLights; i++)
	{
		aiColor3D color = scene->mLights[i]->mColorDiffuse;
		aiVector3D point = scene->mLights[i]->mPosition;
		auto lightCol = glm::vec3(color.r, color.g, color.b);
		auto lightPos = glm::vec3(point.x, point.y, point.z);
		this->light = std::make_unique<PointLight>(lightPos, lightCol);
	}
}

const aiScene* Scene::loadScene(std::string fileName)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	std::string scene_file = std::string(std::filesystem::current_path().generic_string()).append("/../res/").
		append(fileName);
	const aiScene* scene = importer.ReadFile(scene_file,
	                                         aiProcess_CalcTangentSpace | aiProcess_Triangulate |
	                                         aiProcess_JoinIdenticalVertices |
	                                         aiProcess_SortByPType | aiProcess_PreTransformVertices);
	// If the import failed, report it
	if (!scene)
	{
		std::cerr << "Importing of 3D scene failed: " << importer.GetErrorString() << std::endl;
	}
	else
	{
		std::cout << "Import of '" << fileName << "' at: " << scene_file << " successfull" << std::endl;
	}
	return scene;
}
