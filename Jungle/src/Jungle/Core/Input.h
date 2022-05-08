#pragma once

#include "Jungle/Core/Core.h"
#include "Jungle/Core/KeyCodes.h"
#include "Jungle/Core/MouseCodes.h"

namespace Jungle
{
	class JUNGLE_API Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode keyCode);

		inline static bool IsMouseButtonPressed(MouseCode button);
		inline static float GetMouseX();
		inline static float GetMouseY();
		inline static std::pair<float, float> GetMousePosition();
	};
}
