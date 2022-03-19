#pragma once
#include "Events.h"
#include "RE/U/UI.h"
#include "aowMenu.h"
#include "string.h"

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
			aowMenu::toggleVisibility(true);
		}
	}
	return RE::BSEventNotifyControl::kContinue;
}
