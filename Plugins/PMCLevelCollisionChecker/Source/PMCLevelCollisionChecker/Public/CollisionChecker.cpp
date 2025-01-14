#include "CollisionChecker.h"

FReply FCollisionChecker::Hello()
{
	UE_LOG(LogTemp, Log, TEXT("Hello"));
	return FReply::Handled();
}
