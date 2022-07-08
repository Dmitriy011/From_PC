#pragma once

#include <iostream>
#include <vector>
#include <time.h>

#include <cmath>

#include <limits>
#include <iostream>
#include <cmath>
#include <algorithm>

void check_vect_same_el(std::vector<size_t>& zero_indexes, int count_elements)
{
	for (int i = 0; i < zero_indexes.size(); i++)
	{
		for (int j = 0; j < zero_indexes.size(); j++)
		{
			if (i != j && zero_indexes[i] == zero_indexes[j])
			{
				zero_indexes[j] = (zero_indexes[j] + 1) % count_elements;
			}
		}
	}
}

bool NextSet(std::vector<size_t>& _set, int n, int m)
{
	int k = m;

	for (int i = k - 1; i >= 0; --i)
	{
		if (_set[i] < n - k + i + 1)
		{
			++_set[i];
			for (int j = i + 1; j < k; ++j)
			{
				_set[j] = _set[j - 1] + 1;
			}
			return true;
		}
	}

	return false;
}

void sort_price_with_weight(std::vector<int>& prices, std::vector<int>& weights)
{
	int buff_weight = 0; // для временного хранения значения, при перезаписи
	int buff_price = 0; // для временного хранения значения, при перезаписи
	for (int i = 0; i < prices.size() - 1; i++) // 
	{
		for (int j = prices.size() - 1; j > i; j--)
		{
			if (prices[j] < prices[j - 1])
			{
				buff_weight = weights[j - 1];
				weights[j - 1] = weights[j];
				weights[j] = buff_weight;

				buff_price = prices[j - 1];
				prices[j - 1] = prices[j];
				prices[j] = buff_price;
			}
		}
	}
}

void change_prices_to_spec_value_less_1(std::vector<int>& prices, std::vector<int>& weights);

class BackPackItem
{
public:
	BackPackItem();
	BackPackItem(std::vector<int>& prices, std::vector<int>& weights, size_t _elements);

	float Plunk(float _MaxWeight, bool _printOrnot = 0);
	float Greedy(float _MaxWeight, bool _printOrnot = 0);
	
