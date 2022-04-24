#pragma once

#include "Jungle/Core/Input.h"

namespace Jungle
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
	};
}

