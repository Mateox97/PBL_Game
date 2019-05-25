#pragma once
#include "Drawable.hpp"
#include "Texture.hpp"
#include <vector>
#include <array>

class ShapeRenderer3D :public Drawable 
{

    float* g_vertex_buffer_data;
    unsigned int * indices;
    int  g_vertex_buffer_data_size;
    int  indices_size;

    int what_Draw_use;
    void Draw_Elements();
    void Draw_Arrays();
    unsigned textureNumberDisplayed;
    std::vector<Texture *> textures;
	std::array<glm::vec4, 8> extrema;
    
	void calculateExtrema(float* vertexBufferData, int size);

    public:

    ShapeRenderer3D(float* g_vertex_buffer_data,
                    unsigned int * aindices,
                    int array_size,
                    int aindices_size,
                    Shader& ShaderProgram,
                    Texture* Texture);
                    
    ShapeRenderer3D(float * g_vertex_buffer_date,
                    int indices_size,
                    Shader & shaderProgram,
                    Texture * texture);

    ShapeRenderer3D * GetCopy();
                    
    void Draw(glm::mat4 &  transform) override;
    void SwitchTexture(int aTextureNumber);
    void AsignSecondTexture(Texture *aTexture);

    ComponentSystem::ComponentType GetComponentType() override;
	std::string Serialize() {
		return Drawable::Serialize();
	}

	std::array<glm::vec4, 8> getExtrema();
	float* getVertexData();
	int getVertexDataSize();
	int getVerticesPositionStride();
	unsigned int *getIndices();
	int getIndicesSize();
    ~ShapeRenderer3D();


};

