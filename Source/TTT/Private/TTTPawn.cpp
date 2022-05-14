// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTPawn.h"
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

