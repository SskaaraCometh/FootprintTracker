// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_Guard.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "ConstructorHelpers.h"

AAIController_Guard::AAIController_Guard()
{
	//Initialise BB and BT
	SetPlayerPerception();

	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Comp"));
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour tree Comp"));

	//Set the references of the BB and BT
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviourTreeRef(TEXT("BehaviorTree'/Game/NPC/AI/BT_AIGuard.BT_AIGuard'"));
	if (BehaviourTreeRef.Object)
	{
		BehaviourTree = BehaviourTreeRef.Object;
		UE_LOG(LogTemp, Warning, TEXT("BT1 init"));
	}

	ConstructorHelpers::FObjectFinder<UBlackboardData> BlackboardDataRef(TEXT("BlackboardData'/Game/NPC/AI/BB_AIGuard.BB_AIGuard'"));
	if (BlackboardDataRef.Object)
	{
		Blackboard = BlackboardDataRef.Object;
		UE_LOG(LogTemp, Warning, TEXT("BB1 init"));
	}
}

void AAIController_Guard::SenseStuff(AActor * Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		BBComp->SetValueAsObject("Enemy", Actor);
	}
	else
	{
		BBComp->ClearValue("Enemy");
	}
}

void AAIController_Guard::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	uint8 WaypointKeyID = BBComp->GetKeyID("Waypoint");
	uint8 IndexID = BBComp->GetKeyID("NextWaypointIndex");
	uint8 EnemyID = BBComp->GetKeyID("Enemy");

	RunBehaviorTree(BehaviourTree);
	UseBlackboard(Blackboard, BBComp);
	BTComp->StartTree(*BehaviourTree);
}

void AAIController_Guard::SetPlayerPerception()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

	SightConfig->SightRadius = 500;
	SightConfig->LoseSightRadius = 550.f;
	SightConfig->PeripheralVisionAngleDegrees = 140.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	PerceptionComp->ConfigureSense(*SightConfig);

	UE_LOG(LogTemp, Warning, TEXT("Init Perception"));
}