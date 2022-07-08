#pragma once

double factorial(int number)
{
	int res = 1;
	for (int j = 1; j <= number; j++)
	{
		res = res * j;
	}

	return res;
}

double combination(int n, int k)
{
	if (n == k)
	{
		return 1;
	}
	if (k == 1)
	{
		return n;
	}
	if (k == 0)
	{
		return 1;
	}

	return factorial(n) / (factorial(n - k) * factorial(k));
}