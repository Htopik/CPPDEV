#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
using namespace std;

int RESULT = 0;

void summ(vector<int> numbers) {
    int res = 0;
    for (int i = 0; i < numbers.size(); ++i)
        res += numbers[i];
    RESULT += res;
}

int sum(vector<int> numbers) {
    int res = 0;
    for (int i = 0; i < numbers.size(); ++i)
        res += numbers[i];
    return res;
}

int main()
{
    int N, M, x;
    cin >> N >> M;
    while (N <= M) {
        cout << "Incorrect M, N." << endl;
        cin >> N >> M;
    }
    unsigned int start_time = clock();
    vector<int> numbs, partnumbs;
    for (int i = 0; i < N; i++) {
        x = rand() % 100;
        numbs.push_back(x);
    }
    /*for (int i = 0; i < numbs.size(); ++i)
        cout << numbs[i] << ' ';
    cout << endl;*/
    x = N / M + (N % M != 0);
    for (int i = 0; i < M; ++i) {
        if (i != M-1) {
            partnumbs = vector<int>(numbs.begin() + i*x, numbs.begin() + (i+1)*x);
        }
        else {
            partnumbs = vector<int>(numbs.begin() + i*x, numbs.end());
        }
        /*for (int i = 0; i < partnumbs.size(); ++i)
            cout << partnumbs[i] << ' ';
        cout << endl;*/
        thread t(summ, partnumbs);
        t.join();
    }
    //RESULT = sum(numbs);
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    cout << RESULT << endl << search_time;
    return 0;
}