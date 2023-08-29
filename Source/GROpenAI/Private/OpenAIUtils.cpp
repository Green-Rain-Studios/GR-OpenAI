// Copyright Epic Games, Inc. All Rights Reserved.

#include "OpenAIUtils.h"

#include "GROpenAISettings.h"

UOpenAIUtils::UOpenAIUtils(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString UOpenAIUtils::GetAPIToken()
{
	return GetDefault<UGROpenAISettings>()->Token;
}
