#ifndef CLEGINE_CORE_APPLICATION_HPP
#define CLEGINE_CORE_APPLICATION_HPP

#include <Core/Logger.hpp>

#include <ImGUI/ImGUIContext.hpp>

namespace Clegine {
	struct WindowData {
		std::string title;
		int width;
		int height;
	};

	class Application : public Singleton<Application> {
	public:
		Application();
		~Application();

		void Init(const WindowData& data);
		void Run();

		inline bool IsOpen() { return static_cast<bool>(glfwWindowShouldClose(mainWindow) != 1); }
		inline GLFWwindow* GetWindow() { return mainWindow; }
	private:
		GLFWwindow* mainWindow = {};
		WindowData wndData = {};
	};
}

#endif // CLEGINE_CORE_APPLICATION_HPP