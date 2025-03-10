/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef WORLD_OBJECT_H
#define WORLD_OBJECT_H

#include "System/Object.h"
#include "System/float4.h"
#include "System/Threading/ThreadPool.h"

struct S3DModel;

class CWorldObject: public CObject
{
public:
	CR_DECLARE(CWorldObject)

	CWorldObject() = default;
	CWorldObject(const float3& pos, const float3& spd): CWorldObject()
	{
		SetPosition(pos);
		SetVelocity(spd);
	}

	virtual ~CWorldObject() {}

	// NOTE: used only by projectiles, SolidObject's override this!
	virtual float GetDrawRadius() const { return drawRadius; }
	virtual void  SetDrawRadius(float r) { drawRadius = r; }

	virtual void SetPosition(const float3& p) {   pos = p; }
	virtual void SetVelocity(const float3& v) { speed = v; }

	virtual void SetVelocityAndSpeed(const float3& v) {
		// set velocity first; do not assume f4::op=(f3) will not touch .w
		SetVelocity(v);
		SetSpeed(v);
	}

	// by default, SetVelocity does not set magnitude (for efficiency)
	// so SetSpeed must be explicitly called to update the w-component
	float SetSpeed(const float3& v) { return (speed.w = v.Length()); }

	void SetRadiusAndHeight(float r, float h) {
		radius = r;
		height = h;
		sqRadius = r * r;
		drawRadius = r;
	}

	void SetRadiusAndHeight(const S3DModel* model);

	// extrapolated base-positions; used in unsynced code
	float3 GetDrawPos(                float t) const { return (speed.w != 0.0f) ? (pos + speed * t) : pos; }
	float3 GetDrawPos(const float3 v, float t) const { return (pos +     v * t); }

	inline int GetMtTempNum() const { return mtTempNum[ThreadPool::GetThreadNum()]; }
	inline void SetMtTempNum(int value) { mtTempNum[ThreadPool::GetThreadNum()] = value; }

public:
	int id = -1;
	int tempNum = 0;            ///< used to check if object has already been processed (in QuadField queries, etc)

	float3 pos;                 ///< position of the very bottom of the object
	float4 speed;               ///< current velocity vector (elmos/frame), .w = |velocity|

	float radius = 0.0f;        ///< used for collisions
	float height = 0.0f;        ///< The height of this object
	float sqRadius = 0.0f;

	bool useAirLos = false;     ///< if true, the object's visibility is checked against airLosMap[allyteam]
	bool alwaysVisible = false; ///< if true, object is drawn even if not in LOS

	S3DModel* model = nullptr;
protected:
	float drawRadius = 0.0f;    ///< unsynced, used for projectile visibility culling

public:
	std::array<int, ThreadPool::MAX_THREADS> mtTempNum = {};
};

#endif /* WORLD_OBJECT_H */
