#pragma once
#include "Drawable.hpp"
#include "Texture.hpp"
#include <vector>
#include <map>

class ShapeRenderer3D : public Drawable
{

    float *g_vertex_buffer_data;
    unsigned int *indices;
    int g_vertex_buffer_data_size;
    int indices_size;

    int what_Draw_use;
    void Draw_Elements();
    void Draw_Arrays();
    std::string textureDisplayed;
    std::map<std::string,Texture *> textures;

public:
    ShapeRenderer3D(float *g_vertex_buffer_data,
                    unsigned int *aindices,
                    int array_size,
                    int aindices_size,
                    Shader &ShaderProgram,
                    Texture *Texture,
                    std::string textureName);

    ShapeRenderer3D(float *g_vertex_buffer_date,
                    int indices_size,
                    Shader &shaderProgram,
                    Texture *texture,
                    std::string textureName);

    ShapeRenderer3D *GetCopy();

    void Draw(glm::mat4 &transform) override;
    void SwitchTexture(std::string aTextureName);
    void AsignTexture(Texture *aTexture,std::string aTextureName);

    ComponentSystem::ComponentType GetComponentType() override;
    std::string Serialize()
    {
        return Drawable::Serialize();
    }

    ~ShapeRenderer3D();
};
