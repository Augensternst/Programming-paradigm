#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> prices;
    bool input = true;

    // �����Ʊ�۸�ֱ������س�Ϊֹ
    while (1)
    {
        int temp = 0;
        if (input)
        {
            cout << "���������ɹ�Ʊ�۸���30-100��Χ�ڣ�����-1��������" << endl;
        }
        input = false;
        cin >> temp;
        if (temp==-1)
        {
            break;
        }
        else if (temp < 30 || temp > 100)
        {
            cout << "�����Ʊ�۸���30-100��Χ�ڣ�����������" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            prices.clear(); // �������
            continue;
        }
        else
        {
            prices.push_back(temp);
        }
    }
    vector<int>(prices).swap(prices);//����swap�����ڴ�
    vector<int> answer(prices.size(), 0);

    for (unsigned int i = 0; i < prices.size(); i++)
    {
        for (unsigned int j = i + 1; j < prices.size(); j++)
        {
            if (prices[j] > prices[i])
            {
                answer[i] = j - i;
                break;
            }
        }
    }

    // ������
    for (unsigned int i = 0; i < answer.size(); i++)
    {
        cout << answer[i] << " ";
    }
    return 0;
}
