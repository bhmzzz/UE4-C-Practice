// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MYBTD_CheckDistance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICETEMP_API UMYBTD_CheckDistance : public UBTDecorator
{
	GENERATED_BODY()
public:
		virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
		UPROPERTY(EditAnywhere, Category = LimitDis)
			float fDis;
};
