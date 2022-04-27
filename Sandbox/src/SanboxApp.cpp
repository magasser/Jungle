#include <Jungle.h>

#include "imgui.h"

#include "ExampleLayer.h"

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
