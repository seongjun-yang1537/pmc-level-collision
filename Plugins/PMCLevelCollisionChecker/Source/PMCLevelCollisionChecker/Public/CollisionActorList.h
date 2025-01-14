#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_MULTICAST_DELEGATE(FOnCheckCollision);

class SCollisionActorList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCollisionActorList) {}
		SLATE_ARGUMENT(FOnCheckCollision*, OnCheckCollision)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	FOnCheckCollision* OnCheckCollision;
	TArray<AActor*> ActorList;
	
	TSharedPtr<SListView<AActor*>> ActorListWidget;
	void UpdateListWidget();
	TSharedRef<ITableRow> OnGenerateElement(AActor* Item, const TSharedRef<STableViewBase>& OwnerTable);
};
