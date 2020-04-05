#include "MathUtils.h"

int MathUtils::GetRandomDiscreteDistribution(vector<float> weights)
{
	random_device rd;
	mt19937 generator(rd());

	discrete_distribution<int> discreteDistribution(weights.begin(), weights.end());

	return discreteDistribution(generator);
}