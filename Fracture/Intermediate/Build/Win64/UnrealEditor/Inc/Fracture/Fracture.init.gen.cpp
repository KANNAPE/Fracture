// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFracture_init() {}
	FRACTURE_API UFunction* Z_Construct_UDelegateFunction_Fracture_OnPickUp__DelegateSignature();
	FRACTURE_API UFunction* Z_Construct_UDelegateFunction_Fracture_OnUseItem__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Fracture;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Fracture()
	{
		if (!Z_Registration_Info_UPackage__Script_Fracture.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_Fracture_OnPickUp__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_Fracture_OnUseItem__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Fracture",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xD2682561,
				0x698FF28B,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Fracture.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Fracture.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Fracture(Z_Construct_UPackage__Script_Fracture, TEXT("/Script/Fracture"), Z_Registration_Info_UPackage__Script_Fracture, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xD2682561, 0x698FF28B));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
