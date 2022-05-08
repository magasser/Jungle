#include "EditorApp.h"

#include <Jungle/Core/EntryPoint.h>

#include "Layers/EditorLayer.h"

Jungle::App* Jungle::CreateApp()
{
	return new Jungle::JungleEditor();
}

namespace Jungle
{
	JungleEditor::JungleEditor()
		: App("Jungle Editor")
	{
		PushLayer(new EditorLayer());
	}
}
