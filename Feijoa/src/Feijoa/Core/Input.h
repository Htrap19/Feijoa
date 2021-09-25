#pragma once

#include "fjpch.h"
#include "Feijoa/Core/Base.h"
#include "Feijoa/Core/KeyCodes.h"
#include "Feijoa/Core/MouseCodes.h"

namespace Feijoa
{
	class Input
	{
	protected:
		Input() = default;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static inline bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static inline bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static inline std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static inline float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static inline float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		static Scope<Input> Create();

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Scope<Input> s_Instance;
	};
}