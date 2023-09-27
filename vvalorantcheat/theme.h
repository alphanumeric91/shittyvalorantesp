#include "main.h"
#include "icons.h"
#include "fonthelper.h"

const char* healthtype[2] = { "Text", "Bar" };

char FpsInfo[64];


void sextheme()
{
    ImGuiStyle& s = ImGui::GetStyle();
	s.WindowMinSize = ImVec2(696, 437);
	s.WindowRounding = 7.0f;
	s.WindowPadding = ImVec2(0, 0);
	s.ChildRounding = 5.f;
    //ImGui::StyleColorsClassic();

    
	const ImColor accentCol = ImColor(255, 0, 0, 255);
	const ImColor bgSecondary = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_WindowBg] = ImColor(32, 32, 32, 255);
	s.Colors[ImGuiCol_ChildBg] = bgSecondary;
	s.Colors[ImGuiCol_FrameBg] = ImColor(65, 64, 64, 255);
	s.Colors[ImGuiCol_FrameBgActive] = ImColor(35, 37, 39, 255);
	s.Colors[ImGuiCol_Border] = ImColor(1, 1, 1, 255);
	s.Colors[ImGuiCol_CheckMark] = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 0, 0, 255);
	s.Colors[ImGuiCol_ResizeGrip] = ImColor(24, 24, 24, 255);
	s.Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_HeaderHovered] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_TitleBg] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_TitleBgActive] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_FrameBgHovered] = ImColor(65, 64, 64, 255);
	s.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 255);
	s.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	s.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	s.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	s.Colors[ImGuiCol_Header] = ImColor(42, 42, 42, 255);
	s.Colors[ImGuiCol_HeaderHovered] = ImColor(50, 50, 50, 255);
	s.Colors[ImGuiCol_HeaderActive] = ImColor(50, 50, 50, 255);
	s.Colors[ImGuiCol_PopupBg] = ImColor(15, 15, 15, 255);
	s.Colors[ImGuiCol_Button] = ImColor(30, 30, 30, 255);
	s.Colors[ImGuiCol_ButtonHovered] = ImColor(30, 30, 30, 255);
	s.Colors[ImGuiCol_ButtonActive] = ImColor(30, 30, 30, 255);
	s.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);


}

