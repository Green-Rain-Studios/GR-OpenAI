#include "GROpenAIEditor.h"

IMPLEMENT_GAME_MODULE(FGROpenAIEditorModule, GROpenAIEditor);

DEFINE_LOG_CATEGORY(GROpenAIEditor)

#define LOCTEXT_NAMESPACE "GROpenAIEditor"

void FGROpenAIEditorModule::StartupModule()
{
    //UE_LOG(MyGameEditor, Warning, TEXT("GREXToolsEditor: Log Started"));
}

void FGROpenAIEditorModule::ShutdownModule()
{
    //UE_LOG(MyGameEditor, Warning, TEXT("GREXToolsEditor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE