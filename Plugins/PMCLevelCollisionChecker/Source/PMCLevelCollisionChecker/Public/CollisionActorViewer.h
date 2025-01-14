#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCheckCollision, FName);

class SCollisionActorViewer : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCollisionActorViewer){}
		SLATE_ARGUMENT(FOnCheckCollision*, OnCheckCollision)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	const FSlateIcon VisibleIcons[2] = {
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Level.NotVisibleIcon16x"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Level.VisibleIcon16x")
	};
	
	bool bState;
	FName PresetName;
	FOnCheckCollision* OnCheckCollision;
	
	FReply OnClicked();
	void UpdateVisible();
};
