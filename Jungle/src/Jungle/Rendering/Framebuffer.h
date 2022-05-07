#pragma once

#include "Jungle/Core/Core.h"

namespace Jungle
{
	struct FramebufferSpecification
	{
		uint32_t Width;
		uint32_t Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class JUNGLE_API Framebuffer
	{
	public:
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& specification);
	};
}