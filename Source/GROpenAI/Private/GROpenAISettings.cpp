// Green Rain Studios LLP

#include "GROpenAISettings.h"

#define LOCTEXT_NAMESPACE "GROpenAI"

UGROpenAISettings::UGROpenAISettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CategoryName = TEXT("Plugins");
	SectionName  = TEXT("GR-OpenAI");
}

bool UGROpenAISettings::CanEditChange(const FProperty* InProperty) const
{
	bool bCanEditChange = Super::CanEditChange(InProperty);
	
	return bCanEditChange;
}

void UGROpenAISettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

FText UGROpenAISettings::GetSectionText() const
{
	return LOCTEXT("SettingsDisplayName", "GR-OpenAI");
}