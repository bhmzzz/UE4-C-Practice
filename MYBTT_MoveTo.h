// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MYBTT_MoveTo.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICETEMP_API UMYBTT_MoveTo : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UMYBTT_MoveTo();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
