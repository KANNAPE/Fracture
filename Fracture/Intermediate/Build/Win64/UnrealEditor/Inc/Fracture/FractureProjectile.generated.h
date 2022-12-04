// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef FRACTURE_FractureProjectile_generated_h
#error "FractureProjectile.generated.h already included, missing '#pragma once' in FractureProjectile.h"
#endif
#define FRACTURE_FractureProjectile_generated_h

#define FID_Fracture_Source_Fracture_FractureProjectile_h_15_SPARSE_DATA
#define FID_Fracture_Source_Fracture_FractureProjectile_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit);


#define FID_Fracture_Source_Fracture_FractureProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit);


#define FID_Fracture_Source_Fracture_FractureProjectile_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAFractureProjectile(); \
	friend struct Z_Construct_UClass_AFractureProjectile_Statics; \
public: \
	DECLARE_CLASS(AFractureProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Fracture"), NO_API) \
	DECLARE_SERIALIZER(AFractureProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Fracture_Source_Fracture_FractureProjectile_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAFractureProjectile(); \
	friend struct Z_Construct_UClass_AFractureProjectile_Statics; \
public: \
	DECLARE_CLASS(AFractureProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Fracture"), NO_API) \
	DECLARE_SERIALIZER(AFractureProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Fracture_Source_Fracture_FractureProjectile_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AFractureProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AFractureProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFractureProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFractureProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFractureProjectile(AFractureProjectile&&); \
	NO_API AFractureProjectile(const AFractureProjectile&); \
public:


#define FID_Fracture_Source_Fracture_FractureProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFractureProjectile(AFractureProjectile&&); \
	NO_API AFractureProjectile(const AFractureProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFractureProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFractureProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AFractureProjectile)


#define FID_Fracture_Source_Fracture_FractureProjectile_h_12_PROLOG
#define FID_Fracture_Source_Fracture_FractureProjectile_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Fracture_Source_Fracture_FractureProjectile_h_15_SPARSE_DATA \
	FID_Fracture_Source_Fracture_FractureProjectile_h_15_RPC_WRAPPERS \
	FID_Fracture_Source_Fracture_FractureProjectile_h_15_INCLASS \
	FID_Fracture_Source_Fracture_FractureProjectile_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Fracture_Source_Fracture_FractureProjectile_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Fracture_Source_Fracture_FractureProjectile_h_15_SPARSE_DATA \
	FID_Fracture_Source_Fracture_FractureProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Fracture_Source_Fracture_FractureProjectile_h_15_INCLASS_NO_PURE_DECLS \
	FID_Fracture_Source_Fracture_FractureProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FRACTURE_API UClass* StaticClass<class AFractureProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Fracture_Source_Fracture_FractureProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
