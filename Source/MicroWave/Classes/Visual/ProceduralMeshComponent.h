// UE4 Procedural Mesh Generation from the Epic Wiki (https://wiki.unrealengine.com/Procedural_Mesh_Generation)
//
// forked from "Engine/Plugins/Runtime/CustomMeshComponent/Source/CustomMeshComponent/Classes/CustomMeshComponent.h"

#pragma once

#include "ProceduralMeshComponent.generated.h"

USTRUCT(BlueprintType)
struct FProceduralMeshVertex
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category=Triangle)
	FVector Position;

	UPROPERTY(EditAnywhere, Category=Triangle)
	FColor Color;

	UPROPERTY(EditAnywhere, Category=Triangle)
	float U;

	UPROPERTY(EditAnywhere, Category=Triangle)
	float V;
};

USTRUCT(BlueprintType)
struct FProceduralMeshTriangle
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category=Triangle)
	FProceduralMeshVertex Vertex0;

	UPROPERTY(EditAnywhere, Category=Triangle)
	FProceduralMeshVertex Vertex1;

	UPROPERTY(EditAnywhere, Category=Triangle)
	FProceduralMeshVertex Vertex2;
};

/** Component that allows you to specify custom triangle mesh geometry */
UCLASS(editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup=Rendering)
class UProceduralMeshComponent : public UMeshComponent, public IInterface_CollisionDataProvider
{
	GENERATED_UCLASS_BODY()

public:
	/** Set the geometry to use on this triangle mesh */
	// TODO: This is to be removed when the Actors get rid of the dependecy on this method
	UFUNCTION(BlueprintCallable, Category="Components|ProceduralMesh")
	bool SetProceduralMeshTriangles(const TArray<FProceduralMeshTriangle>& Triangles);

	/** Description of collision */
	UPROPERTY(BlueprintReadOnly, Category="Collision")
	class UBodySetup* ModelBodySetup;

	// Begin Interface_CollisionDataProvider Interface
	virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;
	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;
	virtual bool WantsNegXTriMesh() override{ return false; }
	// End Interface_CollisionDataProvider Interface

	// Begin UPrimitiveComponent interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual class UBodySetup* GetBodySetup() override;
	// End UPrimitiveComponent interface.

	// Begin UMeshComponent interface.
	virtual int32 GetNumMaterials() const override;
	// End UMeshComponent interface.

	void UpdateBodySetup();
	void UpdateCollision();

protected:

	/**
	* Set the triangles mesh.
	* @param Triangles - Array of triangles of the mesh.
	*/
	UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")
	void SetMesh(const TArray<FProceduralMeshTriangle>& Mesh);

private:
	// Begin USceneComponent interface.
	virtual FBoxSphereBounds CalcBounds(const FTransform & LocalToWorld) const override;
	// Begin USceneComponent interface.

	/** */
	TArray<FProceduralMeshTriangle> ProceduralMeshTris;

	friend class FProceduralMeshSceneProxy;
};
