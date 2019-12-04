#include "application.h"

namespace ot {

Application::Application(int& argc, char** argv)
	: QApplication(argc, argv)
{  }

Application::~Application() = default;

} // namespace ot

