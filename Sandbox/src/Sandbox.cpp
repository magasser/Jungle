#include "Sandbox.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

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
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(Jungle::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,	0.5f, 0.5f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.5f, 0.5f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f
		};

		std::shared_ptr<Jungle::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Jungle::VertexBuffer::Create(vertices, sizeof(vertices)));
		Jungle::BufferLayout layout = {
			{ Jungle::ShaderDataType::Float3, "a_Position" },
			{ Jungle::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Jungle::IndexBuffer> indexBuffer;
		indexBuffer.reset(Jungle::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Jungle::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
				0.75f, -0.75f, 0.0f,
				0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Jungle::VertexBuffer> squareVB;
		squareVB.reset(Jungle::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Jungle::BufferLayout squareLayout = {
			{ Jungle::ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Jungle::IndexBuffer> squareIB;
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

		void main()
		{
			color = vec4(0.2, 0.8, 0.3, 1.0);
		}
		)";

		m_Shader.reset(new Jungle::Shader(vertexSrc, fragmentSrc));
		m_SquareShader.reset(new Jungle::Shader(squareVertexSrc, squareFragmentSrc));
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

		if (Jungle::Input::IsKeyPressed(JNGL_KEY_J))
		{
			m_SquarePosition.x -= m_SquareSpeed * timestep;
		}
		else if (Jungle::Input::IsKeyPressed(JNGL_KEY_L))
		{
			m_SquarePosition.x += m_SquareSpeed * timestep;
		}
		if (Jungle::Input::IsKeyPressed(JNGL_KEY_I))
		{
			m_SquarePosition.y += m_SquareSpeed * timestep;
		}
		else if (Jungle::Input::IsKeyPressed(JNGL_KEY_K))
		{
			m_SquarePosition.y -= m_SquareSpeed * timestep;
		}

		glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), m_SquarePosition);

		Jungle::RenderCommand::Clear({ 0.2f, 0.5f, 0.2f, 1 });

		m_Camera.SetPosition(cameraPosition);
		m_Camera.SetRotation(cameraRotation);

		Jungle::Renderer::BeginScene(m_Camera);

		Jungle::Renderer::Submit(m_SquareShader, m_SquareVA, squareTransform);
		Jungle::Renderer::Submit(m_Shader, m_VertexArray);

		Jungle::Renderer::EndScene();
	}

	void ExampleLayer::OnImGuiRender()
	{

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
