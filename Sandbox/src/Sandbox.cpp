#include "Sandbox.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Jungle::App* Jungle::CreateApp()
{
	return new Sandbox::SandboxApp();
}

namespace Sandbox
{
	SandboxApp::SandboxApp()
	{
		PushLayer(new ExampleLayer());
	}
	
	ExampleLayer::ExampleLayer()
		: Layer("ExampleLayer"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray.reset(Jungle::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,	0.5f, 0.5f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.5f, 0.5f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f
		};

		Jungle::VertexBufferRef vertexBuffer;
		vertexBuffer.reset(Jungle::VertexBuffer::Create(vertices, sizeof(vertices)));
		Jungle::BufferLayout layout = {
			{ Jungle::ShaderDataType::Float3, "a_Position" },
			{ Jungle::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Jungle::IndexBufferRef indexBuffer;
		indexBuffer.reset(Jungle::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Jungle::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Jungle::VertexBufferRef squareVB;
		squareVB.reset(Jungle::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Jungle::BufferLayout squareLayout = {
			{ Jungle::ShaderDataType::Float3, "a_Position" },
			{ Jungle::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Jungle::IndexBufferRef squareIB;
		squareIB.reset(Jungle::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;
		out vec4 v_Color;

		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
		)";
		std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		in vec4 v_Color;

		void main()
		{
			color = vec4(v_Position * 0.5 + 0.5, 1.0);
			color = v_Color;
		}
		)";

		std::string squareVertexSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;

		void main()
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
		)";
		std::string squareFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec3 v_Position;

		uniform vec3 u_Color;

		void main()
		{
			color = vec4(u_Color, 1.0);
		}
		)";

		std::string texVertexSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
		)";
		std::string texFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		in vec2 v_TexCoord;

		uniform vec3 u_Color;

		void main()
		{
			color = vec4(v_TexCoord, 0.0, 1.0);
		}
		)";

		m_Shader.reset(Jungle::Shader::Create(vertexSrc, fragmentSrc));
		m_TexShader.reset(Jungle::Shader::Create(texVertexSrc, texFragmentSrc));
		m_SquareShader.reset(Jungle::Shader::Create(squareVertexSrc, squareFragmentSrc));
	}

	ExampleLayer::~ExampleLayer()
	{

	}

	void ExampleLayer::OnUpdate(Jungle::Timestep timestep)
	{
		glm::vec3 cameraPosition = m_Camera.GetPosition();
		float cameraRotation = m_Camera.GetRotation();

		if (Jungle::Input::IsKeyPressed(JNGL_KEY_A))
		{
			cameraPosition.x -= m_CameraSpeed * timestep;
		}
		else if (Jungle::Input::IsKeyPressed(JNGL_KEY_D))
		{
			cameraPosition.x += m_CameraSpeed * timestep;
		}
		if (Jungle::Input::IsKeyPressed(JNGL_KEY_W))
		{
			cameraPosition.y += m_CameraSpeed * timestep;
		}
		else if (Jungle::Input::IsKeyPressed(JNGL_KEY_S))
		{
			cameraPosition.y -= m_CameraSpeed * timestep;
		}
		if (Jungle::Input::IsKeyPressed(JNGL_KEY_Q))
		{
			cameraRotation += m_CameraSpeed * timestep;
		}
		else if (Jungle::Input::IsKeyPressed(JNGL_KEY_E))
		{
			cameraRotation -= m_CameraSpeed * timestep;
		}

		Jungle::RenderCommand::Clear({ 0.2f, 0.5f, 0.2f, 1 });

		m_Camera.SetPosition(cameraPosition);
		m_Camera.SetRotation(cameraRotation);

		Jungle::Renderer::BeginScene(m_Camera);

		std::static_pointer_cast<Jungle::OpenGLShader>(m_SquareShader)->Bind();
		std::static_pointer_cast<Jungle::OpenGLShader>(m_SquareShader)->UploadUniform("u_Color", m_SquareColor);

		Jungle::Renderer::Submit(m_TexShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//Jungle::Renderer::Submit(m_Shader, m_VertexArray);

		Jungle::Renderer::EndScene();
	}

	void ExampleLayer::OnImGuiRender()
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void ExampleLayer::OnEvent(Jungle::Event& e)
	{
		Jungle::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Jungle::KeyPressedEvent>(JNGL_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool ExampleLayer::OnKeyPressedEvent(Jungle::KeyPressedEvent& e)
	{

		return false;
	}
}
