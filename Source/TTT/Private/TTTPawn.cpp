// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTPawn.h"
#include "TTTSystem.h"
#include "TTT_HUD_UI.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATTTPawn::ATTTPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(Root);
	Camera->SetRelativeTransform(FTransform(FRotator(-90.f, 0.f, 0.f),FVector(0.f, 0.f, 1000.f),FVector(1.f, 1.f, 1.f)));
}

// Called when the game starts or when spawned
void ATTTPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (InputComponent)
	{
		InputComponent->BindAction(
			"Select",
			IE_Pressed,
			this,
			&ATTTPawn::InputActionSelect
		);
	}
	InitUI();
	InitSystem();
	UpdateCamera(3, GridDistanceMultiplier);
}

// Called every frame
void ATTTPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATTTPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void ATTTPawn::InitUI()
{
	HUD_UI = InitUI_BP();
	if (HUD_UI == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: TTTPawn must be instantiated as BP, with InitUI_BP() implemented and returning a valid UI pointer."));
		return;
	}
	if (HUD_UI != nullptr) { HUD_UI->AddToViewport(); }
	PlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, HUD_UI, EMouseLockMode::DoNotLock, false);
	HUD_UI->OnGridAdjust.AddDynamic(this, &ATTTPawn::GridAdjust);
	HUD_UI->OnGameStartStop.AddDynamic(this, &ATTTPawn::GameStartStop);
	
}

void ATTTPawn::InitSystem()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATTTSystem::StaticClass(), OutActors);
	TTTSystem = Cast<ATTTSystem>(OutActors[0]);
}

void ATTTPawn::UpdateCamera(int32 GridDimensions, float DistanceMultiplier)
{
	float NewZ = GridDimensions * DistanceMultiplier;
	Camera->SetRelativeLocation(FVector(0.f, 0.f, NewZ));
}

void ATTTPawn::GameStartStop()
{
	UE_LOG(LogTemp, Display, TEXT("GameStartStop"));
	bIsGameActive = !bIsGameActive;
	HUD_UI->SwitchIsPlaying(bIsGameActive, bIsCurrentlyOPlayer);
	TTTSystem->StartStopGame(bIsGameActive);
	bIsCurrentlyOPlayer = false;
}

void ATTTPawn::InputActionSelect()
{
	UE_LOG(LogTemp, Display, TEXT("Click"));
	if (bIsGameActive)
	{
		UE_LOG(LogTemp, Display, TEXT("IsGameActive True"));
		int32 TraceIndex = -1;
		if (ClickTraceForTile(TraceIndex))
		{
			UE_LOG(LogTemp, Display, TEXT("ClickTraceForTile: %d"),TraceIndex);
			if (TTTSystem->AddPiece(bIsCurrentlyOPlayer, TraceIndex))
			{
				ETileState TState = TTTSystem->CheckWinner(TraceIndex);
				switch (TState)
				{
					case ETileState::Neutral:
						if (TTTSystem->IsGameTied()) {
							EndGame(TState);
						}
						else
						{
							bIsCurrentlyOPlayer = !bIsCurrentlyOPlayer;
							HUD_UI->UpdateStatusTextCurrentPlayer(bIsCurrentlyOPlayer, true);
						}
					break;
					case ETileState::X:
						EndGame(TState);
					break;
					case ETileState::O:
						EndGame(TState);
					break;
				}
			}
		}
	}
}

void ATTTPawn::EndGame(ETileState State)
{
	HUD_UI->EndGame(State);
	bIsGameActive = false;
}

void ATTTPawn::GridAdjust(bool bIsIncrementing)
{
	//UE_LOG(LogTemp, Display, TEXT("Pawn GridAdjust %s"), bIsIncrementing ? TEXT("True") : TEXT("False"));
	int32 GridDim = TTTSystem->AdjustGrid(bIsIncrementing);
	UpdateCamera(GridDim, GridDistanceMultiplier);
}

bool ATTTPawn::ClickTraceForTile(int32& OutIndex)
{
	FVector WorldLocation;
	FVector WorldDirection;
	if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) {
		FVector Start = WorldLocation;
		FVector End = WorldLocation + (WorldDirection * 5000);
		FHitResult HitData;
		/*DrawDebugLine(
			GetWorld(),
			Start,
			End,
			FColor(255,0,0,0),
			true,
			5.f,
			0u,
			3.f
		);*/
		if (GetWorld()->LineTraceSingleByProfile(
			HitData,
			Start,
			End,
			FName(TEXT("TTT")),
			FCollisionQueryParams(false)
		))
		{
			OutIndex = HitData.Item;
			return true;
		}
	}
	return false;
}
