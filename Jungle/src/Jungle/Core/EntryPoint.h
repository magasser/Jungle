#pragma once

#ifdef JNGL_PLATFORM_WINDOWS

extern Jungle::App* Jungle::CreateApp();

int main(int argc, char** argv)
{
	auto three = 3;
	Jungle::Log::Init();
	JNGL_CORE_LOG_INFO("Initialize Jungle Engine.");

	JNGL_PROFILE_BEGIN_SESSION("Startup", "JungleProfile-Startup.json");
	auto app = Jungle::CreateApp();
	JNGL_PROFILE_END_SESSION();

	JNGL_PROFILE_BEGIN_SESSION("Runtime", "JungleProfile-Runtime.json");
	JNGL_CORE_LOG_INFO("Run Jungle Engine.");
	app->Run();
	JNGL_PROFILE_END_SESSION();

	JNGL_PROFILE_BEGIN_SESSION("Shutdown", "JungleProfile-Shutdown.json");
	delete app;
	JNGL_PROFILE_END_SESSION();
}

#endif
