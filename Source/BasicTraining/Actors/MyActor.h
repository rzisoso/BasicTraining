// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class BASICTRAINING_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(VisibleAnywhere, Category = "My Actor Components")
	class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties|Vector")
	FVector InitLocation;
	UPROPERTY(VisibleInstanceOnly, Category = "My Actor Properties|Vector")
	FVector OriginLocation;
	UPROPERTY(EditDefaultsOnly, Category = "My Actor Properties|Vector")
	bool bGoToInitLocation;
	UPROPERTY(VisibleDefaultsOnly, Category = "My Actor Properties|Vector")
	FVector WorldOrigin;
	UPROPERTY(EditAnywhere, Category = "My Actor Properties|Vector", meta = (ClampMin = -500.f, ClampMax = 500.f, UIMin = -500.f, UIMax = 500.f))
	FVector TickLocationOffset;
	UPROPERTY(EditAnywhere, Category = "My Actor Properties|Vector")
	bool bShouldMove;
	UPROPERTY(EditInstanceOnly, Category = "Physics")
	FVector InitForce;
	UPROPERTY(EditInstanceOnly, Category = "Physics")
	FVector InitTorque;
	UPROPERTY(EditInstanceOnly, Category = "Physics")
	bool bAccelChange;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
