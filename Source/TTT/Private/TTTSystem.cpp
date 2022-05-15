// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTSystem.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATTTSystem::ATTTSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Grid = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));

}

// Called when the game starts or when spawned
void ATTTSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATTTSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATTTSystem::UpdateGrid()
{
	CurrentInstances.Reset();
	Meshes.Reset();
	TileState.Reset();
	Grid->ClearInstances();
	float GridOffsetVal = GetGridOffsetCenteringVal(GridDimensions, GridGap);
	int32 LastIndex = GetMainArraysLastIndex(GridDimensions);
	for (int i = 0; i < LastIndex; i++) {
		TArray<int32> GridCoords = GetGridCoordsFromIndex(i, GridDimensions);
		float LocationX = (GridCoords[0] * GridGap) - GridOffsetVal;
		float LocationY = (GridCoords[1] * GridGap) - GridOffsetVal;
		FTransform NewInst = FTransform(
			FRotator(0.f, 0.f, 0.f),
			FVector(LocationX, LocationY, 0.f),
			FVector(1.f, 1.f, 1.f)
		);
		CurrentInstances.Add(NewInst);
	}
	Grid->AddInstances(CurrentInstances,false);
	Meshes.SetNum(LastIndex);
	TileState.SetNum(LastIndex);
}
int32 ATTTSystem::AdjustGrid(bool bIsIncrementing)
{
	int32 Adder = 0;
	bIsIncrementing ? Adder = 1 : Adder = -1;
	GridDimensions += UKismetMathLibrary::Clamp(Adder, 3, 10);
	UpdateGrid();
	return GridDimensions;
}
bool ATTTSystem::AddPiece(bool bIsOPlayer, int32 LocationIndex)
{
	bool bIsTileStateNeutral = (TileState[LocationIndex] == ETileState::Neutral);
	if (bIsTileStateNeutral) {
		TileState[LocationIndex] = GetTileStateFromIsO(bIsOPlayer);
	}
	else { return false; }
	AStaticMeshActor* CurrentMesh = GetWorld()->SpawnActor<AStaticMeshActor>(
		AStaticMeshActor::StaticClass(),
		CurrentInstances[LocationIndex]
	);
	CurrentMesh->SetMobility(EComponentMobility::Movable);
	UStaticMesh* PlayerMesh;
	bIsOPlayer ? PlayerMesh = MeshO : PlayerMesh = MeshX;
	CurrentMesh->GetStaticMeshComponent()->SetStaticMesh(PlayerMesh);
	Meshes[LocationIndex] = CurrentMesh;
	PieceCount++;
	return false;
}
void ATTTSystem::ResetPieces()
{

}
void ATTTSystem::StartStopGame(bool IsStarting)
{
	return;
}

ETileState ATTTSystem::CheckWinner(int32 StartFromIndex)
{
	return ETileState::Neutral;
}

bool ATTTSystem::GetAdjacentTile(int32 Index, int32 GridDim, ETileDirection Direction, int32* OutIndex)
{
	return false;
}

TArray<int32> ATTTSystem::GetCoordAdderFromDirection(ETileDirection Direction)
{
	TArray<int32> Arr;
	return Arr;
}

int32 ATTTSystem::GetMainArraysLastIndex(int32 GridDim)
{
	return 0;
}

int32 ATTTSystem::GetMainArraysLength(int32 GridDim)
{
	return 0;
}

bool ATTTSystem::ScanRowOrColumn(ETileState CompareTileState, int32 GridDim, bool bIsRows)
{
	return false;
}

bool ATTTSystem::ScanDiagonal(ETileState CompareTileState, int32 GridDim, bool bIsReversed)
{
	return false;
}

bool ATTTSystem::IsGameTied()
{
	return false;
}


TArray<int32> ATTTSystem::GetGridCoordsFromIndex(int32 Index, int32 GridDim)
{
	TArray<int32> Arr;
	return Arr;
}

int32 ATTTSystem::GetIndexFromGridCoords(int32 X, int32 Y, int32 GridDim)
{
	return 0;
}


float ATTTSystem::GetGridOffsetCenteringVal(int32 GridDim, float GGap)
{
	return 0.f;
}

ETileState ATTTSystem::GetTileStateFromIsO(bool IsO)
{
	return ETileState::Neutral;
}
