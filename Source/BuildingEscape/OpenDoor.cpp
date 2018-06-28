// anyone can use this trash

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
	Opener = GetWorld()->GetFirstPlayerController()->GetPawn(); // at the begining of play Opener becomes the first controlable pawn
}

void UOpenDoor::OpenDoor()
{
	AActor *Owner = GetOwner();
	FRotator NewRotation = FRotator(0, -180, 0);
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
	AActor *Owner = GetOwner();
	FRotator NewRotation = FRotator(0, -90, 0);
	Owner->SetActorRotation(NewRotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate->IsOverlappingActor(Opener)) {
		OpenDoor();
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetRealTimeSeconds() >= LastOpenTime + OpenTime) {
		CloseDoor();
	}
	// ...
}

