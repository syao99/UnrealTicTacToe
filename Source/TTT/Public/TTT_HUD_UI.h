// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TTTSystem.h"
#include "TTT_HUD_UI.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGridAdjustSignature, bool, bIsIncrementing);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStartStopSignature);

UCLASS()
class UTTT_HUD_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void NewSwitchIsPlaying(bool bIsPlaying, bool bIsOPlayer);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EndGame(ETileState State);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void NewUpdateStatusTextCurrentPlayer(bool bIsOPlayer, bool bIsGameActive);

public:
	UPROPERTY(BlueprintAssignable)
	FOnGridAdjustSignature OnGridAdjust;

	UPROPERTY(BlueprintAssignable)
	FOnGameStartStopSignature OnGameStartStop;

	UFUNCTION(BlueprintCallable)
	void CallOnGridAdjust(bool bIsIncrementing);

	UFUNCTION(BlueprintCallable)
	void CallOnGameStartStop();
};
