// anyone can use this trash

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	reach = 100.f;

}
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//setting up the PhysicsHandle at the beggining of the game
	FindPhysicsHandleComponent();
	//setting up the InputComponent at the beggining of the game
	SetupInputComponent();
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerViewPointLocation;//this is a reference to the Player Location
	FRotator PlayerViewPointRotation;//this is a reference to the Player Rotation

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,// the get method takes the adress of a Fvector and put the value of of player location in it(a FVector from (0,0,0))
		OUT PlayerViewPointRotation// same thing to the rotation
	);//really weird Get lol

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*reach;
	// if we push the grab key, LINE TRACE and see if it reaches a physics body, if it does move it
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	// else do nothing.
	
}
//custom made methods
void UGrabber::FindPhysicsHandleComponent()
{
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
}
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {//if InputComponent is not nullptr anymore

		UE_LOG(LogTemp, Warning, TEXT("Input Component Found from:%s"),
			*(InputComponent->GetOwner()->GetName())
		);
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);//its the action, divided in two events.
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Physics Component not Found from:%s"),
			*(GetOwner()->GetName())
		);
	}
}
void UGrabber::Grab() {

	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	auto HitResult = GetFirstPhysicsBodyInReach();//if we press the grab key the whole method starts
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	//atach physics handle
	if (ActorHit) {
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Released Input!"));
	PhysicsHandle->ReleaseComponent();
	//release physics handle
}
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;//this is a reference to the Player Location
	FRotator PlayerViewPointRotation;//this is a reference to the Player Rotation

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,// the get method takes the adress of a Fvector and put the value of of player location in it(a FVector from (0,0,0))
		OUT PlayerViewPointRotation// same thing to the rotation
	);//really weird Get lol

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*reach;

	//line trace (aka raycast)

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());// set up to ignore the owner of the grabber, so the line trace dont keep tracing the owner

	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,//out mean it gets the thing and puts in Hit, essentially this the crucial part where we update the HIT variable with a valid data.
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
	return Hit;
}