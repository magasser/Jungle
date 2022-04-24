#include <Jungle.h>

class Sandbox : public Jungle::App
{
public:
	Sandbox()
	{
		PushOverlay(new Jungle::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Jungle::App* Jungle::CreateApp()
{
	return new Sandbox();
}
