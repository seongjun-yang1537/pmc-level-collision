#include "CollisionCheckerUI.h"
#include "CollisionChecker.h"

#pragma region Public
void SCollisionCheckerUI::Construct(const FArguments& args)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				CreateCollisionPresetDropDownList()	
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				CreateValidateButton()
			]
		]
	];
}
#pragma endregion

#pragma region Private
FText SCollisionCheckerUI::GetSelecedPreset() const
{
	return FText::FromString(SelectedPreset.ToString());
}

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

TSharedRef<SWidget> SCollisionCheckerUI::CreateValidateButton()
{
	return SNew(SButton)
	.Text(FText::FromString("Find"))
	.OnClicked_Lambda([]()
	{
		UE_LOG(LogTemp, Log, TEXT("hihihi"));
		return FReply::Handled();
	});
}

TSharedRef<SWidget> SCollisionCheckerUI::OnGenerateDropDownElement(TSharedPtr<FName> Element)
{
	return SNew(STextBlock)
		.Text(FText::FromString(Element->ToString()));
}

#pragma endregion 