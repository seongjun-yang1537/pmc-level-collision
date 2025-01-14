#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SCollisionCheckerUI : public SCompoundWidget  
{
public:
	SLATE_BEGIN_ARGS(SCollisionCheckerUI) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& args);

private:
	TArray<TSharedPtr<FName>> CollisionPresetNames;
	FName SelectedPreset;
	
	TSharedRef<SWidget> CreateCollisionPresetDropDownList();
	FText GetSelecedPreset() const;
	
	TSharedRef<SWidget> OnGenerateDropDownElement(TSharedPtr<FName> Element);
};
