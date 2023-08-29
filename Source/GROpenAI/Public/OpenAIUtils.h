// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "OpenAIUtils.generated.h"

struct FJsonObjectWrapper;

UCLASS()
class UOpenAIUtils : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	// Get the API token stored in the settings
	UFUNCTION(BlueprintPure, Category="GROpenAI", meta=(CompactNodeTitle="Token"))
	static FString GetAPIToken();
};
