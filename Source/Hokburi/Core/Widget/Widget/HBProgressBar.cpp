// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Widget/Widget/HBProgressBar.h"

void UHBProgressBar::Init(float NewCur, float NewMax)
{
	Cur = NewCur;
	Max = NewMax;
	SetPercent(Cur / Max);
}

void UHBProgressBar::UpdateCur(float NewCur)
{
	Cur = NewCur;
	SetPercent(Cur / Max);
}

void UHBProgressBar::UpdateMax(float NewMax)
{
	Max = NewMax;
	SetPercent(Cur / Max);
}
