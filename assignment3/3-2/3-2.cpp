#include<iostream>
#include<map>
#include<vector>
using namespace std;

// 函数用于检查数组中是否存在两个相同的元素，它们的索引差不超过 k
bool contain_suit_same_num(vector<int>& nums, int k)
{
	map<int, int> find_num; // 使用map来存储元素及其最近出现的索引
	for (int i = 0; i < nums.size(); i++)
	{
		if (find_num.find(nums[i]) != find_num.end() && i - find_num[nums[i]] <= k)
			return true; // 如果找到相同元素且索引差不超过 k，返回 true
		else
			find_num[nums[i]] = i; // 否则更新元素的索引
	}
	return false; // 如果没有找到满足条件的元素对，返回 false
}

int main()
{
	vector<int> nums;
	bool input = true;
	while (1)
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
		else if (tem < -1000000000 || tem>1000000000 || !cin.good())
		{
			cout << "输入错误或不在范围内，请重新输入" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			nums.clear();
			continue; // 如果输入不合法，清除输入缓冲区并继续循环
		}
		else
		{
			nums.push_back(tem); // 将合法的元素添加到数组中
		}
	}
	cout << "请输入整数k的值" << endl;
	int k = 0;
	while (1)
	{
		cin >> k;
		if (k < 0 || k>100000 || !cin.good())
		{
			cout << "输入k的值不合法，请重新输入" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue; // 如果输入不合法，清除输入缓冲区并继续循环
		}
		else
			break; // 如果输入合法，跳出循环
	}
	if (contain_suit_same_num(nums, k))
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}