	int Approximate_to_k_elements(float _MaxWeight, std::vector<int>& res_vec_prices, std::vector<int>& res_vec_weights)
	{
		srand(time(NULL));
		double res_price = 0.0;
		size_t count_zero_elements = 3;

		std::vector<int> tmp_prices;
		std::vector<int> tmp_weights;
		std::vector<size_t> indexes;
		for (size_t i = 0; i < count_elements; i++)
		{
			indexes.push_back(i + 1);
		}
		for (size_t i = 0; i < count_elements - count_zero_elements; i++)
		{
			//1)
			tmp_prices.push_back(0);
			tmp_weights.push_back(0);
		}
		
		/*
		//3)
		tmp_prices = prices;
		tmp_weights = weights;
		int buff_weight = 0; // для временного хранения значения, при перезаписи
		int buff_price = 0; // для временного хранения значения, при перезаписи
		for (int i = 0; i < count_elements - 1; i++) // 
		{
			for (int j = count_elements - 1; j > i; j--)
			{
				if (tmp_weights[j] < tmp_weights[j - 1])
				{
					buff_weight = tmp_weights[j - 1];
					tmp_weights[j - 1] = tmp_weights[j];
					tmp_weights[j] = buff_weight;

					buff_price = tmp_prices[j - 1];
					tmp_prices[j - 1] = tmp_prices[j];
					tmp_prices[j] = buff_price;
				}
			}
		}


		std::vector<int> end_prices;
		std::vector<int> end_weights;
		for (size_t i = 0; i < count_elements - count_zero_elements; i++)
		{
			end_prices.push_back(tmp_prices[i]);
			end_weights.push_back(tmp_weights[i]);
		}
		BackPackItem tmp_backpack(tmp_prices, tmp_weights, count_elements - count_zero_elements);
		res_price = tmp_backpack.Method_dynamic_programming(_MaxWeight);
		*/

		/*
		//2)
		std::vector<int> end_prices;
		std::vector<int> end_weights;
		for (size_t i = 0; i < count_elements - count_zero_elements; i++)
		{
			end_prices.push_back(0);
			end_weights.push_back(0);
		}

		tmp_prices = prices;
		tmp_weights = weights;
		for (int i = 0; i < count_zero_elements; i++)
		{
			tmp_prices.pop_back();
			tmp_weights.pop_back();
		}

		BackPackItem tmp_backpack(tmp_prices, tmp_weights, count_elements - count_zero_elements);
		res_price = tmp_backpack.Method_dynamic_programming(_MaxWeight);
		*/



		/*
		//1)
		std::vector<int> end_prices;
		std::vector<int> end_weights;
		for (size_t i = 0; i < count_elements - count_zero_elements; i++)
		{
			end_prices.push_back(0);
			end_weights.push_back(0);
		}
		for (size_t i = 0; i < count_elements - count_zero_elements; i++)
		{
			tmp_prices[i] = prices[indexes[i]];
			tmp_weights[i] = weights[indexes[i]];
		}

		std::vector<size_t> tmp_indexes;
		while (NextSet(indexes, count_elements - 1, count_elements - count_zero_elements))
		{
			for (size_t i = 0; i < count_elements - count_zero_elements; i++)
			{
				tmp_prices[i] = prices[indexes[i]];
				tmp_weights[i] = weights[indexes[i]];
			}

			BackPackItem tmp_backpack(tmp_prices, tmp_weights, count_elements - count_zero_elements);
			float tmp_res_price = tmp_backpack.Method_dynamic_programming(_MaxWeight);

			if (tmp_res_price > res_price)
			{
				end_prices = tmp_prices;
				end_weights = tmp_weights;
				res_price = tmp_res_price;
			}
		}
		*/

		
		//4)
		int m = 2;
		std::vector<int> test_p;
		std::vector<int> test_w;
		for(int i =0; i < m; i++)
		{
			test_p.push_back(prices[indexes[i] - 1]);
			test_w.push_back(weights[indexes[i] - 1]);
		}
		BackPackItem test_back(test_p, test_w, m);
		if (res_price < test_back.Method_dynamic_programming(_MaxWeight))
		{
			res_price = test_back.Method_dynamic_programming(_MaxWeight);
		}
		res_vec_prices = test_p;
		res_vec_weights = test_w;
		while (NextSet(indexes, count_elements, m))
		{
			for (int i = 0; i < m; i++)
			{
				test_p.pop_back();
				test_w.pop_back();
			}

			for (int i = 0; i < m; i++)
			{
				test_p.push_back(prices[indexes[i] - 1]);
				test_w.push_back(weights[indexes[i] - 1]);
			}

			BackPackItem test_b_2(test_p, test_w, m);
			if (res_price < test_b_2.Method_dynamic_programming(_MaxWeight))
			{
				res_price = test_b_2.Method_dynamic_programming(_MaxWeight);

				res_vec_prices = test_p;
				res_vec_weights = test_w;
			}
		}

		return res_price;	
	}

