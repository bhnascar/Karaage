// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyProject6.h"
#include "MyProject6GameMode.h"
#include "MyProject6Pawn.h"

AMyProject6GameMode::AMyProject6GameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AMyProject6Pawn::StaticClass();
}
