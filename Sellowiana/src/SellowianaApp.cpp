#include <Feijoa.h>
#include <Feijoa/Core/EntryPoint.h>

#include "SellowianaLayer.h"

namespace Feijoa
{
	class Sellowiana : public Application
	{
	public:
		Sellowiana()
			: Application("Feijoa Sellowiana")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new SellowianaLayer);
		}

		~Sellowiana()
		{
		}
	};

	Application* CreateApplication()
	{
		return new Sellowiana();
	}
}