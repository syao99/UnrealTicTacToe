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

void UpdateGrid()
{

}
int32 AdjustGrid(bool bIsIncrementing)
{
	return 0;
}
bool AddPiece(bool IsOPlayer, int32 LocationIndex)
{
	return false;
}
void ResetPieces()
{

}
void StartStopGame(bool IsStarting)
{

}

ETileState CheckWinner(int32 StartFromIndex)
{
	return ETileState::Neutral;
}

bool GetAdjacentTile(int32 Index, int32 GridDimensions, ETileDirection Direction, int32* OutIndex)
{
	return false;
}

TArray<int32> GetCoordAdderFromDirection(ETileDirection Direction)
{
	TArray<int32> Arr;
	return Arr;
}

int32 GetMainArraysLastIndex(int32 GridDimensions)
{
	return 0;
}

int32 GetMainArraysLength(int32 GridDimensions)
{
	return 0;
}

bool ScanRowOrColumn(ETileState CompareTileState, int32 GridDimensions, bool bIsRows)
{
	return false;
}

bool ScanDiagonal(ETileState CompareTileState, int32 GridDimensions, bool bIsReversed)
{
	return false;
}

bool IsGameTied()
{
	return false;
}


TArray<int32> GetGridCoordsFromIndex(int32 Index, int32 GridDimensions)
{
	TArray<int32> Arr;
	return Arr;
}

int32 GetIndexFromGridCoords(int32 X, int32 Y, int32 GridDimensions)
{
	return 0;
}


float GetGridOffsetCenteringVal(int32 GridDimensions, float GridGap)
{
	return 0.f;
}

ETileState GetTileStateFromIsO(bool IsO)
{
	return ETileState::Neutral;
}
