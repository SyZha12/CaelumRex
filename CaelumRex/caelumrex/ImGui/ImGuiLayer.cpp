/** CaelumRex libraries **/
#include <Core/Application.h>

/** Third-Party Libraries & Co **/
#include <ImGui/ImGuiLayer.h>
#include <GLFW/glfw3.h>
#include <imgui-docking/backends/imgui_impl_glfw.h>
#include <imgui-docking/backends/imgui_impl_opengl3.h>

namespace CaelumRex
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {

    }

    void ImGuiLayer::OnAttach()
    {
        // Context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Config flags
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable keyboard controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // Enable gamepad controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable multi-viewport (for Windows)
        // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // Style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsLight();
        ImGuiStyle& style = ImGui::GetStyle();
        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        const Application& app = Application::Get();
        const auto window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 430");
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnImGuiRender()
    {
        // static bool show = true;
        // ImGui::ShowDemoWindow(&show);
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }


}
