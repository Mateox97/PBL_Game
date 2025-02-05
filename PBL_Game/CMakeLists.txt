# CMake entry point
cmake_minimum_required (VERSION 3.9.3)
project (PBL_Game)

find_package(OpenGL REQUIRED)
 
if(UNIX)
  set(CMAKE_C_COMPILER /usr/bin/gcc-8 CACHE PATH "" FORCE)
  set(CMAKE_CXX_COMPILER /usr/bin/g++-8 CACHE PATH "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)

# Compile external dependencies 
add_subdirectory (external)

include_directories(
	Src/Include/
	external/Imgui/Include/
	external/Imgui/examples/libs/gl3w/
	external/glfw-3.2.1/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-4.1.0/include/
	external/tinyxml2/
	Build/external/assimp-4.1.0/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
	assimp
	tinyxml2
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(PBL_Game 
    PBL_Game.cpp
    Src/Include/Transform.cpp
    Src/Include/Game.cpp
    Src/Include/GameObject.cpp 
	  Src/Include/Transform.cpp
	  Src/Include/Window.cpp
	  Src/Include/Camera.cpp
	  Src/Include/Shader.cpp
	  Src/Include/Texture.cpp
	  Src/Include/SceneNode.cpp
		Src/Include/Collider.cpp
		Src/Include/ColliderStatic.cpp
		Src/Include/PlayerCollider.cpp
		Src/Include/Trigger.cpp
		Src/Include/Triggers/Key.cpp
		Src/Include/Triggers/TrapTrigger.cpp
		Src/Include/Triggers/EnemyTrigger.cpp
		Src/Include/Triggers/ChestTrigger.cpp
		#PostProcessing
		Src/Include/PostProcessing/FrameBuffer.cpp
		Src/Include/PostProcessing/ScreenQuad.cpp
		Src/Include/PostProcessing/PostProcessShader.cpp
		#ConfigUtils
		Src/Include/Configuration/ConfigUtils.cpp
		#PathFinding
		Src/Include/PathFinding/PathFindingUtils.cpp
		Src/Include/PathFinding/MapTile.cpp
		Src/Include/PathFinding/MapTileRenderUtils.cpp
		#MapGenerator
		Src/Include/MapGenerator/MapGenerator.cpp
		Src/Include/MapGenerator/MapElement.cpp
		Src/Include/MapGenerator/MapConverter.cpp
		Src/Include/MapGenerator/MapKey.cpp
	  #Component
	  Src/Include/Component/ShapeRenderer3D.cpp
	  Src/Include/Component/ConeRenderer.cpp
	  Src/Include/Component/ConeRenderable.cpp
	  Src/Include/Component/Mesh.cpp
	  Src/Include/Component/Model.cpp
	  Src/Include/Component/AnimatedModel.cpp
		Src/Include/Component/BoneUtils.cpp
		#Player
		Src/Include/Player.cpp
		#Enemy/AI
		Src/Include/AI/EnemyController.cpp
		#Factorys
		Src/Include/NodeWithModelFactory.cpp
	  #Stb_image
		Src/Include/stb_image.cpp
		#Gui
		Src/Include/GuiElement.cpp
	  #ImGui
	  external/Imgui/examples/libs/gl3w/GL/gl3w.c
	  external/Imgui/Include/imgui.cpp
	  external/Imgui/Include/imgui_impl_glfw.cpp
	  external/Imgui/Include/imgui_impl_opengl3.cpp
	  external/Imgui/Include/imgui_draw.cpp
	  external/Imgui/Include/imgui_widgets.cpp
	
)

target_link_libraries(PBL_Game
	${ALL_LIBS}
)
