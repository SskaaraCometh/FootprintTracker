// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_ChooseNextWaypoint.h"
#include "AC_PatrolRoute.h"
#include "AI_Guard.h"
#include "AIController_Guard.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Classes/BehaviorTree/BlackboardComponent.h"

//EBTNodeResult::Type UBTT_ChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	//Find Pawn
//	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
//	UAC_PatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UAC_PatrolRoute>();
//	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();
//
//	if (PatrolPoints.Num() == 0)
//	{
//		EBTNodeResult::Failed;
//	}
//
//	//Get blackboard
//	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
//	//Set keys
//	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
//	//Get Key
//	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
//
//	//Cycle Index
//	int CycleIndex = (Index + 1) % PatrolPoints.Num();
//	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, CycleIndex);
//
//	 return EBTNodeResult::Succeeded;
//
//	
//}
//
//EBTNodeResult::Type UBTT_ChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	//Find pawn + Waypoint route
//	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
//	UAC_PatrolRoute* PartrolPoints = ControlledPawn->FindComponentByClass<UAC_PatrolRoute>();
//	TArray<AActor*> PointsArray = PartrolPoints->GetPatrolPoints();
//
//	if (PointsArray.Num() == 0)
//	{
//		EBTNodeResult::Failed;
//	}
//
//	//Get blackboard data
//	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
//	// get Keys
//	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
//	//set Key
//	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PointsArray[Index]);
//
//	//Cycle Index
//	int CycleIndex = (Index + 1) % PointsArray.Num();
//	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, CycleIndex);
//
//	EBTNodeResult::Succeeded;
//}

EBTNodeResult::Type UBTT_ChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Pawn
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	//Patrol Points
	UAC_PatrolRoute* PatrolPoints = ControlledPawn->FindComponentByClass<UAC_PatrolRoute>();

	TArray<AActor*> PatrolArray = PatrolPoints->GetPatrolPoints();

	if (PatrolArray.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	//Get Blackboard Component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	//Get Blackboard Keys
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto Objects = BlackboardComp->GetValueAsObject(WaypointKey.SelectedKeyName);

	//Set Keys
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolArray[Index]);

	//Iterate
	int CycleIndex = (Index + 1) % PatrolArray.Num();

	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, CycleIndex);
	 
	return EBTNodeResult::Succeeded;
}