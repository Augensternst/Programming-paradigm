#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> prices;
    bool input = true;

    // 输入股票价格，直到输入回车为止
    while (1)
    {
        int temp = 0;
        if (input)
        {
            cout << "请输入若干股票价格，在30-100范围内，输入-1结束输入" << endl;
        }
        input = false;
        cin >> temp;
        if (temp==-1)
        {
            break;
        }
        else if (temp < 30 || temp > 100)
        {
            cout << "输入股票价格不在30-100范围内，请重新输入" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            prices.clear(); // 清空容器
            continue;
        }
        else
        {
            prices.push_back(temp);
        }
    }
    vector<int>(prices).swap(prices);//运用swap收缩内存
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

    // 输出结果
    for (unsigned int i = 0; i < answer.size(); i++)
    {
        cout << answer[i] << " ";
    }
    return 0;
}
