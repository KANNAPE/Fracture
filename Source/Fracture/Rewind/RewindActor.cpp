// Copyright (c) 2022 Thomas Berger. Project published under MIT License.


#include "RewindActor.h"

ARewindActor::ARewindActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARewindActor::BeginPlay()
{
	Super::BeginPlay();

	RewindPositionsArray.Add(GetActorLocation());	

	RootPrimitiveComponent = Cast<UPrimitiveComponent>(RootComponent);
}

void ARewindActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickRegisterPositionWhenMoving(DeltaTime);
	if (bIsRewinding)
	{
		TickRewind(DeltaTime);
	}
}

void ARewindActor::TickRegisterPositionWhenMoving(float DeltaTime)
{
	FVector CurrentVelocity = RootComponent->GetComponentVelocity();

	if ((CurrentVelocity.SizeSquared() >= .05f || bIsRewinding)
		&& RegisterTimer >= RegisterPositionRateSeconds)
	{
		RegisterTimer = 0.f;

		RegisteredPositionsArray.Add(GetActorLocation());
		RegisteredRotationsArray.Add(GetActorRotation());
	}

	RegisterTimer += DeltaTime;
}

void ARewindActor::TickRewind(float DeltaTime)
{
	// Rewind is over
	if (RewindTimer >= RewindDurationTimeSeconds)
	{
		bIsRewinding = false;
		RootPrimitiveComponent->SetSimulatePhysics(true);
		return;
	}

	// Lerping position & rotation
	if (RewindingLerpPositionTimer >= RegisterPositionRateSeconds)
	{
		RewindingLerpPositionTimer = 0.f;

		// Position
		OriginPosition = DestinationPosition;
		if (RewindPositionsArray.Num() != 0)
		{
			DestinationPosition = RewindPositionsArray.Pop();
		}

		// Rotation
		OriginRotation = DestinationRotation;
		if (RewindRotationsArray.Num() != 0)
		{
			DestinationRotation = RewindRotationsArray.Pop();
		}
	}

	// Lerping
	float Alpha = RewindingLerpPositionTimer / RegisterPositionRateSeconds;
	FVector LerpedPosition = FMath::Lerp(OriginPosition, DestinationPosition, Alpha);
	FRotator LerpedRotation = FMath::Lerp(OriginRotation, DestinationRotation, Alpha);
	SetActorLocation(LerpedPosition);
	SetActorRotation(LerpedRotation);

	// Updating timers
	GEngine->AddOnScreenDebugMessage(3, 0.f, FColor::Yellow, FString::Printf(TEXT("Rewinding: %.1f s"), RewindTimer));
	RewindingLerpPositionTimer += DeltaTime;
	RewindTimer += DeltaTime;
}

void ARewindActor::TriggerRewind()
{
	// If the actor is already in rewind, we return
	if (bIsRewinding)
	{
		return;
	}

	// Timer + rewind bool
	bIsRewinding = true;
	RewindTimer = 0.f;

	// Deactivate physics
	RootPrimitiveComponent->SetSimulatePhysics(false);

	// Rewind positions & rotations
	RewindPositionsArray.Empty();
	RewindPositionsArray.Append(RegisteredPositionsArray);
	RewindRotationsArray.Empty();
	RewindRotationsArray.Append(RegisteredRotationsArray);

	// If the rewind array is empty, we set our destination to current, so the actor will be frozen in time but won't move
	if (RewindPositionsArray.Num() < 2 || RewindRotationsArray.Num() < 2)
	{
		if (RewindPositionsArray.Num() < 2)
		{
			OriginPosition = GetActorLocation();
			DestinationPosition = OriginPosition;
		}
		if (RewindRotationsArray.Num() < 2)
		{
			OriginRotation = GetActorRotation();
			DestinationRotation = OriginRotation;
		}
		return;
	}
	OriginPosition = RewindPositionsArray.Pop();
	DestinationPosition = RewindPositionsArray.Pop();
	OriginRotation = RewindRotationsArray.Pop();
	DestinationRotation = RewindRotationsArray.Pop();
}

