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
	UFUNCTION(BlueprintCallable)
	void SwitchIsPlaying(bool bIsPlaying, bool bIsOPlayer);

	UFUNCTION(BlueprintCallable)
	void EndGame(ETileState State);

	UFUNCTION(BlueprintCallable)
	void UpdateStatusTextCurrentPlayer(bool bIsOPlayer, bool bIsGameActive);
};
