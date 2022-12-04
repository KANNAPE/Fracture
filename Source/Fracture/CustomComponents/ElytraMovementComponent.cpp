// Fill out your copyright notice in the Description page of Project Settings.


#include "ElytraMovementComponent.h"

#include "GameFramework/Character.h"

// FSavedMove_Fracture
bool UElytraMovementComponent::FSavedMove_Fracture::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	const FSavedMove_Fracture* NewCharacterMove = static_cast<FSavedMove_Fracture*>(NewMove.Get());

	if(Saved_bWantsToSprint != NewCharacterMove->Saved_bWantsToSprint)
	{
		return false;
	}
	
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}
void UElytraMovementComponent::FSavedMove_Fracture::Clear()
{
	FSavedMove_Character::Clear();

	Saved_bWantsToSprint = 0;
}
uint8 UElytraMovementComponent::FSavedMove_Fracture::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if(Saved_bWantsToSprint) Result |= FLAG_Custom_0;

	return Result;
}
void UElytraMovementComponent::FSavedMove_Fracture::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	const UElytraMovementComponent* CharacterMovement = Cast<UElytraMovementComponent>(C->GetCharacterMovement());

	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
}
void UElytraMovementComponent::FSavedMove_Fracture::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);

	UElytraMovementComponent* CharacterMovement = Cast<UElytraMovementComponent>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
}
//



// FNetworkPredictionData_Client_Fracture
UElytraMovementComponent::FNetworkPredictionData_Client_Fracture::FNetworkPredictionData_Client_Fracture(const UElytraMovementComponent& ClientMovement)
	: Super(ClientMovement) {}
FSavedMovePtr UElytraMovementComponent::FNetworkPredictionData_Client_Fracture::AllocateNewMove()
{
	return MakeShared<FSavedMove_Fracture>();
}
//




UElytraMovementComponent::UElytraMovementComponent()
{
	
}

void UElytraMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

FNetworkPredictionData_Client* UElytraMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != nullptr)

	if(ClientPredictionData == nullptr)
	{
		UElytraMovementComponent* MutableThis = const_cast<UElytraMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Fracture(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}

	return ClientPredictionData;
}

void UElytraMovementComponent::SprintPressed()
{
	Safe_bWantsToSprint = true;
}

void UElytraMovementComponent::SprintReleased()
{
	Safe_bWantsToSprint = false;
}
