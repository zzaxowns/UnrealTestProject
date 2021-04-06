// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransferVolum.generated.h"

UCLASS()
class TESTPROJECT_API ALevelTransferVolum : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransferVolum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString TransferLevelName;

	UPROPERTY()
	class UBoxComponent *TransferVolume;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
