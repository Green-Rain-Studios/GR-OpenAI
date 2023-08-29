// Green Rain Studios LLP

#pragma once

#include "CoreMinimal.h"

#include "GROpenAISettings.generated.h"

/** 
 * 
 */
UCLASS(config=Game, defaultconfig)
class GROPENAI_API UGROpenAISettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UGROpenAISettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
	//~ UObject interface
	virtual bool CanEditChange(const FProperty* InProperty) const override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	//~ UDeveloperSettings interface
	virtual FText GetSectionText() const override;
#endif
	/**
	* OpenAI API Token (https://platform.openai.com/account/api-keys)
	*/
	UPROPERTY(config, EditAnywhere, Category="Settings")
	FString Token = "sk-****";
};
