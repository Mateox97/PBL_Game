#pragma once
#include "Window.hpp"
#include "Shader.hpp"
#include "SceneNode.hpp"
#include "Collider.hpp"
#include "Trigger.hpp"
#include "Triggers/Key.hpp"
#include "PostProcessing/PostProcessShader.hpp"
#include "Configuration/ConfigUtils.hpp"
#include "Component/ConeRenderer.hpp"
#include "PathFinding/MapTile.hpp"
#include "PathFinding/MapTileRenderUtils.cpp"
#include "Component/AnimatedModel.hpp"
#include "Player.hpp"
#include "AI/EnemyController.hpp"
#include "GuiElement.hpp"
#include "Triggers/EnemyTrigger.hpp"
#include "PostProcessing/FrameBuffer.hpp"
#include "PostProcessing/ScreenQuad.hpp"


const int TICKS_PER_SECOND = 64;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

using namespace PBLGame;



static bool mouseToUpdate = false;
static double posx;
static double posy;

static bool First_tab_push = false;
static bool Tab_Pressed = false;
static bool Enemy_Swtiched = false;


static bool renderPloot = true;


void mouse_callback(GLFWwindow *window, double xpos, double ypos);


class EnemyController;
class Game
{

  //DebugHelpers

  glm::vec2 vector2DHelper{0,0};
  glm::vec2 vector2DHelper2{0,0};
  bool debugMode = false;


 //PostProcess
 FrameBuffer* framebuffer;
 FrameBuffer* mirrorBuffer;
 ScreenQuad* screenQuad;


 glm::vec3 lastUpdatePosition;

  //
  Window &okienko;
  Shader *shaderProgram;
  Shader *shaderProgram_For_Model;
  Shader *shaderAnimatedModel;
  Shader *shaderViewCone;
  Shader * guiShader;
  Shader * skyboxShader;
  Shader * mirrorShader;

  PostProcessShader * postProcessShader;
  SceneNode wholeScene;

  SceneNode *leftScene;
  SceneNode *rightScene;
  
  std::vector<SceneNode *> sNodes;
  std::vector<SceneNode *> rightNodes;
  std::vector<Collider *> collidableObjects;
  std::vector<Trigger *> triggers;
  std::map<int,bool> KeyInEq;





Transform modelTransofrm;
   glm::mat4 model;
       unsigned int cubeVAO, cubeVBO,cubeEBO;


SceneNode * mirrorBoxNode = nullptr;

//Map Generation
MapGenerator * generator = nullptr;
std::vector<MapKey *> mapped;


  //PathFinding
  #pragma region PathFindingAndMapGenerationUtils
  std::vector<MapTile *> mapTiles;
  GridWithWeights grid;
  unsigned MapSize = 0;
  unsigned MapScale = 0;
  bool debugPathFinding = false;

  GridLocation start{0, 0};
  GridLocation goal{8, 5};
  std::unordered_map<GridLocation, GridLocation> came_from;
  std::unordered_map<GridLocation, double> cost_so_far;
  std::vector<glm::vec2> Corners;

  float floorTransform;
  float TileScale;
  #pragma endregion PathFindingAndMapGenerationUtils


  SceneNode leftPlayerNode;
  SceneNode leftPlayerNodeForModel;
  SceneNode rightPlayerNode;
  SceneNode rightPlayerNodeForModel;
  SceneNode Enemy_Node; //Rotation + scale
  SceneNode Enemy_Node_For_Model;

  EnemyController *enemyController;
  EnemyTrigger *killer;


  void InitializeConfig();
  //How to get value from config
  //ConfigUtils::GetValueFromMap<TYPE>(NAME,ConfigUtils::GlobalConfigMap) 
  

  float TileScaleTimes100;

  float movementSpeed; //Move to PlayerData
  float EnemyBaseSpeed;
  float EnemyXoffset;
  float EnemyYoffset;
  float EnemyZoffset;
  float PlayerXOffset;
  float PlayerYOffset ;
  float PlayerZOffset;
  float PlayerScale;
  float EnemyScale;
  float EnemyScaleInverse;
  float PlayerScaleInverse;