	float Method_anneal(float _MaxWeight)
	{
		srand(time(NULL));

		int z = 0;
		float sum_of_elems = 0;
		float inf_ratio = 1;
		float tmp_inf_ratio = 1;
		int tmp_MaxWeight = _MaxWeight;
		int price_approx = 0;
		int price_dynamic_programming = 0;

		size_t i = 0;
		size_t j = 0;
		size_t k = 0;

		std::vector<int> tmp_prices;
		std::vector<int> tmp_weights;
		size_t tmp_elements = 0;

		tmp_prices = prices;
		tmp_weights = weights;
		tmp_elements = count_elements;

		std::vector<int> res_prices;
		std::vector<int> res_weights;
		double res_price_dynamic_programming = 0;
		double res_price_approx = 0;
		int res_max_weight = 0;
		std::vector<int> res_appr_prices;
		std::vector<int> res_appr_weights;
		std::vector<int> tmp_appr_prices;
		std::vector<int> tmp_appr_weights;

		std::vector<double> temperature;
		temperature.push_back(10000000);
		float temperature_min = 10;

		while (temperature[i] > temperature_min)
		{
			BackPackItem B(tmp_prices, tmp_weights, tmp_elements);

			int tmp_max_weight = 0;
			for (int i = 0; i < tmp_elements; i++)
			{
				tmp_max_weight = tmp_max_weight + B.weights[i];
				tmp_MaxWeight = tmp_max_weight;
			}

			price_approx = B.Approximate_to_k_elements(tmp_max_weight, tmp_appr_prices, tmp_appr_weights);
			price_dynamic_programming = B.Method_dynamic_programming(tmp_max_weight);
			if(price_dynamic_programming != 0)
			{
				tmp_inf_ratio = double(price_approx) / double(price_dynamic_programming);
			}
			
			if (tmp_inf_ratio <= inf_ratio)
			{
				inf_ratio = tmp_inf_ratio;

				res_price_approx = price_approx;
				res_price_dynamic_programming = price_dynamic_programming;

				res_prices = tmp_prices;
				res_weights = tmp_weights;

				res_appr_prices = tmp_appr_prices;
				res_appr_weights = tmp_appr_weights;

				res_max_weight = tmp_MaxWeight;
			}
			/*
			else
			{
				float probability = exp(-(inf_ratio - tmp_inf_ratio) * temperature[i]);
				if (float(rand() % 1) < probability)
				{
					inf_ratio = tmp_inf_ratio;
				}
				else
				{
					//go next
				}
			}
			*/

			for (int k = 0; k < count_elements; k++)
			{
				if (rand() % 2)
				{
					tmp_prices[k] = (tmp_prices[k] + pow(-1, rand() % 2) * (rand() % 27 + 1));
				}

				if (tmp_prices[k] <= 0)
				{
					tmp_prices[k] = tmp_prices[k] * (-1) + 1;
				}

				tmp_prices[k] = tmp_prices[k] % 2000 + 1;
			}


			for (int k = 0; k < count_elements; k++)
			{
				if (rand() % 2)
				{
					tmp_weights[k] = (tmp_weights[k] + pow(-1, rand() % 2) * (rand() % 27 + 1));
				}

				if (tmp_weights[k] <= 0)
				{
					tmp_weights[k] = tmp_weights[k] * (-1) + 1;
				}

				tmp_weights[k] = tmp_weights[k] % 2000 + 1;
			}
			
			
			/*
			while (j < count_elements - (rand() % count_elements + 1))
			{
				tmp_prices[j] = (tmp_prices[j] + (rand() % 2 + 1) )% 100 + 1; //цена от 0 до 50
				j = rand() % count_elements;
			}
			while (k < count_elements - (rand() % count_elements + 1))
			{
				tmp_weights[k] = (tmp_weights[k] + rand() % 2 + 1) % 50 + 1; // Вес от 0 до 10
				k = rand() % count_elements;
			}
			*/
			

			change_prices_to_spec_value_less_1(tmp_prices, tmp_weights);

			temperature.push_back(temperature[0] * 0.1 / (i + 1));
			i++;
		}

		sort_price_with_weight(res_prices, res_weights);

		/*
		int w = 0;
		int interv_searching = 15;
		std::vector<int> last_tmp_prices;
		std::vector<int> last_tmp_weights;
		last_tmp_prices = tmp_prices;
		last_tmp_weights = tmp_weights;
		while (w < 100)
		{
			for (int k = 0; k < count_elements; k++)
			{
				if (rand() % 2)
				{
					tmp_prices[k] = (tmp_prices[k] + pow(-1, rand() % 2) * (rand() % 13 + 1));
				}

				if (tmp_prices[k] < last_tmp_prices[k] - interv_searching || last_tmp_prices[k] - interv_searching <= 0)
				{
					if (last_tmp_prices[k] - interv_searching <= 0)
					{
						tmp_prices[k] = last_tmp_prices[k];
						break;
					}
					else
					{
						tmp_prices[k] = last_tmp_prices[k] - interv_searching;
						break;
					}		
				}

				if (tmp_prices[k] > last_tmp_prices[k] + interv_searching)
				{
					tmp_prices[k] = last_tmp_prices[k];
					break;
				}
			}


			for (int k = 0; k < count_elements; k++)
			{
				if (rand() % 2)
				{
					tmp_weights[k] = (tmp_weights[k] + pow(-1, rand() % 2) * (rand() % 7 + 1));
				}

				if (tmp_weights[k] < last_tmp_weights[k] - interv_searching || last_tmp_weights[k] - interv_searching <= 0)
				{
					if (last_tmp_weights[k] - interv_searching <= 0)
					{
						tmp_weights[k] = last_tmp_weights[k];
						break;
					}
					else
					{
						tmp_weights[k] = last_tmp_weights[k] - interv_searching;
						break;
					}
					
				}

				if (tmp_weights[k] > last_tmp_weights[k] + interv_searching)
				{
					tmp_weights[k] = last_tmp_weights[k];
					break;
				}
			}

			BackPackItem B(tmp_prices, tmp_weights, tmp_elements);

			int tmp_max_weight = 0;
			for (int i = 0; i < tmp_elements; i++)
			{
				tmp_max_weight = tmp_max_weight + B.weights[i];
				tmp_MaxWeight = tmp_max_weight;
			}

			price_approx = B.Approximate_to_k_elements(tmp_max_weight, tmp_appr_prices, tmp_appr_weights);
			price_dynamic_programming = B.Method_dynamic_programming(tmp_max_weight);
			if (price_dynamic_programming != 0)
			{
				tmp_inf_ratio = double(price_approx) / double(price_dynamic_programming);
			}

			if (tmp_inf_ratio <= inf_ratio)
			{
				inf_ratio = tmp_inf_ratio;

				res_price_approx = price_approx;
				res_price_dynamic_programming = price_dynamic_programming;

				res_prices = tmp_prices;
				res_weights = tmp_weights;

				res_appr_prices = tmp_appr_prices;
				res_appr_weights = tmp_appr_weights;

				res_max_weight = tmp_MaxWeight;
			}


			w++;
		}
		*/
		

		//if(inf_ratio != 1)
		//{
			std::cout << "Prices: ";
			for (int i = 0; i < count_elements; i++)
			{
				std::cout << res_prices[i] << ", ";
			}
			std::cout << std::endl << "Weights: ";
			for (int i = 0; i < count_elements; i++)
			{
				std::cout << res_weights[i] << ", ";
			}
			std::cout << std::endl << "Appr prices : ";
			for (int i = 0; i < res_appr_prices.size() ;i++)
			{
				std::cout << res_appr_prices[i] << ", ";
			}
			std::cout << std::endl << "Appr weights: ";
			for (int i = 0; i < res_appr_prices.size(); i++)
			{
				std::cout << res_appr_weights[i] << ", ";
			}
			std::cout << std::endl << "MaxWeight: " << res_max_weight << std::endl << inf_ratio << " " << res_price_approx << " " << res_price_dynamic_programming;
		//}
		

		return inf_ratio;
	}


