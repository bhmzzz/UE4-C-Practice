// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PracticeTempGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyDoor.generated.h"

UCLASS()
class PRACTICETEMP_API AMyDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* MyRootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* DoorMesh;

	APracticeTempGameModeBase* GameModeTemp;


	FTimerHandle handler;

	UWorld* world;


	FRotator DoorCurrentRotation;
	FRotator DoorTargetRotation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void OpenTheDoor(bool bResult);

	UFUNCTION(BlueprintImplementableEvent)
	void Test();

	UFUNCTION()
		void RotationDoorOpen();
	UFUNCTION()
		void RotationDoorClose();

};
