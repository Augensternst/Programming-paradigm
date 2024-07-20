//2252709 杨烜赫
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

// 计算需要的最小放映厅数量
int min_meeting_rooms(vector<PII>& intervals)
{
    // 创建两个数组，分别存储起始时间和结束时间
    vector<int> start_times;
    vector<int> end_times;

    // 将时间段的起始和结束时间分别存储在数组中
    for (const PII& interval : intervals)
    {
        start_times.push_back(interval.first);
        end_times.push_back(interval.second);
    }

    // 对起始时间和结束时间进行排序
    sort(start_times.begin(), start_times.end());
    sort(end_times.begin(), end_times.end());

    int rooms = 0;      // 放映厅数量
    int end_idx = 0;    // 结束时间的索引

    // 遍历起始时间数组
    for (int i = 0; i < start_times.size(); i++)
    {
        if (start_times[i] < end_times[end_idx])
        {
            // 需要分配新的放映厅，因为新的电影开始时间早于已有放映厅的结束时间
            rooms++;
        }
        else
        {
            // 一个电影结束，释放一个放映厅，增加结束时间的索引
            end_idx++;
        }
    }

    return rooms;
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
    int min_rooms = min_meeting_rooms(intervals);
    cout << "最小需要的放映厅数量为：" << min_rooms << endl;

    return 0;
}
