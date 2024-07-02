#pragma once

// For use by IBX Engine client applications

#include "IBX/Application.h"
#include "IBX/Core.h"
#include "IBX/Layers/Layer.h"
#include "IBX/Log.h"

// Input
#include "IBX/Input.h"
#include "IBX/KeyCodes.h"
#include "IBX/MouseButtons.h"

#include "IBX/ImGui/ImGuiLayer.h"

// ---------------Core----------------------
#include "IBX/Core//Timestep.h"
#include "IBX/Core/Window.h"
// -----------------------------------------

// ---------------Renderer-------------------
#include "IBX/Renderer/Buffer.h"
#include "IBX/Renderer/OrthographicCamera.h"
#include "IBX/Renderer/Renderer.h"
#include "IBX/Renderer/RenderCommand.h"
#include "IBX/Renderer/RendererAPI.h"
#include "IBX/Renderer/Shader.h"
#include "IBX/Renderer/VertexArray.h"
// -----------------------------------------

// ---------------Entry Point---------------
#include "IBX/EntryPoint.h"
// -----------------------------------------