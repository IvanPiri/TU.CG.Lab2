#pragma once

#include "Input/InputManager.hpp"

namespace Applications
{
	class IApplication
	{
		protected:
			IApplication() = default;
		public:
			virtual ~IApplication() = default;
			IApplication(const IApplication& other) = delete;
			IApplication& operator=(const IApplication& other) = delete;
			IApplication(IApplication&& other) = delete;
			IApplication& operator=(IApplication&& other) = delete;

			virtual Input::InputManager& GetInputManager() = 0;
	};
}
