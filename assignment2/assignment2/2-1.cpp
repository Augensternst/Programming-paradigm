//2252709 ��@��
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

// �ж��Ƿ���Թۿ����е�Ӱ
bool can_watch_all(vector<PII>& segs)
{
    // ��ʱ��ΰ�����ʱ������
    sort(segs.begin(), segs.end());

    // ��ʼ������ʱ��
    int end = -2e9;

    // ����ʱ���
    for (const PII& seg : segs) {
        if (seg.first > end) {
            // ���Թۿ��ⲿ��Ӱ�����½���ʱ��
            end = seg.second;
        }
        else {
            // ʱ���ͻ�����ܿ������е�Ӱ
            return false;
        }
    }

    // ���е�Ӱ�����Թۿ�
    return true;
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

    vector<PII> segs;
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
