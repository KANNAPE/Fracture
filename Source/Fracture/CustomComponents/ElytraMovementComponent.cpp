// Copyright (c) 2022 Thomas Berger. Project published under MIT License.


#include "ElytraMovementComponent.h"

#include "GameFramework/Character.h"

#pragma region FSavedMove_Fracture
bool UElytraMovementComponent::FSavedMove_FractureCharacter::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	const FSavedMove_FractureCharacter* NewCharacterMove = static_cast<FSavedMove_FractureCharacter*>(NewMove.Get());

	if(Saved_bWantsToSprint != NewCharacterMove->Saved_bWantsToSprint)
	{
		return false;
	}
	
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}
void UElytraMovementComponent::FSavedMove_FractureCharacter::Clear()
{
	FSavedMove_Character::Clear();

	Saved_bWantsToSprint = 0;
}
uint8 UElytraMovementComponent::FSavedMove_FractureCharacter::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if(Saved_bWantsToSprint) Result |= FLAG_Custom_0;

	return Result;
}
void UElytraMovementComponent::FSavedMove_FractureCharacter::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	const UElytraMovementComponent* CharacterMovement = Cast<UElytraMovementComponent>(C->GetCharacterMovement());

	Saved_bWantsToSprint = CharacterMovement->Safe_bWantsToSprint;
}
void UElytraMovementComponent::FSavedMove_FractureCharacter::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);

	UElytraMovementComponent* CharacterMovement = Cast<UElytraMovementComponent>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
}
#pragma endregion


#pragma region FNetworkPredictionData_Client_Fracture
UElytraMovementComponent::FNetworkPredictionData_Client_FractureCharacter::FNetworkPredictionData_Client_FractureCharacter(const UElytraMovementComponent& ClientMovement)
	: Super(ClientMovement) {}
FSavedMovePtr UElytraMovementComponent::FNetworkPredictionData_Client_FractureCharacter::AllocateNewMove()
{
	return MakeShared<FSavedMove_FractureCharacter>();
}
#pragma endregion 


#pragma region CMC
UElytraMovementComponent::UElytraMovementComponent()
{
	NavAgentProps.bCanCrouch = true;
}

void UElytraMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	Safe_bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
}

void UElytraMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if(MovementMode == MOVE_Walking)
	{
		if(Safe_bWantsToSprint)
		{
			MaxWalkSpeed = Sprint_MaxWalkSpeed;
			return;
		}

		MaxWalkSpeed = Walk_MaxWalkSpeed;
	}
}

FNetworkPredictionData_Client* UElytraMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner)

	if(ClientPredictionData == nullptr)
	{
		UElytraMovementComponent* MutableThis = const_cast<UElytraMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_FractureCharacter(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}

	return ClientPredictionData;
}
#pragma endregion


void UElytraMovementComponent::SetFlyingMode(const bool Flying)
{
	CMovementMode = Flying ? ECustomMovementMode::CMOVE_JetFlying : ECustomMovementMode::CMOVE_Walking;
}

void UElytraMovementComponent::SprintPressed()
{
	Safe_bWantsToSprint = true;
}

void UElytraMovementComponent::SprintReleased()
{
	Safe_bWantsToSprint = false;
}

void UElytraMovementComponent::CrouchPressed()
{
	bWantsToCrouch = !bWantsToCrouch;
}
