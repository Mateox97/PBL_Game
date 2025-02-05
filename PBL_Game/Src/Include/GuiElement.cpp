#include "GuiElement.hpp"
#include <stb_image.hpp>
#include <iostream>

namespace SimpleGUI
{

GuiElement::GuiElement(std::string texturePath, glm::mat4 atransform,Shader * aDefaultShader) : transform(atransform),shader(aDefaultShader)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Texture *texture = new Texture(texturePath.c_str(), GL_LINEAR);
    texture->Load();
    textures.insert(std::pair<std::string,Texture *>("default",std::move(texture)));
    currentTexture = textures["default"];
}

void GuiElement::setTransform(glm::mat4 aTransform)
{
    transform = aTransform;
}

void GuiElement::AddTexture(std::string aPath, std::string aName)
{
    Texture *texture = new Texture(aPath.c_str(), GL_LINEAR);
    texture->Load();
    textures[aName.c_str()] = texture;
}

void GuiElement::SwitchTexture(std::string aName)
{
    currentTexture = textures[aName];
}
void GuiElement::SwtichVisiblity()
{
    visible = !visible;
}
void GuiElement::FadeFromTransparent(float aFadeSpeed)
{
	fadeFromTransparent = true;
	fadeFromTransparentSpeed = aFadeSpeed;
	shader->use();
	shader->setBool("fadeFromTransparent", fadeFromTransparent);
}
void GuiElement::Reset()
{
	FadeFromTransparentValue = 0.0f;
	FadeToColorValue = 0.0f;
	fadeFromTransparent = false;

	fadeToColor = false;
	visible = false;

}

void GuiElement::FadeToColor(glm::vec3 aColor,float aFadeSpeed)
{
	ColorFade = aColor;
	fadeToColor = true;
	fadeToColorSpeed = aFadeSpeed;

	shader->use();
	shader->setVec3("ColorFade", ColorFade);
	shader->setBool("fadeToColor", fadeToColor);
}

void GuiElement::Draw()
{
    
    if(visible)
    {
    shader->use();
    currentTexture->Bind();

	shader->setMat4("transform", transform);
	shader->setBool("fadeToColor", fadeToColor);
	shader->setBool("fadeFromTransparent", fadeFromTransparent);

	if (fadeToColor && FadeToColorValue <1)
	{
		shader->setFloat("fadeToColorValue", FadeToColorValue);
		FadeToColorValue += 0.001 * fadeToColorSpeed;
	}
	if (fadeFromTransparent && FadeFromTransparentValue < 1)
	{
		shader->setFloat("fadeFromTransparentValue", FadeFromTransparentValue);
		FadeFromTransparentValue += 0.001 * fadeFromTransparentSpeed;
	}
	if (fadeFromTransparent && FadeFromTransparentValue >= 1)
	{
		shader->setFloat("fadeFromTransparentValue", 1);
	}

    // Render Block
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

} // namespace SimpleGUI