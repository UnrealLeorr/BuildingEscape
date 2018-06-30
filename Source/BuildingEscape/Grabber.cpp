// anyone can use this trash

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//setting up the PhysicsHandle at the beggining of the game
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {//if PhysicsHandle is not nullptr anymore

		UE_LOG(LogTemp, Warning, TEXT("Physics Handler Found from:%s"),
			*(PhysicsHandle->GetOwner()->GetName())
		);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Physics Handler not Found from:%s"),
			*(GetOwner()->GetName()) 
		);
	}
	//setting up the InputComponent at the beggining of the game
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {//if InputComponent is not nullptr anymore

		UE_LOG(LogTemp, Warning, TEXT("Input Component Found from:%s"),
			*(InputComponent->GetOwner()->GetName())
		);
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Physics Component not Found from:%s"),
			*(GetOwner()->GetName())
		);
	}
	
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	FVector PlayerViewPointLocation;//this is a reference to the Player Location
	FRotator PlayerViewPointRotation;//this is a reference to the Player Rotation

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,// the get method takes the adress of a Fvector and put the value of of player location in it(a FVector from (0,0,0))
		OUT PlayerViewPointRotation// same thing to the rotation
	);//really weird Get lol
	
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*reach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		5.f
	);
	//line trace (aka raycast)

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());// set up to ignore the owner of the grabber, so the line trace dont keep tracing the owner

	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,//out mean it gets the thing and puts in Hit
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	if (Hit.GetActor()) {//if the pointer is not null
		UE_LOG(LogTemp, Log, TEXT("HIT! %s"),
			*(Hit.GetActor()->GetName())
		);
	}
}

