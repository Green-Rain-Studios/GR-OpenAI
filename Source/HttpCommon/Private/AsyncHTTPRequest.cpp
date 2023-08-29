// 2023 Green Rain Studios

#include "AsyncHTTPRequest.h"

void UAsyncHTTPRequest::Activate()
{
	// Create HTTP Request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetURL(URL);
	HttpRequest->SetContentAsString(RequestBody);
	switch (RequestType)
	{
		case EHttpRequestType::HRT_GET:
			HttpRequest->SetVerb("GET");
			break;
		case EHttpRequestType::HRT_POST:
			HttpRequest->SetVerb("POST");
			break;
		case EHttpRequestType::HRT_PUT:
			HttpRequest->SetVerb("PUT");
			break;
		case EHttpRequestType::HRT_DELETE:
			HttpRequest->SetVerb("DELETE");
			break;
	}

	// Setup async response lambda
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsyncHTTPRequest::ProcessHTTPRequest);

	// Handle actual http request
	HttpRequest->ProcessRequest();
}

void UAsyncHTTPRequest::HandleRequestCompleted(FString ResponseString, bool bSuccess)
{
	if(Completed.IsBound())
		Completed.Broadcast(ResponseString, bSuccess);
}

void UAsyncHTTPRequest::ProcessHTTPRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	FString ResponseString = "";
	if (bSuccess)
	{
		ResponseString = Response->GetContentAsString();
	}

	this->HandleRequestCompleted(ResponseString, bSuccess);
}

UAsyncHTTPRequest* UAsyncHTTPRequest::AsyncRequestHTTP(UObject* WorldContextObject, const FString& Url,
                                                       const FString& RequestBody, const EHttpRequestType& RequestMethod)
{
	// Create blueprint action instance
	UAsyncHTTPRequest* action = NewObject<UAsyncHTTPRequest>();
	action->URL = Url;
	action->RequestBody = RequestBody;
	action->RequestType = RequestMethod;

	action->RegisterWithGameInstance(WorldContextObject);

	return action;
}
