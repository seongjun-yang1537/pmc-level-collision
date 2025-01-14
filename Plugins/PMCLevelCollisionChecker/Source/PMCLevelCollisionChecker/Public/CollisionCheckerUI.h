#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_MULTICAST_DELEGATE(FOnCheckCollision);

class SCollisionCheckerUI : public SCompoundWidget  
{
public:
	SLATE_BEGIN_ARGS(SCollisionCheckerUI) {}
	SLATE_END_ARGS()

	FOnCheckCollision OnCheckCollision;
	
	void Construct(const FArguments& args);

private:
	TArray<TSharedPtr<FName>> CollisionPresetNames;
	
	FName SelectedPreset;
	FText GetSelecedPreset() const;
	
	TSharedRef<SWidget> CreateCollisionPresetDropDownList();
	TSharedRef<SWidget> CreateValidateButton();
	
	TSharedRef<SWidget> OnGenerateDropDownElement(TSharedPtr<FName> Element);
};