void TssakliMenu()
{
	sprintf_s(FpsInfo, "Overlay FPS: %0.f", ImGui::GetIO().Framerate);
	static int tab = 0;
	ImGui::BeginGroup();

	ImGui::SetCursorPos(ImVec2(20, 40));
	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); // Varsayılan fontu kullan
	ImGui::SetWindowFontScale(0.9f);
	ImGui::Text("speedygonzales.dev");
	ImGui::PopFont();
	ImGui::SetWindowFontScale(1.0f); // Yazı boyutunu eski haline getir
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
	ImGui::SetCursorPos(ImVec2(145, 30));
	if (ImGui::Button(std::string(std::string(XorString(ICON_FA_EYE)) + XorString(" V!suals")).c_str(), ImVec2(120, 40))) {
		tab = 0;
	}

	if (ImGui::IsItemHovered()) {
		ImVec2 start = ImGui::GetItemRectMin();
		ImVec2 end = ImVec2(start.x + ImGui::GetItemRectSize().x, start.y);
		ImGui::GetWindowDrawList()->AddLine(start, end, ImColor(255, 255, 255, 255));
	}
	ImGui::SetCursorPos(ImVec2(270, 30));
	if (ImGui::Button(std::string(std::string(XorString(ICON_FA_CROSSHAIRS)) + XorString(" Aimb0t")).c_str(), ImVec2(120, 40))) {
		tab = 1;
	}
	if (ImGui::IsItemHovered()) {
		ImVec2 start = ImGui::GetItemRectMin();
		ImVec2 end = ImVec2(start.x + ImGui::GetItemRectSize().x, start.y);
		ImGui::GetWindowDrawList()->AddLine(start, end, ImColor(255, 255, 255, 255));
	}
	ImGui::SetCursorPos(ImVec2(395, 30));
	if (ImGui::Button(std::string(std::string(XorString(ICON_FA_PENCIL)) + XorString(" Color")).c_str(), ImVec2(120, 40))) {
		tab = 2;
	}
	if (ImGui::IsItemHovered()) {
		ImVec2 start = ImGui::GetItemRectMin();
		ImVec2 end = ImVec2(start.x + ImGui::GetItemRectSize().x, start.y);
		ImGui::GetWindowDrawList()->AddLine(start, end, ImColor(255, 255, 255, 255));
	}
	ImGui::SetCursorPos(ImVec2(520, 30));
	if (ImGui::Button(std::string(std::string(XorString(ICON_FA_FILE)) + XorString(" Config")).c_str(), ImVec2(120, 40))) {
		tab = 3;
	}
	if (ImGui::IsItemHovered()) {
		ImVec2 start = ImGui::GetItemRectMin();
		ImVec2 end = ImVec2(start.x + ImGui::GetItemRectSize().x, start.y);
		ImGui::GetWindowDrawList()->AddLine(start, end, ImColor(255, 255, 255, 255));
	}
	ImGui::EndGroup();

	ImGui::BeginGroup();
	ImGui::SameLine(100);
	ImGui::EndGroup();
	switch (tab)
	{
	case 0 :
		ImGui::SetCursorPos(ImVec2(45, 80));
		ImGui::BeginGroup();
		{
			ImGui::Checkbox("ESP Box", &config.player_box);
			ImGui::Combo("ESP Type", &config.esptype, type, IM_ARRAYSIZE(type));
			ImGui::Checkbox("Head Box", &config.circlehead);
			ImGui::Checkbox("Enemy View Angle", &config.player_view_angle);
			ImGui::Checkbox("Skeleton ESP", &config.player_skeleton);
			ImGui::Checkbox("Snapline", &config.player_snapline);
			ImGui::Checkbox("Distance ESP", &config.player_distance);
			ImGui::Checkbox("Show Health", &config.player_healthbar);
			ImGui::Combo("Health Type", &config.healthhtype, healthtype, IM_ARRAYSIZE(healthtype));
			ImGui::Checkbox("Ignore Dormant", &config.player_ignore_dormant);
			ImGui::Checkbox("Glow", &config.glow);
			ImGui::Checkbox("Agents Names", &config.characterr);
			ImGui::Checkbox("Fov Changer", &config.fovchanger);

			ImGui::SliderFloat("Fov Value", &config.fovchangervalue, 100.f, 170.f, "%.f"); //i will make this to degrees later
		}
		ImGui::EndGroup();
		break;
	case 1:
		ImGui::SetCursorPos(ImVec2(45, 80));
		ImGui::BeginGroup();
		{
			ImGui::Checkbox("Aimbot", &config.aimenable);
			ImGui::Combo("Key", &config.aimbotkey, optKey, IM_ARRAYSIZE(optKey));
			ImGui::SliderFloat("Fov", &config.aimbot_fov, 10.f, 1000.f, "%.f"); //i will make this to degrees later
				ImGui::SliderFloat("Smooth", &config.aimbot_smooth, 1.f, 20.f, "%.f");
			ImGui::Combo("Target Bone", &config.aimboness, aimbone, IM_ARRAYSIZE(aimbone));
			ImGui::Checkbox("Draw FOV", &config.aimbot_draw_fov);
			ImGui::Checkbox("RCS [min smooth 2]", &config.rcs);

		}
		ImGui::EndGroup();
		break;
	case 2:
		ImGui::SetCursorPos(ImVec2(45, 80));
		ImGui::BeginGroup();
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 0, 0, 0));
			ImGui::ColorEdit4("Esp Color", (float*)&config.espcolor);
			ImGui::ColorEdit4("Snapline Color", (float*)&config.snapcolor);
			ImGui::ColorEdit4("Skeleton Color", (float*)&config.skeleton);
			ImGui::ColorEdit4("Head Circle Color", (float*)&config.headboxcolor);
		}
		ImGui::EndGroup();
		break;
	case 3:
		ImGui::SetCursorPos(ImVec2(270, 120));
		ImGui::BeginGroup();
		{


			if (ImGui::Button("Save"))
			{
				SaveConfig();
			}
			if (ImGui::IsItemHovered()) {
				ImVec2 start = ImGui::GetItemRectMin();
				ImVec2 end = ImVec2(start.x + ImGui::GetItemRectSize().x, start.y);
				ImGui::GetWindowDrawList()->AddLine(start, end, ImColor(255, 255, 255, 255));
			}
			ImGui::SetCursorPos(ImVec2(360, 120));
			if (ImGui::Button("Load"))
			{
				LoadConfig();
			}
			if (ImGui::IsItemHovered()) {
				ImVec2 start = ImGui::GetItemRectMin();
				ImVec2 end = ImVec2(start.x + ImGui::GetItemRectSize().x, start.y);
				ImGui::GetWindowDrawList()->AddLine(start, end, ImColor(255, 255, 255, 255));
			}

		}
		ImGui::EndGroup();
		break;
	}
}