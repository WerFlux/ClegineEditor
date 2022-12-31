#ifndef CLEGINE_GUI_IMGUI_CONTEXT_HPP
#define CLEGINE_GUI_IMGUI_CONTEXT_HPP

#include <EntryPoint.hpp>
#include <Core/Logger.hpp>
#include <Core/Application.hpp>

namespace Clegine {
	class ImGUIContext : public Singleton<ImGUIContext> {
	public:
		ImGUIContext();
		~ImGUIContext();

		ImGuiIO& Create();

		void NewFrame();
		void EndFrame();

		void Update();
	};
}

#endif // CLEGINE_GUI_IMGUI_CONTEXT_HPP