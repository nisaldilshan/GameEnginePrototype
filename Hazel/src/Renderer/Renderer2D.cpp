#include "pch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

#include "src/Platform/OpenGL/OpenGLShader.h"

namespace Hazel {

	struct Renderer2DStorage
	{
		// types of vertex array needed for various polygons
		std::shared_ptr<VertexArray> QuadVertexArray;

		// list of all shaders
		std::shared_ptr<Shader> CombinedTextureShader;
		
		// This white texture is necessary to use combined flat-color & texture shader
		// So we keeping it as a storage element of Renderer2D 
		std::shared_ptr<Texture2D> WhiteTexture; 
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		HZ_PROFILE_FUNCTION();
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->CombinedTextureShader = Shader::Create("C:/Users/Nisal Dilshan/Desktop/Cpp/GameEnginePrototype/Sandbox/assets/shaders/TexNColor.glsl");
		s_Data->CombinedTextureShader->Bind();
		s_Data->CombinedTextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		HZ_PROFILE_FUNCTION();
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		HZ_PROFILE_FUNCTION();
		s_Data->CombinedTextureShader->Bind();
		s_Data->CombinedTextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		HZ_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		HZ_PROFILE_FUNCTION();
		s_Data->CombinedTextureShader->SetFloat4("u_Color", color);
		s_Data->CombinedTextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->CombinedTextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		HZ_PROFILE_FUNCTION();
		s_Data->CombinedTextureShader->SetFloat4("u_Color", tintColor);
		s_Data->CombinedTextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->CombinedTextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		HZ_PROFILE_FUNCTION();

		s_Data->CombinedTextureShader->SetFloat4("u_Color", color);
		s_Data->CombinedTextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->CombinedTextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		HZ_PROFILE_FUNCTION();
		s_Data->CombinedTextureShader->SetFloat4("u_Color", tintColor);
		s_Data->CombinedTextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
			
		s_Data->CombinedTextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
} 