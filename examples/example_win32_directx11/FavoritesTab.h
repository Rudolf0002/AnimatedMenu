#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

inline void FavTab()
{
    static int TopTab = 1;

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(19, 19, 19, 255).Value);
    ImGui::BeginChild("##top", ImVec2(450, 50), false);

    ImGui::SetCursorPosX(15);
    ImGui::SetCursorPosY(15);

    {
        static int CurrentTab = 1;
        static int Alpha = 126;

        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(Alpha, Alpha, Alpha, 255).Value);
        ImGui::Text("Auto Clicker");
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && Alpha < 255)
            Alpha += 5;
        if (TopTab == CurrentTab && Alpha < 255)
            Alpha += 5;
        else if (!ImGui::IsItemHovered() && Alpha > 126 && TopTab != CurrentTab)
            Alpha -= 5;

        if (ImGui::IsItemClicked())
            TopTab = CurrentTab;
    }

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(126, 126, 126, 126).Value);
    ImGui::SetCursorPosY(15);
    ImGui::Text("|");
    ImGui::PopStyleColor();

    ImGui::SameLine();

    ImGui::SetCursorPosY(15);

    {
        static int CurrentTab = 2;
        static int Alpha = 126;

        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(Alpha, Alpha, Alpha, 255).Value);
        ImGui::Text("Aim Assist");
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && Alpha < 255)
            Alpha += 5;
        if (TopTab == CurrentTab && Alpha < 255)
            Alpha += 5;
        else if (!ImGui::IsItemHovered() && Alpha > 126 && TopTab != CurrentTab)
            Alpha -= 5;

        if (ImGui::IsItemClicked())
            TopTab = CurrentTab;
    }

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(126, 126, 126, 126).Value);
    ImGui::SetCursorPosY(15);
    ImGui::Text("|");
    ImGui::PopStyleColor();

    ImGui::SameLine();

    ImGui::SetCursorPosY(15);

    {
        static int CurrentTab = 3;
        static int Alpha = 126;

        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(Alpha, Alpha, Alpha, 255).Value);
        ImGui::Text("Velocity");
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && Alpha < 255)
            Alpha += 5;
        if (TopTab == CurrentTab && Alpha < 255)
            Alpha += 5;
        else if (!ImGui::IsItemHovered() && Alpha > 126 && TopTab != CurrentTab)
            Alpha -= 5;

        if (ImGui::IsItemClicked())
            TopTab = CurrentTab;
    }

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(126, 126, 126, 126).Value);
    ImGui::SetCursorPosY(15);
    ImGui::Text("|");
    ImGui::PopStyleColor();

    ImGui::SameLine();

    ImGui::SetCursorPosY(15);

    {
        static int CurrentTab = 4;
        static int Alpha = 126;

        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(Alpha, Alpha, Alpha, 255).Value);
        ImGui::Text("Reach");
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && Alpha < 255)
            Alpha += 5;
        if (TopTab == CurrentTab && Alpha < 255)
            Alpha += 5;
        else if (!ImGui::IsItemHovered() && Alpha > 126 && TopTab != CurrentTab)
            Alpha -= 5;

        if (ImGui::IsItemClicked())
            TopTab = CurrentTab;
    }

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(126, 126, 126, 126).Value);
    ImGui::SetCursorPosY(15);
    ImGui::Text("|");
    ImGui::PopStyleColor();

    ImGui::SameLine();

    ImGui::SetCursorPosY(15);

    {
        static int CurrentTab = 5;
        static int Alpha = 126;

        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(Alpha, Alpha, Alpha, 255).Value);
        ImGui::Text("W-Tap");
        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && Alpha < 255)
            Alpha += 5;
        if (TopTab == CurrentTab && Alpha < 255)
            Alpha += 5;
        else if (!ImGui::IsItemHovered() && Alpha > 126 && TopTab != CurrentTab)
            Alpha -= 5;

        if (ImGui::IsItemClicked())
            TopTab = CurrentTab;
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();

    ImGui::SetCursorPosY(65);
    ImGui::BeginChild("##bottomleft", ImVec2(225, 355), false);

    switch (TopTab)
    {
    case 1:
    {
        static bool bool1 = false;
        ImGui::Toggle("Enable Clicker", &bool1);

        ImGui::SameLine();
        ImGui::SetCursorPosX(120);

        static int key1 = 0;
        ImGui::Hotkey("##Hotkey", &key1);

        ImGui::Dummy(ImVec2(10, 10));

        static int int1 = 1;
        ImGui::SliderInt("Clicks Per Second", &int1, 1, 99);

        ImGui::Dummy(ImVec2(10, 10));

        static bool bool2 = false;
        ImGui::Checkbox("Swords Only", &bool2);

        ImGui::Dummy(ImVec2(10, 10));

        static bool bool3 = false;
        ImGui::Checkbox("Inventory", &bool3);

        ImGui::Dummy(ImVec2(10, 10));

        static bool bool4 = false;
        ImGui::Checkbox("CPS Drops", &bool4);

        ImGui::Dummy(ImVec2(10, 10));

        static bool bool5 = false;
        ImGui::Checkbox("Prevent Unrefill", &bool5);

        ImGui::Dummy(ImVec2(10, 10));

        {
            static ImColor color = ImColor(59, 158, 126, 255);

            ImGui::SetCursorPosX(3);

            ImGui::Text("Color picker");

            ImGui::SameLine(180);

            ImGui::ColorEdit4("##Colorpicker", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
        }

        break;
    }
    default:
        break;
    }

    ImGui::EndChild();

    ImGui::SameLine(0.f, 15.f);

    ImGui::BeginChild("##bottomright", ImVec2(210, 355), false);

    switch (TopTab)
    {
    case 1:
    {
        static bool bool1 = false;
        ImGui::Toggle("Enable Block Hit", &bool1);

        ImGui::Dummy(ImVec2(10, 10));

        static int int1 = 1;
        ImGui::SliderInt("Block Hit Chance", &int1, 1, 99);

        ImGui::Dummy(ImVec2(10, 10));

        static bool bool2 = false;
        ImGui::Checkbox("Jitter", &bool2);

        ImGui::Dummy(ImVec2(10, 10));

        static int int2 = 20;
        ImGui::SliderInt("Jitter Intensity", &int2, 1, 99);

        ImGui::Dummy(ImVec2(10, 10));

        static bool bool3 = false;
        ImGui::Checkbox("Break Block", &bool3);

        ImGui::Dummy(ImVec2(10, 28));

        static const char* MovementCombo[] = {
            "Horizontal",
            "Vertical"
        };
        static const char* combo1 = MovementCombo[0];

        ImGui::PushStyleColor(ImGuiCol_Header, ImColor(40, 40, 40, 255).Value);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImColor(40, 40, 40, 255).Value);
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImColor(60, 60, 60, 255).Value);
        ImGui::PushStyleColor(ImGuiCol_PopupBg, ImColor(19, 19, 19, 255).Value);
        ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 5.f);
        ImGui::Text("Movement");
        if (ImGui::BeginCombo("##Movement", combo1))
        {
            for (const auto a : MovementCombo)
            {
                const bool selected = (combo1 == a);
                if (ImGui::Selectable(a, selected))
                    combo1 = a;
                if (selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(4);

        break;
    }
    default:
        break;
    }

    ImGui::EndChild();
}
