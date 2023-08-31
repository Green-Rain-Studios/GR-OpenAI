// Copyright Epic Games, Inc. All Rights Reserved.

#include "HttpCommonUtils.h"

#include "JsonObjectWrapper.h"



UHttpCommonUtils::UHttpCommonUtils(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FJsonObjectWrapper UHttpCommonUtils::DictToJson(const TMap<FString, FString>& InDict)
{
	FJsonObjectWrapper outJsonObject;
	for (const TTuple<FString, FString>& Entry : InDict)
	{
		outJsonObject.JsonObject->SetStringField(Entry.Key, Entry.Value);
	}

	return outJsonObject;
}

TMap<FString, FString> UHttpCommonUtils::JsonToDict(const FJsonObjectWrapper& InJson)
{
	TMap<FString, FString> outMap;
	if(InJson)
	{
		for (const TTuple<FString, TSharedPtr<FJsonValue>>& jObj : InJson.JsonObject->Values)
		{
			outMap.Emplace(jObj.Key, jObj.Value->AsString());
		}
	}

	return outMap;
}

bool UHttpCommonUtils::FindStringFieldInJson(FJsonObjectWrapper JsonObject, FString Field, FString& OutValue)
{
	// Try to get the string field from the current JSON object
	if (JsonObject.JsonObject->TryGetStringField(Field, OutValue))
		return true;

	// If the field was not found in the current JSON object, 
	// iterate over all fields of the JSON object
	for (const TTuple<FString, TSharedPtr<FJsonValue>>& Pair : JsonObject.JsonObject->Values)
	{
		// Check if the field value is a JSON object
		if (Pair.Value->Type == EJson::Object)
		{
			// If the field value is a JSON object, 
			// recursively search this JSON object for the field
			FJsonObjectWrapper obj;
			obj.JsonObject = Pair.Value->AsObject();
			if (FindStringFieldInJson(obj, Field, OutValue))
				return true;
		}
  	}

	// If the field was not found in the current JSON object or any nested JSON objects, return false
	return false;
}

bool UHttpCommonUtils::GetSingleArrayFieldFromJson(FJsonObjectWrapper JsonObject, FString Field, int Index,
	FJsonObjectWrapper& OutValue)
{
	const TArray<TSharedPtr<FJsonValue>>* ArrayField;
	if(JsonObject.JsonObject->TryGetArrayField(Field, ArrayField))
	{
		if(Index < ArrayField->Num())
		{
			// Check if the FJsonValue is an object
			if ((*ArrayField)[Index]->Type == EJson::Object)
			{
				// Convert the FJsonValue to a FJsonObject
				const TSharedPtr<FJsonObject> JO = (*ArrayField)[Index]->AsObject();
				OutValue.JsonObject = JO;
				return true;
			}
		}
	}

	return false;
}
