// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h" // TODO Remove coupling

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Patrol Points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	if (PatrolPoints.Num() > 0)
	{
		// Set next waypoint
		auto BlackbordComp = OwnerComp.GetBlackboardComponent();
		auto Index = BlackbordComp->GetValueAsInt(IndexKey.SelectedKeyName);
		BlackbordComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

		// Cycle Index
		auto NextIndex = (Index + 1) % PatrolPoints.Num();
		BlackbordComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	}

	return EBTNodeResult::Succeeded;
}