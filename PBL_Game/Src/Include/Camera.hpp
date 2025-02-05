#pragma once

#include <glm/glm.hpp>

 enum Camera_Movement 
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const glm::vec3 CAMERA_DEFAULT_POSTITION(0.0f, 3.5f, 7.0f);
const glm::vec3 CAMERA_DEFAULT_WORLD_UP(0.0f, 1.0f, 0.0f);
const glm::vec3 CAMERA_DAFAULT_FRONT(0.0f, 0.0f, -1.0f);
const float CAMERA_DEFAULT_YAW(-90.0f);
const float CAMERA_DEFAULT_PITCH(-60.0f);
const float CAMERA_DEFAULT_SPEED(0.20f);
const float CAMERA_DEFAULT_MOUSE_SENSIVITY(0.1f);
const float CAMERA_DEFAULT_ZOOM(45.0f);

static bool Cursor_Enabled = false;

class Camera
{

  public: 
  
  //Camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;
  
  //Eular Angles
  float Yaw;
  float Pitch;
  
  //Camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  glm::mat4 GetViewMatrix();  
    
  
  Camera();
  Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch); 
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);



  void ProcessKeyboard(Camera_Movement direction,float interpolation);
  void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
  void ProcessMouseScroll(float yoffset);

  void updateCameraVectors();

  private:
  //Calculates the front vector from the Camera's (updated) Eular Angles
  


};