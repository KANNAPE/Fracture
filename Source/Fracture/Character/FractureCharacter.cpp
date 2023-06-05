// Copyright Epic Games, Inc. All Rights Reserved.


#include "FractureCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "FractureSuit.h"
#include "Fracture/CustomComponents/ElytraMovementComponent.h"
#include "Fracture/Rewind/RewindActor.h"

DEFINE_LOG_CATEGORY(LogFracture);



AFractureCharacter::AFractureCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UElytraMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	ElytraMovementComponent = Cast<UElytraMovementComponent>(GetCharacterMovement());
	check(ElytraMovementComponent);
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

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

void AFractureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind run event
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFractureCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFractureCharacter::StopSprinting);

	// Bind crouch event
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFractureCharacter::ToggleCrouching);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AFractureCharacter::OnPrimaryAction);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AFractureCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AFractureCharacter::MoveRight);

	// Bind mouse events
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	// Bind switch Walking <-> Flying event
	PlayerInputComponent->BindAction("SwitchMode", IE_Pressed, this, &AFractureCharacter::TrySwitchMode);

	// Bind Rewind events
	PlayerInputComponent->BindAction("TriggerRewind", IE_Pressed, this, &AFractureCharacter::TriggerRewind);
}

void AFractureCharacter::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* World = GetWorld();
	if(IsValid(World))
	{
		Suit = Cast<AFractureSuit>(UGameplayStatics::GetActorOfClass(World, AFractureSuit::StaticClass()));
	}
}

void AFractureCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AFractureCharacter::OnPrimaryAction()
{
	OnUseItem.Broadcast();
}

void AFractureCharacter::Sprint()
{
	ElytraMovementComponent->SprintPressed();
}

void AFractureCharacter::StopSprinting()
{
	ElytraMovementComponent->SprintReleased();
}

void AFractureCharacter::ToggleCrouching()
{
	ElytraMovementComponent->CrouchPressed();
}

void AFractureCharacter::MoveForward(float Val)
{
	// If the character is flying, WASD keys are not used.
	if(!ElytraMovementComponent->IsFlying())
	{
		if (Val != 0.0f)
		{
			// add movement in that direction
			AddMovementInput(GetActorForwardVector(), Val);
		}
	}	
}

void AFractureCharacter::MoveRight(float Val)
{
	// If the character is flying, WASD keys are not used.
	if(!ElytraMovementComponent->IsFlying())
	{
		if (Val != 0.0f)
		{
			// add movement in that direction
			AddMovementInput(GetActorRightVector(), Val);
		}	
	}
}

void AFractureCharacter::TrySwitchMode()
{
	OnModeSwitchedDelegate.Broadcast();
}

void AFractureCharacter::TriggerRewind()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!IsValid(PlayerController))
	{
		return;
	}

	FHitResult HitResult;
	float HalfCapsuleSize = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FVector StartPosition = GetActorLocation() + FVector::UpVector * HalfCapsuleSize;
	FVector EndPosition = StartPosition + GetFirstPersonCameraComponent()->GetForwardVector() * 10000.f;
	World->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECollisionChannel::ECC_Visibility);

	RewindCube = Cast<ARewindActor>(HitResult.GetActor());
	if (!IsValid(RewindCube))
	{
		// Hit actor isn't a rewind cube
		return;
	}

	RewindCube->TriggerRewind();
}

FCollisionQueryParams AFractureCharacter::GetIgnoreCharacterParams() const
{
	FCollisionQueryParams Params;

	TArray<AActor*> CharacterChildren;
	GetAllChildActors(CharacterChildren);
	Params.AddIgnoredActors(CharacterChildren);
	Params.AddIgnoredActor(this);

	return Params;
}
