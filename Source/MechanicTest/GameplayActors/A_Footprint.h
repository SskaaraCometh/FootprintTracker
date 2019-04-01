// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Footprint.generated.h"

class USphereComponent;
class ACharacter;
class UCharacterMovementComponent;

UCLASS()
class MECHANICTEST_API AA_Footprint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Footprint();

	USphereComponent* Footprint = nullptr;
	TArray<USphereComponent*> CollisionArray;
	ACharacter* PlayerCharacter = nullptr;

protected:


private:

	void SpawnObject();

};
