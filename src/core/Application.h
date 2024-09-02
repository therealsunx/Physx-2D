#pragma once
/*
	Application object handles the window for any application created using it.
	User have to create the application themselves by inheriting from this class.
	Finally return the application by defining the CreateApplication function.
	Entry point of the program gets the application and runs it.
*/
#include "pch.h"
#include "../window/window.h"

namespace Physx2D {
	class PHYSX2D_API Application {
	public:
		Application();

		virtual ~Application();

		virtual void Run();

	protected:
		Window* m_window;
	};
}
