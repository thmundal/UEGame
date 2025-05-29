#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDynamicGameEventTickPriority : uint8
{
	OnDemand,		// Only tick when requested
	Low,			// Tick after everything else if there is still time, might not tick in the frame if there is not enough time
	Normal,			// Tick after High, and can get deferred to next tick if there is not enough time, but will eventually get called
	High,			// Tick before Low, but ensure that it is called every tick interval
	Critical,		// Tick before everything else
	RealTime,		// Tick every frame, but not when the game is paused
	RealTimePaused,	// Tick every frame, even when the game is paused
};