// Dear ImGui: standalone example application for DirectX 11
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <cstdint>

#include "Icons.h"

#include "FavoritesTab.h"
#include "CombatTab.h"

// Data
static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Line(ImVec2 start, ImVec2 Size)
{
    ImGui::GetWindowDrawList()->AddLine(ImGui::GetWindowPos() + start, ImGui::GetWindowPos() + Size, ImColor(45, 45, 45, 255), 1.5f);
    ImGui::GetWindowDrawList()->AddCircleFilled(ImGui::GetWindowPos() + start, 6.f, ImColor(45, 45, 45, 255), 100.f);
}

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"ImGui Example", NULL };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX11 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);

    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;

    ImFont* BigFont = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\calibri.ttf", 28.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\calibri.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 19.0f, &icons_config, icons_ranges);

    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::GetStyle().WindowRounding = 15.f;
        ImGui::GetStyle().FrameRounding = 15.f;
        ImGui::GetStyle().ChildRounding = 15.f;
        ImGui::GetStyle().Colors[ImGuiCol_Text] = ImColor(126, 126, 126, 255);
        //ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImColor(16, 16, 16, 255);

        static int Tab = 1;

        static bool Tick = false;
        static float Speed = 0.01f;
        static float Alpha = 1.f;

        if (Tick || Alpha >= 1.f)
        {
            // Tick = true;
            if (!(Alpha <= 0.f))
                Alpha -= Speed;
            //else if (Alpha <= 0)
            //    Tick ^= 1;
        }
        else if (!Tick || Alpha != 1.f)
        {
            //Tick = false;
            if (!(Alpha >= 1.f))
                Alpha += Speed;
            //else if (Alpha >= 1.f)
            //    Tick ^= 1;
        }

        ImGui::PushFont(font);
        auto CursorPos = ImGui::GetMousePos();

        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Alpha);
        ImGui::SetNextWindowSize(ImVec2(850, 550));

        if (Alpha < 0.1f)
            exit(-1);

        if (Alpha > 0.1f)
        {
            if (ImGui::Begin("Begin", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
            {
                ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos() + ImVec2(1, 0), ImGui::GetWindowPos() + ImVec2(849, 35), ImColor(19, 19, 19, (int)(Alpha)), 15.f);
                ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos() + ImVec2(1, 20.f), ImGui::GetWindowPos() + ImVec2(849, 35), ImColor(19, 19, 19, (int)(Alpha)), 0);

                ImGui::SetCursorPosX(20);
                ImGui::SetCursorPosY(10);

                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(200, 200, 200, 255).Value);
                ImGui::Text("Project name");
                ImGui::PopStyleColor();

                ImGui::SameLine(780);

                ImGui::Text(ICON_FA_MINUS);
                if (ImGui::IsItemClicked())
                    Tick ^= 1;

                ImGui::SameLine(815);

                ImGui::Text(ICON_FA_PLUS);
                if (ImGui::IsItemClicked())
                {
                    Tick ^= 1;
                }

                ImGui::Dummy(ImVec2(700, 10));

                Line(ImVec2(75, 45), ImVec2(700, 45));

                ImGui::SameLine(800);

                ImGui::SetCursorPosY(40);

                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(62, 135, 242, 255).Value);
                ImGui::Text(ICON_FA_COG);
                ImGui::PopStyleColor();

                ImGui::Dummy(ImVec2(800, 10));

                ImGui::BeginChild("##rightside", ImVec2(200, 450), false);

                ImGui::PushFont(BigFont);

                ImGui::Dummy(ImVec2(800, 30));

                ImGui::SetCursorPosX(25);
                {
                    static int CurrentTab = 1;
                    static int Alpha = 126;

                    ImGui::PushStyleColor(ImGuiCol_Text, Tab == CurrentTab ? ImColor(Alpha, Alpha, Alpha, 255).Value : ImColor(Alpha, Alpha, Alpha, 255).Value);
                    auto text_pos = ImGui::TextButton("Favorites");
                    ImGui::PopStyleColor();
                    static float x = 0.f;

                    if (ImGui::IsItemHovered() && Alpha < 255)
                        Alpha += 5;
                    if (Tab == CurrentTab && Alpha < 255)
                        Alpha += 5;
                    else if (!ImGui::IsItemHovered() && Alpha > 126 && Tab != CurrentTab)
                        Alpha -= 5;

                    if (Tab == CurrentTab && x < 25.f)
                        x += 1.f;
                    else if (x > 0.f && Tab != CurrentTab)
                        x -= 1.;

                    if (x > 0.1f)
                    {
                        ImVec2 _1 = text_pos + ImVec2(1, 27) - ImVec2(0, 0);
                        ImGui::GetForegroundDrawList()->AddRectFilled(_1, _1 + ImVec2(x, 3.f), ImColor(54, 158, 233, 255));
                    }

                    if (ImGui::IsItemClicked())
                        Tab = CurrentTab;
                }

                ImGui::Dummy(ImVec2(180, 25));

                ImGui::SetCursorPosX(25);
                {
                    static int CurrentTab = 2;
                    static int Alpha = 126;

                    ImGui::PushStyleColor(ImGuiCol_Text, Tab == CurrentTab ? ImColor(Alpha, Alpha, Alpha, 255).Value : ImColor(Alpha, Alpha, Alpha, 255).Value);
                    auto text_pos = ImGui::TextButton("Combat");
                    ImGui::PopStyleColor();
                    static float x = 0.f;

                    if (ImGui::IsItemHovered() && Alpha < 255)
                        Alpha += 5;
                    if (Tab == CurrentTab && Alpha < 255)
                        Alpha += 5;
                    else if (!ImGui::IsItemHovered() && Alpha > 126 && Tab != CurrentTab)
                        Alpha -= 5;

                    if (Tab == CurrentTab && x < 25.f)
                        x += 1.f;
                    else if (x > 0.f && Tab != CurrentTab)
                        x -= 1.;

                    if (x > 0.1f)
                    {
                        ImVec2 _1 = text_pos + ImVec2(1, 27) - ImVec2(0, 0);
                        ImGui::GetForegroundDrawList()->AddRectFilled(_1, _1 + ImVec2(x, 3.f), ImColor(54, 158, 233, 255));
                    }

                    if (ImGui::IsItemClicked())
                        Tab = CurrentTab;
                }

                ImGui::Dummy(ImVec2(180, 25));

                ImGui::SetCursorPosX(25);
                {
                    static int CurrentTab = 3;
                    static int Alpha = 126;

                    ImGui::PushStyleColor(ImGuiCol_Text, Tab == CurrentTab ? ImColor(Alpha, Alpha, Alpha, 255).Value : ImColor(Alpha, Alpha, Alpha, 255).Value);
                    auto text_pos = ImGui::TextButton("Render");
                    ImGui::PopStyleColor();
                    static float x = 0.f;

                    if (ImGui::IsItemHovered() && Alpha < 255)
                        Alpha += 5;
                    if (Tab == CurrentTab && Alpha < 255)
                        Alpha += 5;
                    else if (!ImGui::IsItemHovered() && Alpha > 126 && Tab != CurrentTab)
                        Alpha -= 5;

                    if (Tab == CurrentTab && x < 25.f)
                        x += 1.f;
                    else if (x > 0.f && Tab != CurrentTab)
                        x -= 1.;

                    if (x > 0.1f)
                    {
                        ImVec2 _1 = text_pos + ImVec2(1, 27) - ImVec2(0, 0);
                        ImGui::GetForegroundDrawList()->AddRectFilled(_1, _1 + ImVec2(x, 3.f), ImColor(54, 158, 233, 255));
                    }

                    if (ImGui::IsItemClicked())
                        Tab = CurrentTab;
                }

                ImGui::Dummy(ImVec2(180, 25));

                ImGui::SetCursorPosX(25);
                {
                    static int CurrentTab = 4;
                    static int Alpha = 126;

                    ImGui::PushStyleColor(ImGuiCol_Text, Tab == CurrentTab ? ImColor(Alpha, Alpha, Alpha, 255).Value : ImColor(Alpha, Alpha, Alpha, 255).Value);
                    auto text_pos = ImGui::TextButton("Utility");
                    ImGui::PopStyleColor();
                    static float x = 0.f;

                    if (ImGui::IsItemHovered() && Alpha < 255)
                        Alpha += 5;
                    if (Tab == CurrentTab && Alpha < 255)
                        Alpha += 5;
                    else if (!ImGui::IsItemHovered() && Alpha > 126 && Tab != CurrentTab)
                        Alpha -= 5;

                    if (Tab == CurrentTab && x < 25.f)
                        x += 1.f;
                    else if (x > 0.f && Tab != CurrentTab)
                        x -= 1.;

                    if (x > 0.1f)
                    {
                        ImVec2 _1 = text_pos + ImVec2(1, 27) - ImVec2(0, 0);
                        ImGui::GetForegroundDrawList()->AddRectFilled(_1, _1 + ImVec2(x, 3.f), ImColor(54, 158, 233, 255));
                    }

                    if (ImGui::IsItemClicked())
                        Tab = CurrentTab;
                }

                ImGui::PopFont();
                ImGui::EndChild();

                ImGui::SameLine();

                {
                    ImGui::BeginChild("##leftside", ImVec2(600, 450), false);

                    static int TopTab = 1;

                    switch (Tab)
                    {
                    case 1:
                    {
                        FavTab();
                        break;
                    }
                    case 2:
                    {
                        CombatTab();
                        break;
                    }
                    case 3:
                        //RenderTab();
                        break;
                    case 4:
                        //UtilityTab();
                        break;
                    default:
                        break;
                    }

                    ImGui::EndChild();
                }

                ImGui::End();
            }
        }

        ImGui::PopStyleVar();

        ImGui::PopFont();

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
