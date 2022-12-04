// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Fracture/FractureGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFractureGameMode() {}
// Cross Module References
	FRACTURE_API UClass* Z_Construct_UClass_AFractureGameMode_NoRegister();
	FRACTURE_API UClass* Z_Construct_UClass_AFractureGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Fracture();
// End Cross Module References
	void AFractureGameMode::StaticRegisterNativesAFractureGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFractureGameMode);
	UClass* Z_Construct_UClass_AFractureGameMode_NoRegister()
	{
		return AFractureGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AFractureGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFractureGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Fracture,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFractureGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "FractureGameMode.h" },
		{ "ModuleRelativePath", "FractureGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFractureGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFractureGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AFractureGameMode_Statics::ClassParams = {
		&AFractureGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AFractureGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFractureGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFractureGameMode()
	{
		if (!Z_Registration_Info_UClass_AFractureGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFractureGameMode.OuterSingleton, Z_Construct_UClass_AFractureGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AFractureGameMode.OuterSingleton;
	}
	template<> FRACTURE_API UClass* StaticClass<AFractureGameMode>()
	{
		return AFractureGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFractureGameMode);
	struct Z_CompiledInDeferFile_FID_Fracture_Source_Fracture_FractureGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Fracture_Source_Fracture_FractureGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AFractureGameMode, AFractureGameMode::StaticClass, TEXT("AFractureGameMode"), &Z_Registration_Info_UClass_AFractureGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFractureGameMode), 2497772021U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Fracture_Source_Fracture_FractureGameMode_h_4043637669(TEXT("/Script/Fracture"),
		Z_CompiledInDeferFile_FID_Fracture_Source_Fracture_FractureGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Fracture_Source_Fracture_FractureGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
