#include "ExampleLayer.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

namespace Sandbox
{
	ExampleLayer::ExampleLayer()
		: Layer("ExampleLayer"),
		m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray = Jungle::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,	0.5f, 0.5f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.5f, 0.5f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f
		};

		Jungle::Ref<Jungle::VertexBuffer> vertexBuffer;
		vertexBuffer = Jungle::VertexBuffer::Create(vertices, sizeof(vertices));
		Jungle::BufferLayout layout = {
			{ Jungle::ShaderDataType::Float3, "a_Position" },
			{ Jungle::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Jungle::Ref<Jungle::IndexBuffer> indexBuffer;
		indexBuffer = Jungle::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Jungle::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Jungle::Ref<Jungle::VertexBuffer> squareVB;
		squareVB = Jungle::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		Jungle::BufferLayout squareLayout = {
			{ Jungle::ShaderDataType::Float3, "a_Position" },
			{ Jungle::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Jungle::Ref<Jungle::IndexBuffer> squareIB;
		squareIB = Jungle::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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

		auto triangleShader = m_ShaderLibrary.Load("Triangle", vertexSrc, fragmentSrc);
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		auto squareShader = m_ShaderLibrary.Load("Square", squareVertexSrc, squareFragmentSrc);

		m_Texture = Jungle::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Jungle::Texture2D::Create("assets/textures/Logo.png");

		std::static_pointer_cast<Jungle::OpenGLShader>(textureShader)->Bind();
		std::static_pointer_cast<Jungle::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	ExampleLayer::~ExampleLayer()
	{

	}

	void ExampleLayer::OnUpdate(Jungle::Timestep timestep)
	{
		m_CameraController.OnUpdate(timestep);

		Jungle::RenderCommand::Clear({ 0.2f, 0.5f, 0.2f, 1 });

		Jungle::Renderer::BeginScene(m_CameraController.GetCamera());

		auto textureShader = m_ShaderLibrary.Get("Texture");
		auto squareShader = m_ShaderLibrary.Get("Square");

		squareShader->Bind();
		squareShader->SetFloat3("u_Color", m_SquareColor);

		m_Texture->Bind();
		Jungle::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_LogoTexture->Bind();
		Jungle::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//Jungle::Renderer::Submit(m_ShaderLibrary.Get("Triangle"), m_VertexArray);

		Jungle::Renderer::EndScene();
	}

	void ExampleLayer::OnEvent(Jungle::Event& e)
	{
		m_CameraController.OnEvent(e);

		if (e.GetEventType() == Jungle::EventType::WindowResize)
		{
			auto& re = (Jungle::WindowResizeEvent&)e;

			float zoom = (float)re.GetWidth() / 1280.0f;

			m_CameraController.SetZoomLevel(zoom);

		}
	}

	void ExampleLayer::OnImGuiRender()
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}
}
