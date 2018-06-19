#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

// 積分計算クラス
class Calc {

private:
	const int DIVISION_NUMBER = 100000;
	double width; // 1区間の幅
	double x; // x値
	double f_o, f_e; // 奇数項の合計、偶数項の合計
	double area; // 面積

	double function(const double & x);

public:
	void calcIntegral(const double & start, const double & end);
	
};

// 関数の処理時間計測用
template<typename Function>
long long measureProcessTime(const Function f) {
	auto start = high_resolution_clock::now();
	f();
	auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
	cout << " time = " << duration << " ms " << endl;
	return duration;
}

// メイン関数
int main() {

	double a, b; // 積分区間[a, b]

	cout << "積分区間を入力してください" << endl;
	cin >> a >> b; // a, b 入力

	Calc c;
	
	measureProcessTime([&] (void) {
		c.calcIntegral(a, b);
	});

	system("pause");
	return 0;
}

// 被積分関数の定義
double Calc::function(const double & x)
{
	double result = 2 * pow(x, 3) - pow(x, 2) + 4;

	return result;
}

// 積分計算
void Calc::calcIntegral(const double & start, const double & end)
{
	// 1区間の幅を決定する
	width = (end - start) / (2 * DIVISION_NUMBER);

	// 初期化
	x = start;
	f_o = f_e = 0.0;
	area = 0.0;

	// 奇数項の合計、偶数項の合計を計算する
	for (int k = 1; k <= 2 * DIVISION_NUMBER - 2; k++) {
		x += width;
		if (k % 2 == 1) { // 奇数の場合
			f_o += function(x);
		}
		else { // 偶数の場合
			f_e += function(x);
		}
	}

	// 面積を計算する
	area = function(start) + function(end);
	area += 4 * (f_o + function(end - width)) + 2 * f_e;
	area *= width / 3;

	// 結果を表示する
	cout << "(a, b) = (" << start << ", " << end << ") " << endl;
	cout << "∫f(x)dx = " << area << endl;

}