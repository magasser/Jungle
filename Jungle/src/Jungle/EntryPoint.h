#pragma once

#ifdef JNGL_PLATFORM_WINDOWS

extern Jungle::App* Jungle::CreateApp();

int main(int argc, char** argv)
{
	auto app = Jungle::CreateApp();
	app->Run();
	delete app;
}

#endif
