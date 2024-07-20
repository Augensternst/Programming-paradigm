#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

// 函数用于检查数组中是否存在重复的元素
bool contains_nums(vector<int>& nums)
{
	sort(nums.begin(), nums.end()); // 对数组进行排序
	for (int i = 0; i < nums.size() - 1; i++)
	{
		if (nums[i + 1] == nums[i])
		{
			return true; // 如果找到重复的元素，返回true
		}
	}
	return false; // 如果没有找到重复的元素，返回false
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
	if (contains_nums(nums))
	{
		cout << "true" << endl;
	}
	else
		cout << "false" << endl;

	return 0;
}
