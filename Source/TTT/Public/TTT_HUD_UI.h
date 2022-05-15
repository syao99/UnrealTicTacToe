// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTTSystem.h"
#include "TTT_HUD_UI.generated.h"

/**
 * 
 */
UCLASS()
class UTTT_HUD_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void NewSwitchIsPlaying(bool bIsPlaying, bool bIsOPlayer);

	UFUNCTION(BlueprintImplementableEvent)
	void EndGame(ETileState State);

	UFUNCTION(BlueprintImplementableEvent)
	void NewUpdateStatusTextCurrentPlayer(bool bIsOPlayer, bool bIsGameActive);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FNewOnGridAdjustSignature, bool, bIsIncrementing );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FNewOnGameStartStopSignature );

	UPROPERTY(BlueprintAssignable)
	FNewOnGridAdjustSignature NewOnGridAdjust;

	UPROPERTY(BlueprintAssignable)
	FNewOnGameStartStopSignature NewOnGameStartStop;
};
