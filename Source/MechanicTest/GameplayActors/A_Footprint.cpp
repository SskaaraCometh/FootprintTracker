// Fill out your copyright notice in the Description page of Project Settings.

#include "A_Footprint.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/GameFramework/Character.h"
#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "EngineUtils.h"

// Sets default values
AA_Footprint::AA_Footprint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Footprint = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Comp"));

	//SpawnObject();
}

void AA_Footprint::SpawnObject()
{
	if (PlayerCharacter->GetVelocity() != FVector(0.0, 0.0, 0.0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Init Spawn Object"));
	}
}
