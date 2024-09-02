#include "pch.h"
#include "Application.h"

namespace Physx2D {
	Application::Application() {
		m_window = new Window();
		m_window->OnInit();
		LOG_INFO("Application Successfully Created");
	}

	Application::~Application() {
		delete m_window;
		LOG_INFO("Application Successfully Destroyed");
	}

	void Application::Run() {
	}
}
