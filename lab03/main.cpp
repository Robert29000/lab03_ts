//
//  main.cpp
//  lab03
//
//  Created by Роберт Артур Меликян on 21/10/2020.
//  Copyright © 2020 Роберт Артур Меликян. All rights reserved.
//

#include <iostream>
#include <random>
#include <math.h>
#include "TextTable.h"

double f_uni(double x){
    return -2 * sqrt(x) * sin(0.5 * x);
}

double f_multi(double x){
    return -2 * sqrt(x) * sin(0.5 * x) * sin(5 * x);
}

void add_data_to_table(TextTable& t, int count, double T, double x, double f){
    t.add(std::to_string(count));
    t.add(std::to_string(T));
    t.add(std::to_string(x));
    t.add(std::to_string(f));
    t.endOfRow();
}

int main(int argc, const char * argv[]) {
    TextTable t('-', '|', '+');
    t.add("N");
    t.add("T");
    t.add("x");
    t.add("f(x)");
    t.endOfRow();
    double a = 2.0;
    double b = 6.0;
    const double Tmax = 10000;
    const double Tmin = 0.1;
    double Ti = Tmax;
    int count = 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(a, b);
    std::uniform_real_distribution<double> prob(0, 1);
    auto x = dis(gen);
    auto f_x = f_multi(x);
    add_data_to_table(t, count, Ti, x, f_x);
    while(Ti > Tmin){
        count++;
        auto x_i = dis(gen);
        auto f_i = f_multi(x_i);
        auto f_delta = f_i - f_x;
        if (f_delta <= 0){
            x = x_i;
            f_x = f_i;
        } else {
            double chance = exp(-f_delta / Ti);
            auto p = prob(gen);
            if (p < chance) {
                x = x_i;
                f_x = f_i;
            }
        }
        Ti = Ti * 0.95;
        add_data_to_table(t, count, Ti, x, f_x);
    }
    std::cout << t << std::endl;
    return 0;
}
