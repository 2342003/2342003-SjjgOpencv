<<<<<<< HEAD
#include<opencv2\imgproc\imgproc_c.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string.h>
#include<math.h>
#include<vector>
#define    CLOCKS_PER_SEC      ((clock_t)1000)
#define    BLACK     0
#define    WHITE     255
using namespace std;
using namespace cv;

static string testImgPath = "./ǩ��/*";//ͼƬ·��

int  medianValue(int* pixels, int size)//ȡ��ֵ
{
	sort(pixels, pixels + size);//��������
	return pixels[size / 2];//������ֵ
}
void toGrey(Mat& Img)//ת��Ϊ�Ҷ�ͼ��
{
	int row = Img.rows;//��������
	int col = Img.cols;//����
	Mat greyImg;//����Ҷ�ͼ
	greyImg.create(row, col, CV_8UC1);//��ʼ����С
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			//�õ�����ͨ��������ֵ
			int B = Img.at<Vec3b>(i, j)[0];
			int G = Img.at<Vec3b>(i, j)[1];
			int R = Img.at<Vec3b>(i, j)[2];
			//���ûҶȻ���ʽ����ɫͼ������ͨ��������ֵת��Ϊ�Ҷ�ͼ��ͨ��������ֵ
			greyImg.at<uchar>(i, j) = static_cast<uchar>(0.114 * B + 0.587 * G + 0.299 * R);
		}
	Img = greyImg;
}

void quickSort(vector<int>& a, int low, int high)
{
	if (low < high)  //�ж��Ƿ����������������ݹ����ֹ����
	{
		int i = low, j = high;
		int x = a[low];
		while (i < j)
		{
			while (i < j && a[j] >= x) j--;
			if (i < j) a[i++] = a[j];
			while (i < j && a[i] <= x) i++;
			if (i < j) a[j--] = a[i];
		}
		a[i] = x;
		quickSort(a, low, i - 1);
		quickSort(a, i + 1, high);
	}
}

int bubbleMedian(vector<int>& a)//�õ���ֵ������
{
	int median = 0;//�ҵ���ֵ
	quickSort(a, 0, 8);
	median = a[4];
	return median;
}

void denoising(Mat gray1, Mat& grayImg)//������ ȥ�봦����ֵ�˲���,ʵ��Ⱦ�ֵ�˲�Ч��Ҫ��һ��
{
	grayImg = Mat(gray1.rows, gray1.cols, CV_8UC1);//�½�һ��һ����С��ͼƬ

	vector<int>temp(9); //����Ÿ�����������꣩
	int dx[9] = { 1,-1,1,-1,-1,0,1,0,0 };
	int dy[9] = { 1,-1,-1,1,0,1,0,-1,0 };

	for (int i = 1; i < gray1.rows - 1; i++)
	{
		for (int j = 1; j < gray1.cols - 1; j++)
		{
			//��Ե���ֲ�������
			{
				for (int k = 0; k < 9; k++)
				{
					temp[k] = gray1.at<uchar>(i + dx[k], j + dy[k]);//�õ���������
				}
				grayImg.at<uchar>(i, j) = bubbleMedian(temp);
			}
		}
	}
}

int getThreshold(Mat& Img)//�����ֵ��
{
	//1.���ƻҶ�ֱ��ͼ
	int fig[256] = { 0 };//ֱ��ͼ����
	for (int i = 0; i < Img.rows; i++)
		for (int j = 0; j < Img.cols; j++)
			fig[Img.at<uchar>(i, j)]++;

	//2.������ֵ
	int Threshold;//��ֵ
	double var = 0;//��䷽��
	int sum = Img.rows * Img.rows;
	for (int i = 0; i < 255; i++)//ö����ֵ
	{
		double firstAVG = 0, firstRate = 0, backAVG = 0, backRate = 0;
		//ǰ��ɫƽ���Ҷȣ�ǰ��ɫ����ռ�ȣ�����ɫƽ���Ҷȣ�����ɫ����ռ��
		for (int j = 0; j < 256; j++)
			if (j <= i)firstAVG += fig[j] * j, firstRate += fig[j];//ͳ��ǰ��ɫ���ܻҶ�ֵ����������
			else  backAVG += fig[j] * j, backRate += fig[j];//ͳ�Ʊ���ɫ���ܻҶ�ֵ����������
		firstAVG /= firstRate, firstRate /= sum;//����ǰ��ɫ��ƽ���Ҷ�ֵ������ռ��
		backAVG /= backRate, backRate /= sum;//���㱳��ɫ��ƽ���Ҷ�ֵ������ռ��
		double var1 = firstRate * backRate * (firstAVG - backAVG) * (firstAVG - backAVG);
		if (var1 > var)var = var1, Threshold = i;
	}
	return Threshold;
}


