#pragma once

#ifdef JNGL_PLATFORM_WINDOWS

extern Jungle::App* Jungle::CreateApp();

int main(int argc, char** argv)
{
	auto three = 3;
	Jungle::Log::Init();
	JNGL_CORE_WARN("Core Inited");
	JNGL_INFO("Client Inited {0}", three);

	auto app = Jungle::CreateApp();
	app->Run();
	delete app;
}

#endif
