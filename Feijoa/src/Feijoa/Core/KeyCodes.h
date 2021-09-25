#pragma once

namespace Feijoa
{
	typedef enum class KeyCode : uint16_t
	{
		// Form glfw3.h
		Space              = 32,
		Apostrophe         = 39,  /* ' */
		Comma              = 44,  /* , */
		Minus              = 45,  /* - */
		Period             = 46,  /* . */
		Slash              = 47,  /* / */
		D0                 = 48,
		D1                 = 49,
		D2                 = 50,
		D3                 = 51,
		D4                 = 52,
		D5                 = 53,
		D6                 = 54,
		D7                 = 55,
		D8                 = 56,
		D9                 = 57,
		Semicolon          = 59,  /* ; */
		Equal              = 61,  /* = */
		A                  = 65,
		B                  = 66,
		C                  = 67,
		D                  = 68,
		E                  = 69,
		F                  = 70,
		G                  = 71,
		H                  = 72,
		I                  = 73,
		J                  = 74,
		K                  = 75,
		L                  = 76,
		M                  = 77,
		N                  = 78,
		O                  = 79,
		P                  = 80,
		Q                  = 81,
		R                  = 82,
		S                  = 83,
		T                  = 84,
		U                  = 85,
		V                  = 86,
		W                  = 87,
		X                  = 88,
		Y                  = 89,
		Z                  = 90,
		Left_bracket       = 91,  /* [ */
		Backslash          = 92,  /* \ */
		Right_bracket      = 93,  /* ] */
		Grave_accent       = 96,  /* ` */
		World1             = 161, /* non-US #1 */
		World2             = 162, /* non-US #2 */

		Escape             = 256,
		Enter              = 257,
		Tab                = 258,
		Backspace          = 259,
		Insert             = 260,
		Delete             = 261,
		Right              = 262,
		Left               = 263,
		Down               = 264,
		Up                 = 265,
		Page_up            = 266,
		Page_down          = 267,
		Home               = 268,
		End                = 269,
		CapsLock           = 280,
		ScrollLock         = 281,
		NumLock            = 282,
		PrintScreen        = 283,
		Pause              = 284,
		F1                 = 290,
		F2                 = 291,
		F3                 = 292,
		F4                 = 293,
		F5                 = 294,
		F6                 = 295,
		F7                 = 296,
		F8                 = 297,
		F9                 = 298,
		F10                = 299,
		F11                = 300,
		F12                = 301,
		F13                = 302,
		F14                = 303,
		F15                = 304,
		F16                = 305,
		F17                = 306,
		F18                = 307,
		F19                = 308,
		F20                = 309,
		F21                = 310,
		F22                = 311,
		F23                = 312,
		F24                = 313,
		F25                = 314,
		/* Keypad */
		KP0                = 320,
		KP1                = 321,
		KP2                = 322,
		KP3                = 323,
		KP4                = 324,
		KP5                = 325,
		KP6                = 326,
		KP7                = 327,
		KP8                = 328,
		KP9                = 329,
		KPDecimal          = 330,
		KPDivide           = 331,
		KPMultiply         = 332,
		KPSubtract         = 333,
		KPAdd              = 334,
		KPEnter            = 335,
		KPEqual            = 336,

		LeftShift          = 340,
		LeftControl        = 341,
		LeftAlt            = 342,
		LeftSuper          = 343,
		RightShift         = 344,
		RightControl       = 345,
		RightAlt           = 346,
		RightSuper         = 347,
		Menu               = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

/* Printable keys */
#define FJ_KEY_SPACE              ::Feijoa::Key::Space              
#define FJ_KEY_APOSTROPHE         ::Feijoa::Key::Apostrophe          /* ' */
#define FJ_KEY_COMMA              ::Feijoa::Key::Comma               /* , */
#define FJ_KEY_MINUS              ::Feijoa::Key::Minus               /* - */
#define FJ_KEY_PERIOD             ::Feijoa::Key::Period              /* . */
#define FJ_KEY_SLASH              ::Feijoa::Key::Slash               /* / */
#define FJ_KEY_0                  ::Feijoa::Key::D0                 
#define FJ_KEY_1                  ::Feijoa::Key::D1                 
#define FJ_KEY_2                  ::Feijoa::Key::D2                 
#define FJ_KEY_3                  ::Feijoa::Key::D3                 
#define FJ_KEY_4                  ::Feijoa::Key::D4                 
#define FJ_KEY_5                  ::Feijoa::Key::D5                 
#define FJ_KEY_6                  ::Feijoa::Key::D6                 
#define FJ_KEY_7                  ::Feijoa::Key::D7                 
#define FJ_KEY_8                  ::Feijoa::Key::D8                 
#define FJ_KEY_9                  ::Feijoa::Key::D9                 
#define FJ_KEY_SEMICOLON          ::Feijoa::Key::Semicolon           /* ; */
#define FJ_KEY_EQUAL              ::Feijoa::Key::Equal               /* = */
#define FJ_KEY_A                  ::Feijoa::Key::A                  
#define FJ_KEY_B                  ::Feijoa::Key::B                  
#define FJ_KEY_C                  ::Feijoa::Key::C                  
#define FJ_KEY_D                  ::Feijoa::Key::D                  
#define FJ_KEY_E                  ::Feijoa::Key::E                  
#define FJ_KEY_F                  ::Feijoa::Key::F                  
#define FJ_KEY_G                  ::Feijoa::Key::G                  
#define FJ_KEY_H                  ::Feijoa::Key::H                  
#define FJ_KEY_I                  ::Feijoa::Key::I                  
#define FJ_KEY_J                  ::Feijoa::Key::J                  
#define FJ_KEY_K                  ::Feijoa::Key::K                  
#define FJ_KEY_L                  ::Feijoa::Key::L                  
#define FJ_KEY_M                  ::Feijoa::Key::M                  
#define FJ_KEY_N                  ::Feijoa::Key::N                  
#define FJ_KEY_O                  ::Feijoa::Key::O                  
#define FJ_KEY_P                  ::Feijoa::Key::P                  
#define FJ_KEY_Q                  ::Feijoa::Key::Q                  
#define FJ_KEY_R                  ::Feijoa::Key::R                  
#define FJ_KEY_S                  ::Feijoa::Key::S                  
#define FJ_KEY_T                  ::Feijoa::Key::T                  
#define FJ_KEY_U                  ::Feijoa::Key::U                  
#define FJ_KEY_V                  ::Feijoa::Key::V                  
#define FJ_KEY_W                  ::Feijoa::Key::W                  
#define FJ_KEY_X                  ::Feijoa::Key::X                  
#define FJ_KEY_Y                  ::Feijoa::Key::Y                  
#define FJ_KEY_Z                  ::Feijoa::Key::Z                  
#define FJ_KEY_LEFT_BRACKET       ::Feijoa::Key::Left_bracket        /* [ */
#define FJ_KEY_BACKSLASH          ::Feijoa::Key::Backslash           /* \ */
#define FJ_KEY_RIGHT_BRACKET      ::Feijoa::Key::Right_bracket       /* ] */
#define FJ_KEY_GRAVE_ACCENT       ::Feijoa::Key::Grave_accent        /* ` */
#define FJ_KEY_WORLD_1            ::Feijoa::Key::World1              /* non-US #1 */
#define FJ_KEY_WORLD_2            ::Feijoa::Key::World2              /* non-US #2 */

/* Function keys */				  
#define FJ_KEY_ESCAPE             ::Feijoa::Key::Escape             
#define FJ_KEY_ENTER              ::Feijoa::Key::Enter              
#define FJ_KEY_TAB                ::Feijoa::Key::Tab                
#define FJ_KEY_BACKSPACE          ::Feijoa::Key::Backspace          
#define FJ_KEY_INSERT             ::Feijoa::Key::Insert             
#define FJ_KEY_DELETE             ::Feijoa::Key::Delete             
#define FJ_KEY_RIGHT              ::Feijoa::Key::Right              
#define FJ_KEY_LEFT               ::Feijoa::Key::Left               
#define FJ_KEY_DOWN               ::Feijoa::Key::Down               
#define FJ_KEY_UP                 ::Feijoa::Key::Up                 
#define FJ_KEY_PAGE_UP            ::Feijoa::Key::Page_up            
#define FJ_KEY_PAGE_DOWN          ::Feijoa::Key::Page_down          
#define FJ_KEY_HOME               ::Feijoa::Key::Home               
#define FJ_KEY_END                ::Feijoa::Key::End                
#define FJ_KEY_CAPS_LOCK          ::Feijoa::Key::CapsLock           
#define FJ_KEY_SCROLL_LOCK        ::Feijoa::Key::ScrollLock         
#define FJ_KEY_NUM_LOCK           ::Feijoa::Key::NumLock            
#define FJ_KEY_PRINT_SCREEN       ::Feijoa::Key::PrintScreen        
#define FJ_KEY_PAUSE              ::Feijoa::Key::Pause              
#define FJ_KEY_F1                 ::Feijoa::Key::F1                 
#define FJ_KEY_F2                 ::Feijoa::Key::F2                 
#define FJ_KEY_F3                 ::Feijoa::Key::F3                 
#define FJ_KEY_F4                 ::Feijoa::Key::F4                 
#define FJ_KEY_F5                 ::Feijoa::Key::F5                 
#define FJ_KEY_F6                 ::Feijoa::Key::F6                 
#define FJ_KEY_F7                 ::Feijoa::Key::F7                 
#define FJ_KEY_F8                 ::Feijoa::Key::F8                 
#define FJ_KEY_F9                 ::Feijoa::Key::F9                 
#define FJ_KEY_F10                ::Feijoa::Key::F10                
#define FJ_KEY_F11                ::Feijoa::Key::F11                
#define FJ_KEY_F12                ::Feijoa::Key::F12                
#define FJ_KEY_F13                ::Feijoa::Key::F13                
#define FJ_KEY_F14                ::Feijoa::Key::F14                
#define FJ_KEY_F15                ::Feijoa::Key::F15                
#define FJ_KEY_F16                ::Feijoa::Key::F16                
#define FJ_KEY_F17                ::Feijoa::Key::F17                
#define FJ_KEY_F18                ::Feijoa::Key::F18                
#define FJ_KEY_F19                ::Feijoa::Key::F19                
#define FJ_KEY_F20                ::Feijoa::Key::F20                
#define FJ_KEY_F21                ::Feijoa::Key::F21                
#define FJ_KEY_F22                ::Feijoa::Key::F22                
#define FJ_KEY_F23                ::Feijoa::Key::F23                
#define FJ_KEY_F24                ::Feijoa::Key::F24                
#define FJ_KEY_F25                ::Feijoa::Key::F25                
#define FJ_KEY_KP_0               ::Feijoa::Key::KP0                
#define FJ_KEY_KP_1               ::Feijoa::Key::KP1                
#define FJ_KEY_KP_2               ::Feijoa::Key::KP2                
#define FJ_KEY_KP_3               ::Feijoa::Key::KP3                
#define FJ_KEY_KP_4               ::Feijoa::Key::KP4                
#define FJ_KEY_KP_5               ::Feijoa::Key::KP5                
#define FJ_KEY_KP_6               ::Feijoa::Key::KP6                
#define FJ_KEY_KP_7               ::Feijoa::Key::KP7                
#define FJ_KEY_KP_8               ::Feijoa::Key::KP8                
#define FJ_KEY_KP_9               ::Feijoa::Key::KP9                
#define FJ_KEY_KP_DECIMAL         ::Feijoa::Key::KPDecimal          
#define FJ_KEY_KP_DIVIDE          ::Feijoa::Key::KPDivide           
#define FJ_KEY_KP_MULTIPLY        ::Feijoa::Key::KPMultiply         
#define FJ_KEY_KP_SUBTRACT        ::Feijoa::Key::KPSubtract         
#define FJ_KEY_KP_ADD             ::Feijoa::Key::KPAdd              
#define FJ_KEY_KP_ENTER           ::Feijoa::Key::KPEnter            
#define FJ_KEY_KP_EQUAL           ::Feijoa::Key::KPEqual            
#define FJ_KEY_LEFT_SHIFT         ::Feijoa::Key::LeftShift          
#define FJ_KEY_LEFT_CONTROL       ::Feijoa::Key::LeftControl        
#define FJ_KEY_LEFT_ALT           ::Feijoa::Key::LeftAlt            
#define FJ_KEY_LEFT_SUPER         ::Feijoa::Key::LeftSuper          
#define FJ_KEY_RIGHT_SHIFT        ::Feijoa::Key::RightShift         
#define FJ_KEY_RIGHT_CONTROL      ::Feijoa::Key::RightControl       
#define FJ_KEY_RIGHT_ALT          ::Feijoa::Key::RightAlt           
#define FJ_KEY_RIGHT_SUPER        ::Feijoa::Key::RightSuper         
#define FJ_KEY_MENU               ::Feijoa::Key::Menu               