// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "TTTSystem.generated.h"


UENUM()
enum ETileState
{
	Neutral UMETA(DisplayName = "Neutral"),
	X UMETA(DisplayName = "X"),
	O UMETA(DisplayName = "O"),
};

UENUM()
enum ETileDirection
{
	Up UMETA(DisplayName = "Up"),
	UpRight UMETA(DisplayName = "UpRight"),
	Right UMETA(DisplayName = "Right"),
	DownRight UMETA(DisplayName = "DownRight"),
	Down UMETA(DisplayName = "Down"),
	DownLeft UMETA(DisplayName = "DownLeft"),
	Left UMETA(DisplayName = "Left"),
	UpLeft UMETA(DisplayName = "UpLeft"),
};

/*
USTRUCT()
struct FIndexSuccessInfo
{
	GENERATED_BODY()
	int32 OutIndex;
	bool bIsInRange;
};
*/

UCLASS()
class ATTTSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATTTSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UInstancedStaticMeshComponent* Grid;
	TArray<AStaticMeshActor*> Meshes;
	UStaticMesh* MeshO;
	UStaticMesh* MeshX;

	TArray<FTransform> CurrentInstances;
	TArray<TEnumAsByte<ETileState>> TileState;
	int32 PieceCount = 0;
	
	int32 GridDimensions = 3;
	float GridGap = 240.f;
	
public:
	void UpdateGrid();
	int32 AdjustGrid(bool bIsIncrementing);
	bool AddPiece(bool IsOPlayer, int32 LocationIndex);
	void ResetPieces();
	void StartStopGame(bool IsStarting);

public:
	ETileState CheckWinner(int32 StartFromIndex);

	bool GetAdjacentTile(int32 Index, const int32 GridDim, ETileDirection Direction, int32& OutIndex);
	TArray<int32> GetCoordAdderFromDirection(ETileDirection Direction) const;
	int32 GetMainArraysLastIndex(int32 GridDim) const;
	int32 GetMainArraysLength(int32 GridDim) const;
	bool ScanRowOrColumn(ETileState CompareTileState, const int32 GridDim, bool bIsRows) const;
	bool ScanDiagonal(ETileState CompareTileState, const int32 GridDim, bool bIsReversed) const;
	bool IsGameTied() const;

	TArray<int32> GetGridCoordsFromIndex(int32 Index, const int32 GridDim) const;
	int32 GetIndexFromGridCoords(int32 X, int32 Y, const int32 GridDim) const;

	float GetGridOffsetCenteringVal(const int32 GridDim, const float GGap) const;
	ETileState GetTileStateFromIsO(bool bIsO) const;

};