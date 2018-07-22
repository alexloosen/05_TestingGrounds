// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
//#include "PatrollingGuard.h" // TODO Remove coupling
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO Protect against no patrol route component

	// Get Patrol Points
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute))
	{
		return EBTNodeResult::Failed;
	}

	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

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
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}