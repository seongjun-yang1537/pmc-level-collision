// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FPMCLevelCollisionCheckerModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterMenus();
	void RegisterDockTab();

	void UnRegisterDockTab();

	TSharedRef<SDockTab> CreateDockTab(const FSpawnTabArgs& SpawnTabArgs);
	void OnSpawnDockTab();
};
