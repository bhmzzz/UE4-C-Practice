// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

UMyAnimInstance::UMyAnimInstance()
{
}

void UMyAnimInstance::updateAnimData()
{
    MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	if (MainCharacter)
	{
		speed = MainCharacter->GetVelocity().Size();
		direction = CalculateDirection(MainCharacter->GetVelocity(), MainCharacter->GetBaseAimRotation());
	}
}

