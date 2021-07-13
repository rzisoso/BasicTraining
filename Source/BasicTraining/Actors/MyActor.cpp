// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	InitLocation = FVector(0.f);
	OriginLocation = FVector(100.f);
	bGoToInitLocation = true;
	WorldOrigin = FVector(0.f);
	TickLocationOffset = FVector(0.f);
	bShouldMove = false;
	InitForce = FVector(0.f);
	InitTorque = FVector(0.f);
	bAccelChange = false;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetActorLocation();

	if (bGoToInitLocation)
	{
		SetActorLocation(InitLocation);
	}

	StaticMesh->AddForce(InitForce, NAME_None, bAccelChange);
	StaticMesh->AddTorque(InitTorque, NAME_None, bAccelChange);
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldMove)
	{
		FHitResult Hit;
		AddActorLocalOffset(TickLocationOffset * DeltaTime, true, &Hit);
		UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), Hit.Location.X, Hit.Location.Y, Hit.Location.Z);
		
	}
}

