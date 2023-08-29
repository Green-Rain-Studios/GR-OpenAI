// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HttpCommonUtils.generated.h"

struct FJsonObjectWrapper;

UCLASS()
class UHttpCommonUtils : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	// Create a valid json string from a dictionary of string key-value pairs
	UFUNCTION(BlueprintPure, Category="GROpenAI|Json", meta=(CompactNodeTitle="Dict2JSON"))
	static FJsonObjectWrapper DictToJson(const TMap<FString, FString>& InDict);

	// Deserialize a json string into a dictionary of key-value pairs of strings
	UFUNCTION(BlueprintPure, Category="GROpenAI|Json", meta=(CompactNodeTitle="JSON2Dict"))
	static TMap<FString, FString> JsonToDict(const FJsonObjectWrapper& InJson);
};
