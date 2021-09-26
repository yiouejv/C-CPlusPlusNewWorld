#include<ctime>
#include<cstdlib>


class random {
public:
    int RandRange(int m, int n) {
        return (rand() / RAND_MAX) * (n - m) + m;
    }

    double RandRangeF(double m, double n) {
        double ratio = static_cast<double>(rand()) / RAND_MAX;
        return ratio * (n - m) + m;
    }
};