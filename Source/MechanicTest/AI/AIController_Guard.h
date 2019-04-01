// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIController_Guard.generated.h"


UCLASS()
class MECHANICTEST_API AAIController_Guard : public AAIController
{
	GENERATED_BODY()

public:
	AAIController_Guard();

	UPROPERTY(EditAnywhere, Category = AI)
	class UAISenseConfig_Sight* SightConfig = nullptr;

	UPROPERTY(EditAnywhere, Category = AI)
	class UAISenseConfig_Hearing* HearingConfig = nullptr;

	UPROPERTY(EditAnywhere, Category = AI)
	class UAIPerceptionComponent* PerceptionComp = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = AI)
	class UBlackboardComponent* BBComp = nullptr;

	void SenseStuff(AActor* Actor, FAIStimulus Stimulus);

private:
	virtual void Possess(APawn* InPawn) override;
	void SetPlayerPerception();

private:
	
	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTreeComponent* BTComp = nullptr;

	UBehaviorTree* BehaviourTree = nullptr;
	UBlackboardData* Blackboard = nullptr;
};
