#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h" // Incluir el header correcto para TargetPoint
#include "CubeAgent.generated.h"

UCLASS()
class PRACTICASEMAFOROS_API ACubeAgent : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACubeAgent();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Propiedades editables en el editor
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MovementSpeed;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float CloseEnoughDistance;

    UPROPERTY(EditAnywhere, Category = "Target Points")
    TArray<class ATargetPoint*> TargetPoints;

private:
    // Índice del punto de destino actual
    int32 CurrentTargetIndex;

    // Referencia al componente de malla estática
    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* MeshComponent;

    // Función para mover el cubo hacia el objetivo actual
    void MoveToTarget(float DeltaTime);
};