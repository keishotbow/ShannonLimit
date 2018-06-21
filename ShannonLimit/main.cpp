#include <iostream>
#include <chrono>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace chrono;

// �ϕ��v�Z�N���X
class Calc {

private:
	const int DIVISION_NUMBER = 100000;
	double width; // 1��Ԃ̕�
	double x; // x�l
	double alpha; // ���̒l
	double f_o, f_e; // ����̍��v�A�������̍��v
	double area; // �ʐ�

	double function(const double & x, const double & alpha);

public:
	void calcIntegral(const double & start, const double & end);
	
};

// �֐��̏������Ԍv���p
template<typename Function>
long long measureProcessTime(const Function f) {
	auto start = high_resolution_clock::now();
	f();
	auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
	cout << " time = " << duration << " ms " << endl;
	return duration;
}

// ���C���֐�
int main() {

	double a, b; // �ϕ����[a, b]

	cout << "�ϕ���Ԃ���͂��Ă�������" << endl;
	cin >> a >> b; // a, b ����

	Calc c;
	
	measureProcessTime([&] (void) {
		c.calcIntegral(a, b);
	});

	system("pause");
	return 0;
}

// ��ϕ��֐��̒�`
double Calc::function(const double & x, const double & alpha)
{
	double sigma2 = pow(10, (alpha / 10)*(-1));
	double temp1 = exp(pow(x - 1, 2)*(-1) / (2 * sigma2));
	double temp2 = exp(pow(x + 1, 2)*(-1) / (2 * sigma2));
	double f_mix = (temp1 + temp2) / 2 * sqrt(2*M_PI*sigma2);
	
	return f_mix * log2(f_mix);
}

// �ϕ��v�Z
void Calc::calcIntegral(const double & start, const double & end)
{
	// 1��Ԃ̕������肷��
	width = (end - start) / (2 * DIVISION_NUMBER);

	// ������
	x = start;
	alpha = 0;
	f_o = f_e = 0.0;
	area = 0.0;

	// ����̍��v�A�������̍��v���v�Z����
	for (int k = 1; k <= 2 * DIVISION_NUMBER - 2; k++) {
		x += width;
		alpha += 2;
		if (k % 2 == 1) { // ��̏ꍇ
			f_o += function(x, alpha);
		}
		else { // �����̏ꍇ
			f_e += function(x, alpha);
		}
	}

	// �ʐς��v�Z����
	area = function(start, alpha) + function(end, alpha);
	area += 4 * (f_o + function(end - width, alpha)) + 2 * f_e;
	area *= width / 3;
	area *= -1;
	area -= log2(2 * M_PI*pow(10, (-1)*alpha / 10)*M_E);

	// ���ʂ�\������
	cout << "(a, b) = (" << start << ", " << end << ") " << endl;
	cout << "��f(x)dx = " << area << endl;

}