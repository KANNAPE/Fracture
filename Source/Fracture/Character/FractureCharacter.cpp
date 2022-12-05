// Copyright Epic Games, Inc. All Rights Reserved.

#include "FractureCharacter.h"
#include "../Template/FractureProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "CrashReportCore/Public/Android/AndroidErrorReport.h"
#include "Fracture/CustomComponents/ElytraMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"


//////////////////////////////////////////////////////////////////////////
// AFractureCharacter

AFractureCharacter::AFractureCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UElytraMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}

void AFractureCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

//////////////////////////////////////////////////////////////////////////// Input

void AFractureCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AFractureCharacter::OnPrimaryAction);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AFractureCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AFractureCharacter::MoveRight);

	// Bind mouse events
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("SwitchMode", IE_Pressed, this, &AFractureCharacter::SwitchMode);
}

void AFractureCharacter::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}

void AFractureCharacter::MoveForward(float Value)
{
	const auto* ElytraMovementComponent = Cast<UElytraMovementComponent>(GetMovementComponent());

	// If the character is flying, WASD keys are not used.
	if(IsValid(ElytraMovementComponent) && !ElytraMovementComponent->IsJetFlying())
	{
		if (Value != 0.0f)
		{
			// add movement in that direction
			AddMovementInput(GetActorForwardVector(), Value);
		}
	}	
}

void AFractureCharacter::MoveRight(float Value)
{
	const auto* ElytraMovementComponent = Cast<UElytraMovementComponent>(GetMovementComponent());

	// If the character is flying, WASD keys are not used.
	if(IsValid(ElytraMovementComponent) && !ElytraMovementComponent->IsJetFlying())
	{
		if (Value != 0.0f)
		{
			// add movement in that direction
			AddMovementInput(GetActorRightVector(), Value);
		}	
	}
}

void AFractureCharacter::SwitchMode()
{
	auto* ElytraMovementComponent = Cast<UElytraMovementComponent>(GetCharacterMovement());

	if(!IsValid(ElytraMovementComponent))
	{
		// assertion
		//UE_LOG(LogTemp, Error, TEXT("Elytra Movement Component is null!"))
		return;
	}

	// CMovementMode = ECustomMovementMode::CMOVE_Walking
	if(!ElytraMovementComponent->IsJetFlying())
	{
		// Can't fly if the character is grounded
		if(ElytraMovementComponent->IsMovingOnGround())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Cannot initiate flying while character is grounded!")));
			return;
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Flying mode (fun)")));
		ElytraMovementComponent->SetFlying();
		return;
	}

	// CMovementMode = ECustomMovementMode::CMOVE_JetFlying
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Walking mode (boring)")));
	ElytraMovementComponent->SetFlying(false);
}
