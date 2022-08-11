// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimNotify.h"
#include "MainCharacter.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/StaticMeshComponent.h"

UMyAnimNotify::UMyAnimNotify()
{
}

void UMyAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	UE_LOG(LogTemp, Warning, TEXT("TEST"));
	PlayerTemp = Cast<AMainCharacter>(MeshComp->GetOwner());
	if (PlayerTemp)
	{
		UStaticMeshComponent* WeaponMesh = PlayerTemp->GetWeapon();
		WeaponMesh->AttachTo(PlayerTemp->GetMesh(), FName("EquipWeapon"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT"));
	}
}
