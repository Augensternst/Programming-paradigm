/*2252709 ��@��*/
#include<iostream>
#include<vector>
using namespace std;

int maxprofit(vector<int>& prices)
{
    int n = prices.size();
    if (n <= 1)
        return 0;

    vector<int> buy(n, 0);
    vector<int> sell(n, 0);
    vector<int> rest(n, 0);

    buy[0] = -prices[0];

    for (int i = 1; i < n; i++) 
    {
        // �ڵ� i ����Ϣ��״̬��ǰһ��������Ʊ������䶳�ڻ���ǰһ����Ϣ״̬�����ֵ
        rest[i] = max(sell[i - 1], rest[i - 1]);
        // �ڵ� i �������Ʊ��Ҫô��ǰһ����Ϣ״̬ת�ƹ����ģ�Ҫô��ǰһ����й�Ʊ��״̬
        buy[i] = max(rest[i - 1] - prices[i], buy[i - 1]);
        // �ڵ� i ��������Ʊ��ֻ����ǰһ����й�Ʊ��״̬
        sell[i] = buy[i - 1] + prices[i];
    }

    // �������Ϊ���һ�첻���й�Ʊ�����ֵ
    return max(sell[n - 1], rest[n - 1]);
}

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
            cout << "���������ɹ�Ʊ�۸���0-1000��Χ��,����-1��������" << endl;
        }
        input = false;
        cin >> temp;
        if (temp == -1)
        {
            break;
        }
        else if (temp < 0 || temp > 1000)
        {
            cout << "�����Ʊ�۸���0-1000��Χ�ڣ�����������" << endl;
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
    // �����������
    int max_profit = maxprofit(prices);

    // ����������
    cout << "�������Ϊ: " << max_profit << endl;
    return 0;
}
