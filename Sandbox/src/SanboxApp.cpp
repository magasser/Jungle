#include <Jungle.h>

class Sandbox : public Jungle::App
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Jungle::App* Jungle::CreateApp()
{
	return new Sandbox();
}
