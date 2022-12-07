#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

inline void CombatTab()
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
        ImGui::Text("KillAura");
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
        ImGui::Text("MobAura");
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
        ImGui::Text("Trigger");
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
        ImGui::Text("Criticals");
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
        ImGui::Text("FastBow");
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

    ImGui::EndChild();

    ImGui::SameLine(0.f, 15.f);

    ImGui::BeginChild("##bottomright", ImVec2(210, 355), false);

    ImGui::EndChild();
}
