#pragma once
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace olc;

const uint64_t NumRuns = 12;					// Number of runs per parameter combination
const uint64_t NumTrainingPerRuns = 100;		// Number of error saples per run
const uint64_t NumTrainingBeforeSample = 100;	// Number of training runs between each sample

const uint64_t NumRequiredConsecutiveOks = 4;	// Number of consecutive oks parameters we will be testing
const uint64_t NumGradientPrecision = 4;		// Number of precision parameters we will be testing
const uint64_t NumLearningRate = 4;				// Number of learning rate parameters we will be testing
const uint64_t NumPhantomCoefficient = 4;		// Number of phantom coefficient parameters we will be testing

const uint64_t NumItems = NumRequiredConsecutiveOks * NumGradientPrecision * NumLearningRate * NumPhantomCoefficient;	// The total number of combinations of parameters we will be testing