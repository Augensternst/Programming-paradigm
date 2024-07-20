#include<iostream>
#include<map>
#include<vector>
using namespace std;
unsigned max(int i, unsigned right);
// 函数用于检查数组中是否存在两个元素的差的绝对值小于等于给定的值
bool contains_nearby_almost_duplicate(const vector<int>& nuns, int indexDiff, int valueDiff)
{
	map<int, int> find_num; // 使用map来存储元素和它们的索引 

	for (unsigned int i = 0; i < nuns.size(); i++)
	{
		// 遍历整个数组
		for (unsigned int j = max(0, i - indexDiff); j < i; j++)
		{
			// 在索引范围内查找可能满足条件的元素对
			if (abs(static_cast<long long>(nuns[i]) - nuns[j]) <= valueDiff)
			{
				// 检查差的绝对值是否满足条件
				return true; // 如果满足条件，返回true
			}
		}
		find_num[nuns[i]] = i; // 将元素和它们的索引添加到map中
	} 
	return false; // 如果没有找到满足条件的元素对，返回false
}

int main()
{
	vector<int> nun;
	bool input = true;

	while (true)
	{
		int tem = 0;
		if (input)
		{
			cout << "请输入数组的值，用空格隔开，输入-1回车结束输入" << endl;
		}
		input = false;
		cin >> tem;

		if (tem == -1)
		{
			break; // 如果输入-1，则结束输入
		}
		if (tem < -1000000000 || tem > 1000000000 || !cin.good())
		{
			cout << "输入错误或不在范围内，请重新输入" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			nun.clear();
			continue; // 如果输入不合法，清除输入缓冲区并继续循环
		}
		nun.push_back(tem); // 将合法的元素添加到数组中
	}

	cout << "请输入整数 indexDiff 的值：" << endl;
	int index_diff = 0;

	while (true)
	{
		cin >> index_diff;

		if (index_diff < 0 || index_diff > nun.size() - 1 || !cin.good())
		{
			cout << "输入 indexDiff 的值不合法，请重新输入" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue; // 如果输入不合法，清除输入缓冲区并继续循环
		}
		break; // 如果输入合法，跳出循环
	}

	cout << "请输入整数 valueDiff 的值：" << endl;
	int value_diff = 0;

	while (true)
	{
		cin >> value_diff;

		if (value_diff < 0 || !cin.good())
		{
			cout << "输入 valueDiff 的值不合法，请重新输入" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue; // 如果输入不合法，清除输入缓冲区并继续循环
		}
		break; // 如果输入合法，跳出循环
	}

	if (contains_nearby_almost_duplicate(nun, index_diff, value_diff))
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

	return 0;
}
