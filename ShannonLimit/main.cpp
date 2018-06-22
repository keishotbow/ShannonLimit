#include <iostream> // コンソール描画用
#define _USE_MATH_DEFINES // 円周率とネイピア数
#include <math.h> // M_PI, M_E
#include <fstream> // エクセル出力用
#include <vector> // 可変配列

// 名前空間の宣言
using namespace std;

// 関数プロトタイプ宣言
double function(const double & x, const double & alpha, const double & C, const int & M);

// メイン関数
int main() {

	const double a = -5;    // 積分開始点
	const double b =  5;    // 積分終了点
	const int    m =  1000; // 積分区間の分割数
	int          M =  20;   // 信号点の個数

	ofstream ofs; // ファイル入力用
	ofs.open("shannon.csv", ios::out);

	const double haba = (b - a) / m; // 微小区間を定義

	double sigma{ 0.0 };
	for (int k = 1; k <= M / 2; ++k) {
		sigma += pow(double(2 * k - 1), 2);
	}

	double C = sqrt(M / (2 * sigma)); // 信号点間隔

    // αは区間[0, 40]に設定
	for (int alpha = 0; alpha <= 40; alpha += 2) {
	
		double x{ 0.0 }; // 微小区間の左端
		double menseki{ 0.0 };

		// 台形公式で区分求積計算
		for (int i = 0; i < m; i++) {
			x = a + i * haba;
			double x2 = x + haba; // 微小区間の右端
			menseki += (haba * (function(x, alpha, C, M) + function(x2, alpha, C, M))) / 2;
		}

		double sigma2 = pow(10.0, (alpha / 10.0)*(-1)); // σの2乗の計算

		double usiro = log2(2 * M_PI * sigma2 * M_E) / 2.0;
		double capacity = - menseki - usiro;
		
		cout << capacity << " m^2" << endl;
		
		ofs << capacity << endl; // 結果格納
	}

	ofs.close(); // ファイルクローズ

	system("pause");
	return 0;
}

// 被積分関数 f_mix * log2(f_mix) の定義
double function(const double & x, const double & alpha, const double & C, const int & M) {

	double sigma2 = pow(10.0, (alpha / 10.0)*(-1));
	vector<double> v; // 信号点間距離の格納用配列

	for (int i = 1 - M; i <= M - 1; i += 2) {
		v.push_back(i * C);
	}

	double sum{ 0.0 }; // シグマ計算の結果格納用
	for (auto & v : v) {
		sum += exp(pow(x - v, 2)*(-1) / (2 * sigma2));
	}
	double f_mix = sum / (M * sqrt(2*M_PI*sigma2));
	
	return log2(pow(f_mix, f_mix));
}