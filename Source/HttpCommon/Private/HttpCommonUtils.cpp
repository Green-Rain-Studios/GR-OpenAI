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
