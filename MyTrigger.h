// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "PracticeTempGameModeBase.h"

#include "MyDoor.h"
#include "MyTrigger.generated.h"

UCLASS()
class PRACTICETEMP_API AMyTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTrigger();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* MyTrigger;

	AMainCharacter* PlayerTemp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APracticeTempGameModeBase* GameModeTemp;

	void DoExcuted(bool bResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
