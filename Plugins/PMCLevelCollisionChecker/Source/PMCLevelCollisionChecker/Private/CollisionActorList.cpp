#include "CollisionActorList.h"
#include "Engine.h"

#pragma region Public

void SCollisionActorList::Construct(const FArguments& InArgs)
{
	OnCheckCollision = InArgs._OnCheckCollision;
	OnCheckCollision->AddLambda([this]()
	{
		UpdateListWidget();
	});
	
	UpdateListWidget();
	
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
void SCollisionActorList::UpdateListWidget()
{
	if (!GEditor)
	{
		return;
	}
	
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		return;
	}

	ActorList.Reset();

	const TArray<AActor*>& Actors = World->PersistentLevel->Actors;
	for (auto Actor : Actors)
	{
		if (Actor)
		{
			ActorList.Add(Actor);	
		}
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
		SNew(STextBlock)
		.Text(FText::FromString(Item->GetActorLabel()))
	];
}
#pragma endregion 