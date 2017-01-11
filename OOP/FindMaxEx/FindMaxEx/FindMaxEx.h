#pragma once
template < typename T, typename Less>

bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	bool isFinded = true;
	if (arr.empty())
	{
		isFinded = false;
	}

	if (isFinded)
	{
		auto maxElem = arr.begin();
		for (auto it = arr.begin(); it != arr.end(); ++it)
		{
			if (less(*maxElem, *it))
			{
				maxElem = it;
			}
		}
		maxValue = *maxElem;
	}
	return isFinded;
}