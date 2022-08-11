// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacter.h"
#include "MyAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class PRACTICETEMP_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance();

protected:

	AMainCharacter* MainCharacter;

	UPROPERTY(BlueprintReadOnly)
		float speed;

	UPROPERTY(BlueprintReadOnly)
		float direction;

	UFUNCTION(BlueprintCallable)
		void updateAnimData();

private:


	
};
