//2252709 ��@��
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

// ������Ҫ����С��ӳ������
int min_meeting_rooms(vector<PII>& intervals)
{
    // �����������飬�ֱ�洢��ʼʱ��ͽ���ʱ��
    vector<int> start_times;
    vector<int> end_times;

    // ��ʱ��ε���ʼ�ͽ���ʱ��ֱ�洢��������
    for (const PII& interval : intervals)
    {
        start_times.push_back(interval.first);
        end_times.push_back(interval.second);
    }

    // ����ʼʱ��ͽ���ʱ���������
    sort(start_times.begin(), start_times.end());
    sort(end_times.begin(), end_times.end());

    int rooms = 0;      // ��ӳ������
    int end_idx = 0;    // ����ʱ�������

    // ������ʼʱ������
    for (int i = 0; i < start_times.size(); i++)
    {
        if (start_times[i] < end_times[end_idx])
        {
            // ��Ҫ�����µķ�ӳ������Ϊ�µĵ�Ӱ��ʼʱ���������з�ӳ���Ľ���ʱ��
            rooms++;
        }
        else
        {
            // һ����Ӱ�������ͷ�һ����ӳ�������ӽ���ʱ�������
            end_idx++;
        }
    }

    return rooms;
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
    int min_rooms = min_meeting_rooms(intervals);
    cout << "��С��Ҫ�ķ�ӳ������Ϊ��" << min_rooms << endl;

    return 0;
}
