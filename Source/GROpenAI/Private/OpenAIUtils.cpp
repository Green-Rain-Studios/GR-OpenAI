// Copyright Epic Games, Inc. All Rights Reserved.

#include "OpenAIUtils.h"

#include "GROpenAISettings.h"

UOpenAIUtils::UOpenAIUtils(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void FGPTConversation::ConstructConversationJsonObject()
{
	// Set model name
	JsonObject.JsonObject->SetStringField("model", UOpenAIUtils::GetModelName(Model));

	// Set max tokens if a value is provided
	if(ResponseLength > 0)
		JsonObject.JsonObject->SetNumberField("max_tokens", ResponseLength);
	
	// Create initial system message to set up context
	TSharedPtr<FJsonObject> roleJO = MakeShared<FJsonObject>();
	roleJO->SetStringField("role", "system");
	roleJO->SetStringField("content", Context);
	
	// Create a TArray of TSharedPtr<FJsonValue> and add the system message to it
	TArray<TSharedPtr<FJsonValue>> messagesArray;
	messagesArray.Add(MakeShared<FJsonValueObject>(roleJO));

	// Set the messages array field
	JsonObject.JsonObject->SetArrayField("messages", messagesArray);
}

FString UOpenAIUtils::GetAPIToken()
{
	return GetDefault<UGROpenAISettings>()->Token;
}

FString UOpenAIUtils::GetModelName(EGPTModel ModelEnum)
{
	const UEnum* EnumPtr = StaticEnum<EGPTModel>();
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetDisplayNameTextByIndex(static_cast<int32>(ModelEnum)).ToString();
}

void UOpenAIUtils::InitializeConversation(FGPTConversation& InConversation)
{
	InConversation.ConstructConversationJsonObject();
}

void UOpenAIUtils::AddMessage(FGPTConversation& InConversation, FString Role, FString Message)
{
	// Create user message as json
	TSharedPtr<FJsonObject> msgJO = MakeShared<FJsonObject>();
	msgJO->SetStringField("role", Role);
	msgJO->SetStringField("content", Message);

	// Add new message to the end
	TArray<TSharedPtr<FJsonValue>> messagesArray = InConversation.JsonObject.JsonObject->GetArrayField("messages");
	messagesArray.Add(MakeShared<FJsonValueObject>(msgJO));

	// Apply changes
	InConversation.JsonObject.JsonObject->SetArrayField("messages", messagesArray);
}

void UOpenAIUtils::AddUserMessage(FGPTConversation& InConversation, FString Message)
{
	AddMessage(InConversation,"user", Message);
}

void UOpenAIUtils::AddAssistantMessage(FGPTConversation& InConversation, FString Message)
{
	AddMessage(InConversation,"assistant", Message);
}

FString UOpenAIUtils::GetConversationString(FGPTConversation InConversation)
{
	FString str;
	InConversation.JsonObject.JsonObjectToString(str);

	return str;
}
