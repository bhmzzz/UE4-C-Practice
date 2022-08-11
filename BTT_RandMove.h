// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_RandMove.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICETEMP_API UBTT_RandMove : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_RandMove();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
