#pragma once
#include "Events.h"
#include "RE/U/UI.h"
#include "aowMenu.h"
#include "string.h"
#include "RE/T/TESForm.h"

MenuOpenCloseEventHandler* MenuOpenCloseEventHandler::GetSingleton()
{
	static MenuOpenCloseEventHandler singleton;
	return std::addressof(singleton);
}

void MenuOpenCloseEventHandler::Register()
{
	auto ui = RE::UI::GetSingleton();
	ui->AddEventSink(GetSingleton());
}

RE::BSEventNotifyControl MenuOpenCloseEventHandler::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
{
	// from ersh TrueHud pretty much verbatim
	if (a_event) {
		if (a_event->menuName == RE::HUDMenu::MENU_NAME) {
			if (a_event->opening) {
				aowMenu::Show();
			} else {
				aowMenu::Hide();
			}
		} else if (a_event->menuName == RE::RaceSexMenu::MENU_NAME && !a_event->opening) {
			aowMenu::Show();
			logger::info("showing menu when racemenu closes");
		}
	}

	auto controlMap = RE::ControlMap::GetSingleton();
	if (controlMap) {
		auto& priorityStack = controlMap->contextPriorityStack;
		if (priorityStack.empty() ||
			(priorityStack.back() != RE::UserEvents::INPUT_CONTEXT_ID::kGameplay &&
				priorityStack.back() != RE::UserEvents::INPUT_CONTEXT_ID::kFavorites &&
				priorityStack.back() != RE::UserEvents::INPUT_CONTEXT_ID::kConsole)) {
					aowMenu::toggleVisibility(false);
		} else {
				SKSE::GetTaskInterface()->AddUITask([]() {
					aowMenu::SetName();
				});
		}
	}
	return RE::BSEventNotifyControl::kContinue;
}

ItemEquipEventHandler* ItemEquipEventHandler::GetSingleton()
{
	static ItemEquipEventHandler singleton;
	return std::addressof(singleton);
}

void ItemEquipEventHandler::Register()
{
	auto equip = RE::ScriptEventSourceHolder::GetSingleton();
	if (equip)
		equip->AddEventSink(GetSingleton());
}

RE::BSEventNotifyControl ItemEquipEventHandler::ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>*) 
{
	if (a_event) {
		auto player = RE::PlayerCharacter::GetSingleton();
		if (player && RE::TESForm::LookupByID(a_event->baseObject)->GetName() != NULL) {
			if (RE::TESForm::LookupByID(a_event->baseObject) == player->selectedPower) {
				SKSE::GetTaskInterface()->AddUITask([]() {
					aowMenu::SetName();
				});
			}
		}
	}
	return RE::BSEventNotifyControl::kContinue;
}
