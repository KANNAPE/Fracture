// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ElytraMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FRACTURE_API UElytraMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	class FSavedMove_Fracture : public FSavedMove_Character
	{
		typedef FSavedMove_Character Super;

		uint8 Saved_bWantsToSprint:1;

		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
		virtual void Clear() override;
		virtual uint8 GetCompressedFlags() const override;
		virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
		virtual void PrepMoveFor(ACharacter* C) override;
	};

	class FNetworkPredictionData_Client_Fracture : public FNetworkPredictionData_Client_Character
	{
	public:
		FNetworkPredictionData_Client_Fracture(const UElytraMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		virtual FSavedMovePtr AllocateNewMove() override;
	};

	bool Safe_bWantsToSprint;

public:
	UElytraMovementComponent();
	
protected:
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	
public:
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	UFUNCTION(BlueprintCallable) void SprintPressed();
	UFUNCTION(BlueprintCallable) void SprintReleased();
};