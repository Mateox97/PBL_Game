#include "SceneNode.hpp"
#include "ShapeRenderer3D.hpp"

SceneNode::SceneNode() : local(Transform::origin()), dirty_flag(true), gameObject(nullptr)
{
	parent = this;
}

SceneNode::SceneNode(GameObject *aGameobject) : local(Transform::origin()), dirty_flag(true), gameObject(aGameobject)
{
	parent = this;
}

void SceneNode::AddGameObject(GameObject *aGameObject)
{
	aGameObject->transform = world;
	gameObject = aGameObject;
}

void SceneNode::AddParent(SceneNode *parent)
{
	this->parent = parent;
}

void SceneNode::AddChild(SceneNode *aSceneNode)
{
  children.push_back(aSceneNode);
}

void SceneNode::Render(Transform &parentWorld, bool aDirty_Flag)
{

  aDirty_Flag |= dirty_flag;

  if (aDirty_Flag)
  {
    world = local.combine(parentWorld);
    dirty_flag = false;
  }
  if (gameObject != nullptr)
  {
    ShapeRenderer3D *shape = (ShapeRenderer3D *)gameObject->GetComponent(ComponentSystem::ShapeRenderer3D);
    if (shape != nullptr)
    {
      shape->Draw(world.GetTransform());
    }
  }
  for (SceneNode *sn : children)
  {
    sn->Render(world, aDirty_Flag);
  }
}

void SceneNode::Scale(float x, float y, float z)
{
  local.ScaleTransform(x, y, z);
  dirty_flag = true;
}

void SceneNode::Translate(float x, float y, float z)
{
  local.Translate(glm::vec3(x, y, z));
  dirty_flag = true;
}
void SceneNode::Rotate(float value, glm::vec3 axis)
{
  local.Rotate(value, axis);
  dirty_flag = true;
}

std::string SceneNode::Serialize()
{
	std::string str = "SN\n\t";
	str += "W;" + this->world.Serialize() + "\n\t";
	str += "L;" + this->local.Serialize() + "\n\t";
	if(this->parent)
	str += "P;" + std::to_string((unsigned)this->parent) + "\n\t";
	for(SceneNode* child : this->children)
		str += "CH;" + std::to_string((unsigned)child) + "\n\t";
	str += "O\n\t\t" + this->gameObject->Serialize() + "\n";
	return str;
}