//2252709 杨烜赫
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;

// 合并时间段函数
vector<PII> merge_intervals(vector<PII>& intervals)
{
    if (intervals.empty())
    {
        return {}; // 如果输入为空，直接返回空数组
    }

    // 对时间段按起始时间进行排序
    sort(intervals.begin(), intervals.end());

    vector<PII> merged_intervals;
    merged_intervals.push_back(intervals[0]);

    // 遍历排序后的时间段
    for (int i = 1; i < intervals.size(); i++)
    {
        PII current = intervals[i];
        PII& previous = merged_intervals.back();

        if (current.first <= previous.second)
        {
            // 有重叠，合并时间段
            previous.second = max(previous.second, current.second);
        }
        else {
            // 无重叠，添加新的时间段
            merged_intervals.push_back(current);
        }
    }

    return merged_intervals;
}

int main()
{
    int n;
    while (true) {
        cout << "请输入时间段数量" << endl;
        cin >> n;

        if (n > 0 && n <= 10000)
        {
            break;  // 输入合法，跳出循环
        }
        else
        {
            cout << "时间段数量不在合理范围内，请重新输入" << endl;
        }
    }
    vector<PII> intervals;
    cout << "请输入各个时间段，用回车隔开，每个时间段内两数字用空格隔开" << endl;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;

        if (l > r || l > 1000000 || r > 1000000) {
            cout << "输入不合法，请重新输入当前时间段" << endl;
            i--; // 重新输入当前时间段
            continue;
        }

        intervals.push_back({ l, r });
    }

    // 调用合并时间段函数
    vector<PII> merged_intervals = merge_intervals(intervals);

    cout << "合并后的播放时间表：" << endl;
    for (const PII& interval : merged_intervals)
    {
        cout << "[" << interval.first << ", " << interval.second << "]" << endl;
    }

    return 0;
}
