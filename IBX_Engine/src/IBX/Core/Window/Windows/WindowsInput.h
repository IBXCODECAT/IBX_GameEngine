#pragma once

#include "IBX/Core/Input/Input.h"

namespace IBX_Engine
{
	class WindowsInput : public Input
	{
	protected:

		// Key Pressed Implementation
		virtual bool IsKeyPressedImpl(int keycode) override;

		// Mouse Buttons Implemntation
		virtual bool IsMouseButtonPressedImpl(int button) override;

		// Mouse Position Implementation
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
	};
}