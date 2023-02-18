#include "Scene.hpp"

Scene::Scene(std::string file_name, const GLfloat rot_amount_per_second, const glm::vec3 rot_mat)
{
	this->rot_amount_per_second_ = rot_amount_per_second;
	this->rot_mat_ = rot_mat;
	this->old_time_ = glfwGetTime();

	// import scene
	Assimp::Importer importer;
	std::string scene_file = std::string(std::filesystem::current_path().generic_string()).append("/../res/").
		append(file_name);
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
		std::cout << "Import of '" << file_name << "' at: " << scene_file << " successful" << std::endl;
	}
	// init scene
	this->process_meshes(scene);
	this->process_lights(scene);
	this->process_camera(scene);
}

Scene::Scene(const Scene& scene)
{
	this->rot_amount_per_second_ = scene.rot_amount_per_second_;
	this->rot_mat_ = scene.rot_mat_;
	this->camera_ = std::make_unique<Camera>(*(scene.camera_));
	this->light_ = std::make_unique<PointLight>(*(scene.light_));
	this->old_time_ = scene.old_time_;
	for (auto& m : scene.meshes_)
	{
		this->meshes_.push_back(std::make_unique<Mesh>(*(m)));
	}
}

Scene::~Scene()
{
	this->meshes_.clear();
}

void Scene::render(Shader& shader)
{
	const double time = glfwGetTime();
	const double delta_time = (time - this->old_time_);
	this->old_time_ = time;

	const glm::mat4 tmp_mat_model = glm::rotate(this->mat_model_, this->rot_amount_, this->rot_mat_);
	this->rot_amount_ = glm::radians(static_cast<GLfloat>(this->rot_amount_per_second_ * delta_time) + glm::degrees(this->rot_amount_));
	this->light_->apply_mat(shader, tmp_mat_model);
	for (auto const& i : meshes_)
	{
		i->render(shader, tmp_mat_model);
	}
}

void Scene::set_uniforms(Shader& shader) const
{
	light_->set_uniforms(shader);
	camera_->set_uniforms(shader);
}

glm::mat4 Scene::get_view() const
{
	return this->camera_->get_view();
}

void Scene::set_view(const glm::mat4 view) const
{
	this->camera_->set_view(view);
}

GLfloat Scene::get_rot_amount_per_second() const
{
	return this->rot_amount_per_second_;
}

void Scene::set_rot_amount_per_second(GLfloat rot_amount_per_second)
{
	this->rot_amount_per_second_ = rot_amount_per_second;
}


void Scene::process_camera(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumCameras; i++)
	{
		const aiVector3D point = scene->mCameras[i]->mPosition;
		const aiVector3D look = scene->mCameras[i]->mLookAt;
		auto position = glm::vec3(point.x, point.y, point.z);
		auto look_at = glm::vec3(look.x, look.y, look.z);
		this->camera_ = std::make_unique<Camera>(position, look_at);
	}
}

void Scene::process_meshes(const aiScene* scene)
{
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		std::vector<float> vertices;
		const aiMesh* ai_mesh = scene->mMeshes[i];
		const aiColor4D* ai_color = ai_mesh->mColors[0];
		glm::vec4 obj_color(ai_color->r, ai_color->g, ai_color->b, ai_color->a);
		for (unsigned int j = 0; j < ai_mesh->mNumVertices; j++)
		{
			vertices.push_back(ai_mesh->mVertices[j].x);
			vertices.push_back(ai_mesh->mVertices[j].y);
			vertices.push_back(ai_mesh->mVertices[j].z);
			vertices.push_back(ai_mesh->mNormals[j].x);
			vertices.push_back(ai_mesh->mNormals[j].y);
			vertices.push_back(ai_mesh->mNormals[j].z);
		}

		std::vector<uint32_t> indices;
		for (unsigned int k = 0; k < ai_mesh->mNumFaces; k++)
		{
			const aiFace& face = ai_mesh->mFaces[k];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		std::cout << "Num vertices (& normals): " << vertices.size() << std::endl;
		std::cout << "Num indices: " << indices.size() << std::endl;

		// create and save mash
		this->meshes_.push_back(std::make_unique<Mesh>(vertices, indices, obj_color));
	}
	std::cout << "Num meshes: " << this->meshes_.size() << std::endl;
}

void Scene::process_lights(const aiScene* scene)
{
	for (int i = 0; i < scene->mNumLights; i++)
	{
		const aiColor3D color = scene->mLights[i]->mColorDiffuse;
		const aiVector3D point = scene->mLights[i]->mPosition;
		auto light_col = glm::vec3(color.r, color.g, color.b);
		auto light_pos = glm::vec3(point.x, point.y, point.z);
		this->light_ = std::make_unique<PointLight>(light_pos, light_col);
	}
}

const aiScene* Scene::load_scene(const std::string file_name) const
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	const std::string scene_file = std::string(std::filesystem::current_path().generic_string()).append("/../res/").
		append(file_name);
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
		std::cout << "Import of '" << file_name << "' at: " << scene_file << " successful" << std::endl;
	}
	return scene;
}
