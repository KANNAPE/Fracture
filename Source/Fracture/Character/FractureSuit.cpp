// Copyright (c) 2022 Thomas Berger. Project published under MIT License.


#include "FractureSuit.h"

#include "FractureCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFractureSuit::AFractureSuit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called to bind functionality to input
void AFractureSuit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent)
	PlayerInputComponent->BindAction("SwitchMode", IE_Pressed, this, &AFractureSuit::SwitchToGroundMode);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AFractureSuit::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AFractureSuit::AddControllerPitchInput);
}

// Called when the game starts or when spawned
void AFractureSuit::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* World = GetWorld();
	auto* CharacterActor = UGameplayStatics::GetActorOfClass(World, AFractureCharacter::StaticClass());

	if(IsValid(CharacterActor))
	{
		Character = Cast<AFractureCharacter>(CharacterActor);
	}

	Driver = Cast<UPrimitiveComponent>(RootComponent);
}

// Called every frame
void AFractureSuit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!IsValid(Driver)) return;

	const FVector Torque = -Driver->GetPhysicsAngularVelocityInDegrees() * 2.f;
	Driver->AddTorqueInDegrees(Torque, NAME_None, true);
}



void AFractureSuit::SwitchToGroundMode()
{
	const UWorld* World = GetWorld();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);

	if(IsValid(PlayerController) && IsValid(Character))
	{
		PlayerController->Possess(Character);
	}
}

void AFractureSuit::AddControllerYawInput(float Val)
{	
	if(!IsValid(Driver)) return;

	const FVector YawTorque = Driver->GetUpVector() * Val * AirControl * .5f;
	Driver->AddTorqueInDegrees(YawTorque, NAME_None, true);
}

void AFractureSuit::AddControllerPitchInput(float Val)
{
	if(!IsValid(Driver)) return;

	const FVector PitchTorque = Driver->GetRightVector() * Val * AirControl * .5f;
	Driver->AddTorqueInDegrees(PitchTorque, NAME_None, true);

	const FVector GravityForce = FVector::DownVector * 1500.f;
	Driver->AddForce(GravityForce, NAME_None, true);

	ComputeSpeed();
}

void AFractureSuit::ComputeSpeed()
{
	// Driver is already checked valid in AddControllerPitchInput
	const FVector DriverVelocity = Driver->GetPhysicsLinearVelocity();
	const FVector DriverForward = Driver->GetForwardVector() * ThrottleAmount;

	const FVector NewVelocity = FMath::Lerp(DriverVelocity, DriverForward, 0.01f);

	Driver->SetPhysicsLinearVelocity(NewVelocity);
}

