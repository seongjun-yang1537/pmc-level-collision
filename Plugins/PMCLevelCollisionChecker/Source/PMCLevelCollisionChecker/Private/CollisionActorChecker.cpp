#include "CollisionActorChecker.h"

TArray<AActor*> FCollisionActorChecker::GetActorsByCollisionPreset(FName PresetName)
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	
	TArray<AActor*> Ret;

	if (GEditor && World)
	{
		const TArray<AActor*>& Actors = World->PersistentLevel->Actors;
		for (auto Actor : Actors)
		{
			if (Actor && IsCollisionPreset(Actor, PresetName))
			{
				Ret.Add(Actor);
			}
		}
	}
	
	return Ret;
}

bool FCollisionActorChecker::IsCollisionPreset(AActor* Actor, FName PresetName)
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
		if (CurrentPreset == PresetName)
		{
			return true;
		}
	}
	return false;
}