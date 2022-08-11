// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPlayerStateMode : uint8
{
	ENULLMODE,
	EWalk,
	ERun,
	EFight
};

UCLASS()
class PRACTICETEMP_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMainPlayerState();

	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;
    

	UPROPERTY()
		EPlayerStateMode CurrentPlayerMode;


public:
	UFUNCTION()
		void SetNULL();
	UFUNCTION()
		void SetWALK();
	UFUNCTION()
		void SetRUN();
	UFUNCTION()
		void SetFIGHT();

	
};
