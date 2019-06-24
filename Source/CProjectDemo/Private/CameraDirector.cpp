// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (CameraOne)
	{
		OurPlayerController->SetViewTarget(CameraOne);
	}
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const float SmoothBlendTime = 2.f;
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0)
	{
		TimeToNextCameraChange += 2.1f;
		if (OurPlayerController)
		{
			if (CameraTwo && (OurPlayerController->GetViewTarget() == CameraOne))
			{
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
				// UE_LOG(LogTemp, Warning, TEXT("two"));
			}
			else if (CameraOne && (OurPlayerController->GetViewTarget() == CameraTwo))
			{
				OurPlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
				// UE_LOG(LogTemp, Warning, TEXT("one"));

			}
		}
	}
	
}

