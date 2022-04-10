#include <math.h>
#include <time.h>

#include <iostream>
#include <map>
#include <random>
#include <vector>
#define M_PI 3.14159265358979323846
std::random_device rd;
std::mt19937 generator(rd());
class point {
   public:
    std::vector<double> position;
    int dim;
    point() {
    }
    point(int dim) {
        this->dim = dim;
    }
    double Ackley() {
        int i;
        double t, s1, s2;
        s1 = s2 = 0.0;
        for (i = 0; i < dim; i++) {
            t = position[i];
            s1 += t * t;
            s2 += cos(2.0 * M_PI * position[i]);
        }
        return -20.0 * exp(-0.2 * sqrt(s1 / dim)) - exp(s2 / dim) +
               20.0 + exp(1);
    }
    double Rastrigin() {
        int i;
        long double sum, squaresum = 0.0;
        if (dim > 20) {
            dim = 20;
        }
        sum = 0.0;

        for (i = 0; i < dim; i++) {
            squaresum += position[i] * position[i];
            sum += 10 * cos(2.0 * M_PI * position[i]);
        }
        return dim * 10 - sum + squaresum;

        /* const int dimension = dim;
         const double A = 10;
         double squareSum = 0.0;
         double sum = 0.0;

         for (const auto &input : position) {
             squareSum += input * input;
             sum += A * cos(2 * M_PI * input);
         }
         return A * dimension - sum + squareSum;*/
    }
    double Sphere() {
        int i;
        double sum;
        sum = 0.0;
        for (i = 0; i < dim; i++) {
            sum += position[i] * position[i];
        }
        return sum;
    }
    double Rosenbrock() {
        double s = 0.0;
        int i;
        for (i = 1; i < dim; i++)
            s += 100.0 * pow(position[i] - position[i - 1] * position[i - 1], 2) + pow(position[i - 1] - 1.0, 2);
        return s;
    }
    double Michalewicz() {
        double s = 0.0;
        for (int i = 0; i < dim; i++)
            s += sin(position[i]) * pow(sin((i + 1) * position[i] * position[i] / M_PI), 20);
        return -s;
    }
};
class bh {
   public:
    std::vector<point> vec;  // stars
    std::vector<double> record;
    int population, dim, bestindex = 0, funcindex, rmin, rmax, generation, changecount = 0;
    long double radious, localbestfit, globalbestfit;
    point bestp;

    std::map<std::string, std::vector<double> > size = {{"Ackley", {-30, 30, 0}}, {"Rastrigin", {-5.12, 5.12, 1}}, {"Sphere", {-100, 100, 2}}, {"Rosenbrock", {-10, 10, 3}}, {"Michalewicz", {0, M_PI, 4}}};

    bh(int population, int generation, int dim, std::string func) {  //建構子
        this->population = population;
        this->dim = dim;
        rmin = size[func][0];
        rmax = size[func][1];
        this->funcindex = size[func][2];
        this->generation = generation;
        localbestfit = std::numeric_limits<double>::max();
        globalbestfit = std::numeric_limits<double>::max();
    }
    void init() {  //改c++ random
        std::uniform_real_distribution<double> unif(rmin, rmax);
        for (int i = 0; i < population; i++) {
            point p(dim);
            for (int j = 0; j < dim; j++) {
                p.position.push_back(unif(generator));
            }
            vec.push_back(p);
        }
    }
    void calculatefit() {
        record.clear();
        switch (funcindex) {
            case 0:
                for (int i = 0; i < population; i++) {
                    record.push_back(vec[i].Ackley());
                }
                break;
            case 1:
                for (int i = 0; i < population; i++) {
                    record.push_back(vec[i].Rastrigin());
                }
                break;
            case 2:
                for (int i = 0; i < population; i++) {
                    record.push_back(vec[i].Sphere());
                }
                break;
            case 3:
                for (int i = 0; i < population; i++) {
                    record.push_back(vec[i].Rosenbrock());
                }
                break;
            case 4:
                for (int i = 0; i < population; i++) {
                    record.push_back(vec[i].Michalewicz());
                }
                break;
        }
    }
    void getbest() {
        int temp = 0;
        for (int i = 0; i < population; i++) {
            temp++;
            if (record[i] < localbestfit) {
                localbestfit = record[i];
                bestindex = i;
                if (localbestfit < globalbestfit) {
                    globalbestfit = localbestfit;
                    // bestp.position.clear();
                    /*for (int j = 0; j < dim; j++) {
                        bestp.position.push_back(vec[i].position[j]);
                    }*/
                }
                changecount = 0;
                temp -= 5;
            }
        }
        if (temp == population) {
            changecount++;
        }
    }
    void getradious() {
        double sum = 0;
        for (int i = 0; i < population; i++) {
            sum += record[i];
        }
        radious = record[bestindex] / sum;
    }
    void move(int index) {
        if (index == bestindex) {
        } else {
            for (int i = 0; i < dim; i++) {
                std::uniform_real_distribution<double> unif(0, 1);
                double curposition = vec[index].position[i], bestposition = vec[bestindex].position[i];
                vec[index].position[i] = curposition + unif(generator) * (bestposition - curposition);
                if (vec[index].position[i] > rmax) {
                    vec[index].position[i] = rmax;
                } else if (vec[index].position[i] < rmin) {
                    vec[index].position[i] = rmin;
                }
            }
        }
    }
    void eliminateAndNew(int i) {
        std::uniform_real_distribution<double> unif(rmin, rmax);
        int dis = distance(bestindex, i);
        while (dis < radious) {
            // std::cout << "new star" << std::endl;
            vec[i].position.clear();
            for (int j = 0; j < dim; j++) {
                vec[i].position.push_back(unif(generator));
            }
            dis = distance(bestindex, i);
        }
    }
    void newblackhole(int i) {
        std::uniform_real_distribution<double> unif(rmin, rmax);
        for (int j = 0; j < dim; j++) {
            vec[i].position.push_back(unif(generator));
        }
    }
    double distance(int bestindex, int a) {
        double sum = 0;
        for (int i = 0; i < dim; i++) {
            sum += pow(vec[bestindex].position[i] - vec[a].position[i], 2);
        }
        return sqrt(sum);
    }
    void start() {
        for (int i = 0; i < generation; i++) {
            if (i == 0) {
                init();
            }
            /*if (changecount == 5) {
                changecount = 0;
              newblackhole(bestindex);
            }*/
            calculatefit();
            getbest();
            std::cout << globalbestfit << std::endl;
            getradious();
            for (int j = 0; j < population; j++) {
                if (j == bestindex) {
                    continue;
                }
                if (distance(bestindex, j) < radious) {
                    eliminateAndNew(j);
                } else {
                    move(j);
                }
            }
        }

        /*for (int i = 0; i < dim; i++)
            std::cout << "dim" << i + 1 << "=" << vec[bestindex].position[i] << std::endl;

        std::cout << std::endl;*/
    }
};
