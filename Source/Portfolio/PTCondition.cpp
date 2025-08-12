// Fill out your copyright notice in the Description page of Project Settings.


#include "PTCondition.h"


bool UPTCondition_ExistTarget::Condition() const
{
	return Target.IsValid();
}