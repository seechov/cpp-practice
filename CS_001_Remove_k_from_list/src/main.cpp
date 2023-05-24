// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
struct ListNode
{
    ListNode(const T& v) : value(v), next(nullptr) {}
    T value;
    ListNode* next;
};

ListNode<int>* solution(ListNode<int>* l, int k)
{
    if (l == nullptr)
    {
        return nullptr;
    }
    if (l->value == k)
    {
        if (l->next == nullptr)
        {
            return nullptr;
        }
        else
        {
            l->next = solution(l->next, k);
            return l->next;
        }
    }
    else
    {
        if (l->next == nullptr)
        {
            return l;
        }
        else
        {
            l->next = solution(l->next, k);
            return l;
        }
    }

    // Alternative solution
    // From CodeForces
    //
    // if (l == nullptr) return nullptr;
    // l->next = solution(l->next, k);
    // if (l->value == k) return l->next;
    // return l;
}

int main()
{
    ListNode<int> node5(5);
    ListNode<int> node4(4);
    node4.next = &node5;
    ListNode<int> node3(3);
    node3.next = &node4;
    ListNode<int> node2(2);
    node2.next = &node3;
    ListNode<int> node1(1);
    node1.next = &node2;

    ListNode<int>* result = solution(&node1, 3);

    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    // long long result = 123456789012345678LL;
    int a = 123456789;
    // result = (long long) a * a;

    string first_line;
    string second_line;
    // std::getline(std::cin, first_line);
    // std::getline(std::cin, second_line);


    // cout << result << '\n';

    return 0;
}
