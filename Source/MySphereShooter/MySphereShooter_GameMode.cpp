// Fill out your copyright notice in the Description page of Project Settings.


#include "MySphereShooter_GameMode.h"
#include "MySphereShooter_SphereSpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "MySphereShooter_Sphere.h"
#include "Kismet/GameplayStatics.h"
#include "MySphereShooter_GameState.h"

AMySphereShooter_GameMode::AMySphereShooter_GameMode()
{

}

void AMySphereShooter_GameMode::OnSphereShot(AMySphereShooter_Sphere* ShotSphere)
{
    AMySphereShooter_GameState* GameStateReference = GetGameState<AMySphereShooter_GameState>();
    if (GameState != nullptr)
    {
        GameStateReference->IncNumberSpheresDestroyed();
    }
    if (!IsShotSphereNecessary(ShotSphere))
    {
        return;
    }
    IncrementNecessarySpheresDestroyedNumber();
}

void AMySphereShooter_GameMode::SpawnSpheres(float NewRadius, int32 NewSpawningSpheresNumber)
{

    float PreviousRadius = SphereSpawner->GetSpawningRadius();
    int32 PreviousSpawningNumber = SphereSpawner->GetSpawnedSpheresNumber();
    
    /*
    * In order not to lose sphere spawner parameters they are saved in Previous variables
    * And when spawning is done they are returned to sphere spawner
    */
    SetSphereSpawnerParameters(NewRadius, NewSpawningSpheresNumber);
    SphereSpawner->SpawnSpheresInRadius();
    SetSphereSpawnerParameters(PreviousRadius, PreviousSpawningNumber);
}

int32 AMySphereShooter_GameMode::GetUnnecessarySpheresAmount()
{ 
    /*
    * Sphere spawner contains a number of all generated spheres
    * Game mode contains a number of necessary spheres.
    * So unnecessary spheres amount = all spheres number - number of necessary spheres
    */
    
    int32 AllSpawningNumber = SphereSpawner->GetSpawnedSpheresNumber();

    float UnnecessarySpheresAmount = AllSpawningNumber - MinimumSpheresNumberToCompleteWave;
    if (UnnecessarySpheresAmount < 0)
    {
        UnnecessarySpheresAmount = 0;
    }

    return UnnecessarySpheresAmount;
}

void AMySphereShooter_GameMode::BeginPlay()
{
    Super::BeginPlay();
    if (IsValid(AMySphereShooter_SphereSpawner::StaticClass()))
    {
        FVector SpawnerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
        FRotator SpawnerRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

        SphereSpawner = GetWorld()->SpawnActor<AMySphereShooter_SphereSpawner>(SphereSpawnerClass, SpawnerLocation, SpawnerRotation);
        if (SphereSpawner != nullptr)
        {
            SphereSpawner->SetSpawnPoint(SpawnerLocation);
            SpawnSpheres(MinimumSpawningRadiusToCompleteWave, MinimumSpheresNumberToCompleteWave);
            SpawnSpheres(SphereSpawner->GetSpawningRadius(), GetUnnecessarySpheresAmount());
        }
    }
}

bool AMySphereShooter_GameMode::IsShotSphereNecessary(AMySphereShooter_Sphere* ShotSphere)
{
    FVector SpawnPoint = SphereSpawner->GetSpawnPoint();
    float Distance = UKismetMathLibrary::Vector_Distance(ShotSphere->GetActorLocation(), SpawnPoint);
    return UKismetMathLibrary::LessEqual_FloatFloat(Distance, MinimumSpawningRadiusToCompleteWave);
}

void AMySphereShooter_GameMode::DestroyRemainingSpheres() const
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMySphereShooter_Sphere::StaticClass(), FoundActors);
    for (AActor* ActorFound : FoundActors)
    {
        AMySphereShooter_Sphere* Sphere = Cast<AMySphereShooter_Sphere>(ActorFound);
        if (Sphere != nullptr)
        {
            Sphere->ShowEffectsBeforeDestroy();
            Sphere->Destroy();
        }    
    }
}

void AMySphereShooter_GameMode::IncrementNecessarySpheresDestroyedNumber()
{
    ++NecessarySpheresDestroyedNumber;
    
    if (NecessarySpheresDestroyedNumber == MinimumSpheresNumberToCompleteWave)
    {
        AMySphereShooter_GameState* GameStateReference = GetGameState<AMySphereShooter_GameState>();
        if (GameState != nullptr)
        {
            GameStateReference->IncWaveNumber();
        }
        NecessarySpheresDestroyedNumber = 0;
        DestroyRemainingSpheres();
        IncreaseSphereSpawnerParameters();
        
        SphereSpawner->SetSpawnPoint(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
        SpawnSpheres(MinimumSpawningRadiusToCompleteWave, MinimumSpheresNumberToCompleteWave);
        SpawnSpheres(SphereSpawner->GetSpawningRadius(), GetUnnecessarySpheresAmount());
    }
}

void AMySphereShooter_GameMode::IncreaseSphereSpawnerParameters()
{
    float PreviousRadius = SphereSpawner->GetSpawningRadius();
    int32 PreviousSpawningNumber = SphereSpawner->GetSpawnedSpheresNumber();

    float NewRadius = PreviousRadius * (1 + SpawningRadiusPercentageIncrease / 100.f);
    int32 NewSpawningNumber = PreviousSpawningNumber * (1 + SpheresAmountPercentageIncrease / 100.f);

    SetSphereSpawnerParameters(NewRadius, NewSpawningNumber);
}

void AMySphereShooter_GameMode::SetSphereSpawnerParameters(float Radius, int32 SpawningSpheresNumber)
{
    SphereSpawner->SetSpawnedSpheresNumber(SpawningSpheresNumber);
    SphereSpawner->SetSpawningRadius(Radius);
}
