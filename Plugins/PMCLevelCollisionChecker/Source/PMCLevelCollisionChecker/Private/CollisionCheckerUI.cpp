#include "CollisionCheckerUI.h"
#include "CollisionChecker.h"

#pragma region Public
void SCollisionCheckerUI::Construct(const FArguments& args)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			CreateCollisionPresetDropDownList()	
		]
	];
}
#pragma endregion

#pragma region Private
TSharedRef<SWidget> SCollisionCheckerUI::CreateCollisionPresetDropDownList()
{
	CollisionPresetNames.Reset();
	UCollisionProfile::GetProfileNames(CollisionPresetNames);
	
	auto OnSelected = [this](TSharedPtr<FName> NewSelection, ESelectInfo::Type SelectInfo)
	{
		SelectedPreset = *NewSelection;
	};
	
	return SNew(SComboBox<TSharedPtr<FName>>)
		.OptionsSource(&CollisionPresetNames)
		.OnGenerateWidget(this, &SCollisionCheckerUI::OnGenerateDropDownElement)
		.OnSelectionChanged_Lambda(OnSelected)
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &SCollisionCheckerUI::GetSelecedPreset)
		];
}

FText SCollisionCheckerUI::GetSelecedPreset() const
{
	return FText::FromString(SelectedPreset.ToString());
}

TSharedRef<SWidget> SCollisionCheckerUI::OnGenerateDropDownElement(TSharedPtr<FName> Element)
{
	return SNew(STextBlock)
		.Text(FText::FromString(Element->ToString()));
}

#pragma endregion 