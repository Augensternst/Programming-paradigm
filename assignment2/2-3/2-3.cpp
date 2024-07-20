//2252709 ��@��
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;

// �ϲ�ʱ��κ���
vector<PII> merge_intervals(vector<PII>& intervals)
{
    if (intervals.empty())
    {
        return {}; // �������Ϊ�գ�ֱ�ӷ��ؿ�����
    }

    // ��ʱ��ΰ���ʼʱ���������
    sort(intervals.begin(), intervals.end());

    vector<PII> merged_intervals;
    merged_intervals.push_back(intervals[0]);

    // ����������ʱ���
    for (int i = 1; i < intervals.size(); i++)
    {
        PII current = intervals[i];
        PII& previous = merged_intervals.back();

        if (current.first <= previous.second)
        {
            // ���ص����ϲ�ʱ���
            previous.second = max(previous.second, current.second);
        }
        else {
            // ���ص�������µ�ʱ���
            merged_intervals.push_back(current);
        }
    }

    return merged_intervals;
}

int main()
{
    int n;
    while (true) {
        cout << "������ʱ�������" << endl;
        cin >> n;

        if (n > 0 && n <= 10000)
        {
            break;  // ����Ϸ�������ѭ��
        }
        else
        {
            cout << "ʱ����������ں���Χ�ڣ�����������" << endl;
        }
    }
    vector<PII> intervals;
    cout << "���������ʱ��Σ��ûس�������ÿ��ʱ������������ÿո����" << endl;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;

        if (l > r || l > 1000000 || r > 1000000) {
            cout << "���벻�Ϸ������������뵱ǰʱ���" << endl;
            i--; // �������뵱ǰʱ���
            continue;
        }

        intervals.push_back({ l, r });
    }

    // ���úϲ�ʱ��κ���
    vector<PII> merged_intervals = merge_intervals(intervals);

    cout << "�ϲ���Ĳ���ʱ���" << endl;
    for (const PII& interval : merged_intervals)
    {
        cout << "[" << interval.first << ", " << interval.second << "]" << endl;
    }

    return 0;
}
