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

FString UOpenAIUtils::GetModelName(EGPTModels ModelEnum)
{
	const UEnum* EnumPtr = FindObject<UEnum>(GetTransientPackage(), TEXT("EGPTModels"), true);
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(ModelEnum)).ToString();
}
