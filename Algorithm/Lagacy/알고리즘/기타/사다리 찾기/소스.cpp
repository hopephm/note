#include<iostream>
#include<math.h>

using namespace std;

double calcul(double a, double b, double r) {
	double c;
	c = (sqrt(pow(a, 2) - pow(r, 2)))/(1+(sqrt(pow(a, 2) - pow(r, 2)) / sqrt(pow(b, 2) - pow(r, 2))));
	return c;
}

double compare(double a, double b) {
	if (a > b) return b; else return a;
}

int main() {
	double a, b, c;
	cin >> a >> b >> c;

	double r_start = 0;
	double r_end = compare(a,b);

	double result = 0;

	while (true) {
		result = (r_start + r_end) / 2;

		if (abs(r_start - r_end) < 0.0001) {
			printf("%0.3lf", r_end);
			break;
		}

		if (calcul(a, b, result) < c) {
			r_end = result;
		}
		else {
			r_start = result;
		}

	}

	cin >> a;
}