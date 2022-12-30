#include <Core/Application.hpp>

namespace Clegine {
	Application::Application() { }

	Application::~Application() {
		if (mainWindow) {
			glfwDestroyWindow(mainWindow);
		}
		glfwTerminate();
		LOG_DEBUG("GLFW terminated for processId={0} threadId={1}",
			GetCurrentProcessId(), std::this_thread::get_id());
	}

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	void Application::Init(const WindowData& data) {
		mainData = data;
		LOG_DEBUG("Address of WindowData={0}, argument Data={1}", fmt::ptr(&mainData), fmt::ptr(&data));

		LOG_INFO("Initializing Main Window, title={0}, width={1}, height={2}, VSync={3}",
			data.title, data.width, data.height, data.VSync);

		glfwSetErrorCallback([](int errId, const char* reason) {
			LOG_ERROR("Application invoked a window error 0x{0:x} with reason: {1}", errId, reason);
		});

		int success = glfwInit();
		ASSERT(!success, "Fail when initializing GLFW!");
		LOG_INFO("Initializing GLFW, success!");

		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		mainWindow = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
		ASSERT(!mainWindow, "Fail creating main window!");
		LOG_INFO("Creating main window, success!");
		LOG_DEBUG("GLFW address of window={0}", fmt::ptr(mainWindow));

		glfwMakeContextCurrent(mainWindow);
		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ASSERT(!success, "Fail when initializing GLAD (OpenGL Function Loader)");

		ASSERT(!(GLVersion.major == 4 && GLVersion.minor >= 3),
			"Clegine Editor / Core requires atleast OpenGL version 4.3 or later");

		LOG_INFO("OpenGL Client Information:");
		LOG_INFO("GPU Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		LOG_INFO("GPU Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		LOG_INFO("OpenGL Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		SetVSync(data.VSync);

		glfwGetWindowSize(mainWindow, &mainData.width, &mainData.height);
		glfwSetWindowUserPointer(mainWindow, &mainData);

		Shader shader;
		shader.ReadFromRuntime(vertexShaderSource, fragmentShaderSource);
		GLuint firstShader = shader.Compile();

		float vertices[] = {
			0.5f,  0.5f, 0.0f,  
			0.5f, -0.5f, 0.0f, 
			-0.5f, -0.5f, 0.0f, 
			-0.5f,  0.5f, 0.0f
		};
		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3 
		};
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		LOG_DEBUG("VSync is={0}", IsVSync());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		Framebuffer FBO(512, 512, GL_RGBA, GL_RGBA);

		ImGuiIO& io = ImGUIContext::Get().Create(); IM_UNUSED(io);

		while (IsOpen()) {
			FBO.Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			glUseProgram(firstShader);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			ImGUIContext::Get().NewFrame();

			ImGui::ShowDemoWindow();

			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
			if (ImGui::Begin("Scene")) {
				ImVec2 pos = ImGui::GetCursorScreenPos();
				ImVec2 windowSize = ImGui::GetWindowSize();
				ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)FBO.GetImageID(),
					pos,
					ImVec2(pos.x + windowSize.x, pos.y + windowSize.y),
					ImVec2(0, 1),
					ImVec2(1, 0));
			}
			ImGui::End();

			FBO.UnBind();
			
			ImGUIContext::Get().EndFrame();
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
		/* Implement Application Main-Loop (a.k.a Run) */
	}

	bool Application::IsOpen() {
		return static_cast<bool>(glfwWindowShouldClose(mainWindow) != 1);
	}

	bool Application::IsVSync() {
		return mainData.VSync;
	}
	
	void Application::SetVSync(bool toggle) {
		if (toggle) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
		mainData.VSync = toggle;
	}
}