	float iteration100_to_compare(float _MaxWeight)
	{
		float inf_ratio = 1;
		float tmp_inf_ratio = 1;
		size_t i = 1;
		size_t j = 0;
		size_t k = 0;
		std::vector<int> tmp_prices;
		std::vector<int> tmp_weights;
		size_t tmp_elements = 0;
		BackPackItem A;
		tmp_prices = A.prices;
		tmp_weights = A.weights;
		tmp_elements = A.count_elements;
		std::vector<float> temperature;
		float temperature_min = 0;

		while (i < 100)
		{
			srand(time(NULL));
			while (j < count_elements - (rand() % count_elements + 1))
			{
				tmp_prices[j] = tmp_prices[j] + rand() % 10 + 1;
				j = rand() % count_elements;
			}

			while (k < count_elements - (rand() % count_elements + 1))
			{
				tmp_weights[k] = tmp_weights[k] + rand() % 10 + 1;
				k = rand() % count_elements;
			}

			BackPackItem B(tmp_prices, tmp_weights, tmp_elements);

			// РАЗКОММЕНТИРОВАТЬ tmp_inf_ratio = B.Approximate_kZero(_MaxWeight) / B.Plunk(_MaxWeight);

			if (tmp_inf_ratio < inf_ratio)
			{
				inf_ratio = tmp_inf_ratio;
			}

			i++;

			/*
			BackPackItem A;
			tmp_inf_ratio = A.approximate_kZero(_MaxWeight) / A.Plunk(_MaxWeight);

			if (tmp_inf_ratio < inf_ratio)
			{
				inf_ratio = tmp_inf_ratio;
			}
			i++;
			*/
		}

		return inf_ratio;
	}

