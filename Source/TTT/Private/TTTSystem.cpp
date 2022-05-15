// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTSystem.h"

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

}
int32 ATTTSystem::AdjustGrid(bool bIsIncrementing)
{
	return 0;
}
bool ATTTSystem::AddPiece(bool IsOPlayer, int32 LocationIndex)
{
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
