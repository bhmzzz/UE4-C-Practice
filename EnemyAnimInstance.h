// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICETEMP_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float EnemySpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float EnemyDirection;
public:
	UFUNCTION(BlueprintCallable)
		void UpdateData();
};