	int Method_dynamic_programming(int max_weight)
	{
		int size_n = prices.size();
		int size_m = max_weight;

		std::vector<std::vector <int>> d_i_c(size_n + 1, std::vector<int>(size_m + 1));

		for (int i = 0; i <= max_weight; i++)
		{
			d_i_c[0][i];
		}

		for (int i = 1; i <= size_n; i++)
		{
			for (int j = 1; j <= max_weight; j++)
			{
				if (j <= weights[i - 1] - 1 && j >= 0)
				{
					d_i_c[i][j] = d_i_c[i - 1][j];
				}
				else
				{
					int value1 = d_i_c[i - 1][j];
					int value2 = d_i_c[i][j - weights[i - 1]] + prices[i - 1];
					int value = std::max(value1, value2);
					d_i_c[i][j] = value;
				}
			}
		}

		return d_i_c[size_n][max_weight];
	}

	std::vector<int> Method_dynamic_programming_find_set(int max_weight)
	{
		int size_n = prices.size();
		int size_m = max_weight;

		std::vector<std::vector <int>> d_i_c(size_n + 1, std::vector<int>(size_m + 1));

		for (int i = 0; i <= max_weight; i++)
		{
			d_i_c[0][i];
		}

		for (int i = 1; i <= size_n; i++)
		{
			for (int j = 1; j <= max_weight; j++)
			{
				if (j <= weights[i - 1] - 1 && j >= 0)
				{
					d_i_c[i][j] = d_i_c[i - 1][j];
				}
				else
				{
					int value1 = d_i_c[i - 1][j];
					int value2 = d_i_c[i][j - weights[i - 1]] + prices[i - 1];
					int value = std::max(value1, value2);
					d_i_c[i][j] = value;
				}
			}
		}

		std::vector<int> ans;
		to_help(count_elements, max_weight, d_i_c, ans);

		return ans;
	}

	void to_help(int k, int s, std::vector<std::vector <int>> d_i_c, std::vector<int>& ans)
	{
		if (d_i_c[k][s] == 0)
		{
			return;
		}

		if (d_i_c[k - 1][s] == d_i_c[k][s])
		{
			to_help(k - 1, s, d_i_c, ans);
		}
		else
		{
			to_help(k - 1, s - weights[k], d_i_c, ans);
			ans.push_back(k);
		}
	}

	void print(std::vector<int>& prices, std::vector<int>& weights, std::vector<float>& _SpecValue, size_t _elements) const;
	void print() const;



	~BackPackItem();

private:
	std::vector<int> prices;
	std::vector<int> weights;
	std::vector<float> SpecValue;
	size_t count_elements;

	void swap(int& a, int& b);
	void swap(float& a, float& b);
};

BackPackItem::BackPackItem()
{
	srand(time(NULL));

	count_elements = 10;
	for (int i = 0; i < count_elements; i++)
	{
		prices.push_back(rand() % 10 + 1);
		weights.push_back(rand() % 10 + 1);
		SpecValue.push_back(double(prices[i]) / double(weights[i]));
	}
}

BackPackItem::BackPackItem(std::vector<int>& _prices, std::vector<int>& _weights, const size_t _elements)
{
	count_elements = _elements;
	for (int i = 0; i < count_elements; i++)
	{
		prices.push_back(_prices[i]);
		weights.push_back(_weights[i]);
		SpecValue.push_back(double(prices[i]) / double(weights[i]));
	}
}

inline float BackPackItem::Greedy(const float _MaxWeight, bool _printOrnot)
{
	int Count_items = 0;

	float SumWeights = 0;
	float SumPrice = 0;

	for (int i = 0; i < count_elements - 1; i++)
	{
		for (int j = i + 1; j < count_elements; j++)
		{
			if ((SpecValue[i] < SpecValue[j]) || ((SpecValue[i] == SpecValue[j]) && (weights[i] < weights[j])))
			{
				swap(prices[i], prices[j]);
				swap(weights[i], weights[j]);
				swap(SpecValue[i], SpecValue[j]);
			}
		}
	}

	if(_printOrnot == 1)
	{
		std::cout << "Sorted items:" << std::endl;
		print(prices, weights, SpecValue, count_elements);
	}

	for (int i = 0; i < count_elements; i++)
	{
		if (SumWeights + weights[i] <= _MaxWeight)
		{
			SumWeights = SumWeights + weights[i];
			SumPrice = SumPrice + prices[i];
			Count_items++;
		}
		else
		{
			break;
		}
	}

	if (_printOrnot == 1)
	{
		print(prices, weights, SpecValue, Count_items);
		std::cout << "Answer Greedy: ";
		std::cout << "Weidth, Price, Count_items: " << SumWeights << ", " << SumPrice << ", " << Count_items;
	}

	return SumPrice;
}

inline float BackPackItem::Plunk(float _MaxWeight, bool _printOrnot)
{
	size_t count_subsets = pow(2, count_elements);
	int weidth_candidate = 0;
	int tmp_weidth = 0;
	int price_candidate = 0;
	int tmp_price = 0;
	std::vector<size_t> multiplicity0;
	std::vector<int> subset_candidate;
	for (size_t i = 0; i < count_elements; i++)
	{
		subset_candidate.push_back(-1);
	}
	for (size_t i = 0; i < count_elements; i++)
	{
		multiplicity0.push_back(i);
	}

	if (_printOrnot == 1)
	{
		std::cout << std::endl;
	}

	for (size_t i = 0; i < count_subsets; i++)
	{
		for (size_t j = 0; j < count_elements; j++)
		{
			if ((i >> j) & 1)
			{
				subset_candidate[j] = multiplicity0[j];
			}
		}

		if (_printOrnot == 1)
		{
			std::cout << "Subset" << i << ": ";
		}
		for (size_t q = 0; q < count_elements; q++)
		{
			if (_printOrnot == 1)
			{
				std::cout << subset_candidate[q] << ", ";
			}

			if (subset_candidate[q] != -1)
			{
				tmp_weidth = tmp_weidth + weights[q];
				tmp_price = tmp_price + prices[q];
			}
		}
		if (_printOrnot == 1)
		{
			std::cout << " \t" << "Weidth, Price: " << tmp_weidth << ", " << tmp_price << std::endl;
		}

		if (tmp_weidth <= _MaxWeight && tmp_price > price_candidate)
		{
			price_candidate = tmp_price;
			weidth_candidate = tmp_weidth;
		}

		tmp_weidth = 0;
		tmp_price = 0;
		for (size_t p = 0; p < count_elements; p++)
		{
			subset_candidate[p] = -1;
		}
	}

	if (_printOrnot == 1)
	{
		std::cout << "ANSWER Plunk: " << "Weidth, Price: " << weidth_candidate << ", " << price_candidate << std::endl;
	}
	
	return price_candidate;
}

inline void BackPackItem::print(std::vector<int>& prices, std::vector<int>& weights, std::vector<float>& _SpecValue, size_t _elements) const
{
	std::cout  << "Price \t" << "Weight \t" << "SpecValue" << std::endl;

	for (int i = 0; i < _elements; i++)
	{
		std::cout << prices[i] << "\t" << weights[i] << "\t" << _SpecValue[i] << std::endl;
	}
}

inline void BackPackItem::print() const
{
	std::cout << "Price \t" << "Weight \t" << "SpecValue" << std::endl;

	for (int i = 0; i < count_elements; i++)
	{
		std::cout << prices[i] << "\t" << weights[i] << "\t" << SpecValue[i] << std::endl;
	}
}

inline void BackPackItem::swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

inline void BackPackItem::swap(float& a, float& b)
{
	float tmp = a;
	a = b;
	b = tmp;
}

BackPackItem::~BackPackItem()
{
}
