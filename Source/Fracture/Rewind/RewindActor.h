// Copyright (c) 2022 Thomas Berger. Project published under MIT License.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RewindActor.generated.h"

UCLASS()
class FRACTURE_API ARewindActor : public AActor
{
	GENERATED_BODY()
	
public:
	ARewindActor();

	virtual void Tick(float DeltaTime) override;

	void TriggerRewind();

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Rewind")
	float RegisterPositionRateSeconds = .1f;
	UPROPERTY(EditAnywhere, Category = "Rewind")
	float RewindDurationTimeSeconds = 5.f;

private:
	void TickRegisterPositionWhenMoving(float DeltaTime);
	void TickRewind(float DeltaTime);


	float RegisterTimer;
	float RewindTimer;
	float RewindingLerpPositionTimer;

	bool bIsRewinding;

	// Position
	TArray<FVector> RegisteredPositionsArray;
	TArray<FVector> RewindPositionsArray;
	FVector OriginPosition;
	FVector DestinationPosition;
	// Rotation
	TArray<FRotator> RegisteredRotationsArray;
	TArray<FRotator> RewindRotationsArray;
	FRotator OriginRotation;
	FRotator DestinationRotation;
	

	UPrimitiveComponent* RootPrimitiveComponent;
};
