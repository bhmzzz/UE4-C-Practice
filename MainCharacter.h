// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "MainPlayerState.h"
#include "MainCharacter.generated.h"

UCLASS(Blueprintable)
class PRACTICETEMP_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* camera1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USpringArmComponent* CameraArm;

	UPROPERTY(Editanywhere,BlueprintReadWrite,Category = "MontageToPlay")
		UAnimMontage* PlayerAttackAnim;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "MontageToPlay")
		UAnimMontage* PlayerEquipAnim;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "BOOL")
		bool bIsEquip;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "BOOL")
		bool bIsAttacking;


	void InitPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FOnMontageEnded MontageEndedDelegate;

	FName MontageNeedToJump;

	AMainPlayerState* PlayerStateTemp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* WeaponMesh;

	UPROPERTY()
		bool bIsHit;
	UPROPERTY(BlueprintReadWrite, Category = "CheckAttack")
		TArray<FVector> socketLocation;
	UPROPERTY(BlueprintReadWrite, Category = "CheckAttack")
		TArray<FName> socketsName;

	UPROPERTY()
		TArray<TEnumAsByte<EObjectTypeQuery> > TargetTypes;

	UPROPERTY()
		FTimerHandle handler;
	UPROPERTY()
		TArray<class AEnemyCharacter*> TargetEnemy;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move_Forward(float value);
	void Move_Right(float value);


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PlayerTurn(float value);
	void PlayerLookUp(float value);
	void PlayerJumpStart();
	void PlayerJumpEnd();

	UFUNCTION()
		void PlayerAttack();
	UFUNCTION()
		void EquipWeapon();
	UFUNCTION()
		void AttackEnded(UAnimMontage* Montage, bool bValue);
	UFUNCTION()
		void EquipEnded(UAnimMontage* montage, bool bInterrupted);
	UFUNCTION()
		void AttackCheck();
	UFUNCTION()
		void InitSocketLocation();
	UFUNCTION()
		void AddTargetEnemy(TArray<FHitResult> OutHits);
	UFUNCTION()
		void ClearTargetEnemy();
	UFUNCTION()
		UStaticMeshComponent* GetWeapon();

	UFUNCTION()
		void SetNULL();
	UFUNCTION()
		void SetWALK();
	UFUNCTION()
		void SetRUN();
	UFUNCTION()
		void SetFIGHT();
	UFUNCTION()
		void CombatNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
		void CombatNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

};
