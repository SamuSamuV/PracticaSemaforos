#include "CubeAgent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACubeAgent::ACubeAgent()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Crear y configurar el componente de malla estática
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // Configurar valores por defecto
    MovementSpeed = 200.0f;
    CloseEnoughDistance = 50.0f;
    CurrentTargetIndex = 0;
}

// Called when the game starts or when spawned
void ACubeAgent::BeginPlay()
{
    Super::BeginPlay();

    // Verificar que hay puntos de destino asignados
    if (TargetPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No hay Target Points asignados al CubeAgent"));
    }
}

// Called every frame
void ACubeAgent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TargetPoints.Num() > 0)
    {
        MoveToTarget(DeltaTime);
    }
}

void ACubeAgent::MoveToTarget(float DeltaTime)
{
    // Obtener el punto de destino actual
    ATargetPoint* CurrentTarget = TargetPoints[CurrentTargetIndex];

    if (CurrentTarget)
    {
        // Calcular dirección hacia el objetivo
        FVector Direction = CurrentTarget->GetActorLocation() - GetActorLocation();
        Direction.Normalize();

        // Calcular la nueva posición
        FVector NewLocation = GetActorLocation() + Direction * MovementSpeed * DeltaTime;

        // Mover el actor
        SetActorLocation(NewLocation);

        // Verificar si hemos llegado lo suficientemente cerca del objetivo
        float DistanceToTarget = FVector::Dist(GetActorLocation(), CurrentTarget->GetActorLocation());

        if (DistanceToTarget < CloseEnoughDistance)
        {
            // Pasar al siguiente punto de destino
            CurrentTargetIndex = (CurrentTargetIndex + 1) % TargetPoints.Num();
        }
    }
}