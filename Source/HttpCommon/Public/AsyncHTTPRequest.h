// 2023 Green Rain Studios

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "AsyncHTTPRequest.generated.h"

UENUM(BlueprintType)
enum class EHttpRequestType : uint8
{
	HRT_GET     UMETA(DisplayName = "GET"),
	HRT_POST    UMETA(DisplayName = "POST"),
	HRT_PUT     UMETA(DisplayName = "PUT"),
	HRT_DELETE  UMETA(DisplayName = "DELETE")
};

// Event that will be the 'Completed' exec wire in the blueprint node along with all parameters as output pins.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHttpRequestCompleted, const FString&, ResponseString, bool, bSuccess);

UCLASS()
class HTTPCOMMON_API UAsyncHTTPRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "GROpenAI|HTTP", WorldContext = "WorldContextObject"))
	static UAsyncHTTPRequest* AsyncRequestHTTP(UObject* WorldContextObject, const FString& Url, const TMap<FString, FString>& AdditionalHeaders, const FString& RequestBody, const EHttpRequestType& RequestMethod);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FOnHttpRequestCompleted Completed;

	// Variables
	EHttpRequestType RequestType;
	FString URL;
	FString RequestBody;
	TMap<FString, FString> AdditionalHeaders;

protected:
	void HandleRequestCompleted(FString ResponseString, bool bSuccess);
	void ProcessHTTPRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
};
