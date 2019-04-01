// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_PatrolRoute.h"

TArray<AActor*> UAC_PatrolRoute::GetPatrolPoints() const
{
	return PatrolPoints;
}
