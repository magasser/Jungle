#pragma once

#ifdef JNGL_PLATFORM_WINDOWS

extern Jungle::App* Jungle::CreateApp();

int main(int argc, char** argv)
{
	auto three = 3;
	Jungle::Log::Init();
	JNGL_CORE_LOG_INFO("Initialize Jungle Engine.");

	auto app = Jungle::CreateApp();
	JNGL_CORE_LOG_INFO("Run Jungle Engine.");
	app->Run();
	delete app;
}

#endif
