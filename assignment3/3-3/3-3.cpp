#include<iostream>
#include<map>
#include<vector>
using namespace std;
unsigned max(int i, unsigned right);
// �������ڼ���������Ƿ��������Ԫ�صĲ�ľ���ֵС�ڵ��ڸ�����ֵ
bool contains_nearby_almost_duplicate(const vector<int>& nuns, int indexDiff, int valueDiff)
{
	map<int, int> find_num; // ʹ��map���洢Ԫ�غ����ǵ����� 

	for (unsigned int i = 0; i < nuns.size(); i++)
	{
		// ������������
		for (unsigned int j = max(0, i - indexDiff); j < i; j++)
		{
			// ��������Χ�ڲ��ҿ�������������Ԫ�ض�
			if (abs(static_cast<long long>(nuns[i]) - nuns[j]) <= valueDiff)
			{
				// ����ľ���ֵ�Ƿ���������
				return true; // �����������������true
			}
		}
		find_num[nuns[i]] = i; // ��Ԫ�غ����ǵ�������ӵ�map��
	} 
	return false; // ���û���ҵ�����������Ԫ�ضԣ�����false
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
			cout << "�����������ֵ���ÿո����������-1�س���������" << endl;
		}
		input = false;
		cin >> tem;

		if (tem == -1)
		{
			break; // �������-1�����������
		}
		if (tem < -1000000000 || tem > 1000000000 || !cin.good())
		{
			cout << "���������ڷ�Χ�ڣ�����������" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			nun.clear();
			continue; // ������벻�Ϸ���������뻺����������ѭ��
		}
		nun.push_back(tem); // ���Ϸ���Ԫ����ӵ�������
	}

	cout << "���������� indexDiff ��ֵ��" << endl;
	int index_diff = 0;

	while (true)
	{
		cin >> index_diff;

		if (index_diff < 0 || index_diff > nun.size() - 1 || !cin.good())
		{
			cout << "���� indexDiff ��ֵ���Ϸ�������������" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue; // ������벻�Ϸ���������뻺����������ѭ��
		}
		break; // �������Ϸ�������ѭ��
	}

	cout << "���������� valueDiff ��ֵ��" << endl;
	int value_diff = 0;

	while (true)
	{
		cin >> value_diff;

		if (value_diff < 0 || !cin.good())
		{
			cout << "���� valueDiff ��ֵ���Ϸ�������������" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue; // ������벻�Ϸ���������뻺����������ѭ��
		}
		break; // �������Ϸ�������ѭ��
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
