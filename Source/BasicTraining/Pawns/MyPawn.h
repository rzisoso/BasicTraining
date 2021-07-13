// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class BASICTRAINING_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class UStaticMeshComponent* MyPawnStaticMesh;
	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class UCameraComponent* MyCamera;
	UPROPERTY(EditAnywhere, Category = "My Pawn Movement")
	float MaxSpeed;
	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class USphereComponent* Sphere;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveForward(float val);
	void MoveRight(float val);

	FVector Velocity;

	FORCEINLINE UStaticMeshComponent* GetStaticMesh() { return MyPawnStaticMesh; }
	FORCEINLINE USpringArmComponent* GetSpringArm() { return SpringArm; }

	void LookUp(float Val);
	void LookRight(float Val);

	FVector2D MouseInput;
};
