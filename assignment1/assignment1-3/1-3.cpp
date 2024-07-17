/*2252709 杨烜赫*/
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
        // 在第 i 天休息的状态是前一天卖出股票进入的冷冻期或者前一天休息状态的最大值
        rest[i] = max(sell[i - 1], rest[i - 1]);
        // 在第 i 天买入股票，要么是前一天休息状态转移过来的，要么是前一天持有股票的状态
        buy[i] = max(rest[i - 1] - prices[i], buy[i - 1]);
        // 在第 i 天卖出股票，只能是前一天持有股票的状态
        sell[i] = buy[i - 1] + prices[i];
    }

    // 最大利润为最后一天不持有股票的最大值
    return max(sell[n - 1], rest[n - 1]);
}

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
            cout << "请输入若干股票价格，在0-1000范围内,输入-1结束输入" << endl;
        }
        input = false;
        cin >> temp;
        if (temp == -1)
        {
            break;
        }
        else if (temp < 0 || temp > 1000)
        {
            cout << "输入股票价格不在0-1000范围内，请重新输入" << endl;
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
    // 计算最大利润
    int max_profit = maxprofit(prices);

    // 输出最大利润
    cout << "最大利润为: " << max_profit << endl;
    return 0;
}
