#include "CollisionActorList.h"
#include "CollisionActorElement.h"

#pragma region Public

void SCollisionActorList::Construct(const FArguments& InArgs)
{
	OnCheckCollision = InArgs._OnCheckCollision;
	OnCheckCollision->AddLambda([&](FName PresetName)
	{
		NowPresetName = PresetName;
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
		if (Actor && IsVisible(Actor))
		{
			ActorList.Add(Actor);
		}
	}

	if (ActorListWidget.IsValid())
	{
		ActorListWidget->RebuildList();
	}
}

bool SCollisionActorList::IsVisible(AActor* Actor) const
{
	TArray<UActorComponent*> Components = Actor->K2_GetComponentsByClass(UPrimitiveComponent::StaticClass());

	for (auto Component : Components)
	{
		if (!Component)
		{
			continue;
		}
			
		UPrimitiveComponent* PrimitiveComponent =
				Cast<UPrimitiveComponent>(Component);
		if (!PrimitiveComponent)
		{
			continue;
		}

		FName CurrentPreset = PrimitiveComponent->GetCollisionProfileName();
		if (CurrentPreset == NowPresetName)
		{
			return true;
		}
	}
	return false;
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