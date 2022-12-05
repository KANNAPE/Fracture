// Fill out your copyright notice in the Description page of Project Settings.




#include "FractureSuit.h"

// Sets default values
AFractureSuit::AFractureSuit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFractureSuit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFractureSuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFractureSuit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

