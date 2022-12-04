// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FRACTURE_FractureCharacter_generated_h
#error "FractureCharacter.generated.h already included, missing '#pragma once' in FractureCharacter.h"
#endif
#define FRACTURE_FractureCharacter_generated_h

#define FID_Fracture_Source_Fracture_FractureCharacter_h_16_DELEGATE \
static inline void FOnUseItem_DelegateWrapper(const FMulticastScriptDelegate& OnUseItem) \
{ \
	OnUseItem.ProcessMulticastDelegate<UObject>(NULL); \
}


#define FID_Fracture_Source_Fracture_FractureCharacter_h_21_SPARSE_DATA
#define FID_Fracture_Source_Fracture_FractureCharacter_h_21_RPC_WRAPPERS
#define FID_Fracture_Source_Fracture_FractureCharacter_h_21_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Fracture_Source_Fracture_FractureCharacter_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAFractureCharacter(); \
	friend struct Z_Construct_UClass_AFractureCharacter_Statics; \
public: \
	DECLARE_CLASS(AFractureCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Fracture"), NO_API) \
	DECLARE_SERIALIZER(AFractureCharacter)


#define FID_Fracture_Source_Fracture_FractureCharacter_h_21_INCLASS \
private: \
	static void StaticRegisterNativesAFractureCharacter(); \
	friend struct Z_Construct_UClass_AFractureCharacter_Statics; \
public: \
	DECLARE_CLASS(AFractureCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Fracture"), NO_API) \
	DECLARE_SERIALIZER(AFractureCharacter)


#define FID_Fracture_Source_Fracture_FractureCharacter_h_21_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AFractureCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AFractureCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFractureCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFractureCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFractureCharacter(AFractureCharacter&&); \
	NO_API AFractureCharacter(const AFractureCharacter&); \
public:


#define FID_Fracture_Source_Fracture_FractureCharacter_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFractureCharacter(AFractureCharacter&&); \
	NO_API AFractureCharacter(const AFractureCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFractureCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFractureCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AFractureCharacter)


#define FID_Fracture_Source_Fracture_FractureCharacter_h_18_PROLOG
#define FID_Fracture_Source_Fracture_FractureCharacter_h_21_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Fracture_Source_Fracture_FractureCharacter_h_21_SPARSE_DATA \
	FID_Fracture_Source_Fracture_FractureCharacter_h_21_RPC_WRAPPERS \
	FID_Fracture_Source_Fracture_FractureCharacter_h_21_INCLASS \
	FID_Fracture_Source_Fracture_FractureCharacter_h_21_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Fracture_Source_Fracture_FractureCharacter_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Fracture_Source_Fracture_FractureCharacter_h_21_SPARSE_DATA \
	FID_Fracture_Source_Fracture_FractureCharacter_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Fracture_Source_Fracture_FractureCharacter_h_21_INCLASS_NO_PURE_DECLS \
	FID_Fracture_Source_Fracture_FractureCharacter_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FRACTURE_API UClass* StaticClass<class AFractureCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Fracture_Source_Fracture_FractureCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
