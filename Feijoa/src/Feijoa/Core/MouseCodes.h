#pragma once

namespace Feijoa
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0         = 0,
		Button1         = 1,
		Button2         = 2,
		Button3         = 3,
		Button4         = 4,
		Button5         = 5,
		Button6         = 6,
		Button7         = 7,
		ButtonLast      = Button7,
		ButtonLeft      = Button0,
		ButtonRight     = Button1,
		ButtonMiddle    = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define FJ_MOUSE_BUTTON_0         ::Feijoa::Mouse::Button0     
#define FJ_MOUSE_BUTTON_1         ::Feijoa::Mouse::Button1     
#define FJ_MOUSE_BUTTON_2         ::Feijoa::Mouse::Button2     
#define FJ_MOUSE_BUTTON_3         ::Feijoa::Mouse::Button3     
#define FJ_MOUSE_BUTTON_4         ::Feijoa::Mouse::Button4     
#define FJ_MOUSE_BUTTON_5         ::Feijoa::Mouse::Button5     
#define FJ_MOUSE_BUTTON_6         ::Feijoa::Mouse::Button6     
#define FJ_MOUSE_BUTTON_7         ::Feijoa::Mouse::Button7     
#define FJ_MOUSE_BUTTON_LAST      ::Feijoa::Mouse::ButtonLast  
#define FJ_MOUSE_BUTTON_LEFT      ::Feijoa::Mouse::ButtonLeft  
#define FJ_MOUSE_BUTTON_RIGHT     ::Feijoa::Mouse::ButtonRight 
#define FJ_MOUSE_BUTTON_MIDDLE    ::Feijoa::Mouse::ButtonMiddle