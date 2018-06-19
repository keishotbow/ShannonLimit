#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

// �ϕ��v�Z�N���X
class Calc {

private:
	const int DIVISION_NUMBER = 100000;
	double width; // 1��Ԃ̕�
	double x; // x�l
	double f_o, f_e; // ����̍��v�A�������̍��v
	double area; // �ʐ�

	double function(const double & x);

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
double Calc::function(const double & x)
{
	double result = 2 * pow(x, 3) - pow(x, 2) + 4;

	return result;
}

// �ϕ��v�Z
void Calc::calcIntegral(const double & start, const double & end)
{
	// 1��Ԃ̕������肷��
	width = (end - start) / (2 * DIVISION_NUMBER);

	// ������
	x = start;
	f_o = f_e = 0.0;
	area = 0.0;

	// ����̍��v�A�������̍��v���v�Z����
	for (int k = 1; k <= 2 * DIVISION_NUMBER - 2; k++) {
		x += width;
		if (k % 2 == 1) { // ��̏ꍇ
			f_o += function(x);
		}
		else { // �����̏ꍇ
			f_e += function(x);
		}
	}

	// �ʐς��v�Z����
	area = function(start) + function(end);
	area += 4 * (f_o + function(end - width)) + 2 * f_e;
	area *= width / 3;

	// ���ʂ�\������
	cout << "(a, b) = (" << start << ", " << end << ") " << endl;
	cout << "��f(x)dx = " << area << endl;

}