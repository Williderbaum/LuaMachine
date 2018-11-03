// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "lua.hpp"
#include "LuaValue.generated.h"

// required for Mac
#ifdef Nil
#undef Nil
#endif

/**
 *
 */

UENUM(BlueprintType)
enum class ELuaValueType : uint8
{
	Nil,
	Bool,
	Integer,
	Number,
	String,
	Function,
	Table,
	UFunction,
	UObject,
};

class ULuaState;

USTRUCT(BlueprintType)
struct LUAMACHINE_API FLuaValue
{
	GENERATED_BODY()

	FLuaValue()
	{
		Type = ELuaValueType::Nil;
		Object = nullptr;
		LuaRef = LUA_NOREF;
		LuaState = nullptr;
		Bool = false;
		Integer = 0;
		Number = 0;
	}

	FLuaValue(const FLuaValue& SourceValue);
	FLuaValue& operator = (const FLuaValue &SourceValue);

	FLuaValue(FString InString) : FLuaValue()
	{
		Type = ELuaValueType::String;
		String = InString;
	}

	FLuaValue(float Value) : FLuaValue()
	{
		Type = ELuaValueType::Number;
		Number = Value;
	}

	FLuaValue(int32 Value) : FLuaValue()
	{
		Type = ELuaValueType::Integer;
		Integer = Value;
	}

	FLuaValue(bool bInBool) : FLuaValue()
	{
		Type = ELuaValueType::Bool;
		Bool = bInBool;
	}

	FLuaValue(UObject* InObject) : FLuaValue()
	{
		Type = ELuaValueType::UObject;
		Object = InObject;
	}

	~FLuaValue();

	static FLuaValue Function(UObject* Context, FName FunctionName)
	{
		FLuaValue LuaValue;
		LuaValue.Type = ELuaValueType::UFunction;
		LuaValue.Object = Context;
		LuaValue.FunctionName = FunctionName;
		return LuaValue;
	}

	FString ToString();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ELuaValueType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Bool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Integer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString String;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Object;

	UPROPERTY(EditAnywhere)
	FName FunctionName;

	int LuaRef;

	ULuaState* LuaState;
};
