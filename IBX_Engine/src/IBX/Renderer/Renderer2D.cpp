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
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		float squareVerts[3 * 4] = {
		   -0.5f, -0.5f, 0.0f, // Bottom Left
			0.5f, -0.5f, 0.0f, // Bottom Right
			0.5f,  0.5f, 0.0f, // Top Right
		   -0.5f,  0.5f, 0.0f,  // Top Left
		};

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		Ref<VertexBuffer> squareVB;
		squareVB = VertexBuffer::Create(squareVerts, sizeof(squareVerts));

		Ref<IndexBuffer> squareIB;
		squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		BufferLayout squareBufferLayout = {
			{ ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(squareBufferLayout);
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->FlatColorShader = Shader::Create("assets/Shaders/Color.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
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
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);

		float rotationRadians = glm::radians(rotation);

		// TODO: ADD ROTATION
		glm::mat4 transform = 
			glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), rotationRadians, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->FlatColorShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}