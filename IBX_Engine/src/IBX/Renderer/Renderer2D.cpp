#include "ibxpch.h"
#include "Renderer2D.h"

#include "IBX/Renderer/RenderCommand.h"
#include "IBX/Renderer/Shader.h"
#include "IBX/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace IBX_Engine
{
	struct Renderer2DStorage
	{
		IBXRef<VertexArray> QuadVertexArray;
		IBXRef<Shader> Shader;
		IBXRef<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		float squareVerts[5 * 4] = {
		   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom Left
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom Right
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // Top Right
		   -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // Top Left
		};

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		IBXRef<VertexBuffer> squareVB;
		squareVB = VertexBuffer::Create(squareVerts, sizeof(squareVerts));

		IBXRef<IndexBuffer> squareIB;
		squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		BufferLayout squareBufferLayout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareBufferLayout);
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		// Create a white texture for rendering colored quads 1x1 pixel
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->Shader = Shader::Create("assets/Shaders/Texture.glsl");

		s_Data->Shader->Bind();
		s_Data->Shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->Shader->Bind();
		s_Data->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Color& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, rotation, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Color& color)
	{
		s_Data->Shader->SetFloat4("u_Color", color);

		// Bind all-white texture (1x1 white texture)
		s_Data->WhiteTexture->Bind();

		float rotationRadians = glm::radians(rotation);

		glm::mat4 transform = 
			glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), rotationRadians, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->Shader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const IBXRef<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, rotation, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const IBXRef<Texture2D>& texture)
	{
		s_Data->Shader->SetFloat4("u_Color", Color::White);
		texture->Bind();
		
		float rotationRadians = glm::radians(rotation);

		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), rotationRadians, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->Shader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

		texture->Unbind();
	}
}