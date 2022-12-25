#include <Core/Application.hpp>
#include <Renderer/Shader.hpp>

namespace Clegine {
	Application::Application() { }

	Application::~Application() {
		if (mainWindow) {
			glfwDestroyWindow(mainWindow);
		}
		glfwTerminate();
		LOG_DEBUG("GLFW terminated for processId={0}, threadId={1}",
			GetCurrentProcessId(), std::this_thread::get_id());
	}

	void Application::Init(const WindowData& data) {
		wndData = data;
		LOG_DEBUG("Address of WindowData={0}", fmt::ptr(&wndData));

		LOG_INFO("Initializing Main Window, title={0}, width={1}, height={2}",
			data.title, data.width, data.height);

		glfwSetErrorCallback([](int errId, const char* reason) {
				LOG_ERROR("Application invoked a 0x{0:x} with reason: {1}", errId, reason);
			});

		int success = glfwInit();
		ASSERT(success != 0 && "Fail when initializing GLFW!");
		LOG_INFO("Initializing GLFW, success!");

		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		mainWindow = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
		ASSERT(mainWindow != nullptr && "Fail creating main window!");
		LOG_INFO("Creating main window, success!");
		LOG_DEBUG("GLFW address of window={0}", fmt::ptr(mainWindow));

		// Init OpenGL function (GLAD)
		glfwMakeContextCurrent(mainWindow);
		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ASSERT(success != 0 && "Fail when initializing GLAD (OpenGL Function Loader)");

		// Make sure it's 4.3 or later
		ASSERT((GLVersion.major == 4 && GLVersion.minor >= 3) &&
			"Clegine Editor / Core requires atleast OpenGL version 4.3 or later");

		// Send basic OpenGL information (Vendor, Renderer, and Version) to console
		LOG_INFO("OpenGL Client Information:");
		LOG_INFO("GPU Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		LOG_INFO("GPU Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		LOG_INFO("OpenGL Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		glfwGetWindowPos(mainWindow, &wndData.width, &wndData.height);
		glfwSetWindowUserPointer(mainWindow, &wndData);

		glfwSetFramebufferSizeCallback(mainWindow, [](GLFWwindow* wnd, int width, int height) {
				glViewport(0, 0, width, height);
			});

		ImGuiIO& io = ImGUIContext::Get().Create();

		while (IsOpen()) {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			ImGUIContext::Get().NewFrame();

			ImGui::Begin("Hierarchy");

			ImGui::End();

			ImGui::Begin("Properties");

			ImGui::End();

			ImGui::Begin("Content Browser");

			ImGui::End();

			ImGui::Begin("Scene");

			ImGui::End();

			ImGUIContext::Get().Update();

			glfwSwapBuffers(mainWindow);
			glfwPollEvents();
		}
	}

	void Application::Run() {

	}
}