// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "TTT_HUD_UI.h"
#include "TTTSystem.h"
#include "TTTPawn.generated.h"

UCLASS()
class ATTTPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATTTPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	USceneComponent* Root;
	UCameraComponent* Camera;

	UTTT_HUD_UI* HUD_UI;
	ATTTSystem* TTTSystem;

	bool IsGameActive = false;
	bool IsCurrentlyOPlayer = false;

public:
	void InitUI();
	void InitSystem();
	void UpdateCamera(int32 GridDimensions, float DistanceMultiplier);

	void GameStartStop();
	void InputActionSelect();
	void GridAdjust(bool IsIncrementing);

	FIndexSuccessInfo ClickTraceForTile();
};