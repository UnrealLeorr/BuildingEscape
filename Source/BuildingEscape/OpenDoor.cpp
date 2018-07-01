// anyone can use this trash

#include "OpenDoor.h"
#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor(){
// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
// off to improve performance if you don't need them.
PrimaryComponentTick.bCanEverTick = true;
OpenTime = 0.3f;
// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

void UOpenDoor::OpenDoor()
{
	AActor *Owner = GetOwner();
	FRotator NewRotation = FRotator(0, -180, 0);
	if (!Owner) { return; }
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
	AActor *Owner = GetOwner();
	FRotator NewRotation = FRotator(0, -90, 0);
	if (!Owner) { return; }
	Owner->SetActorRotation(NewRotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(GetTotalMassOnPlate() >= 20.f) {
		OpenDoor();
	}
	if (GetWorld()->GetRealTimeSeconds() >= LastOpenTime + OpenTime && GetTotalMassOnPlate() < 20.f) {
		CloseDoor();
	}
	// ...
}

float UOpenDoor::GetTotalMassOnPlate(){
	float TotalMass = 0.f;
	//find the overlaping actors in the pressure plate
	TArray<AActor*>Overlappers;
	if (!PressurePlate) { 
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate not Found from:%s"),
			*(GetOwner()->GetName())
		)
		return 0; 
	}
	PressurePlate->GetOverlappingActors(
		OUT Overlappers
	);//this should fill the array with the pointer to te actors
	//add their masses to total mass
	for (const auto &Iterator : Overlappers) {
		TotalMass += Iterator->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

