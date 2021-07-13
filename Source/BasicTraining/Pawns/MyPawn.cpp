// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include <Components/StaticMeshComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <UObject/ConstructorHelpers.h>
#include <Components/SphereComponent.h>
// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->SetCollisionProfileName(TEXT("Pawn"));

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));



	MyPawnStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyPawnStaticMesh"));
	MyPawnStaticMesh->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (Mesh.Succeeded())
	{
		MyPawnStaticMesh->SetStaticMesh(Mesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial'"));
	if (Material.Succeeded())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Found!!!!!!"));
		MyPawnStaticMesh->SetMaterial(0, Material.Object);
	}
	MyPawnStaticMesh->SetWorldScale3D(FVector(0.5f));
	
	//MyCamera->SetupAttachment(GetRootComponent());

	/*MyCamera->SetRelativeLocation(FVector(-300.0f, 0.f, 300.0f));
	MyCamera->SetRelativeRotation(FRotator(-45.0f, 0.f, 0.f));*/

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetStaticMesh());
	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f,0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.f;

	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	MyCamera->SetupAttachment(GetSpringArm());

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Velocity = FVector::ZeroVector;
	MaxSpeed = 100.f;

	MouseInput = FVector2D::ZeroVector;

	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(Velocity * DeltaTime, true);
	/*FRotator NewSpringArmRotation = SpringArm->GetComponentRotation();
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += MouseInput.Y, -80.f, 80.f);
	SpringArm->SetWorldRotation(NewSpringArmRotation);*/
	AddControllerPitchInput(MouseInput.Y);
	AddControllerYawInput(MouseInput.X);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPawn::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyPawn::LookRight);
}

void AMyPawn::MoveForward(float val)
{
	Velocity.X = FMath::Clamp(val, -1.f, 1.f) * MaxSpeed;
}

void AMyPawn::MoveRight(float val)
{
	Velocity.Y = FMath::Clamp(val, -1.f, 1.f) * MaxSpeed;
}

void AMyPawn::LookUp(float Val)
{
	MouseInput.Y = FMath::Clamp(Val, -1.f, 1.f);
}

void AMyPawn::LookRight(float Val)
{
	MouseInput.X = FMath::Clamp(Val, -1.f, 1.f);
}

