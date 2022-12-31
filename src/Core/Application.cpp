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

	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform vec3 size;\n"
		"uniform mat4 transform;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = transform * vec4(size.x * aPos.x, size.y * aPos.y, size.z * aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 color;\n"
		"void main()\n"
		"{\n"
		"   FragColor = color;\n"
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

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glm::vec3 Position(50.0f, 50.0f, 0.0f);
		glm::vec3 Scale(1.0f, 1.0f, 0.0f);

		float Color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };

		Framebuffer::Get().Create(1280, 720, GL_RGBA, GL_RGBA);

		ImGuiIO& io = ImGUIContext::Get().Create(); IM_UNUSED(io);

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 10.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;	

		OrthoCamera::Get().SetProjection(0.0f, 100.0f, 100.0f, 0.0f);

		while (IsOpen()) {
			Framebuffer::Get().Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			glUseProgram(firstShader);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			ImGUIContext::Get().NewFrame();
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

			ImGui::Begin("Properties");
			ImGui::Text("Position");
			ImGui::SameLine(0.0f, 25.f);

			ImGui::Text("X");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(50.f);
			ImGui::InputFloat("##POSX1", &Position.x, 0.0f, 0.0f, "%.2f");
			ImGui::SameLine(0.0f, 5.f);

			ImGui::Text("Y");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(50.f);
			ImGui::InputFloat("##POSY1", &Position.y, 0.0f, 0.0f, "%.2f");
			ImGui::Separator();

			ImGui::Text("Scale");
			ImGui::SameLine(0.0f, 46.f);

			ImGui::Text("X");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(50.f);
			ImGui::InputFloat("##SCALEX1", &Scale.x, 0.0f, 0.0f, "%.2f");
			ImGui::SameLine(0.0f, 5.f);

			ImGui::Text("Y");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(50.f);
			ImGui::InputFloat("##SCALEY1", &Scale.y, 0.0f, 0.0f, "%.2f");
			ImGui::Separator();

			ImGui::ColorEdit4("Color", Color);
			ImGui::End();

			glm::mat4 model = glm::translate(glm::mat4(1.0f), Position) * glm::scale(glm::mat4(1.0f), Scale);
			glm::mat4 MVP = OrthoCamera::Get().GetProjection() * model;
			
			glUseProgram(firstShader);
			UniformBuffer3D::Get().SetFloat(firstShader, "size", Scale.x, Scale.y, Scale.z);
			UniformBuffer4D::Get().SetFloat(firstShader, "color", Color[0], Color[1], Color[2], Color[3]);
			UniformBufferMatrix4x4::Get().Set(firstShader, "transform", MVP);
			glUseProgram(0);

			ImGui::Begin("Scene");
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImVec2 windowSize = ImGui::GetWindowSize();
			ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)Framebuffer::Get().GetImageID(),
				pos,
				ImVec2(pos.x + windowSize.x, pos.y + windowSize.y),
				ImVec2(0, 1),
				ImVec2(1, 0));
			ImGui::End();

			Framebuffer::Get().UnBind();
			
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