void FLoodFill(Mat& Img, int x0, int y0)//���������ֵͼ��߽��ɫ����Ϊ��ɫ
{
	queue<pair<int, int>> q;
	int move[8][2] = { {-1,-1},{-1,0},{-1,1},{0,1},{0,-1},{1,-1},{1,0},{1,1} };//�Ÿ�����
	Img.at<uchar>(x0, y0) = 0;
	q.push({ x0,y0 });
	while (q.size())
	{
		auto t = q.front();
		q.pop();
		for (int i = 0; i < 8; i++)
		{
			int x = t.first + move[i][0];
			int y = t.second + move[i][1];
			if (x >= 0 && x < Img.rows && y >= 0 &&
				y < Img.cols && Img.at<uchar>(x, y) == WHITE)//��ɫ
				q.push({ x,y }), Img.at<uchar>(x, y) = BLACK;//��ɫ
		}
	}
}
void toBinaryGraph(Mat& Img, bool Invert = 1, bool FillEdege = 1)//���Ҷ�ͼ��ֵ���������б���ֵ����ͼ���Ƿ��࣬�Ƿ�����Ե
{
	int Threshold = getThreshold(Img);// ��ֵ
	int front = WHITE, back = BLACK;//Ĭ��ǰ��ɫΪ��ɫ����ɫΪ��ɫ
	if (!Invert)front = BLACK, back = WHITE;
	for (int i = 0; i < Img.rows; i++)
		for (int j = 0; j < Img.cols; j++)
			if (Img.at<uchar>(i, j) > Threshold)Img.at<uchar>(i, j) = back;//������ֵ��Ϊ��ɫ
			else Img.at<uchar>(i, j) = front;//С����ֵ��Ϊ��ɫ
	if (!FillEdege)return;//����Ҫ����Ե���򷵻�
	//��ֹIBSN���𣬶Ա�Ե�������
	for (int i = Img.rows / 2; i < Img.rows; i++)
	{
		if (Img.at<uchar>(i, 0) == WHITE)FLoodFill(Img, i, 0);
		if (Img.at<uchar>(i, Img.cols - 1) == WHITE)FLoodFill(Img, i, Img.cols - 1);
	}
	for (int i = 0; i < Img.cols; i++)
	{
		if (Img.at<uchar>(0, i) == WHITE)FLoodFill(Img, 0, i);
		if (Img.at<uchar>(Img.rows - 1, i) == WHITE)FLoodFill(Img, Img.rows - 1, i);
	}

}
void revolve(Mat& Img, Mat& revolveMatrix, Size& NewSize)//��תͼƬ�����ʵ�λ��
{
	Mat Img_x;
	Sobel(Img, Img_x, -1, 0, 1, 5);
	vector<Vec2f>Lines;
	HoughLines(Img_x, Lines, 1, CV_PI / 180, 180);
	double angle = 0;
	int cnt = 0;
	for (auto i : Lines)
		if (i[1] > CV_PI * 17.0 / 36 && i[1] < CV_PI * 5.0 / 9 && i[0] < Img.rows / 3)
			//����ֱ�ߣ�����ڣ�85��,100�㣩
			angle += i[1], cnt++;
	angle /= cnt;

	revolveMatrix = getRotationMatrix2D(Point(Img.rows / 2, Img.cols / 2), 180 * angle / CV_PI - 90, 1);
	//��ʱ����ת�������ת����
	//������ת���󣬼�����ת��ͼ��Ĵ�С��Ϊ�˷�ֹ�߽��ISBN�����ֶ�ʧ
	double cos = abs(revolveMatrix.at<double>(0, 0));
	double sin = abs(revolveMatrix.at<double>(0, 1));
	int nw = cos * Img.cols + sin * Img.rows;
	int nh = sin * Img.cols + cos * Img.rows;
	revolveMatrix.at<double>(0, 2) += (nw / 2 - Img.cols / 2);
	revolveMatrix.at<double>(1, 2) += (nh / 2 - Img.rows / 2);
	NewSize = { nw,nh };
}

