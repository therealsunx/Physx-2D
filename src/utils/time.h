#pragma once

/*
	Time/Clock related functions...
		> initTimer : resets/initializes the timer
		> get_time : returns the duration passed since timer has been initialized
		> get_fps : returns the fps when in loop
		> get_delta_time : returns the time elapsed between frames in loop
		> update : updates the values in loop
*/

#include "../core/core.h"
#include <GLFW/glfw3.h>

#define TIME glfwGetTime()

namespace Physx2D {
	class PHYSX2D_API Time {
		public:
			double current_time, last_time;

			Time();

			inline void initTimer(){
				current_time = last_time = 0;
				glfwSetTime(0.0);
			}

			inline double get_time(){
				return glfwGetTime();
			}

			inline int get_fps(){
				return current_time < last_time ? 0 : (1.f / (current_time - last_time));
			}

			inline double get_delta_time() {
				return current_time < last_time ? 0.0 :(current_time - last_time);
			}

			inline void update(){
				last_time = current_time, current_time = glfwGetTime();
			}
	};
}
