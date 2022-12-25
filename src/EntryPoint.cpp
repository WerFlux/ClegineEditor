#include <Core/Application.hpp>
using namespace Clegine;

int main() {
    Logger::Init();

    LOG_DEBUG("Compiled: {0} {1}", __DATE__, __TIME__);

    const WindowData data = {
        "Clegine Editor",
        800,
        600
    };

    Application::Get().Init(data);
	return 0;
}