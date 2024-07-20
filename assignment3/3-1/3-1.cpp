#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

// �������ڼ���������Ƿ�����ظ���Ԫ��
bool contains_nums(vector<int>& nums)
{
	sort(nums.begin(), nums.end()); // �������������
	for (int i = 0; i < nums.size() - 1; i++)
	{
		if (nums[i + 1] == nums[i])
		{
			return true; // ����ҵ��ظ���Ԫ�أ�����true
		}
	}
	return false; // ���û���ҵ��ظ���Ԫ�أ�����false
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
			cout << "�����������ֵ���ÿո����������-1�س���������" << endl;
		}
		input = false;
		cin >> tem;
		if (tem == -1)
		{
			break; // �������-1�����������
		}
		else if (tem < -1000000000 || tem>1000000000 || !cin.good())
		{
			cout << "���������ڷ�Χ�ڣ�����������" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			nums.clear();
			continue; // ������벻�Ϸ���������뻺����������ѭ��
		}
		else
		{
			nums.push_back(tem); // ���Ϸ���Ԫ����ӵ�������
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