int rowSum(Mat& Img, int rowi)//һ�����ػҶ�ֵ֮��
{
	int sum = 0;
	for (int i = 0; i < Img.cols; i++)
		if (Img.at<uchar>(rowi, i) == 255)sum++;
	return sum;
}
int colSum(Mat& Img, int coli)//һ�����ػҶ�ֵ֮��
{
	int sum = 0;
	for (int i = 0; i < Img.rows; i++)
		if (Img.at<uchar>(i, coli) == 255)sum++;
	return sum;
}
int allSum(Mat& Img)
{
	int sum = 0;
	for (int i = 0; i < Img.rows; i++)
		for (int j = 0; j < Img.cols; j++)
			if (Img.at<uchar>(i, j) == 255)sum++;
	return sum;
}

void getRow(Mat& Img)//���ISBN��������
{
	double width = 1500;
	double height = width * Img.rows / Img.cols;
	resize(Img, Img, Size(width, height));
	toGrey(Img);
	denoising(Img, Img);
	toBinaryGraph(Img);
	Size newsize;
	Mat m;
	revolve(Img, m, newsize);
	warpAffine(Img, Img, m, newsize, INTER_LINEAR, 0);
	//��ISBN�����е����½�
	int rowi = 0, Uper = 0, Lower = 0, Height = 0;
	while (rowi < Img.rows / 2)
	{
		while (rowi < Img.rows / 2 && rowSum(Img, rowi) < 10)rowi++;
		int upper = rowi;
		while (rowi < Img.rows / 2 && rowSum(Img, rowi) >= 10)rowi++;
		int lower = rowi;
		if (rowi < Img.rows / 2 && lower - upper > Height)
			Uper = upper, Lower = lower, Height = lower - upper;
	}
	if (Uper < Lower)
		Img = Mat(Img, Range(Uper, Lower), Range(0, Img.cols));
}


void getMinRec(Mat& Img)//�����С����
{
	int uper, lower;
	int rowi = 0;
	while (!rowSum(Img, rowi))rowi++;
	uper = rowi;
	rowi = Img.rows - 1;
	while (!rowSum(Img, rowi))rowi--;
	lower = rowi;
	if (uper < lower)
		Img = Mat(Img, Range(uper, lower), Range(0, Img.cols));

	int lefter, righter;
	int coli = 0;
	while (!colSum(Img, coli))coli++;
	lefter = coli;
	coli = Img.cols - 1;
	while (!colSum(Img, coli))coli--;
	righter = coli;
	if (lefter < righter)
		Img = Mat(Img, Range(0, Img.rows), Range(lefter, righter));

}

int main()
{
	int rtNums = 0, accNums = 0, sunNums = 0;//�ֱ������ȷ����������׼ȷʶ����ַ���������Ҫʶ����ַ����ܺ�

	//1.��ȡ ISBN ͼƬ

	vector<String> testImgFN;
	glob(testImgPath, testImgFN, false);//������ ����������ͼƬ ���� testImgFN��
	int testImgNums = testImgFN.size();//�õ�ͼƬ����

	clock_t start = clock();
	for (int i = 0; i < testImgNums; i++)
	{
		Mat Img = imread(testImgFN[i]);
		getRow(Img);
		getMinRec(Img);
		imshow("��ֵͼ��", Img);
		waitKey(6000);
	}
	clock_t end = clock();
	double timeSpend = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "�������ˣ�" << testImgNums << "��ͼƬ�� " << timeSpend / testImgNums << " Sec/prePic" << endl;

}
=======
#include<opencv2\imgproc\imgproc_c.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<string.h>
#include<math.h>
#include<vector>
#define    CLOCKS_PER_SEC      ((clock_t)1000)
#define    BLACK     0
#define    WHITE     255
using namespace std;
using namespace cv;

