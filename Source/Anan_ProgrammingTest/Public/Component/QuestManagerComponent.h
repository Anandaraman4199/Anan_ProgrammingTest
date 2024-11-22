// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjEndedDelegate, const FString&, Id);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANAN_PROGRAMMINGTEST_API UQuestManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess= "true"))
	class UDataTable* QuestDataTable;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UQuestUserWidget> QuestWidgetClass;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UQuestUserWidget* QuestWidget;

public:	
	// Sets default values for this component's properties
	UQuestManagerComponent();

	UFUNCTION(BlueprintCallable)
	bool GetQuestDetails(const FString& Id, struct FQuestDetails& OutQuestDetails);

	UFUNCTION(BlueprintCallable)
	bool GetObjectiveDetails(const FString& Id, struct FObjectiveDetails& OutObjectiveDetails);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Array to store current objectives*/ 
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> CurrentObjectivesId;
	
	UPROPERTY(BlueprintReadOnly)
	FString CurrentQuestId;

	UPROPERTY(BlueprintAssignable)
	FOnObjEndedDelegate OnObjectiveCompleted;
	
	UPROPERTY(BlueprintAssignable)
	FOnObjEndedDelegate OnQuestCompleted;

	UPROPERTY(BlueprintAssignable)
	FOnObjEndedDelegate OnQuestStarted;

	UFUNCTION(BlueprintCallable)
	void AddNewQuest(const FString& Id);

	UFUNCTION(BlueprintCallable)
	bool ObjectiveCompleted(const FString& Id);

	UFUNCTION(BlueprintCallable)
	void QuestCompleted(const FString& Id);
};
