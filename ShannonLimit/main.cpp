#include <iostream> // �R���\�[���`��p
#define _USE_MATH_DEFINES // �~�����ƃl�C�s�A��
#include <math.h> // M_PI, M_E
#include <fstream> // �G�N�Z���o�͗p
#include <vector> // �ϔz��

// ���O��Ԃ̐錾
using namespace std;

// �֐��v���g�^�C�v�錾
double function(const double & x, const double & alpha, const double & C, const int & M);

// ���C���֐�
int main() {

	const double a = -5;    // �ϕ��J�n�_
	const double b =  5;    // �ϕ��I���_
	const int    m =  1000; // �ϕ���Ԃ̕�����
	int          M =  20;   // �M���_�̌�

	ofstream ofs; // �t�@�C�����͗p
	ofs.open("shannon.csv", ios::out);

	const double haba = (b - a) / m; // ������Ԃ��`

	double sigma{ 0.0 };
	for (int k = 1; k <= M / 2; ++k) {
		sigma += pow(double(2 * k - 1), 2);
	}

	double C = sqrt(M / (2 * sigma)); // �M���_�Ԋu

    // ���͋��[0, 40]�ɐݒ�
	for (int alpha = 0; alpha <= 40; alpha += 2) {
	
		double x{ 0.0 }; // ������Ԃ̍��[
		double menseki{ 0.0 };

		// ��`�����ŋ敪���όv�Z
		for (int i = 0; i < m; i++) {
			x = a + i * haba;
			double x2 = x + haba; // ������Ԃ̉E�[
			menseki += (haba * (function(x, alpha, C, M) + function(x2, alpha, C, M))) / 2;
		}

		double sigma2 = pow(10.0, (alpha / 10.0)*(-1)); // �Ђ�2��̌v�Z

		double usiro = log2(2 * M_PI * sigma2 * M_E) / 2.0;
		double capacity = - menseki - usiro;
		
		cout << capacity << " m^2" << endl;
		
		ofs << capacity << endl; // ���ʊi�[
	}

	ofs.close(); // �t�@�C���N���[�Y

	system("pause");
	return 0;
}

// ��ϕ��֐� f_mix * log2(f_mix) �̒�`
double function(const double & x, const double & alpha, const double & C, const int & M) {

	double sigma2 = pow(10.0, (alpha / 10.0)*(-1));
	vector<double> v; // �M���_�ԋ����̊i�[�p�z��

	for (int i = 1 - M; i <= M - 1; i += 2) {
		v.push_back(i * C);
	}

	double sum{ 0.0 }; // �V�O�}�v�Z�̌��ʊi�[�p
	for (auto & v : v) {
		sum += exp(pow(x - v, 2)*(-1) / (2 * sigma2));
	}
	double f_mix = sum / (M * sqrt(2*M_PI*sigma2));
	
	return log2(pow(f_mix, f_mix));
}