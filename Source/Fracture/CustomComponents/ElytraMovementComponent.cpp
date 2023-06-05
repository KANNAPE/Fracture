// Copyright (c) 2022 Thomas Berger. Project published under MIT License.


#include "ElytraMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Fracture/Character/FractureCharacter.h"
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
	Saved_bPrevWantsToCrouch = CharacterMovement->Safe_bPrevWantsToCrouch;
}
void UElytraMovementComponent::FSavedMove_FractureCharacter::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);

	UElytraMovementComponent* CharacterMovement = Cast<UElytraMovementComponent>(C->GetCharacterMovement());

	CharacterMovement->Safe_bWantsToSprint = Saved_bWantsToSprint;
	CharacterMovement->Safe_bPrevWantsToCrouch = Saved_bPrevWantsToCrouch;
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

void UElytraMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	FractureCharacterOwner = Cast<AFractureCharacter>(GetOwner());
	if (!IsValid(FractureCharacterOwner))
	{
		UE_LOG(LogEngine, Fatal, TEXT("Invalid owner component"));
		return;
	}

	FractureCharacterOwner->OnModeSwitchedDelegate.AddUniqueDynamic(this, &UElytraMovementComponent::TrySwitchMode);
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
		}
		else
		{
			MaxWalkSpeed = Walk_MaxWalkSpeed;
		}		
	}

	Safe_bPrevWantsToCrouch = bWantsToCrouch;
}

void UElytraMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
	Super::PhysCustom(DeltaTime, Iterations);

	switch(CustomMovementMode)
	{
	case CMOVE_Flying:
		PhysFlying(DeltaTime, Iterations);
		break;

	default:
		UE_LOG(LogTemp, Fatal, TEXT("Invalid Movement Mode"))
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


// Sprint
void UElytraMovementComponent::SprintPressed()
{
	Safe_bWantsToSprint = true;
}
void UElytraMovementComponent::SprintReleased()
{
	Safe_bWantsToSprint = false;
}

// Crouch
void UElytraMovementComponent::CrouchPressed()
{
	bWantsToCrouch = !bWantsToCrouch;
}
bool UElytraMovementComponent::CanCrouchInCurrentState() const
{
	return Super::CanCrouchInCurrentState() && IsMovingOnGround();
}

// Flying
void UElytraMovementComponent::TrySwitchMode()
{
	if (MovementMode == MOVE_Custom && CustomMovementMode == CMOVE_Flying)
	{
		// Switch back to falling
		LerpedDirectionalVelocity = FVector::ZeroVector;
		SetMovementMode(MOVE_Falling);
		return;
	}

	// Else, try to switch to flying
	if (!IsMovingOnGround())
	{
		FlyingLerpTimer = 0.f;
		InitialLerpVelocity = FractureCharacterOwner->GetFirstPersonCameraComponent()->GetForwardVector().GetSafeNormal2D();
		TargetLerpVelocity = InitialLerpVelocity;
		SetMovementMode(MOVE_Custom, CMOVE_Flying);
	}
}
bool UElytraMovementComponent::IsFlying() const 
{
	return CMovementMode == CMOVE_Flying;
}
void UElytraMovementComponent::PhysFlying(float DeltaTime, int32 Iterations)
{
	// Boilerplate code, prevents the delta time value to be rounded to 0 (and so avoids division by 0)
	if (DeltaTime < MIN_TICK_TIME)
	{
		return;
	}

	RestorePreAdditiveRootMotionVelocity();

	// Perform Move
	++Iterations;
	bJustTeleported = false;

	FVector CameraForwardVector = FractureCharacterOwner->GetFirstPersonCameraComponent()->GetForwardVector();

	if (FlyingLerpTimer >= Flying_VelocityLerpTime)
	{
		FlyingLerpTimer = 0.f;
		InitialLerpVelocity = TargetLerpVelocity;
		TargetLerpVelocity = CameraForwardVector.GetSafeNormal2D();
	}

	float Alpha = FlyingLerpTimer / Flying_VelocityLerpTime;
	LerpedDirectionalVelocity = FMath::Lerp(InitialLerpVelocity, TargetLerpVelocity, Alpha);
	Velocity = (LerpedDirectionalVelocity + CameraForwardVector.Z * FVector::UpVector) * Flying_MaxPropulsionForce;

	const FVector OldLocation = UpdatedComponent->GetComponentLocation();
	const FQuat Rotation = UpdatedComponent->GetComponentRotation().Quaternion();
	const FVector Adjusted = Velocity * DeltaTime; // dx = dv * t
	FHitResult Hit(1.f);
	SafeMoveUpdatedComponent(Adjusted, Rotation, true, Hit);
	if (Hit.Time < 1.f)
	{
		HandleImpact(Hit, DeltaTime, Adjusted);
		SlideAlongSurface(Adjusted, 1.f - Hit.Time, Hit.Normal, Hit, true);
	}

	FlyingLerpTimer += DeltaTime;
}

// Very fat function, the heart of all custom movement modes, so I guess I'll have to write down how it works
//void UElytraMovementComponent::PhysSliding(float deltaTime, int32 Iterations)
//{
//	// Boilerplate code, prevents the delta time value to be rounded to 0 (and so avoids division by 0)
//	if(deltaTime < MIN_TICK_TIME)
//	{
//		return;
//	}
//
//	RestorePreAdditiveRootMotionVelocity();
//
//	FHitResult SurfaceHit;
//	if(!GetSlideSurface(SurfaceHit) || Velocity.SizeSquared() < Slide_MinSpeed * Slide_MinSpeed)
//	{
//		ExitSlide();
//		StartNewPhysics(deltaTime, Iterations);
//		return;
//	}
//
//	// Applying surface gravity to the velocity, so the character doesn't fly off from sliding
//	// (it sticks to the ground)
//	Velocity += Slide_GravityForce * FVector::DownVector * deltaTime;
//
//	// Checking the input vector (Acceleration) for left or right inputs, so we can strafe while sliding
//	// (we then clamp the value so it's not as fast as if we were walking normally)
//	// Returns 0 if the player isn't pressing any keys
//	if(FMath::Abs(FVector::DotProduct(Acceleration.GetSafeNormal(), UpdatedComponent->GetRightVector())) > .5)
//	{
//		Acceleration = Acceleration.ProjectOnTo(UpdatedComponent->GetRightVector());
//	}
//	else
//	{
//		Acceleration = FVector::ZeroVector;
//	}
//
//	// Set the rest of the Velocity only if we don't have any root motion
//	// We set the gravity before because CalcVelocity DOES NOT APPLY GRAVITY
//	if(!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
//	{
//		CalcVelocity(deltaTime, Slide_Friction, true, GetMaxBrakingDeceleration());
//	}
//	ApplyRootMotionToVelocity(deltaTime);
//
//	// Perform Move
//	++Iterations;
//	bJustTeleported = false;
//
//	FVector OldLocation = UpdatedComponent->GetComponentLocation();
//	FQuat OldRotation = UpdatedComponent->GetComponentRotation().Quaternion();
//	FHitResult Hit(1.f);
//	FVector Adjusted = Velocity * deltaTime;
//	FVector VelPlaneDir = FVector::VectorPlaneProject(Velocity, SurfaceHit.Normal).GetSafeNormal();
//	FQuat NewRotation = FRotationMatrix::MakeFromXZ(VelPlaneDir, SurfaceHit.Normal).ToQuat();
//	SafeMoveUpdatedComponent(Adjusted, NewRotation, true, Hit);
//
//	if(Hit.Time < 1.f)
//	{
//		HandleImpact(Hit, deltaTime, Adjusted);
//		SlideAlongSurface(Adjusted, 1.f - Hit.Time, Hit.Normal, Hit, true);
//	}
//
//	FHitResult NewSurfaceHit;
//	if(!GetSlideSurface(NewSurfaceHit) || Velocity.SizeSquared() < Slide_MinSpeed * Slide_MinSpeed)
//	{
//		ExitSlide();
//	}
//
//	if(!bJustTeleported && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
//	{
//		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
//	}
//}

bool UElytraMovementComponent::IsCustomMovementMode(ECustomMovementMode InCustomMovementMode) const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == InCustomMovementMode;
}
