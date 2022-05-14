// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTSystem.h"

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
	
}

// Called every frame
void ATTTSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

