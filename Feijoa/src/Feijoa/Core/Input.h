#pragma once

#include "fjpch.h"
#include "Feijoa/Core/Base.h"

namespace Feijoa
{
	class Input
	{
	public:
		static inline bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static inline bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static inline std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static inline float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static inline float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}