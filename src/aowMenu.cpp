#pragma once
#include "Settings.h"
#include "aowMenu.h"

aowMenu::aowMenu()
{
	auto scaleformManager = RE::BSScaleformManager::GetSingleton();

	depthPriority = 0;

	menuFlags.set(RE::UI_MENU_FLAGS::kAlwaysOpen);
	menuFlags.set(RE::UI_MENU_FLAGS::kRequiresUpdate);
	menuFlags.set(RE::UI_MENU_FLAGS::kAllowSaving);
	inputContext = Context::kNone;

	if (uiMovie) {
		uiMovie->SetMouseCursorCount(0);
	}

	scaleformManager->LoadMovieEx(this, MENU_PATH, [](RE::GFxMovieDef* a_def) -> void {
		a_def->SetState(RE::GFxState::StateType::kLog,
			RE::make_gptr<Logger>().get());
	});
}

void aowMenu::Register()
{
	auto ui = RE::UI::GetSingleton();
	if (ui) {
		ui->Register(MENU_NAME, Creator);
	}
}

void aowMenu::Show()
{
	logger::info("showing aow");
	auto msgQ = RE::UIMessageQueue::GetSingleton();
	if (msgQ) {
		msgQ->AddMessage(aowMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
		SKSE::GetTaskInterface()->AddUITask([]() {
			aowMenu::SetLocation();
		});
	} else
		logger::info("failed to show aow");
}

void aowMenu::Hide()
{
	auto msgQ = RE::UIMessageQueue::GetSingleton();
	if (msgQ) {
		msgQ->AddMessage(aowMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
	}
}

void aowMenu::toggleVisibility(bool mode)
{
	auto ui = RE::UI::GetSingleton();
	if (!ui)
		return;

	auto overlayMenu = ui->GetMenu(aowMenu::MENU_NAME);
	if (!overlayMenu || !overlayMenu->uiMovie)
		return;

	overlayMenu->uiMovie->SetVisible(mode);
}

// overload to allow you to set name manually
void aowMenu::SetName(RE::GFxValue newName)
{
	RE::GPtr<RE::IMenu> menuObject = RE::UI::GetSingleton()->GetMenu(aowMenu::MENU_NAME);
	if (!menuObject || !menuObject->uiMovie) {
		logger::warn("AOWMenu tried to set name, but menuObject did not exist.");
		return;
	}
	menuObject->uiMovie->Invoke("ash.setText", nullptr, &newName, 1);
}

// overload to allow you to set location manually
void aowMenu::SetLocation(float xpos, float ypos, float rot, float xscale, float yscale, float textxpos, float textypos)
{
	RE::GPtr<RE::IMenu> menuObject = RE::UI::GetSingleton()->GetMenu(aowMenu::MENU_NAME);
	if (!menuObject || !menuObject->uiMovie) {
		logger::warn("AOWMenu tried to set location, but menuObject did not exist.");
		return;
	}
	const RE::GFxValue widget_xpos = xpos;
	const RE::GFxValue widget_ypos = ypos;
	const RE::GFxValue widget_rotation = rot;
	const RE::GFxValue widget_xscale = xscale;
	const RE::GFxValue widget_yscale = yscale;
	const RE::GFxValue text_xpos = textxpos;
	const RE::GFxValue text_ypos = textypos;
	RE::GFxValue posArray[7]{ widget_xpos, widget_ypos, widget_rotation, widget_xscale, widget_yscale, text_xpos, text_ypos };
	menuObject->uiMovie->Invoke("ash.setLocation", nullptr, posArray, 7);
}

void aowMenu::SetLocation()
{
	RE::GPtr<RE::IMenu> menuObject = RE::UI::GetSingleton()->GetMenu(aowMenu::MENU_NAME);
	if (!menuObject || !menuObject->uiMovie) {
		logger::warn("AOWMenu tried to set location, but menuObject did not exist.");
		return;
	}
	//replace these Settings calls with toml++ calls
	const RE::GFxValue widget_xpos = Settings::GetSingleton()->widget_xpos;
	const RE::GFxValue widget_ypos = Settings::GetSingleton()->widget_ypos;
	const RE::GFxValue widget_rotation = Settings::GetSingleton()->widget_rotation;
	const RE::GFxValue widget_xscale = Settings::GetSingleton()->widget_xscale;
	const RE::GFxValue widget_yscale = Settings::GetSingleton()->widget_yscale;
	const RE::GFxValue text_xpos = Settings::GetSingleton()->text_xpos;
	const RE::GFxValue text_ypos = Settings::GetSingleton()->text_ypos;
	RE::GFxValue posArray[7]{ widget_xpos, widget_ypos, widget_rotation, widget_xscale, widget_yscale, text_xpos, text_ypos };
	menuObject->uiMovie->Invoke("ash.setLocation", nullptr, posArray, 7);
}

void aowMenu::SetName()
{
	auto ui = RE::UI::GetSingleton();
	if (!ui) {
		logger::warn("could not find ui");
	}
	RE::GPtr<RE::IMenu> menuObject = ui->GetMenu(aowMenu::MENU_NAME);
	if (!menuObject || !menuObject->uiMovie) {
		logger::warn("AOWMenu tried to set name, but menuObject did not exist.");
		return;
	}
	auto player = RE::PlayerCharacter::GetSingleton();
	if (player) {
		auto power = player->selectedPower;
		if (power) {
			RE::GFxValue newName;
			if (auto powerObj = power->As<RE::SpellItem>(); powerObj && Settings::GetSingleton()->widget_showPowers) {
				newName = powerObj->fullName.c_str();
			} else if (auto shoutObj = power->As<RE::TESShout>(); shoutObj && Settings::GetSingleton()->widget_showShouts) {
				newName = shoutObj->fullName.c_str();
			} else {
				aowMenu::toggleVisibility(false);
				return;
			}
			menuObject->uiMovie->Invoke("ash.setText", nullptr, &newName, 1);
			if (!ui->IsMenuOpen(RE::MagicMenu::MENU_NAME)) {
				aowMenu::toggleVisibility(true);
			}
		} else {
			aowMenu::toggleVisibility(false);
		}
	}
}

#if false
// dont really need this for aow atm, but might later on if more is added.
void aowMenu::Update()
{

}


// Every time a new frame of the menu is rendered call the update function.
void aowMenu::AdvanceMovie(float a_interval, std::uint32_t a_currentTime)
{
	//aowMenu::Update();
	RE::IMenu::AdvanceMovie(a_interval, a_currentTime);
}
#endif
