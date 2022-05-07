#include "Sandbox.h"

#include <Jungle/Core/EntryPoint.h>

#include "Layers/ExampleLayer.h"
#include "Layers/Sandbox2D.h"

Jungle::App* Jungle::CreateApp()
{
	return new Sandbox::SandboxApp();
}

namespace Sandbox
{
	SandboxApp::SandboxApp()
	{
		PushLayer(new ExampleLayer());
		//PushLayer(new Sandbox2D());
	}
}
