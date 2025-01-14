#include "CollisionActorElement.h"

void SCollisionActorElement::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString("1"))
		]
		+ SHorizontalBox::Slot()
		[
			SNew(STextBlock)
			.Text(FText::FromString("2"))
		]
	];
}
