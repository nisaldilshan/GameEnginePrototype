#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	Hazel::Input::Init();
	HZ_CORE_WARN("Initialized Input!");

	HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Shutdown.json");
	delete app;
	HZ_PROFILE_END_SESSION();

	// have to destroy in reverse order
	HZ_CORE_WARN("Destroying Input!");
	Hazel::Input::Destroy();
	HZ_CORE_WARN("Destroying Log!");
	Hazel::Log::Destroy();
}

#endif