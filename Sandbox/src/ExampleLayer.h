#pragma once

#include "Jungle.h"

class ExampleLayer : public Jungle::Layer
{
public:
	ExampleLayer();

	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;

private:
	std::shared_ptr<Jungle::Shader> m_Shader;
	std::shared_ptr<Jungle::VertexArray> m_VertexArray;

	std::shared_ptr<Jungle::Shader> m_SquareShader;
	std::shared_ptr<Jungle::VertexArray> m_SquareVA;

	Jungle::OrthographicCamera m_Camera;
};