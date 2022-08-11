// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PracticeTempGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMyDelegate, bool);


/**
 * 
 */

UCLASS()
class PRACTICETEMP_API APracticeTempGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APracticeTempGameModeBase();

	FMyDelegate myDelegate;

protected:

	virtual void BeginPlay() override;




public:

	virtual void Tick(float DeltaTime) override;


private:

	
};
