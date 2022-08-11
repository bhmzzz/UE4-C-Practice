// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTrigger.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyTrigger::AMyTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("MyTrigger"));
	RootComponent = MyTrigger;

}

void AMyTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerTemp =  Cast<AMainCharacter>(OtherActor);
	if (PlayerTemp)
	{
		DoExcuted(true);
	}
}

void AMyTrigger::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerTemp = Cast<AMainCharacter>(OtherActor);
	if (PlayerTemp)
		DoExcuted(false);
}

// Called when the game starts or when spawned
void AMyTrigger::BeginPlay()
{
	Super::BeginPlay();
	MyTrigger->OnComponentBeginOverlap.AddDynamic(this,&AMyTrigger::BeginOverlap);
	MyTrigger->OnComponentEndOverlap.AddDynamic(this,&AMyTrigger::EndOverlap);
}

void AMyTrigger::DoExcuted(bool bResult)
{
	UWorld* MyWorld = GetWorld();  //不能直接获取到GameMode必须通过获取到world来完成。
	if (MyWorld)
	{
		GameModeTemp = Cast<APracticeTempGameModeBase>(UGameplayStatics::GetGameMode(MyWorld));
	}
	if (GameModeTemp)
	{
		if (GameModeTemp->myDelegate.IsBound())
		{
			GameModeTemp->myDelegate.Broadcast(bResult);
		}
	}
}

// Called every frame
void AMyTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

