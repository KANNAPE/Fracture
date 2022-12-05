// Copyright (c) 2022 Thomas Berger. Project published under MIT License.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FractureSuit.generated.h"

UCLASS()
class FRACTURE_API AFractureSuit : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class AFractureCharacter* Character;

	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent* Driver;

	UPROPERTY(EditAnywhere)
	float AirControl = 2500.f;
	
	UPROPERTY(EditAnywhere)
	float ThrottleAmount = 5000.f;

	void ComputeSpeed();

public:
	// Sets default values for this pawn's properties
	AFractureSuit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SwitchToGroundMode();

	virtual void AddControllerYawInput(float Val) override;
	virtual void AddControllerPitchInput(float Val) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
