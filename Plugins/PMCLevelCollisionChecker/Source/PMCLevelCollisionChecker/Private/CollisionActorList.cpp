#include "CollisionActorList.h"
#include "CollisionActorElement.h"
#include "CollisionActorChecker.h"

#pragma region Public

void SCollisionActorList::Construct(const FArguments& InArgs)
{
	OnCheckCollision = InArgs._OnCheckCollision;
	OnCheckCollision->AddLambda([&](FName PresetName)
	{
		UpdateListWidget(PresetName);
	});
	UpdateListWidget(FName("Default"));
	
	ChildSlot[
		SNew(SVerticalBox)
		// + SVerticalBox::Slot()
		// [
		// 		
		// ]
		+ SVerticalBox::Slot()
		.MaxHeight(512)
		[
			SNew(SScrollBox)
			.Orientation(Orient_Vertical)
			+ SScrollBox::Slot()
			.AutoSize()
			[
				SAssignNew(ActorListWidget, SListView<AActor*>)
				.ItemHeight(24)
				.ListItemsSource(&ActorList)
				.OnGenerateRow(this, &SCollisionActorList::OnGenerateElement)
			]
		]
	];
}
#pragma endregion

#pragma region Private
void SCollisionActorList::UpdateListWidget(FName PresetName)
{
	ActorList.Reset();
	ActorList = FCollisionActorChecker::GetActorsByCollisionPreset(PresetName);

	if (ActorListWidget.IsValid())
	{
		ActorListWidget->RebuildList();
	}
}

TSharedRef<ITableRow> SCollisionActorList::OnGenerateElement(AActor* Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (!Item)
	{
		return SNew(STableRow<AActor*>, OwnerTable)
		[
			SNullWidget::NullWidget
		];
	}
	return SNew(STableRow<AActor*>, OwnerTable)
	[
		SNew(SButton)
		.Text(FText::FromString(Item->GetActorLabel()))
			.OnClicked_Lambda([this, Item]()
			{
				SelectActor(Item);
				return FReply::Handled();
			})
	];
}

void SCollisionActorList::SelectActor(AActor* Actor)
{
	GEditor->SelectNone(false, true);
	GEditor->SelectActor(Actor, true, true);
	GEditor->MoveViewportCamerasToActor(*Actor, true);
}

#pragma endregion 