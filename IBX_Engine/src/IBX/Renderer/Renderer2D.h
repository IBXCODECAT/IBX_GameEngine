#pragma once

#include "IBX/Renderer/Color.h"
#include "IBX/Renderer/OrthographicCamera.h"

#include "IBX/Renderer/Texture.h"

namespace IBX_Engine
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Color& color);
		static void DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Color& color);

		static void DrawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const IBXRef<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const IBXRef<Texture2D>& texture);

	};
}