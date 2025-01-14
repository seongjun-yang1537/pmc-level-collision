#include "CollisionActorViewer.h"

#include "CollisionActorChecker.h"

void SCollisionActorViewer::Construct(const FArguments& InArgs)
{
	OnCheckCollision = InArgs._OnCheckCollision;
	OnCheckCollision->AddLambda([&](FName PresetName)
	{
		this->PresetName = PresetName;
	});
	
	ChildSlot
	[
		SNew(SButton)
		.OnClicked(this, &SCollisionActorViewer::OnClicked)
		.Content()
		[
			SNew(SImage)
			.Image(FSlateIcon(FAppStyle::GetAppStyleSetName(), "Level.VisibleIcon16x").GetIcon())
		]
	];
}

FReply SCollisionActorViewer::OnClicked()
{
	UpdateVisible();
	return FReply::Handled();
}

void SCollisionActorViewer::UpdateVisible()
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		return;
	}
	
	auto Actors = FCollisionActorChecker::GetActorsByCollisionPreset(PresetName);
	
	for (auto Actor : Actors)
	{
		DebugDrawActor(Actor);
	}
}

void SCollisionActorViewer::DebugDrawActor(AActor* Actor)
{
	UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World)
	{
		return;
	}

	UStaticMeshComponent* MeshComponent =
		Actor->FindComponentByClass<UStaticMeshComponent>();

	if (!MeshComponent || !MeshComponent->GetStaticMesh())
	{
		return;
	}
	
	const FStaticMeshRenderData* RenderData = MeshComponent->GetStaticMesh()->GetRenderData();
	if (!RenderData)
	{
		return;
	}

	auto DrawLine = [&](FVector a, FVector b)
	{
		DrawDebugLine(World, a, b, FColor::Red, false, 10, 0, 5.0f);
	};
	
	for (const FStaticMeshLODResources& LODResource : RenderData->LODResources)
	{
		const FIndexArrayView& Indices = LODResource.IndexBuffer.GetArrayView();
		const FPositionVertexBuffer& PositionBuffer = LODResource.VertexBuffers.PositionVertexBuffer;
		
		for (int32 i = 0; i < Indices.Num(); i += 3)
		{
			auto Vertex0_Local = FVector(PositionBuffer.VertexPosition(Indices[i]));
			auto Vertex1_Local = FVector(PositionBuffer.VertexPosition(Indices[i + 1]));
			auto Vertex2_Local = FVector(PositionBuffer.VertexPosition(Indices[i + 2]));
			
			FVector Vertex0_World = Actor->GetActorTransform().TransformPosition(Vertex0_Local);
			FVector Vertex1_World = Actor->GetActorTransform().TransformPosition(Vertex1_Local);
			FVector Vertex2_World = Actor->GetActorTransform().TransformPosition(Vertex2_Local);
			
			DrawLine(Vertex0_World, Vertex1_World);
			DrawLine(Vertex1_World, Vertex2_World);
			DrawLine(Vertex2_World, Vertex0_World);
		}
	}
}
