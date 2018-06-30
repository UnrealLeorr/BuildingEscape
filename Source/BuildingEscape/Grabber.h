// anyone can use this trash

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

private:

	UPhysicsHandleComponent *PhysicsHandle = nullptr;

	float reach;
	//findOwnerPhysicsHandle
	void FindPhysicsHandleComponent();
	//input events
	UInputComponent *InputComponent = nullptr;
	void SetupInputComponent();
	void Grab();
	void Release();
	//hot loops
	//return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;

};
