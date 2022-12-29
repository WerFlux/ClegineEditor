#include <ImGUI/ImGUIContext.hpp>

namespace Clegine {
	ImGUIContext::ImGUIContext() {
		IMGUI_CHECKVERSION();
	}

	ImGUIContext::~ImGUIContext() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		LOG_DEBUG("ImGUIContext terminated for processId={0}, threadId={1}",
			GetCurrentProcessId(), std::this_thread::get_id());
	}

	ImGuiIO& ImGUIContext::Create() {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); IM_UNUSED(io);

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(Application::Get().GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		LOG_DEBUG("ImGUIContext created address of IO={0}", fmt::ptr(&io));
		return io;
	}

	void ImGUIContext::NewFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGUIContext::EndFrame() {
		ImGui::EndFrame();
	}

	void ImGUIContext::Update() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}