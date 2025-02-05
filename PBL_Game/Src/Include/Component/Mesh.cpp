#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "Mesh.hpp"

namespace ModelMesh
{

Mesh::Mesh(vector<Vertex> aVertices,
           vector<unsigned int> aIndices,
           vector<Texture> aTextures,
           Shader &aShaderProgram) : ConeRenderable(aShaderProgram, reinterpret_cast<float *>(aVertices.data()), aVertices.size() * getVerticesPositionStride(), getVerticesPositionStride()),
                                     Vertices(aVertices),
                                     Indices(aIndices),
                                     Textures(aTextures)
{
    setupMesh();
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Bitangent));
    glBindVertexArray(0);
}

// render the mesh
void Mesh::Draw(Shader *shader, glm::mat4 &transform)
{

    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = Textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        if (shader == nullptr)
        {
            glUniform1i(glGetUniformLocation(defaultShader.shaderProgramID, (name + number).c_str()), i);
        }
        else
        {
            glUniform1i(glGetUniformLocation(shader->shaderProgramID, (name + number).c_str()), i);
        }
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, Textures[i].id);
    }

    // // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}
float *Mesh::getVertexData()
{
    return reinterpret_cast<float *>(Vertices.data());
}

int Mesh::getVertexDataSize()
{
    return Vertices.size() * getVerticesPositionStride();
}

int Mesh::getVerticesPositionStride()
{
    return 14;
}

unsigned int *Mesh::getIndices()
{
    return Indices.data();
}

int Mesh::getIndicesSize()
{
    return Indices.size();
}

ComponentSystem::ComponentType Mesh::GetComponentType()
{
    return ComponentSystem::ComponentType::ModelMesh;
}

} // namespace ModelMesh