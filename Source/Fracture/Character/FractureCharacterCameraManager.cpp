// Copyright (c) 2022 Thomas Berger. Project published under MIT License.


#include "FractureCharacterCameraManager.h"

#include "FractureCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Fracture/CustomComponents/ElytraMovementComponent.h"

AFractureCharacterCameraManager::AFractureCharacterCameraManager()
{
	
}

void AFractureCharacterCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);

	const auto* Character = Cast<AFractureCharacter>(GetOwningPlayerController()->GetPawn());
	if(IsValid(Character))
	{
		UElytraMovementComponent* ElytraMovementComponent;
		verify((ElytraMovementComponent = Character->GetElytraMovementComponent()) != nullptr);

		const FVector TargetCrouchOffset = FVector(0.,
		                                           0.,
		                                           ElytraMovementComponent->GetCrouchedHalfHeight() - Character->GetClass()->GetDefaultObject<ACharacter>()
		                                                                                                       ->GetCapsuleComponent()->
		                                                                                                       GetScaledCapsuleHalfHeight());
		FVector Offset = FMath::Lerp(FVector::ZeroVector, TargetCrouchOffset, FMath::Clamp(CrouchBlendTime / CrouchBlendDuration, 0.f, 1.f));

		if(ElytraMovementComponent->IsCrouching())
		{
			CrouchBlendTime = FMath::Clamp(CrouchBlendTime + DeltaTime, 0.f, CrouchBlendDuration);
			Offset -= TargetCrouchOffset;
		}
		else
		{
			CrouchBlendTime = FMath::Clamp(CrouchBlendTime - DeltaTime, 0.f, CrouchBlendDuration);
		}

		if(ElytraMovementComponent->IsMovingOnGround())
		{
			OutVT.POV.Location += Offset;
		}
	}
}
