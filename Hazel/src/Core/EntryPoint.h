#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	Hazel::Input::Init();
	HZ_CORE_WARN("Initialized Input!");
	int a = 5;
	HZ_INFO("Hello! Var={0}", a);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;

	// have to destroy in reverse order
	HZ_CORE_WARN("Destroying Input!");
	Hazel::Input::Destroy();
	HZ_CORE_WARN("Destroying Log!");
	Hazel::Log::Destroy();
}

#endif