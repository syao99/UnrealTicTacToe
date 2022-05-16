// Fill out your copyright notice in the Description page of Project Settings.


#include "TTT_HUD_UI.h"

void UTTT_HUD_UI::CallOnGridAdjust(bool bIsIncrementing)
{
	OnGridAdjust.Broadcast(bIsIncrementing);
}

void UTTT_HUD_UI::CallOnGameStartStop()
{
	OnGameStartStop.Broadcast();
}