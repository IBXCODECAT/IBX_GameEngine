#pragma once

// For use by IBX Engine client applications

#include "IBX/Core/Application.h"
#include "IBX/Core/Core.h"
#include "IBX/Core/Layers/Layer.h"
#include "IBX/Core/Log.h"


// ---------------Inputs---------------------
#include "IBX/Core/Input/Input.h"
#include "IBX/Core/Input/KeyCodes.h"
#include "IBX/Core/Input/MouseButtons.h"
// -----------------------------------------

// ---------------ImGui---------------------
#include "IBX/ImGui/ImGuiLayer.h"
// -----------------------------------------

// ---------------Core----------------------
#include "IBX/Renderer/Color.h"
#include "IBX/Core//Timestep.h"
#include "IBX/Core/Window/Window.h"
// -----------------------------------------

// ---------------Renderer-------------------
#include "IBX/Renderer/Buffer.h"
#include "IBX/Renderer/OrthographicCamera.h"
#include "IBX/OrthographicCameraController.h"
#include "IBX/Renderer/Renderer.h"
#include "IBX/Renderer/RenderCommand.h"
#include "IBX/Renderer/RendererAPI.h"
#include "IBX/Renderer/Shader.h"
#include "IBX/Renderer/Texture.h"
#include "IBX/Renderer/VertexArray.h"
// -----------------------------------------

// ---------------Entry Point---------------
#include "IBX/EntryPoint.h"
// -----------------------------------------