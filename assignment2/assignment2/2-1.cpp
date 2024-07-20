//2252709 杨烜赫
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

// 判断是否可以观看所有电影
bool can_watch_all(vector<PII>& segs)
{
    // 对时间段按结束时间排序
    sort(segs.begin(), segs.end());

    // 初始化结束时间
    int end = -2e9;

    // 遍历时间段
    for (const PII& seg : segs) {
        if (seg.first > end) {
            // 可以观看这部电影，更新结束时间
            end = seg.second;
        }
        else {
            // 时间冲突，不能看完所有电影
            return false;
        }
    }

    // 所有电影都可以观看
    return true;
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

    vector<PII> segs;
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

        segs.push_back({ l, r });
    }

    if (can_watch_all(segs))
    {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }
    return 0;
}
