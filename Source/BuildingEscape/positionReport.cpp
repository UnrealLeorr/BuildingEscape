// Fill out your copyright notice in the Description page of Project Settings.

#include "positionReport.h"


// Sets default values for this component's properties
UpositionReport::UpositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UpositionReport::BeginPlay()
{
	Super::BeginPlay();//begins the Inherited constructor

	// ...
	
}


// Called every frame
void UpositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);//begins the Inherited constructor

	// ...
}