  float TrapScale;
  int trapPieces = 0;		// Ilosc posiadanych elementow pu�apki
  int requredPieces = 4;	// Ilosc wymaganych elementow pu�apki

  float movementSpeedTimesPlayerScale;

  float FogDensity = 0.35;
 

   bool mouseCallBack = true;
   bool firstMouse = true;
   double lastY;
   double lastX;

   //camera
   glm::mat4 view;
   glm::mat4 projection;

   Camera camera;
   Camera camera2;

  //Imgui
  bool show_demo_window = true;
  bool printf_path = false;
  GridLocation LastPathNode{0, 0};

  //
  int offset = 125; // Jak bardzo maja sie roznic rozmiary kamery, szerokosc aktywnej to pol okna + offset, szerokosc nieaktywnej to pol okna - offset

  //ModelPtrs
  AnimatedModel *enemyModel = nullptr;
  AnimatedModel *playerModel = nullptr;
  AnimatedModel *player2Model = nullptr;
	
  //Player handling
  Player* playerObj;

  public:

	  //Gui
	  SimpleGUI::GuiElement * LostText = nullptr;
	  SimpleGUI::GuiElement * LostBcg = nullptr;

	  SimpleGUI::GuiElement * WinText = nullptr;
	  SimpleGUI::GuiElement * WinBcg = nullptr;

    SimpleGUI::GuiElement * TrapCollector = nullptr;

	  SimpleGUI::GuiElement * TrapPartInfo = nullptr;

		
  bool EnemyOnLefSide = true;
  bool leftSideActive = true;
  Game(Window &okienko);

  unsigned WINDOW_WIDTH = 0;
  unsigned WINDOW_HEIGHT = 0;

  float cameraZOffset;
  float cameraYOffset;
  float cameraAngle;

  int imgMode = 1;		// 1 - Wyswietlaj grafiki fabularne | 2 - Wyswietlaj GUI | 0 - Nie wyswietlaj nic
  int plotNumber = 1;	// Zmienna wskazujaca na obecna wstawke fabularna
  bool inputBlockade = false;	// Zmienna  blokujaca mozliwosci gracza (domyslnie na czas wstawek fabularnych)

  void SetCamera(Camera camera, int camera_nr);
  void ProcessMouse();
  void ProcessInput(float interpolation, Camera &camera_update);
  void ResetGame();

  void Granko();
  void Update(float interpolation);
  void Render();
  void Serialize();
  void Deserialize(std::string path);
  void UpdatePlayer(SceneNode &player, Camera &camera,float interpolation, bool isLeft);
  void gatherCollidableObjects(std::vector<SceneNode *> &nodes);
  void gatherTriggers(std::vector<SceneNode*>& nodes);
  void RemoveNodesWithGameObjectTag(std::string tag,SceneNode * parentNode);
  std::vector<GameObject*> findByTag(const std::vector<SceneNode*>& data, std::string tag);
  GameObject * findByTagSingle(const std::vector<SceneNode*>& data, std::string tag);

  //Impgui
  void ImGuiFunctions();
  void ImguiStartEndDraw();
  void ImguiDrawData();
  void ImguiClear();

  //Player
  void SetupPlayersColiders();
  void SetPlayerRotation(SceneNode & sceneNode,glm::vec3 Direction_vec, AnimatedModel * playerModel);
  void FixAnimation();
private:
  void SerializeFaza1(std::map<SceneNode *,unsigned long long> &map);
  void SerializeFaza2(std::map<SceneNode *,unsigned long long> &map, std::vector<SceneNode> &temp);
  void SerializeFaza3(std::vector<SceneNode> &temp);
  void SerializeZapisz(std::string serialized);
  void DeserializeOrderPointers(std::map<unsigned long long, SceneNode *> &map);


 

  void SetViewAndPerspective(Camera &aCamera, SceneNode &player, Transform *enemy,bool clip = false);
  void Plot();
  void DisplayAnimationInfo(AnimatedModel * model);
};
