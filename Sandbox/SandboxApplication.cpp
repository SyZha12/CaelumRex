#include <CaelumRex.h>
#include "Core/Entry.h"

#include <glm/gtc/matrix_transform.hpp>

#include "OpenGLShader.h"

#include "glm/gtc/type_ptr.inl"
#include "imgui-docking/imgui.h"

#include "Sandbox2D.h"

class ExampleLayer : public CaelumRex::Layer
{
public:
    ExampleLayer()
		: Layer("Example"), m_CameraController(1920 / 1080, true)
	{
    	// STEP 1: Create Vertex Array
		m_VertexArray = CaelumRex::VertexArray::Create();

    	// STEP 2: Create Vertex Buffer
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
    		// STEP 2.1: Create
		CaelumRex::Ref<CaelumRex::VertexBuffer> vertexBuffer = CaelumRex::VertexBuffer::Create(vertices, sizeof(vertices));
    		// STEP 2.2: Set BufferLayout
		CaelumRex::BufferLayout layout = {
			{ CaelumRex::ShaderDataType::Float3, "a_Position" },
			{ CaelumRex::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
    		// STEP 2.3: Add to Vertex Array
		m_VertexArray->AddVertexBuffer(vertexBuffer);

    	// STEP 3: Create Index Buffer;
		uint32_t indices[3] = { 0, 1, 2 };
    		// STEP 3.1: Create
		CaelumRex::Ref<CaelumRex::IndexBuffer> indexBuffer = CaelumRex::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    		// STEP 3.2: Add to Vertex Array
		m_VertexArray->SetIndexBuffer(indexBuffer);

    	//======================================================================
		m_SquareVertexArray = CaelumRex::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		CaelumRex::Ref<CaelumRex::VertexBuffer> squareVB = CaelumRex::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ CaelumRex::ShaderDataType::Float3, "a_Position" },
			{ CaelumRex::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		CaelumRex::Ref<CaelumRex::IndexBuffer> squareIB = CaelumRex::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVertexArray->SetIndexBuffer(squareIB);
		//======================================================================


    	// Bound in OnUpdate
		// m_Shader = CaelumRex::Shader::Create("assets/shaders/BasicColorShader.glsl");
		m_ColorShader = CaelumRex::Shader::Create("assets/shaders/FlatColorShader.glsl");

    	// Load into Shader Library
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/TextureShader.glsl");

    	// Create Textures
		m_Texture = CaelumRex::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = CaelumRex::Texture2D::Create("assets/textures/ChernoLogo.png");
			// TODO Set texture uniforms in different way
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

    	auto textureShader = m_ShaderLibrary.Get("TextureShader");

        m_Texture->Bind();
        CaelumRex::Renderer::Dispatch(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
        m_ChernoLogoTexture->Bind();
        CaelumRex::Renderer::Dispatch(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

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

    glm::vec3 m_SquareColor = { 0.4f, 0.2f, 0.6f };
};

class Sandbox : public CaelumRex::Application
{
public:
    Sandbox()
    {
        // PushLayer(new ExampleLayer());
    	PushLayer(new Sandbox2D());
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
