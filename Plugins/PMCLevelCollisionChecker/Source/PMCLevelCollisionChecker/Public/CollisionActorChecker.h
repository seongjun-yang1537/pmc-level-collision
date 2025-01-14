#pragma once

#include "CoreMinimal.h"

static class FCollisionActorChecker
{
public:
	static TArray<AActor*> GetActorsByCollisionPreset(FName PresetName);

	static bool IsCollisionPreset(AActor* Actor, FName PresetName);
};
