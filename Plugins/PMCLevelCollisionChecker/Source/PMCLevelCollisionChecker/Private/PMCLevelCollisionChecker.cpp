// Copyright Epic Games, Inc. All Rights Reserved.

#include "PMCLevelCollisionChecker.h"
#include "CollisionCheckerUI.h"

#define LOCTEXT_NAMESPACE "FPMCLevelCollisionCheckerModule"
#define DOCKTAB_NAME "PMCColiisionCheckerDockTab"

#pragma region Public
void FPMCLevelCollisionCheckerModule::StartupModule()
{
	RegisterMenus();
	RegisterDockTab();
}

void FPMCLevelCollisionCheckerModule::ShutdownModule()
{
	UnRegisterDockTab();
}
#pragma endregion

#pragma region Private
void FPMCLevelCollisionCheckerModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
	FToolMenuSection& Section = Menu->AddSection("PMC", LOCTEXT("PMC", "PMC"));

	Section.AddMenuEntry(
		"Open Collision Checker Window",
		LOCTEXT("OpenCollisionCheckerWindow", "Open Collision Checker Window"),
		LOCTEXT("OpenCollisionCheckerWindowTooltip", "Open Collision Checker Window."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "ShowFlagsMenu.Collision"),
		FUIAction(FExecuteAction::CreateRaw(this, &FPMCLevelCollisionCheckerModule::OnSpawnDockTab))
	);
}

void FPMCLevelCollisionCheckerModule::RegisterDockTab()
{
	TSharedRef<FWorkspaceItem> WorkspaceGroup = FWorkspaceItem::NewGroup(FText::FromString(DOCKTAB_NAME));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		DOCKTAB_NAME,
		FOnSpawnTab::CreateRaw(this, &FPMCLevelCollisionCheckerModule::CreateDockTab)
	)
	.SetDisplayName(LOCTEXT(DOCKTAB_NAME, "PMC Level Collision Checker"))
	.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "ShowFlagsMenu.Collision"))
	.SetGroup(WorkspaceGroup);
}

void FPMCLevelCollisionCheckerModule::UnRegisterDockTab()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DOCKTAB_NAME);
}

void FPMCLevelCollisionCheckerModule::OnSpawnDockTab()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FTabId(DOCKTAB_NAME));
}

TSharedRef<SDockTab> FPMCLevelCollisionCheckerModule::CreateDockTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
	.TabRole(ETabRole::NomadTab)
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SCollisionCheckerUI)
		]
	];
}
#pragma endregion

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPMCLevelCollisionCheckerModule, PMCLevelCollisionChecker)