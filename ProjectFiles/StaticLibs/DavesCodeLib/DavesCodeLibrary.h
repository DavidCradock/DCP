/// \file DavesCodeLibrary.h
/// \brief Master include header file for the entire DCL library meant to be included by any applications which wish to access all the code inside DCL.
///
/// If we wish to use the code inside DCL, then when creating an executable, include this header file which includes all code of DCL.
/// Then, link to the compiled DavesCodeLibrary.lib which can be found located at /x64/Release/DavesCodeLibrary.lib
///
/// \todo Go through ALL code and modify the comments so that duplicate "returns this or that" and mentioning of parameters in either \\brief or main stuff too.
/// \todo Add to and check FileManager from X code project
/// \todo Add Renderers from DCP_old
/// \todo Add SDL2 and SDL2_Mixer
/// \todo Check Doxygen build system is working WITHOUT having to have the thing installed.
#ifndef DAVESCODELIBRARY_H
#define DAVESCODELIBRARY_H

// Using Visual Studio library linking preprocessor to link some static libs...
//#pragma comment(lib, "OpenGL32.lib")
//#pragma comment(lib, "GLu32.lib")
//#pragma comment(lib, "dinput8.lib")
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "psapi.lib")

// SDL2 and SDL_Mixer
#pragma comment(lib, "../../../Output/DynamicLibs/SDL3/x64/SDL2-2.30.6/Debug/SDL3.lib")
#pragma comment(lib, "../../external_libs/SDL2-2.30.6/lib/x64/SDL2_mixer.lib")
#pragma comment(lib, "../../external_libs/SDL2-2.30.6/lib/x64/SDL2main.lib")


/// \namespace DCL
/// \brief The namespace in which everything within Dave's Code Library is stored inside.
/// 
/// To prevent name clashes between other libraries/code which any application using DCL may include.

#include "ArtificialIntelligence/FiniteStateMachine.h"
#include "ArtificialIntelligence/GeneticAlgorithm.h"
#include "ArtificialIntelligence/NeuralNetFeedForward.h"
#include "Audio/AudioManager.h"
#include "Audio/AudioSample.h"
#include "Core/Colourf.h"
#include "Core/Colouruc.h"
#include "Core/Exceptions.h"
#include "Core/Logging.h"
#include "Core/Multithreading.h"
#include "Core/Profiler.h"
#include "Core/Singleton.h"
#include "Core/StringUtils.h"
#include "Core/Timer.h"
#include "Core/TimerMinimal.h"
#include "Core/Utilities.h"
#include "Files/FileManager.h"
#include "Files/FileMemory.h"
#include "Image/Image.h"
#include "Image/ImageAtlas.h"
#include "Math/AABB.h"
#include "Math/Frustum.h"
#include "Math/Matrix.h"
#include "Math/Plane.h"
#include "Math/Quaternion.h"
#include "Math/Rect.h"
#include "Math/Vector2f.h"
#include "Math/Vector3f.h"
#include "Math/Vector4f.h"
#include "RayTracer/Ray.h"
//#include "Renderers/RendererBase.h"
//#include "Renderers/RendererManager.h"
//#include "Renderers/RendererOpenGL.h"
//#include "Renderers/RendererVulkan.h"
#include "SpatialPartitioning/octTree.h"
#include "SpatialPartitioning/octTreeEntity.h"
#include "SpatialPartitioning/octTreeNode.h"
#include "SpatialPartitioning/quadTree.h"
#include "SpatialPartitioning/quadTreeEntity.h"
#include "SpatialPartitioning/quadTreeNode.h"

#endif // #ifndef FILENAME_H
