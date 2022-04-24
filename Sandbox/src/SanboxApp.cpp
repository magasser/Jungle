#include <Jungle.h>

#include "imgui.h"

class ExampleLayer : public Jungle::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer") { }

	void OnUpdate() override
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello Jungle Engine");
		ImGui::End();
	}
};

class Sandbox : public Jungle::App
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Jungle::App* Jungle::CreateApp()
{
	return new Sandbox();
}
