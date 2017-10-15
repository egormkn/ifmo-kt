#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

FILE *fin = fopen("schedule.in", "r");
FILE *fout = fopen("schedule.out", "w");

struct task {
    int deadline, fine;

    task(int d, int f) : deadline(d), fine(f) {}
};

bool comparator(task a, task b) {
    return a.fine > b.fine;
}

int main(int argc, char **argv) {
    unsigned n = 0;
    fscanf(fin, "%u", &n);

    vector<task> tasks;
    for (unsigned i = 0, d, w; i < n; i++) {
        fscanf(fin, "%u %u", &d, &w);
        tasks.push_back(task(d, w));
    }
    sort(tasks.begin(), tasks.end(), comparator);

    set<int> time;
    for (int i = 1; i <= n; ++i) {
        time.emplace(i);
    }

    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        set<int>::iterator plan = time.upper_bound(tasks[i].deadline);
        if(plan == time.begin()) {
            time.erase(--time.end());
            answer += tasks[i].fine;
        } else {
            time.erase(--plan);
        }
    }

    fprintf(fout, "%lld", answer);

    fclose(fin);
    fclose(fout);
    return 0;
}