// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonObjectWrapper.h"
#include "OpenAIUtils.generated.h"

UENUM(BlueprintType)
enum EGPTModel : uint8
{
	GPTM_GPT3_5		UMETA(DisplayName = "gpt-3.5-turbo"),
	GPTM_GPT4		UMETA(DisplayName = "gpt-4")
};

USTRUCT(BlueprintType)
struct FGPTConversation
{
	GENERATED_BODY()

public:
	void ConstructConversationJsonObject();

	// The model to use. Defaults to gpt-3.5-turbo
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Conversation")
	TEnumAsByte<EGPTModel> Model = GPTM_GPT3_5;

	// How long the response from GPT should be. Increase this if sentences are getting cut off. Defaults to infinity.
	// Read about what tokens are and how many are needed here: https://platform.openai.com/tokenizer
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Conversation")
	int ResponseLength = -1;

	// The context for how the model should respond as
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Conversation")
	FString Context = "You are a helpful assistant.";

	// Internal json object to track the conversation and other parameters
	UPROPERTY()
	FJsonObjectWrapper JsonObject;
	
};

UCLASS()
class UOpenAIUtils : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	// Get the API token stored in the settings
	UFUNCTION(BlueprintPure, Category="GROpenAI", meta=(CompactNodeTitle="OpenAI Token"))
	static FString GetAPIToken();

	// Get the display name of an EGPTModels enum value
	UFUNCTION(BlueprintPure, Category="GROpenAI")
	static FString GetModelName(EGPTModel ModelEnum);

	// Initialize conversation struct
	UFUNCTION(BlueprintCallable, Category="GROpenAI|Conversation")
	static void InitializeConversation(UPARAM(ref) FGPTConversation& InConversation);

	static void AddMessage(FGPTConversation& InConversation,FString Role, FString Message);
	// Add user message to conversation
	UFUNCTION(BlueprintCallable, Category="GROpenAI|Conversation")
	static void AddUserMessage(UPARAM(ref) FGPTConversation& InConversation, FString Message);

	// Add user message to conversation
	UFUNCTION(BlueprintCallable, Category="GROpenAI|Conversation")
	static void AddAssistantMessage(UPARAM(ref) FGPTConversation& InConversation, FString Message);

	// Get conversation as json string
	UFUNCTION(BlueprintPure, Category="GROpenAI|Conversation")
	static FString GetConversationString(FGPTConversation InConversation);
	
};
