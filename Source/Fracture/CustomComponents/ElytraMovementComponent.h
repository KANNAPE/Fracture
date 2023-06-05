// Copyright (c) 2022 Thomas Berger. Project published under MIT License.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ElytraMovementComponent.generated.h"

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_None			UMETA(Hidden),
	CMOVE_Flying		UMETA(DisplayName = "Jet Flying"),
	CMOVE_MAX			UMETA(Hidden)
};

/**
 * 
 */

// based on the tutorial of youtube channel delgoodie
// https://www.youtube.com/watch?v=17D4SzewYZ0 33:31
UCLASS()
class FRACTURE_API UElytraMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	class FSavedMove_FractureCharacter : public FSavedMove_Character
	{
		typedef FSavedMove_Character Super;

		// Saved Flag
		uint8 Saved_bWantsToSprint:1;
		uint8 Saved_bPrevWantsToCrouch:1;

		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};
	
	class FNetworkPredictionData_Client_FractureCharacter : public FNetworkPredictionData_Client_Character
	{
	public:
		FNetworkPredictionData_Client_FractureCharacter(const UElytraMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		virtual FSavedMovePtr AllocateNewMove() override;
	};

public:
	UElytraMovementComponent();

	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	// Flying temp
	bool IsFlying() const;
	void PhysFlying(float DeltaTime, int32 Iterations);

	UFUNCTION()
	void TrySwitchMode();

	// Sprint
	void SprintPressed();
	void SprintReleased();

	// Crouch
	void CrouchPressed();

	virtual bool CanCrouchInCurrentState() const override;

	// Custom movement mode getter
	UFUNCTION(BlueprintPure)
	bool IsCustomMovementMode(ECustomMovementMode InCustomMovementMode) const;


	// Parameters
	UPROPERTY(EditDefaultsOnly, Category = "Sprinting") 
	float Sprint_MaxWalkSpeed = 1000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Sprinting") 
	float Walk_MaxWalkSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Flying")
	float Flying_MaxPropulsionForce = 50.f;
	UPROPERTY(EditDefaultsOnly, Category = "Flying")
	float Flying_VelocityLerpTime = .2f;

	UPROPERTY(Transient) class AFractureCharacter* FractureCharacterOwner;

	// Safe booleans
	bool Safe_bWantsToSprint;
	bool Safe_bPrevWantsToCrouch;

	// Temp
	ECustomMovementMode CMovementMode;
	
protected:
	virtual void InitializeComponent() override;
	
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	// Handles all the physics for the custom movement modes
	virtual void PhysCustom(float DeltaTime, int32 Iterations) override;


	UPROPERTY(BlueprintReadWrite)
	FVector LerpedDirectionalVelocity;

private:
	float FlyingLerpTimer;
	FVector InitialLerpVelocity;
	FVector TargetLerpVelocity;
};
