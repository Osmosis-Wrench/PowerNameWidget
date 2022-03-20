#pragma once
#include "PCH.h"

class MenuOpenCloseEventHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent>
{
public:
	static MenuOpenCloseEventHandler* GetSingleton();
	static void Register();

	virtual RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
};

class ItemEquipEventHandler : public RE::BSTEventSink<RE::TESEquipEvent>
{
public:
	static ItemEquipEventHandler* GetSingleton();
	static void Register();

	virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) override;
};
