#include <CaelumRex.h>

#include <glm/gtc/matrix_transform.hpp>

#include "OpenGLShader.h"

#include "glm/gtc/type_ptr.inl"
#include "imgui-docking/imgui.h"

class ExampleLayer : public CaelumRex::Layer
{
public:
    ExampleLayer()
		: Layer("Example"), m_CameraController(1920 / 1080, true)
	{
		m_VertexArray.reset(CaelumRex::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		CaelumRex::Ref<CaelumRex::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(CaelumRex::VertexBuffer::Create(vertices, sizeof(vertices)));
		CaelumRex::BufferLayout layout = {
			{ CaelumRex::ShaderDataType::Float3, "a_Position" },
			{ CaelumRex::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		CaelumRex::Ref<CaelumRex::IndexBuffer> indexBuffer;
		indexBuffer.reset(CaelumRex::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(CaelumRex::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		CaelumRex::Ref<CaelumRex::VertexBuffer> squareVB;
		squareVB.reset(CaelumRex::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ CaelumRex::ShaderDataType::Float3, "a_Position" },
			{ CaelumRex::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		CaelumRex::Ref<CaelumRex::IndexBuffer> squareIB;
		squareIB.reset(CaelumRex::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 460 core
			
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
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = (CaelumRex::Shader::Create("", vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 460 core
			
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

		std::string flatColorShaderFragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_ColorShader = (CaelumRex::Shader::Create("ColorShader", flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 460 core
			
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

		std::string textureShaderFragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = CaelumRex::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = CaelumRex::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<CaelumRex::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<CaelumRex::OpenGLShader>(textureShader)->SetUniformInt("u_Texture", 0);
	}

    void OnUpdate(CaelumRex::Timestep ts) override
    {
    	// Update
		m_CameraController.OnUpdate(ts);

    	// Render
        CaelumRex::RenderCommand::SetClearColor( {0.1f, 0.1f, 0.1f, 1.0f} );
        CaelumRex::RenderCommand::Clear();

        CaelumRex::Renderer::Begin(m_CameraController.GetCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1));

        std::dynamic_pointer_cast<CaelumRex::OpenGLShader>(m_ColorShader)->Bind();
        std::dynamic_pointer_cast<CaelumRex::OpenGLShader>(m_ColorShader)->SetUniformFloat3("u_Color", m_SquareColor);

        for(int y = 0; y < 10; y++)
        {
            for(int x = 0; x  < 10; x++)
            {
                glm::vec3 pos(x * 0.20f, y * 0.20f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                CaelumRex::Renderer::Dispatch(m_ColorShader, m_SquareVertexArray, transform);
            }
        }

    	auto textureShader = m_ShaderLibrary.Get("Texture");

        m_Texture->Bind();
        CaelumRex::Renderer::Dispatch(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
        m_ChernoLogoTexture->Bind();
        CaelumRex::Renderer::Dispatch(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

        // CaelumRex::Renderer::Dispatch(m_Shader, m_VertexArray);

        CaelumRex::Renderer::End();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Setting");
            ImGui::ColorEdit3("Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(CaelumRex::Event& event) override
    {
		m_CameraController.OnEvent(event);

    	if(event.GetEventType() == CaelumRex::EventType::WindowResize)
    	{
    		auto& re = static_cast<CaelumRex::WindowResizeEvent&>(event);
    	}
    }

private:
	CaelumRex::ShaderLibrary m_ShaderLibrary;

    CaelumRex::Ref<CaelumRex::Shader> m_Shader;
    CaelumRex::Ref<CaelumRex::VertexArray> m_VertexArray;

    CaelumRex::Ref<CaelumRex::Shader> m_ColorShader;
    CaelumRex::Ref<CaelumRex::VertexArray> m_SquareVertexArray;

    CaelumRex::Ref<CaelumRex::Texture2D> m_Texture, m_ChernoLogoTexture;

    CaelumRex::OrthographicCameraController m_CameraController;

    // glm::vec3 m_SquarePosition;
    // float m_SquareSpeed = 1.0f;
    glm::vec3 m_SquareColor = { 0.4f, 0.2f, 0.6f };
};

class Sandbox : public CaelumRex::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

CaelumRex::Application* CaelumRex::CreateApplication()
{
    CR_INFO("Creating Application...");
    return new Sandbox();
}
