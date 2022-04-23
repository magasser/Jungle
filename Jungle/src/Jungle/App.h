#pragma once
#pragma once

#include "Core.h"

namespace Jungle 
{
	class JUNGLE_API App
	{
	public:
		App();
		virtual ~App();

		void Run();
	};

	App* CreateApp();
}

