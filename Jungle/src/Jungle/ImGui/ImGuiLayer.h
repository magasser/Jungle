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
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}

