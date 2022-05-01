#pragma once

#include "Jungle/Core/Layer.h"
#include "Jungle/Events/KeyEvent.h"
#include "Jungle/Events/MouseEvent.h"
#include "Jungle/Events/AppEvent.h"

namespace Jungle
{
	class JUNGLE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}

