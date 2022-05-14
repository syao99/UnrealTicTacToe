// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
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
	//InitUI();
	//InitSystem();
	//UpdateCamera(3, 269.f);
}

// Called every frame
void ATTTPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATTTPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATTTPawn::InitUI()
{
	HUD_UI = InitUI_BP();
	//HUD_UI = CreateWidget<UTTT_HUD_UI>(GetWorld(), UTTT_HUD_UI::StaticClass());
	if (HUD_UI != nullptr) { HUD_UI->AddToViewport(); }
	PlayerController->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, HUD_UI, EMouseLockMode::DoNotLock, false);
	//HUD_UI->NewOnGridAdjust.BindRaw();
	// todo: figure out dumbfuck docs & delegates
}
/*
void ATTTPawn::InitSystem()
{

}
void ATTTPawn::UpdateCamera(int32 GridDimensions, float DistanceMultiplier)
{

}

void ATTTPawn::GameStartStop()
{

}
void ATTTPawn::InputActionSelect()
{

}
void ATTTPawn::GridAdjust(bool IsIncrementing)
{

}
*/
bool ATTTPawn::ClickTraceForTile(int32& OutIndex)
{
	FVector OutWorldLocation;
	FVector OutWorldDirection;
	if (PlayerController->DeprojectMousePositionToWorld(OutWorldLocation, OutWorldDirection)) { 
		
	}
	return false;
}