static string testImgPath = "./ǩ��/*";//ͼƬ·��

int  medianValue(int* pixels, int size)//ȡ��ֵ
{
	sort(pixels, pixels + size);//��������
	return pixels[size / 2];//������ֵ
}
void toGrey(Mat& Img)//ת��Ϊ�Ҷ�ͼ��
{
	int row = Img.rows;//��������
	int col = Img.cols;//����
	Mat greyImg;//����Ҷ�ͼ
	greyImg.create(row, col, CV_8UC1);//��ʼ����С
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			//�õ�����ͨ��������ֵ
			int B = Img.at<Vec3b>(i, j)[0];
			int G = Img.at<Vec3b>(i, j)[1];
			int R = Img.at<Vec3b>(i, j)[2];
			//���ûҶȻ���ʽ����ɫͼ������ͨ��������ֵת��Ϊ�Ҷ�ͼ��ͨ��������ֵ
			greyImg.at<uchar>(i, j) = static_cast<uchar>(0.114 * B + 0.587 * G + 0.299 * R);
		}
	Img = greyImg;
}

void quickSort(vector<int>& a, int low, int high)
{
	if (low < high)  //�ж��Ƿ����������������ݹ����ֹ����
	{
		int i = low, j = high;
		int x = a[low];
		while (i < j)
		{
			while (i < j && a[j] >= x) j--;
			if (i < j) a[i++] = a[j];
			while (i < j && a[i] <= x) i++;
			if (i < j) a[j--] = a[i];
		}
		a[i] = x;
		quickSort(a, low, i - 1);
		quickSort(a, i + 1, high);
	}
}

int bubbleMedian(vector<int>& a)//�õ���ֵ������
{
	int median = 0;//�ҵ���ֵ
	quickSort(a, 0, 8);
	median = a[4];
	return median;
}

void denoising(Mat gray1, Mat& grayImg)//������ ȥ�봦����ֵ�˲���,ʵ��Ⱦ�ֵ�˲�Ч��Ҫ��һ��
{
	grayImg = Mat(gray1.rows, gray1.cols, CV_8UC1);//�½�һ��һ����С��ͼƬ

	vector<int>temp(9); //����Ÿ�����������꣩
	int dx[9] = { 1,-1,1,-1,-1,0,1,0,0 };
	int dy[9] = { 1,-1,-1,1,0,1,0,-1,0 };

	for (int i = 1; i < gray1.rows - 1; i++)
	{
		for (int j = 1; j < gray1.cols - 1; j++)
		{
			//��Ե���ֲ�������
			{
				for (int k = 0; k < 9; k++)
				{
					temp[k] = gray1.at<uchar>(i + dx[k], j + dy[k]);//�õ���������
				}
				grayImg.at<uchar>(i, j) = bubbleMedian(temp);
			}
		}
	}
}

int getThreshold(Mat& Img)//�����ֵ��
{
	//1.���ƻҶ�ֱ��ͼ
	int fig[256] = { 0 };//ֱ��ͼ����
	for (int i = 0; i < Img.rows; i++)
		for (int j = 0; j < Img.cols; j++)
			fig[Img.at<uchar>(i, j)]++;

	//2.������ֵ
	int Threshold;//��ֵ
	double var = 0;//��䷽��
	int sum = Img.rows * Img.rows;
	for (int i = 0; i < 255; i++)//ö����ֵ
	{
		double firstAVG = 0, firstRate = 0, backAVG = 0, backRate = 0;
		//ǰ��ɫƽ���Ҷȣ�ǰ��ɫ����ռ�ȣ�����ɫƽ���Ҷȣ�����ɫ����ռ��
		for (int j = 0; j < 256; j++)
			if (j <= i)firstAVG += fig[j] * j, firstRate += fig[j];//ͳ��ǰ��ɫ���ܻҶ�ֵ����������
			else  backAVG += fig[j] * j, backRate += fig[j];//ͳ�Ʊ���ɫ���ܻҶ�ֵ����������
		firstAVG /= firstRate, firstRate /= sum;//����ǰ��ɫ��ƽ���Ҷ�ֵ������ռ��
		backAVG /= backRate, backRate /= sum;//���㱳��ɫ��ƽ���Ҷ�ֵ������ռ��
		double var1 = firstRate * backRate * (firstAVG - backAVG) * (firstAVG - backAVG);
		if (var1 > var)var = var1, Threshold = i;
	}
	return Threshold;
}


