#include "jnglpch.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Jungle/Core/Verification.h"
#include "Renderer.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"



namespace Jungle
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(filepath);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	JNGL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		JNGL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		JNGL_CORE_ASSERT(!Exists(name), "Shader name already exists.");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		Add(shader->GetName(), shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}


	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		auto shader = Shader::Create(name, vertexSrc, fragmentSrc);
		Add(name, shader);
		return shader;
	}

	const Ref<Shader>& ShaderLibrary::Get(const std::string& name) const
	{
		JNGL_CORE_ASSERT(Exists(name), "Shader name not found.");
		return m_Shaders.at(name);
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}