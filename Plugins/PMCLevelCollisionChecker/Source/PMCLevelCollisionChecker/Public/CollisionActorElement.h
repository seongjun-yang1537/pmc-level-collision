#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SCollisionActorElement : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCollisionActorElement) {}
		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};