void FLoodFill(Mat& Img, int x0, int y0)//���������ֵͼ��߽��ɫ����Ϊ��ɫ
{
	queue<pair<int, int>> q;
	int move[8][2] = { {-1,-1},{-1,0},{-1,1},{0,1},{0,-1},{1,-1},{1,0},{1,1} };//�Ÿ�����
	Img.at<uchar>(x0, y0) = 0;
	q.push({ x0,y0 });
	while (q.size())
	{
		auto t = q.front();
		q.pop();
		for (int i = 0; i < 8; i++)
		{
			int x = t.first + move[i][0];
			int y = t.second + move[i][1];
			if (x >= 0 && x < Img.rows && y >= 0 &&
				y < Img.cols && Img.at<uchar>(x, y) == WHITE)//��ɫ
				q.push({ x,y }), Img.at<uchar>(x, y) = BLACK;//��ɫ
		}
	}
}
void toBinaryGraph(Mat& Img, bool Invert = 1, bool FillEdege = 1)//���Ҷ�ͼ��ֵ���������б���ֵ����ͼ���Ƿ��࣬�Ƿ�����Ե
{
	int Threshold = getThreshold(Img);// ��ֵ
	int front = WHITE, back = BLACK;//Ĭ��ǰ��ɫΪ��ɫ����ɫΪ��ɫ
	if (!Invert)front = BLACK, back = WHITE;
	for (int i = 0; i < Img.rows; i++)
		for (int j = 0; j < Img.cols; j++)
			if (Img.at<uchar>(i, j) > Threshold)Img.at<uchar>(i, j) = back;//������ֵ��Ϊ��ɫ
			else Img.at<uchar>(i, j) = front;//С����ֵ��Ϊ��ɫ
	if (!FillEdege)return;//����Ҫ����Ե���򷵻�
	//��ֹIBSN���𣬶Ա�Ե�������
	for (int i = Img.rows / 2; i < Img.rows; i++)
	{
		if (Img.at<uchar>(i, 0) == WHITE)FLoodFill(Img, i, 0);
		if (Img.at<uchar>(i, Img.cols - 1) == WHITE)FLoodFill(Img, i, Img.cols - 1);
	}
	for (int i = 0; i < Img.cols; i++)
	{
		if (Img.at<uchar>(0, i) == WHITE)FLoodFill(Img, 0, i);
		if (Img.at<uchar>(Img.rows - 1, i) == WHITE)FLoodFill(Img, Img.rows - 1, i);
	}

}
void revolve(Mat& Img, Mat& revolveMatrix, Size& NewSize)//��תͼƬ�����ʵ�λ��
{
	Mat Img_x;
	Sobel(Img, Img_x, -1, 0, 1, 5);
	vector<Vec2f>Lines;
	HoughLines(Img_x, Lines, 1, CV_PI / 180, 180);
	double angle = 0;
	int cnt = 0;
	for (auto i : Lines)
		if (i[1] > CV_PI * 17.0 / 36 && i[1] < CV_PI * 5.0 / 9 && i[0] < Img.rows / 3)
			//����ֱ�ߣ�����ڣ�85��,100�㣩
			angle += i[1], cnt++;
	angle /= cnt;

	revolveMatrix = getRotationMatrix2D(Point(Img.rows / 2, Img.cols / 2), 180 * angle / CV_PI - 90, 1);
	//��ʱ����ת�������ת����
	//������ת���󣬼�����ת��ͼ��Ĵ�С��Ϊ�˷�ֹ�߽��ISBN�����ֶ�ʧ
	double cos = abs(revolveMatrix.at<double>(0, 0));
	double sin = abs(revolveMatrix.at<double>(0, 1));
	int nw = cos * Img.cols + sin * Img.rows;
	int nh = sin * Img.cols + cos * Img.rows;
	revolveMatrix.at<double>(0, 2) += (nw / 2 - Img.cols / 2);
	revolveMatrix.at<double>(1, 2) += (nh / 2 - Img.rows / 2);
	NewSize = { nw,nh };
}

