#ifndef CLEGINE_CORE_APPLICATION_HPP
#define CLEGINE_CORE_APPLICATION_HPP

#include <EntryPoint.hpp>
#include <Core/Logger.hpp>

#include <ImGUI/ImGUIContext.hpp>
#include <Renderer/OrthoCamera.hpp>
#include <Renderer/Shader.hpp>
#include <Renderer/Framebuffer.hpp>

namespace Clegine {
	struct WindowData {
		std::string title;
		int width;
		int height;
		bool VSync;
	};

	class Application : public Singleton<Application> {
	public:
		Application();
		~Application();

		void Init(const WindowData& data);
		void Run();

		void SetVSync(bool toggle);

		bool IsVSync();
		bool IsOpen();

		inline bool IsVSync() const { return mainData.VSync; }
		inline GLFWwindow* GetWindow() { return mainWindow; }
	private:
		GLFWwindow* mainWindow = {};
		WindowData mainData = {};
	};
}

#endif // CLEGINE_CORE_APPLICATION_HPP