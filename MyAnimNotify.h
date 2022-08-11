// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MyAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICETEMP_API UMyAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UMyAnimNotify();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	class AMainCharacter* PlayerTemp;
};
