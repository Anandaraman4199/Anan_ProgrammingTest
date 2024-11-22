// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/QuestManagerComponent.h"
#include "Data/QuestData.h"
#include "Engine/DataTable.h"
#include "Widget/QuestUserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UQuestManagerComponent::UQuestManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UQuestManagerComponent::GetQuestDetails(const FString& Id, FQuestDetails& OutQuestDetails)
{
	TArray<FQuestDetails*> OutRows;
	QuestDataTable->GetAllRows<FQuestDetails>("RetrievingAllRows", OutRows);

	for (auto &EachRow : OutRows)
	{
		if (EachRow->Id == Id)
		{
			OutQuestDetails = *EachRow;
			return true;
		}
	}

	return false;
}

bool UQuestManagerComponent::GetObjectiveDetails(const FString& Id, FObjectiveDetails& OutObjectiveDetails)
{
	if (CurrentObjectivesId.Contains(Id))
	{
		FQuestDetails CurrentQuestDetails;
		GetQuestDetails(CurrentQuestId, CurrentQuestDetails);

		for (auto& EachObjective : CurrentQuestDetails.ListOfObjectives)
		{
			if (EachObjective.Id == Id)
			{
				OutObjectiveDetails = EachObjective;
				return true;
			}
		}
	}

	return false;
}


// Called when the game starts
void UQuestManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	QuestWidget = CreateWidget<UQuestUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), QuestWidgetClass);
	QuestWidget->AddToViewport();
}


// Called every frame
void UQuestManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestManagerComponent::AddNewQuest(const FString& Id)
{
	FQuestDetails NewQuest;
	if (GetQuestDetails(Id, NewQuest))
	{
		CurrentObjectivesId.Empty();
		for (auto& Objective : NewQuest.ListOfObjectives)
		{
			CurrentObjectivesId.Add(Objective.Id);
		}

		CurrentQuestId = Id;

		OnQuestStarted.Broadcast(Id);
	}
}

bool UQuestManagerComponent::ObjectiveCompleted(const FString& Id)
{
	if (CurrentObjectivesId.Contains(Id))
	{
		CurrentObjectivesId.RemoveSwap(Id, true);
		OnObjectiveCompleted.Broadcast(Id);

		UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentObjectivesId.Num());

		if (CurrentObjectivesId.IsEmpty())
		{
			QuestCompleted(CurrentQuestId);
		}

		return true;
	}

	return false;
}

void UQuestManagerComponent::QuestCompleted(const FString& Id)
{
	OnQuestCompleted.Broadcast(Id);
}

