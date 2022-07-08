#include <iostream>
#include "BackPackItem.h"

void Gen_new_prices(std::vector<int>& prices)
{
	for (int i = 0; i < prices.size(); i++)
	{
		prices[i] = rand() % 5 + 1;
	}
}

void change_prices_to_spec_value_less_1(std::vector<int>& prices, std::vector<int>& weights)
{
	for (int i = 0; i < prices.size(); i++)
	{
		while (double(prices[i]) / weights[i] >= 1)
		{
			prices[i]--;
		}
	}

	for (int i = 0; i < prices.size(); i++)
	{
		while (double(prices[i]) / weights[i] <= 0.4)
		{
			prices[i]++;
		}
	}
}

int main()
	{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	//Вектор цен и веса
	std::vector<int> prices;
	std::vector<int> weights;
	//4 элемента 
	int elements = 5;
	//заполнение цены и веса
	for (int i = 0; i < elements; i++)
	{
		prices.push_back(rand() % 10 + 1);
		weights.push_back(rand() % 10 + 3);
	}
	change_prices_to_spec_value_less_1(prices, weights);

		/*
		//сортировка spec_price_to_weight
		int buff_weight = 0; // для временного хранения значения, при перезаписи
		int buff_price = 0; // для временного хранения значения, при перезаписи
		for (int i = 0; i < elements - 1; i++) // 
		{
			for (int j = elements - 1; j > i; j--)
			{
				if (double(prices[j])/weights[j] > double(prices[j-1]) / weights[j-1])
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
		//корректировка price, чтобы набор был (1,..., 1) НЕ ОЧЕНЬ ПОМОГАЕТ
		for (int i = 0; i < elements - 1; i++)
		{
			while (double(prices[i]) / weights[i] > double(prices[i+1]) / weights[i+1])
			{
				prices[i]--;
			}
		}
		*/
	
	//перменные вес и цена равны начальным
	std::vector<int> tmp_prices;
	std::vector<int> tmp_weights;
	std::vector<int> res_appr_prices;
	std::vector<int> res_appr_weights;
	tmp_prices = prices;
	tmp_weights = weights;
	//нормировка максимального веса
	int max_weight = 0;
	for (int i = 0; i < elements; i++)
	{
		max_weight = max_weight + tmp_weights[i];
	}
	//нормировка цены 
	int max_price_for_set_with_all_1 = 0;
	for (int i = 0; i < elements; i++)
	{
		max_price_for_set_with_all_1 = max_price_for_set_with_all_1 + tmp_prices[i];
	}
	//рюкзак с переменными веса и цены
	BackPackItem B(tmp_prices, tmp_weights, elements);

	size_t j = 0;
	size_t k = 0;
	//сортировка цены в соответсвтии и веса по возрастанию
	sort_price_with_weight(tmp_prices, tmp_weights);
	bool flag = true;
	int result = 0;
	B.Method_dynamic_programming(max_weight);
	B.print();
	std::cout << "des: " << B.Method_dynamic_programming(max_weight) << std::endl;
	std::cout << "approx: " << B.Approximate_to_k_elements(max_weight, res_appr_prices, res_appr_weights) << std::endl << std::endl;
	//B.Method_dynamic_programming_find_set(max_weight);
	/*
	while(flag)
	{
		Gen_new_prices(tmp_prices);
		BackPackItem B_tmp(tmp_prices, tmp_weights, elements);
		if (B.Method_dynamic_programming(max_weight) == tmp_result_price)
		{
			flag = false;
		}
		r++;

		if (r == 100)
		{
			///
		}
		
	}
	BackPackItem B_new(tmp_prices, tmp_weights, elements);
	B.print();
	std::cout << std::endl << B.Method_dynamic_programming(max_weight) << " " << B.Approximate_kZero(max_weight);
	*/
	//

	
	for (int i = 1; i < 10000; i++)
	{
		sort_price_with_weight(tmp_prices, tmp_weights);

		BackPackItem B(tmp_prices, tmp_weights, elements);
		result = B.Method_anneal(max_weight);
		//if(result != 1)
		//{
			std::cout << std::endl << std::endl;
		//}

		while (j < elements - (rand() % elements + 1))
		{
			tmp_prices[j] = tmp_prices[j] + rand() % 10 + 1;
			j = rand() % elements;
		}

		while (k < elements - (rand() % elements + 1))
		{
			tmp_weights[k] = tmp_weights[k] + rand() % 10 + 1;
			k = rand() % elements;
		}

		change_prices_to_spec_value_less_1(tmp_prices, tmp_weights);
	}
	
}