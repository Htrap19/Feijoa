#pragma once

#include "fjpch.h"
#include "Feijoa/Core/Base.h"
#include "Feijoa/Core/KeyCodes.h"
#include "Feijoa/Core/MouseCodes.h"

namespace Feijoa
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}