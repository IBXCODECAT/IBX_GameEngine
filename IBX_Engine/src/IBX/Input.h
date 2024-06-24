#pragma once

// Inut will be a static class that will handle all input from the user
// Input is static we can only have one instance of it

#include "IBX/Core.h"

namespace IBX_Engine
{
	/// <summary>
	/// Input Interface for the Engine
	/// This class will have no data and be used like an interface
	/// </summary>
	class IBX_API Input
	{
	public:
		// Key Pressed
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		// Mouse Buttons
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressed(button); }

		// Mouse Position
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		// Key Pressed Implementation
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		// Mouse Buttons Implementation
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		// Mouse Position Implementation
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* s_Instance;
	};
}