// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerState.h"

AMainPlayerState::AMainPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainPlayerState::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AMainPlayerState::BeginPlay()
{
	Super::BeginPlay();
	CurrentPlayerMode = EPlayerStateMode::ENULLMODE;
	
}

void AMainPlayerState::SetNULL()
{
	CurrentPlayerMode = EPlayerStateMode::ENULLMODE;
}

void AMainPlayerState::SetWALK()
{
	CurrentPlayerMode = EPlayerStateMode::EWalk;
}

void AMainPlayerState::SetRUN()
{
	CurrentPlayerMode = EPlayerStateMode::ERun;
}

void AMainPlayerState::SetFIGHT()
{
	CurrentPlayerMode = EPlayerStateMode::EFight;
}
