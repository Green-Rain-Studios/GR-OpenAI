// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "OpenAIUtils.generated.h"

UENUM()
enum EGPTModels : uint8
{
	GPTM_GPT3_5		UMETA(DisplayName = "gpt-3.5-turbo"),
	GPTM_GPT4		UMETA(DisplayName = "gpt-4")
};

struct FJsonObjectWrapper;

UCLASS()
class UOpenAIUtils : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	// Get the API token stored in the settings
	UFUNCTION(BlueprintPure, Category="GROpenAI", meta=(CompactNodeTitle="Token"))
	static FString GetAPIToken();

	// Get the display name of an EGPTModels enum value
	UFUNCTION(BlueprintPure, Category="GROpenAI")
	static FString GetModelName(EGPTModels ModelEnum);
	
};
