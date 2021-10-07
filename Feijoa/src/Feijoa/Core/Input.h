#pragma once

#include "fjpch.h"
#include <glm/glm.hpp>
#include "Feijoa/Core/KeyCodes.h"
#include "Feijoa/Core/MouseCodes.h"

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