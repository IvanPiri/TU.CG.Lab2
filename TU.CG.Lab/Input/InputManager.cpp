#include "InputManager.hpp"

namespace Input
{
	void InputManager::PressKey(const Keys key)
	{
		keyMap[key] = true;
	}

	void InputManager::ReleaseKey(const Keys key)
	{
		keyMap[key] = false;
	}

	void InputManager::PressButton(const MouseButtons button)
	{
		buttonMap[button] = true;
	}

	void InputManager::ReleaseButton(const MouseButtons button)
	{
		buttonMap[button] = false;
	}

	void InputManager::Scroll(const float value)
	{
		scrollValue = value;
	}

	bool InputManager::IsKeyDown(const Keys key)
	{
		const auto umit = keyMap.find(key);

		if (umit != keyMap.end())
			return umit->second;

		return false;
	}

	bool InputManager::IsButtonDown(MouseButtons button)
	{
		const auto umit = buttonMap.find(button);

		if (umit != buttonMap.end())
			return umit->second;

		return false;
	}

	void InputManager::ResetState()
	{
		scrollValue = 0.0f;
	}
}
