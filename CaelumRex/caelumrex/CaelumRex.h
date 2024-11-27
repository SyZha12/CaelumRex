#ifndef CAELUMREX_H
#define CAELUMREX_H

// This header file is primarily used for the application (client)
// The client application will only be able to use functions from these header files

// ---Header(s) used for other applications using this engine
// ---Core--------------------------------------------------
#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/MouseButtonCodes.h"
#include "Core/Log.h"
#include "Core/Layer.h"
#include "Core/Timestep.h"
// ---Renderer----------------------------------------------
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

#include "Renderer/Camera.h"


// ---Entry point of the application
#include "Core/EntryApplication.h"
//----------------------------------

#endif //CAELUMREX_H
