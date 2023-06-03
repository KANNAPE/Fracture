// Copyright (c) 2022 Thomas Berger. Project published under MIT License.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ElytraMovementComponent.generated.h"

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_None			UMETA(Hidden),
	CMOVE_Sliding		UMETA(DisplayName = "Sliding"),
	CMOVE_JetFlying		UMETA(DisplayName = "Jet Flying"),
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

	// Parameters
	UPROPERTY(EditDefaultsOnly) float Sprint_MaxWalkSpeed = 1000.f;
	UPROPERTY(EditDefaultsOnly) float Walk_MaxWalkSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly) float Slide_MinSpeed = 350.f;
	UPROPERTY(EditDefaultsOnly) float Slide_EnterImpulse = 500.f;
	UPROPERTY(EditDefaultsOnly) float Slide_GravityForce = 5000.f;
	UPROPERTY(EditDefaultsOnly) float Slide_Friction = 1.3f;

	UPROPERTY(Transient) class AFractureCharacter* FractureCharacterOwner;

	// Safe booleans
	bool Safe_bWantsToSprint;
	bool Safe_bPrevWantsToCrouch;

	// Temp
	ECustomMovementMode CMovementMode;

public:
	UElytraMovementComponent();
	
protected:
	virtual void InitializeComponent() override;
	
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	// where the crouch mechanic is being handled
	// (and we need to set variables for the slide before the crouch is being updated)
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;

	// handles all the physics for the custom movement modes
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	
public:
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	// JetFlying temp
	FORCEINLINE bool IsJetFlying() const { return CMovementMode == CMOVE_JetFlying; }
	void SetFlyingMode(const bool Flying = true);

	// Sprint
	UFUNCTION(BlueprintCallable) void SprintPressed();
	UFUNCTION(BlueprintCallable) void SprintReleased();

	// Crouch
	UFUNCTION(BlueprintCallable) void CrouchPressed();
	
	virtual bool IsMovingOnGround() const override;
	virtual bool CanCrouchInCurrentState() const override;

	// Slide
	void EnterSlide();
	void ExitSlide();
	void PhysSliding(float deltaTime, int32 Iterations);
	bool GetSlideSurface(FHitResult& Hit) const;

	// Custom movement mode getter
	UFUNCTION(BlueprintPure) bool IsCustomMovementMode(ECustomMovementMode InCustomMovementMode) const; 
};
