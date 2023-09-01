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
	void RefreshParameters();

	// The model to use. Defaults to gpt-3.5-turbo
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Conversation")
	TEnumAsByte<EGPTModel> Model = GPTM_GPT3_5;

	// How long the response from GPT should be. Increase this if sentences are getting cut off. Defaults to infinity.
	// Read about what tokens are and how many are needed here: https://platform.openai.com/tokenizer
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Conversation")
	int ResponseLength = -1;

	// The context for how the model should respond as
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Conversation")
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

	// Initialize conversation struct. NOTE: Should be called before anything else!
	UFUNCTION(BlueprintCallable, Category="GROpenAI|Conversation")
	static void InitializeConversation(UPARAM(ref) FGPTConversation& InConversation);

	// Set or change the model used. If you dont have access to the model selected, the conversation will fail
	UFUNCTION(BlueprintCallable, Category="GROpenAI|Conversation")
	static void SetConversationGPTModel(UPARAM(ref) FGPTConversation& InConversation, EGPTModel Model);

	// Set or change max tokens response length. Read more about tokens at: https://platform.openai.com/tokenizer
	UFUNCTION(BlueprintCallable, Category="GROpenAI|Conversation")
	static void SetResponseLength(UPARAM(ref) FGPTConversation& InConversation, int ResponseLength);

	// Set or change the context using which the assistant will respond
	UFUNCTION(BlueprintCallable, Category="GROpenAI|Conversation")
	static void SetAssistantContext(UPARAM(ref) FGPTConversation& InConversation, FString Context);

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