int rowSum(Mat& Img, int rowi)//һ�����ػҶ�ֵ֮��
{
	int sum = 0;
	for (int i = 0; i < Img.cols; i++)
		if (Img.at<uchar>(rowi, i) == 255)sum++;
	return sum;
}
int colSum(Mat& Img, int coli)//һ�����ػҶ�ֵ֮��
{
	int sum = 0;
	for (int i = 0; i < Img.rows; i++)
		if (Img.at<uchar>(i, coli) == 255)sum++;
	return sum;
}
int allSum(Mat& Img)
{
	int sum = 0;
	for (int i = 0; i < Img.rows; i++)
		for (int j = 0; j < Img.cols; j++)
			if (Img.at<uchar>(i, j) == 255)sum++;
	return sum;
}

void getRow(Mat& Img)//���ISBN��������
{
	double width = 1500;
	double height = width * Img.rows / Img.cols;
	resize(Img, Img, Size(width, height));
	toGrey(Img);
	denoising(Img, Img);
	toBinaryGraph(Img);
	Size newsize;
	Mat m;
	revolve(Img, m, newsize);
	warpAffine(Img, Img, m, newsize, INTER_LINEAR, 0);
	//��ISBN�����е����½�
	int rowi = 0, Uper = 0, Lower = 0, Height = 0;
	while (rowi < Img.rows / 2)
	{
		while (rowi < Img.rows / 2 && rowSum(Img, rowi) < 10)rowi++;
		int upper = rowi;
		while (rowi < Img.rows / 2 && rowSum(Img, rowi) >= 10)rowi++;
		int lower = rowi;
		if (rowi < Img.rows / 2 && lower - upper > Height)
			Uper = upper, Lower = lower, Height = lower - upper;
	}
	if (Uper < Lower)
		Img = Mat(Img, Range(Uper, Lower), Range(0, Img.cols));
}


void getMinRec(Mat& Img)//�����С����
{
	int uper, lower;
	int rowi = 0;
	while (!rowSum(Img, rowi))rowi++;
	uper = rowi;
	rowi = Img.rows - 1;
	while (!rowSum(Img, rowi))rowi--;
	lower = rowi;
	if (uper < lower)
		Img = Mat(Img, Range(uper, lower), Range(0, Img.cols));

	int lefter, righter;
	int coli = 0;
	while (!colSum(Img, coli))coli++;
	lefter = coli;
	coli = Img.cols - 1;
	while (!colSum(Img, coli))coli--;
	righter = coli;
	if (lefter < righter)
		Img = Mat(Img, Range(0, Img.rows), Range(lefter, righter));

}

int main()
{
	int rtNums = 0, accNums = 0, sunNums = 0;//�ֱ������ȷ����������׼ȷʶ����ַ���������Ҫʶ����ַ����ܺ�

	//1.��ȡ ISBN ͼƬ

	vector<String> testImgFN;
	glob(testImgPath, testImgFN, false);//������ ����������ͼƬ ���� testImgFN��
	int testImgNums = testImgFN.size();//�õ�ͼƬ����

	clock_t start = clock();
	for (int i = 0; i < testImgNums; i++)
	{
		Mat Img = imread(testImgFN[i]);
		getRow(Img);
		getMinRec(Img);
		imshow("��ֵͼ��", Img);
		waitKey(6000);
	}
	clock_t end = clock();
	double timeSpend = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "�������ˣ�" << testImgNums << "��ͼƬ�� " << timeSpend / testImgNums << " Sec/prePic" << endl;

}
>>>>>>> c1abf96 (基础目录创建)
