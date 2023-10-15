#include "Scene.h"
#include "Exception.h"

Scene::Scene()
{}

Scene::~Scene()
{
	UnloadScene();
}

void Scene::LoadScene(std::string file)
{
	scene_path = file;

	std::ifstream sfile(file);
	if (!sfile.is_open())
		throw Exception();

	std::string line;
	std::string section;
	std::vector<std::string> assets_path;
	int ShaderIndex = 0;
	mSceneCamera.RegenerateMatrices();
	glm::vec3 cameraPos = glm::vec3(0, 0, 0);
	std::vector<glm::vec3> geo_position;
	std::map<int, std::string> GeoTexutreBind;


	while (std::getline(sfile, line))
	{
		std::string geo_string[4]; //GEOMETRY STRINGS
		std::string cam_string[3]; //CAMERA STRINGS
		std::string shd_string[3]; //SHADER STRINGS
		std::string texture_path, model_id;
		int comaCounter = 0;
		int lastComaIndex = 0;

		if (section == "SHADER" && (line[0] != '!' && line[0] != '#'))
		{
			mShaders.push_back(Shader());
		}

		if (section == "GEOMETRY" && (line[0] != '!' && line[0] != '#'))
		{
			mAssets.push_back(Mesh());
			assets_path.push_back(std::string());
			geo_position.push_back(glm::vec3());
		}

		if (section == "TEX" && (line[0] != '!' && line[0] != '#'))
		{

		}

		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '#')
			{
				break;
			}

			if (line[i] == '!')
			{
				section.clear();
				//std::cout << "New section: ";
				for (int j = i + 1; j < line.length(); j++)
				{
					//std::cout << line[j];
					section += line[j];
				}
				//std::cout << std::endl;
				break;
			}
			if (section == "GEOMETRY")
			{
				if (line[i] == ',')
				{
					switch (comaCounter)
					{
					case 0:
						for (int j = lastComaIndex; j < i; j++)
						{
							geo_string[0] += line[j];
						}
						//std::cout << "Model: " << geo_string[0] << std::endl;
						assets_path[assets_path.size() - 1] = geo_string[0];
						break;

					case 1:
						for (int j = lastComaIndex + 1; j < i; j++)
						{
							geo_string[1] += line[j];
						}
						//std::cout << "Position x: " << geo_string[1] << std::endl;
						geo_position[geo_position.size() - 1].x = std::stof(geo_string[1]);
						break;

					case 2:
						for (int j = lastComaIndex + 1; j < i; j++)
						{
							geo_string[2] += line[j];
						}
						//std::cout << "Position y: " << geo_string[2] << std::endl;
						geo_position[geo_position.size() - 1].y = std::stof(geo_string[2]);
						break;

					case 3:
						for (int j = lastComaIndex + 1; j < i; j++)
						{
							geo_string[3] += line[j];
						}
						//std::cout << "Position z: " << geo_string[3] << std::endl;
						geo_position[geo_position.size() - 1].z = std::stof(geo_string[3]);
						break;
					}
					lastComaIndex = i;
					comaCounter++;
				}
			}
			else if (section == "CAMERA")
			{
				if (line[i] == ',')
				{
					switch (comaCounter)
					{
					case 0:
						for (int j = lastComaIndex; j < i; j++)
						{
							cam_string[0] += line[j];
						}
						//std::cout << "Position x: " << cam_string[0] << std::endl;
						cameraPos.x = std::stof(cam_string[0]);
						break;

					case 1:
						for (int j = lastComaIndex + 1; j < i; j++)
						{
							cam_string[1] += line[j];
						}
						//std::cout << "Position y: " << cam_string[1] << std::endl;
						cameraPos.y = std::stof(cam_string[1]);
						break;

					case 2:
						for (int j = lastComaIndex + 1; j < i; j++)
						{
							cam_string[2] += line[j];
						}
						//std::cout << "Position z: " << cam_string[2] << std::endl;
						cameraPos.z = std::stof(cam_string[2]);
						break;
					}
					lastComaIndex = i;
					comaCounter++;
				}
			}
			else if (section == "SHADER")
			{
				if (line[i] == ',')
				{
					switch (comaCounter)
					{
					case 0:
						for (int j = lastComaIndex; j < i; j++)
						{
							shd_string[0] += line[j];
						}
						//std::cout << "Vert file: " << shd_string[0] << std::endl;
						mShaders[mShaders.size() - 1].vpath = shd_string[0];
						break;

					case 1:
						for (int j = lastComaIndex + 1; j < i; j++)
						{
							shd_string[1] += line[j];
						}
						//std::cout << "Frag file: " << shd_string[1] << std::endl;
						mShaders[mShaders.size() - 1].fpath = shd_string[1];
						break;

					case 2:
						for (int j = lastComaIndex + 1; j < i; j++)
						{
							shd_string[2] += line[j];
						}
						//std::cout << "Associated model: " << shd_string[2] << std::endl;
						mShaderModelBind.emplace(ShaderIndex, std::stoi(shd_string[2]));
						ShaderIndex++;
						break;
					}
					lastComaIndex = i;
					comaCounter++;
				}
			}
			else if (section == "TEX")
			{
				if (line[i] == ',')
				{
					switch (comaCounter)
					{
					case 0:
						for (int j = lastComaIndex; j < i; j++)
						{
							texture_path += line[j];
						}
						//std::cout << "Texture: " << texture_path << std::endl;
						break;

					case 1:
						for (int j = lastComaIndex + 1; j < i; j++)
						{
							model_id += line[j];
						}
						//std::cout << "Position x: " << geo_string[1] << std::endl;
						GeoTexutreBind.emplace(std::stoi(model_id), texture_path);
						break;
					}
					lastComaIndex = i;
					comaCounter++;
				}
			}

		}
	}

	for (int i = 0; i < mShaders.size(); i++)
	{
		Graphics::OnShaderCompile(mShaders[i]);
	}

	for (int i = 0; i < mAssets.size(); i++)
	{
		Graphics::OnMeshLoad(assets_path[i], mAssets[i]);
		Graphics::OnMeshCreate(mAssets[i]);
		mAssets[i].SetPosition(geo_position[i].x, geo_position[i].y, geo_position[i].z);
		mAssets[i].name = assets_path[i];

		for (const auto bind : GeoTexutreBind)
		{
			if (bind.first == i)
			{
				mAssets[i].mMat.LoadColor(bind.second);
			}
		}
	}

	mSceneCamera.SetCameraLocation(cameraPos.x, cameraPos.y, cameraPos.z);
}

void Scene::UnloadScene()
{
	mShaderModelBind.clear();
	mShaders.clear();
	mAssets.clear();
}

void Scene::DrawScene(Graphics* pgfx)
{
	pgfx->OnSetCamera(mSceneCamera);
	pgfx->OnShaderSet(mShaders[0]);

	for (int i = 0; i < mAssets.size(); i++)
	{		
		pgfx->OnMeshDraw(mAssets[i]);
	}
}
