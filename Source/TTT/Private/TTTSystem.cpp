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
	UpdateGrid();
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
	for (int32 i = 0; i < LastIndex; i++) {
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
	for (int32 i = 0; i < Meshes.Num(); i++) {
		if (Meshes[i])
		{
			if (IsValid(Meshes[i])) {
				Meshes[i]->Destroy();
				Meshes[i] = nullptr;
			}
		}
	}
	PieceCount = 0;
	for (int32 i = 0; i < TileState.Num(); i++) {
		TileState[i] = ETileState::Neutral;
	}
}
void ATTTSystem::StartStopGame(bool IsStarting)
{
	ResetPieces();
}

ETileState ATTTSystem::CheckWinner(int32 StartFromIndex)
{
	if (PieceCount >= GridDimensions) {
		ETileState CompareTileState = TileState[StartFromIndex];
		bool bIsWinner = false;
		bIsWinner = (
			ScanDiagonal(CompareTileState, GridDimensions, false) ||
			ScanDiagonal(CompareTileState, GridDimensions, true) ||
			ScanRowOrColumn(CompareTileState, GridDimensions, false) ||
			ScanRowOrColumn(CompareTileState, GridDimensions, true)
		);
		if (bIsWinner)
		{
			return CompareTileState;
		}
	}
	return ETileState::Neutral;
}

bool ATTTSystem::GetAdjacentTile(int32 Index, const int32 GridDim, ETileDirection Direction, int32& OutIndex)
{
	TArray<int32> GridCoords = GetGridCoordsFromIndex(Index, GridDim);
	TArray<int32> GridCoordAdder = GetCoordAdderFromDirection(Direction);
	GridCoords[0] += GridCoordAdder[0];
	GridCoords[1] += GridCoordAdder[1];
	OutIndex = GetIndexFromGridCoords(GridCoords[0], GridCoords[1], GridDim);
	bool bIsInRange = (
		UKismetMathLibrary::InRange_IntInt(GridCoords[0], 0, GridDim - 1, true, true) &&
		UKismetMathLibrary::InRange_IntInt(GridCoords[1], 0, GridDim - 1, true, true)
	);
	return bIsInRange;
}

TArray<int32> ATTTSystem::GetCoordAdderFromDirection(ETileDirection Direction) const
{
	TArray<int32> Coords;
	Coords.SetNum(2);
	switch (Direction)
	{
	case ETileDirection::Up:
		Coords[0] = 1;
		Coords[1] = 0;
	break;
	case ETileDirection::UpRight:
		Coords[0] = 1;
		Coords[1] = 1;
	break;
	case ETileDirection::Right:
		Coords[0] = 0;
		Coords[1] = 1;
	break;
	case ETileDirection::DownRight:
		Coords[0] = -1;
		Coords[1] = 1;
	break;
	case ETileDirection::Down:
		Coords[0] = -1;
		Coords[1] = 0;
	break;
	case ETileDirection::DownLeft:
		Coords[0] = -1;
		Coords[1] = -1;
	break;
	case ETileDirection::Left:
		Coords[0] = 0;
		Coords[1] = -1;
	break;
	case ETileDirection::UpLeft:
		Coords[0] = 1;
		Coords[1] = -1;
	break;
	}
	return Coords;
}

int32 ATTTSystem::GetMainArraysLastIndex(int32 GridDim) const
{
	return (GridDim ^ 2) - 1;
}

int32 ATTTSystem::GetMainArraysLength(int32 GridDim) const
{
	return GridDim ^ 2;
}

bool ATTTSystem::ScanRowOrColumn(ETileState CompareTileState, const int32 GridDim, bool bIsRows) const
{
	int32 LastIndex = GridDim - 1;
	int32 CurrentCount = 0;
	for (int32 i = 0; i < LastIndex; i++)
	{
		CurrentCount = 0;
		for (int32 j = 0; j < LastIndex; j++)
		{
			int32 X, Y;
			bIsRows ? X = i : X = j;
			bIsRows ? Y = j : Y = i;
			bool bIsMatchingTileState =
				TileState[GetIndexFromGridCoords(X, Y, GridDim)] == CompareTileState;
			if (bIsMatchingTileState)
			{
				CurrentCount++;
				if (CurrentCount >= GridDim)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool ATTTSystem::ScanDiagonal(ETileState CompareTileState, const int32 GridDim, bool bIsReversed) const
{
	int32 LastIndex = GridDim - 1;
	int32 CurrentCount = 0;
	for (int32 i = 0; i < LastIndex; i++)
	{
		int32 X, Y;
		X = i;
		bIsReversed ? Y = LastIndex - i : Y = i;
		bool bIsMatchingTileState =
			TileState[GetIndexFromGridCoords(X, Y, GridDim)] == CompareTileState;
		if (bIsMatchingTileState)
		{
			CurrentCount++;
			if (CurrentCount >= GridDim)
			{
				return true;
			}
		}

	}
	return false;
}

bool ATTTSystem::IsGameTied() const
{
	return PieceCount >= GetMainArraysLength(GridDimensions);
}


TArray<int32> ATTTSystem::GetGridCoordsFromIndex(int32 Index, const int32 GridDim) const
{
	TArray<int32> Coords;
	Coords.SetNum(2);
	Coords[0] = Index % GridDim;
	Coords[1] = Index / GridDim;
	return Coords;
}

int32 ATTTSystem::GetIndexFromGridCoords(int32 X, int32 Y, const int32 GridDim) const
{
	return X + (Y * GridDim);
}


float ATTTSystem::GetGridOffsetCenteringVal(const int32 GridDim, float GGap) const
{
	return ((GridDim - 1) * GGap) / 2;
}

ETileState ATTTSystem::GetTileStateFromIsO(bool bIsO) const
{
	if (bIsO) { return ETileState::O; }
	return ETileState::X;
}
