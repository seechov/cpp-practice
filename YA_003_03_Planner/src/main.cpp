// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <cstdint>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <tuple>
using namespace std;

bool IsQueueEmpty(vector<queue<tuple<int64_t, int32_t, int64_t>>> queue)
{
    for (int32_t q_i = 0; q_i < queue.size(); q_i++)
    {
        if (!queue.at(q_i).empty())
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string first_line;
    std::getline(std::cin, first_line);

    int32_t n, m, k;
    std::sscanf(first_line.c_str(), "%d %d %d\n", &n, &m, &k);

    vector<int64_t> result_time(n), worker_eta(m, 0);
    vector<int32_t> result_worker(n);

    vector<queue<tuple<int64_t, int32_t, int64_t>>> queue(k);

    for (int32_t i = 0; i < n; i++)
    {
        string input_line;
        std::getline(std::cin, input_line);

        int64_t s, q, t;
        std::sscanf(input_line.c_str(), "%lld %lld %lld\n", &s, &q, &t);

        queue.at(q - 1).push(tuple<int64_t, int32_t, int64_t>(s, i, t));
    }

    int64_t time = 0;

    while (!IsQueueEmpty(queue))
    {
        for (int32_t q_i = 0; q_i < queue.size(); q_i++)
        {
            // get worker cut
            int64_t worker_cut_time = std::numeric_limits<int64_t>::max();
            for (int32_t w_i = 0; w_i < worker_eta.size(); w_i++)
            {
                if (worker_eta.at(w_i) < worker_cut_time)
                {
                    worker_cut_time = worker_eta.at(w_i);
                }
            }

            // get tuple cut
            int64_t queue_cut_time = std::numeric_limits<int64_t>::max();
            for (int32_t q_i = 0; q_i < queue.size(); q_i++)
            {
                tuple<int64_t, int32_t, int64_t> tuple = queue.at(q_i).front();
                if (get<2>(tuple) < queue_cut_time)
                {
                    queue_cut_time = get<2>(tuple);
                }
            }
            queue_cut_time = queue_cut_time - time;

            int64_t delta_time = std::min(worker_cut_time, queue_cut_time);
            if (worker_cut_time == 0)
            {
                delta_time = queue_cut_time;
            }
            if (queue_cut_time == 0)
            {
                delta_time = worker_cut_time;
            }

            time += delta_time;


            for (int32_t w_i = 0; w_i < worker_eta.size(); w_i++)
            {
                if (!queue.at(q_i).empty() && worker_eta.at(w_i) == 0)
                {
                    tuple<int64_t, int32_t, int64_t> tuple = queue.at(q_i).front();
                    if (get<0>(tuple) == time)
                    {
                        worker_eta.at(w_i) = get<2>(tuple);
                        result_time.at(get<1>(tuple)) = time;
                        queue.at(q_i).pop();
                    }
                }
            }
        }

    }


    // cout << result << '\n';

    return 0;
}
