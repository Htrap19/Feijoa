#pragma once

#include "fjpch.h"
#include "Feijoa/Core/KeyCodes.h"
#include "Feijoa/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Feijoa
{
	class Input
	{
	public:
		static bool IsKeyPressed(const KeyCode keycode);
		static bool IsMouseButtonPressed(const MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}