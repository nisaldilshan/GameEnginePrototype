#pragma once

#include <Hazel.h>

#include "ParticleSystem.h"

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;
private:
	Hazel::OrthographicCameraController m_CameraController;

	// Temp
	std::shared_ptr<Hazel::VertexArray> m_SquareVA;
	std::shared_ptr<Hazel::Shader> m_FlatColorShader;
	std::shared_ptr<Hazel::Texture2D> m_CheckerboardTexture;
	std::shared_ptr<Hazel::Texture2D> m_logoTexture;
	std::shared_ptr<Hazel::Texture2D> m_SpriteSheet;


	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, std::shared_ptr<Hazel::SubTexture2D>> m_TextureMap;
}; 