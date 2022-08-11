// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "EnemyCharacter.h"


void UEnemyAnimInstance::UpdateData()
{
	AEnemyCharacter* owner = Cast<AEnemyCharacter>(TryGetPawnOwner());
	EnemySpeed = owner->GetVelocity().Size();
}

