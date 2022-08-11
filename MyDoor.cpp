// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDoor.h"

// Sets default values
AMyDoor::AMyDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	RootComponent = MyRootComponent;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void AMyDoor::BeginPlay()
{
	Super::BeginPlay();

	world = GetWorld();
	GameModeTemp = Cast<APracticeTempGameModeBase>(UGameplayStatics::GetGameMode(world));
	if (GameModeTemp)
	{
		GameModeTemp->myDelegate.AddUObject(this, &AMyDoor::OpenTheDoor);
	}

	DoorCurrentRotation = DoorMesh->GetRelativeRotation();
	DoorTargetRotation = DoorMesh->GetRelativeRotation().Add(0, 90, 0);
	
}

// Called every frame
void AMyDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyDoor::OpenTheDoor(bool bResult)
{
	if (bResult)
	{
		GetWorldTimerManager().SetTimer(handler, this, &AMyDoor::RotationDoorOpen, world->GetDeltaSeconds(), true);
	}
	if (bResult == false)
	{
		GetWorldTimerManager().SetTimer(handler, this, &AMyDoor::RotationDoorClose, world->GetDeltaSeconds(), true);
	}
}

void AMyDoor::RotationDoorOpen()
{
	DoorMesh->SetRelativeRotation(UKismetMathLibrary::RInterpTo(DoorMesh->GetRelativeRotation(), DoorTargetRotation, world->GetDeltaSeconds(), 10));
	if ((DoorMesh->GetRelativeRotation() - DoorTargetRotation).Equals(FRotator(0,0,0), 0.1))
	{
		UE_LOG(LogTemp, Warning, TEXT("Test1!"));
		GetWorldTimerManager().ClearTimer(handler);
	}
}

void AMyDoor::RotationDoorClose()
{
	DoorMesh->SetRelativeRotation(UKismetMathLibrary::RInterpTo(DoorMesh->GetRelativeRotation(), DoorCurrentRotation, world->GetDeltaSeconds(), 10));
	if ((DoorMesh->GetRelativeRotation() - DoorCurrentRotation).Equals(FRotator(0, 0, 0), 0.1))
	{
		UE_LOG(LogTemp, Warning, TEXT("Test2!"));
		GetWorldTimerManager().ClearTimer(handler);
	}
}

