#pragma once
#include <vector>
#include <memory>
#include "IGameService.h"

#include <SDK/Options.h>
#include <SDK/imGui/imgui_impl_dx9.h>
#include <SDK/ImGui/imgui.h>
#include <SDK/ImGui/imgui_internal.h>

class IComponent {

private:
	std::vector<std::unique_ptr<IGameService>> mServices;

public:
	// For Menu
	bool mIsActive;
	const char* mTabName;

	IComponent(const char* tabName) {
		mTabName = tabName;
		mIsActive = false;
		mServices = std::vector<std::unique_ptr<IGameService>>();
	}

	template<typename T>
	void AddGameService();

	virtual void OnUpdate() {
		for (auto it = this->mServices.begin(); it != this->mServices.end(); it++) {
			(*it)->OnUpdate();
		}
	}
	virtual void OnEndScene() {
		for (auto it = this->mServices.begin(); it != this->mServices.end(); it++) {
			(*it)->OnEndScene();
		}
	}

#pragma region MENU
	virtual void RenderMenu() {}

	void Start(int nbColumns) {
		bool placeholder_true = true;
		auto& style = ImGui::GetStyle();
		float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });

		ImGui::Columns(nbColumns, nullptr, true);
		for (int i = 1; i <= nbColumns; ++i)
			ImGui::SetColumnOffset(i, group_w / (float)nbColumns);
	}

	void End() { ImGui::PopStyleVar(); }
#pragma endregion

};

template<typename T>
inline void IComponent::AddGameService()
{
	this->mServices.push_back(std::make_unique<T>());
}