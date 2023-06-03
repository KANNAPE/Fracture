// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FractureCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFracture, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

class USkeletalMeshComponent;
class UCameraComponent;
class UElytraMovementComponent;
class AFractureSuit;
class ARewindActor;

UCLASS(config=Game)
class FRACTURE_API AFractureCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	UElytraMovementComponent* ElytraMovementComponent;

	// For now, we'll place the suit in the level, and we'll switch the possessed pawn when calling SwitchMode
	UPROPERTY(VisibleAnywhere)
	AFractureSuit* Suit;

public:
	AFractureCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	// Move
	void MoveForward(float Val);
	void MoveRight(float Val);

	// Shoot
	void OnPrimaryAction();

	// Sprint
	void Sprint();
	void StopSprinting();

	// Crouch
	void ToggleCrouching();

	// Fly (basic method)
	void SwitchMode();

	// Fly (movement mode method)
	void ToggleFlying();

	// Rewind
	void TriggerRewind();

public:
	FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	FORCEINLINE UElytraMovementComponent* GetElytraMovementComponent() const { return ElytraMovementComponent; }

	FCollisionQueryParams GetIgnoreCharacterParams() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float TurnRateGamepad;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;

	// Rewind
	UPROPERTY()
	ARewindActor* RewindCube;
};
