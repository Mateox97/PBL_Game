#pragma once

#include "Component.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

using glm::vec3;

class PointLight : public ComponentSystem::Component
{
    vec3 mAmbient;
    vec3 mDiffuse;
    vec3 mSpecular;
    
    float mConstant;
    float mLinear;
    float mQuadratic;
    Shader & mShaderProgram;
    
    unsigned mLightNumber;
    std::string mLightNumberAsString;

  public:
    PointLight(vec3 aAmbient, vec3 aDiffuse, vec3 aSpecular,
               float aConstant, float aLinear, float aQuadratic,Shader & aShaderProgram,unsigned aLightNumber);

    void SendValuesToShader();

    void SetLightNumber(unsigned aLightNumber);

    ComponentSystem::ComponentType GetComponentType();
};