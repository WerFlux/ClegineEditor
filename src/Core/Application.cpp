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

		GLuint framebuffer;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		GLuint textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
		GLuint renderbufferId;
		glGenRenderbuffers(1, &renderbufferId);
		glBindRenderbuffer(GL_RENDERBUFFER, renderbufferId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 512, 512);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbufferId);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			LOG_ERROR("Framebuffer is not complete!");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		ImGuiIO& io = ImGUIContext::Get().Create();
		IM_UNUSED(io);

		while (IsOpen()) {
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			ImGUIContext::Get().NewFrame();

			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
			if (ImGui::Begin("Scene")) {
				ImVec2 pos = ImGui::GetCursorScreenPos();
				ImVec2 windowSize = ImGui::GetWindowSize();
				ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)textureId,
					pos,
					ImVec2(pos.x + windowSize.x, pos.y + windowSize.y),
					ImVec2(0, 1),
					ImVec2(1, 0));
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
			ImGui::End();

			ImGUIContext::Get().Update();

			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				LOG_ERROR("OpenGL error: {0}", error);
			}

			glfwSwapBuffers(mainWindow);
			glfwPollEvents();
		}
	}

	void Application::Run() {

	}
}