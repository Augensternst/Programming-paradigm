#include<iostream>
#include<map>
#include<vector>
using namespace std;

// �������ڼ���������Ƿ����������ͬ��Ԫ�أ����ǵ���������� k
bool contain_suit_same_num(vector<int>& nums, int k)
{
	map<int, int> find_num; // ʹ��map���洢Ԫ�ؼ���������ֵ�����
	for (int i = 0; i < nums.size(); i++)
	{
		if (find_num.find(nums[i]) != find_num.end() && i - find_num[nums[i]] <= k)
			return true; // ����ҵ���ͬԪ������������� k������ true
		else
			find_num[nums[i]] = i; // �������Ԫ�ص�����
	}
	return false; // ���û���ҵ�����������Ԫ�ضԣ����� false
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
	cout << "����������k��ֵ" << endl;
	int k = 0;
	while (1)
	{
		cin >> k;
		if (k < 0 || k>100000 || !cin.good())
		{
			cout << "����k��ֵ���Ϸ�������������" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue; // ������벻�Ϸ���������뻺����������ѭ��
		}
		else
			break; // �������Ϸ�������ѭ��
	}
	if (contain_suit_same_num(nums, k))
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}
