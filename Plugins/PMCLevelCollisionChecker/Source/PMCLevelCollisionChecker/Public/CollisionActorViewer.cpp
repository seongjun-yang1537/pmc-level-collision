#include "CollisionActorViewer.h"

void SCollisionActorViewer::Construct(const FArguments& InArgs)
{
	OnCheckCollision = InArgs._OnCheckCollision;
	OnCheckCollision->AddLambda([&](FName PresetName)
	{
		this->PresetName = PresetName;
		UpdateVisible();
	});
	
	ChildSlot
	[
		SNew(SButton)
		.OnClicked(this, &SCollisionActorViewer::OnClicked)
		.Content()
		[
			SNew(SImage)
			.Image_Lambda([this]()
			{
				return VisibleIcons[bState].GetIcon();
			})
		]
	];
}

FReply SCollisionActorViewer::OnClicked()
{
	bState = !bState;
	UpdateVisible();
	return FReply::Handled();
}

void SCollisionActorViewer::UpdateVisible()
{
}
