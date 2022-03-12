<<<<<<< HEAD
//#include<iostream>
//#include<string.h>
//#include<math.h>
//#include<vector>
//#include<opencv2/opencv.hpp>
//#include<opencv2\imgproc\imgproc_c.h>
//using namespace std;
//using namespace cv;
//
//void ToGrey(Mat& OrigImg)//תΪ�Ҷ�ͼ
//{
//	int row = OrigImg.rows;
//	int col = OrigImg.cols;
//	Mat GreyImg;
//	GreyImg.create(row, col, CV_8UC1);
//	for (int i = 0; i < row; i++)
//		for (int j = 0; j < col; j++)
//		{
//			int B = OrigImg.at<Vec3b>(i, j)[0];
//			int G = OrigImg.at<Vec3b>(i, j)[1];
//			int R = OrigImg.at<Vec3b>(i, j)[2];
//			GreyImg.at<uchar>(i, j) = static_cast<uchar>(0.114 * B + 0.587 * G + 0.299 * R);
//		}
//	OrigImg = GreyImg;
//}
//
//int  MedianFilter(int* pixels, int size)//ȡ��ֵ
//{
//	sort(pixels, pixels + size);
//	return pixels[size / 2];
//}
//
//
//void RemoveNoise(Mat& OrigImg)//ȥ����㣬��ֵ�˲���
//{
//	int row = OrigImg.rows;
//	int col = OrigImg.cols;
//	Mat ResImg = OrigImg.clone();
//	int pixels[9];
//	int move[9][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1} };
//	for (int i = 1; i < row - 1; i++)
//		for (int j = 1; j < col - 1; j++)
//		{
//			for (int k = 0; k < 9; k++)
//				pixels[k] = OrigImg.at<uchar>(i + move[k][0], j + move[k][1]);
//			ResImg.at<uchar>(i, j) = MedianFilter(pixels, 9);
//		}
//	OrigImg = ResImg;
//}
//
//
//int GetOtusThreshold(Mat& Img)//�����ֵ��
//{
//	//���ƻҶ�ֱ��ͼ
//	int histogram[256] = { 0 };
//	for (int i = 0; i < Img.rows; i++)
//		for (int j = 0; j < Img.cols; j++)
//			histogram[Img.at<uchar>(i, j)]++;
//	//������ֵ
//	int T;//��ֵ
//	double Var = 0;//��䷽��
//	int Total = Img.rows * Img.rows;
//	for (int i = 0; i < 255; i++)//ö����ֵ
//	{
//		double FrontAvg = 0, FrontRate = 0, BackAvg = 0, BackRate = 0;
//		//ǰ��ɫƽ���Ҷȣ�ǰ��ɫ����ռ�ȣ�����ɫƽ���Ҷȣ�����ɫ����ռ��
//		for (int j = 0; j < 256; j++)
//			if (j <= i)FrontAvg += histogram[j] * j, FrontRate += histogram[j];//ͳ��ǰ��ɫ���ܻҶ�ֵ����������
//			else  BackAvg += histogram[j] * j, BackRate += histogram[j];//ͳ�Ʊ���ɫ���ܻҶ�ֵ����������
//		FrontAvg /= FrontRate, FrontRate /= Total;//����ǰ��ɫ��ƽ���Ҷ�ֵ������ռ��
//		BackAvg /= BackRate, BackRate /= Total;//���㱳��ɫ��ƽ���Ҷ�ֵ������ռ��
//		double Var1 = FrontRate * BackRate * (FrontAvg - BackAvg) * (FrontAvg - BackAvg);
//		if (Var1 > Var)Var = Var1, T = i;
//	}
//	return T;
//}
//
//
//void FLoodFill(Mat& Img, int x0, int y0)//���������ֵͼ��߽��ɫ����Ϊ��ɫ
//{
//	queue<pair<int, int>> q;
//	int move[8][2] = { {-1,-1},{-1,0},{-1,1},{0,1},{0,-1},{1,-1},{1,0},{1,1} };
//	Img.at<uchar>(x0, y0) = 0;
//	q.push({ x0,y0 });
//	while (q.size())
//	{
//		auto t = q.front();
//		q.pop();
//		for (int i = 0; i < 8; i++)
//		{
//			int x = t.first + move[i][0];
//			int y = t.second + move[i][1];
//			if (x >= 0 && x < Img.rows && y >= 0 &&
//				y < Img.cols && Img.at<uchar>(x, y) == 255)
//				q.push({ x,y }), Img.at<uchar>(x, y) = 0;
//		}
//	}
//}
//void ToBinary(Mat& Img, bool Invert = 1, bool FillEdege = 1)//���Ҷ�ͼ��ֵ���������б���ֵ����ͼ���Ƿ��࣬�Ƿ�����Ե
//{
//	int Threshold = GetOtusThreshold(Img);
//	int front = 255, back = 0;//Ĭ��ǰ��ɫΪ��ɫ����ɫΪ��ɫ
//	if (!Invert)front = 0, back = 255;
//	for (int i = 0; i < Img.rows; i++)
//		for (int j = 0; j < Img.cols; j++)
//			if (Img.at<uchar>(i, j) > Threshold)Img.at<uchar>(i, j) = back;
//			else Img.at<uchar>(i, j) = front;
//	if (!FillEdege)return;//����Ҫ����Ե���򷵻�
//	//��ֹIBSN���𣬶Ա�Ե�������
//	for (int i = Img.rows / 2; i < Img.rows; i++)
//	{
//		if (Img.at<uchar>(i, 0) == 255)FLoodFill(Img, i, 0);
//		if (Img.at<uchar>(i, Img.cols - 1) == 255)FLoodFill(Img, i, Img.cols - 1);
//	}
//	for (int i = 0; i < Img.cols; i++)
//	{
//		if (Img.at<uchar>(0, i) == 255)FLoodFill(Img, 0, i);
//		if (Img.at<uchar>(Img.rows - 1, i) == 255)FLoodFill(Img, Img.rows - 1, i);
//	}
//
//}
//
//void Rotate(Mat& Img, Mat& RotateMatrix, Size& NewSize)//��תͼƬ�����ʵ�λ��
//{
//	Mat Img_x;
//	Sobel(Img, Img_x, -1, 0, 1, 5);
//	vector<Vec2f>Lines;
//	HoughLines(Img_x, Lines, 1, CV_PI / 180, 180);
//	double angle = 0;
//	int cnt = 0;
//	for (auto i : Lines)
//		if (i[1] > CV_PI * 17.0 / 36 && i[1] < CV_PI * 5.0 / 9 && i[0] < Img.rows / 3)
//			//����ֱ�ߣ�����ڣ�85��,100�㣩
//			angle += i[1], cnt++;
//	angle /= cnt;
//
//	RotateMatrix = getRotationMatrix2D(Point(Img.rows / 2, Img.cols / 2), 180 * angle / CV_PI - 90, 1);
//	//��ʱ����ת�������ת���󣬸�����ת���󣬼�����ת��ͼ��Ĵ�С��Ϊ�˷�ֹ�߽��ISBN�����ֶ�ʧ
//	double cos = abs(RotateMatrix.at<double>(0, 0));
//	double sin = abs(RotateMatrix.at<double>(0, 1));
//	int nw = cos * Img.cols + sin * Img.rows;
//	int nh = sin * Img.cols + cos * Img.rows;
//	RotateMatrix.at<double>(0, 2) += (nw / 2 - Img.cols / 2);
//	RotateMatrix.at<double>(1, 2) += (nh / 2 - Img.rows / 2);
//	NewSize = { nw,nh };
//}
//
//int RowSum(Mat& Img, int RowIndex)//һ�����ػҶ�ֵ֮��
//{
//	int sum = 0;
//	for (int i = 0; i < Img.cols; i++)
//		if (Img.at<uchar>(RowIndex, i) == 255)sum++;
//	return sum;
//}
//int ColSum(Mat& Img, int ColIndex)//һ�����ػҶ�ֵ֮��
//{
//	int sum = 0;
//	for (int i = 0; i < Img.rows; i++)
//		if (Img.at<uchar>(i, ColIndex) == 255)sum++;
//	return sum;
//}
//int AllSum(Mat& Img)
//{
//	int sum = 0;
//	for (int i = 0; i < Img.rows; i++)
//		for (int j = 0; j < Img.cols; j++)
//			if (Img.at<uchar>(i, j) == 255)sum++;
//	return sum;
//}
//
//void GetISBNRow(Mat& Img)//���ISBN��������
//{
//	double width = 1500;
//	double height = width * Img.rows / Img.cols;
//	resize(Img, Img, Size(width, height));
//	ToGrey(Img);
//	RemoveNoise(Img);
//	ToBinary(Img);
//	Size newsize;
//	Mat m;
//	Rotate(Img, m, newsize);
//	warpAffine(Img, Img, m, newsize, INTER_LINEAR, 0);
//	//��ISBN�����е����½�
//	int RowIndex = 0, Upper_bound = 0, Lower_bound = 0, Height = 0;
//	while (RowIndex < Img.rows / 2)
//	{
//		while (RowIndex < Img.rows / 2 && RowSum(Img, RowIndex) < 10)RowIndex++;
//		int upper = RowIndex;
//		while (RowIndex < Img.rows / 2 && RowSum(Img, RowIndex) >= 10)RowIndex++;
//		int lower = RowIndex;
//		if (RowIndex < Img.rows / 2 && lower - upper > Height)
//			Upper_bound = upper, Lower_bound = lower, Height = lower - upper;
//	}
//	if (Upper_bound < Lower_bound)
//		Img = Mat(Img, Range(Upper_bound, Lower_bound), Range(0, Img.cols));
//}
//
//
//void GetMinRectangle(Mat& Img)//�����С����
//{
//	int Upper_bound, Lower_bound;
//	int RowIndex = 0;
//	while (!RowSum(Img, RowIndex))RowIndex++;
//	Upper_bound = RowIndex;
//	RowIndex = Img.rows - 1;
//	while (!RowSum(Img, RowIndex))RowIndex--;
//	Lower_bound = RowIndex;
//	if (Upper_bound < Lower_bound)
//		Img = Mat(Img, Range(Upper_bound, Lower_bound), Range(0, Img.cols));
//
//	int Left_bound, Right_bound;
//	int ColIndex = 0;
//	while (!ColSum(Img, ColIndex))ColIndex++;
//	Left_bound = ColIndex;
//	ColIndex = Img.cols - 1;
//	while (!ColSum(Img, ColIndex))ColIndex--;
//	Right_bound = ColIndex;
//	if (Left_bound < Right_bound)
//		Img = Mat(Img, Range(0, Img.rows), Range(Left_bound, Right_bound));
//
//}
//
//
//void SplitISBNRow(Mat& Img, vector<Mat>& Ch)//�ָ�ISBN�У��浽Ch��
//{
//	imshow("�з�ǰ��ͼƬ", Img);
//	waitKey(100);
//	int ColIndex = 0, Left_bound, Right_bound;
//	vector<Mat> ChCache;
//	int Height[30];
//	int Cnt = 0;
//	while (ColIndex < Img.cols)
//	{
//		while (ColIndex < Img.cols && !ColSum(Img, ColIndex))ColIndex++;
//		Left_bound = ColIndex;
//		while (ColIndex < Img.cols && ColSum(Img, ColIndex))ColIndex++;
//		Right_bound = ColIndex - 1;
//		if (Left_bound < Right_bound)
//		{
//			Mat Character = Mat(Img, Range(0, Img.rows), Range(Left_bound, Right_bound));
//			GetMinRectangle(Character);
//			ChCache.push_back(Character);
//			Height[Cnt++] = Character.rows;
//		}
//	}
//	int Mid = MedianFilter(Height, Cnt);
//	for (auto i : ChCache)
//		if (i.rows > 0.7 * Mid && i.rows < 1.3 * Mid) {
//			Ch.push_back(i);
//		}
//
//}
//
//bool Comp(pair<int, int>a, pair<int, int>b) {
//	return a.second < b.second;
//}
//int CalcImg(Mat inputImg) {
//	int nums = 0;
//	for (int i = 0; i < inputImg.rows; i++) {
//		for (int j = 0; j < inputImg.cols; j++) {
//			if (inputImg.at<uchar>(i, j) != 0) {
//				nums += inputImg.at<uchar>(i, j);
//			}
//		}
//	}
//	return nums;
//}
//
//char Compare(Mat TestImg, vector<pair<char, Mat>>& Mould) {
//	char best = '?';
//	double Max = 0;
//	resize(TestImg, TestImg, Size(40, 60));
//	//��ȡģ��ͼƬ
//	string sampleImgPath = "./ISBN/��������/*";
//	vector<String> sampleImgFN;
//	glob(sampleImgPath, sampleImgFN, false);
//	int sampleImgNums = sampleImgFN.size();
//	pair<int, int>* nums = new pair<int, int>[sampleImgNums];//first ��¼ģ��������ţ�second ��¼��ͼ��֮��
//	for (int i = 0; i < sampleImgNums; i++) {
//		nums[i].first = i;
//		Mat numImg = imread(sampleImgFN[i], 0);
//		Mat delImg;
//		resize(numImg, numImg, Size(40, 60));
//		absdiff(numImg, TestImg, delImg);
//		nums[i].second = CalcImg(delImg);
//	}
//	sort(nums, nums + sampleImgNums, Comp);//ѡ���ֵ��С��ģ��
//	//int index = nums[0].first / 2;
//	int index = nums[0].first;
//	return Mould[index].first;
//}
//
//int Judge(string& a, string& b)
//{
//	int f[50][50] = { 0 };
//	if (a[0] == b[0])f[0][0] = 1;
//	for (int i = 1; i < a.length(); i++)
//		for (int j = 1; j < b.length(); j++)
//			if (a[i] == b[j])f[i][j] = f[i - 1][j - 1] + 1;
//			else
//			{
//				f[i][j] = f[i - 1][j - 1];
//				f[i][j] = max(f[i][j], f[i - 1][j]);
//				f[i][j] = max(f[i][j], f[i][j - 1]);
//			}
//	return f[a.length() - 1][b.length() - 1];
//}
//
//void ReadTest(vector<String>& ImgFile)
//{
//	string testPath = "./ISBN/Train/*";
//	glob(testPath, ImgFile, false);
//}
//
//void ReadMould(vector<pair<char, Mat>>& Mould)
//{
//	vector<String> MouldPath;
//	string testPath = "./ISBN/��������/*";
//	glob(testPath, MouldPath, false);
//	for (auto i : MouldPath)
//	{
//		Mat MouldImg = imread(i, 0);
//		int p = i.find('\\');
//		ToBinary(MouldImg, 0, 0);
//		Mould.push_back({ i[p + 1],MouldImg });
//	}
//}
//
//int main()
//{
//	vector<String> TestFile;
//	ReadTest(TestFile);
//	vector<pair<char, Mat>> Mould;
//	ReadMould(Mould);
//	int OriginNumCnt = 0;
//	int RecogNumCnt = 0;
//	int Success = 0;
//	for (int i = 0; i < TestFile.size(); i++)
//	{
//		//��ͼ����ȡISBN�ַ���Ch
//		Mat Img = imread(TestFile[i]);
//		imshow("��ǰͼƬ", Img);
//		waitKey(100);
//		GetISBNRow(Img);
//		vector<Mat> Ch;
//		SplitISBNRow(Img, Ch);
//		//ͳ��ԭʼISBN�����ֵĸ���
//		int p1 = TestFile[i].find(' ');
//		int p2 = TestFile[i].rfind('.');
//		string OriginISBN = TestFile[i].substr(p1 + 1, p2 - p1 - 1);
//		for (int j = 0; j < OriginISBN.length(); j++)
//			if (isdigit(OriginISBN[j]))OriginNumCnt++;
//			else OriginISBN.erase(j, 1), j--;
//		//ʶ��ISBN�ַ���ͳ�Ƴɹ�ʶ�����ISBN�е����ָ���
//		string RecogISBN;
//		int Start = -1, Pos = 0;
//		int num = 0;
//		for (auto j : Ch)
//		{
//			num++;
//			char c = Compare(j, Mould);
//			if (!isdigit(c))continue;
//			if (num > 4) {
//				if (Start == -1 && (c == '7' || c == '9'))Start = Pos;
//				RecogISBN += c;
//				Pos++;
//			}
//		}
//		if (Start != -1)
//		{
//			int len = 13;
//			if (RecogISBN[0] == '7')len = MIN(10, RecogISBN.length() - Start);
//			if (RecogISBN[0] == '9')len = MIN(13, RecogISBN.length() - Start);
//			RecogISBN = RecogISBN.substr(Start, len);
//		}
//		RecogNumCnt += Judge(OriginISBN, RecogISBN);
//		//�жϸ�ISBN���Ƿ�ʶ��ɹ�
//		if (RecogISBN == OriginISBN) {
//			Success++, cout << OriginISBN << ' ' << RecogISBN << ' ' << "��ȷ" << endl;
//		}
//		else {
//			cout << OriginISBN << ' ' << RecogISBN << ' ' << "����" << endl;
//		}
//	}
//	cout << "��ʶ���ˣ�" << TestFile.size() << "��ͼƬ��" << endl;
//	cout << "��ȷ��Ϊ:" << fixed << setprecision(2) << Success * 100.0 / TestFile.size() << "%  ׼ȷ��Ϊ:" << fixed << setprecision(2) << RecogNumCnt * 100.0 / OriginNumCnt << "%" << endl;
//}
=======
//#include<iostream>
//#include<string.h>
//#include<math.h>
//#include<vector>
//#include<opencv2/opencv.hpp>
//#include<opencv2\imgproc\imgproc_c.h>
//using namespace std;
//using namespace cv;
//
//void ToGrey(Mat& OrigImg)//תΪ�Ҷ�ͼ
//{
//	int row = OrigImg.rows;
//	int col = OrigImg.cols;
//	Mat GreyImg;
//	GreyImg.create(row, col, CV_8UC1);
//	for (int i = 0; i < row; i++)
//		for (int j = 0; j < col; j++)
//		{
//			int B = OrigImg.at<Vec3b>(i, j)[0];
//			int G = OrigImg.at<Vec3b>(i, j)[1];
//			int R = OrigImg.at<Vec3b>(i, j)[2];
//			GreyImg.at<uchar>(i, j) = static_cast<uchar>(0.114 * B + 0.587 * G + 0.299 * R);
//		}
//	OrigImg = GreyImg;
//}
//
//int  MedianFilter(int* pixels, int size)//ȡ��ֵ
//{
//	sort(pixels, pixels + size);
//	return pixels[size / 2];
//}
//
//
//void RemoveNoise(Mat& OrigImg)//ȥ����㣬��ֵ�˲���
//{
//	int row = OrigImg.rows;
//	int col = OrigImg.cols;
//	Mat ResImg = OrigImg.clone();
//	int pixels[9];
//	int move[9][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1} };
//	for (int i = 1; i < row - 1; i++)
//		for (int j = 1; j < col - 1; j++)
//		{
//			for (int k = 0; k < 9; k++)
//				pixels[k] = OrigImg.at<uchar>(i + move[k][0], j + move[k][1]);
//			ResImg.at<uchar>(i, j) = MedianFilter(pixels, 9);
//		}
//	OrigImg = ResImg;
//}
//
//
//int GetOtusThreshold(Mat& Img)//�����ֵ��
//{
//	//���ƻҶ�ֱ��ͼ
//	int histogram[256] = { 0 };
//	for (int i = 0; i < Img.rows; i++)
//		for (int j = 0; j < Img.cols; j++)
//			histogram[Img.at<uchar>(i, j)]++;
//	//������ֵ
//	int T;//��ֵ
//	double Var = 0;//��䷽��
//	int Total = Img.rows * Img.rows;
//	for (int i = 0; i < 255; i++)//ö����ֵ
//	{
//		double FrontAvg = 0, FrontRate = 0, BackAvg = 0, BackRate = 0;
//		//ǰ��ɫƽ���Ҷȣ�ǰ��ɫ����ռ�ȣ�����ɫƽ���Ҷȣ�����ɫ����ռ��
//		for (int j = 0; j < 256; j++)
//			if (j <= i)FrontAvg += histogram[j] * j, FrontRate += histogram[j];//ͳ��ǰ��ɫ���ܻҶ�ֵ����������
//			else  BackAvg += histogram[j] * j, BackRate += histogram[j];//ͳ�Ʊ���ɫ���ܻҶ�ֵ����������
//		FrontAvg /= FrontRate, FrontRate /= Total;//����ǰ��ɫ��ƽ���Ҷ�ֵ������ռ��
//		BackAvg /= BackRate, BackRate /= Total;//���㱳��ɫ��ƽ���Ҷ�ֵ������ռ��
//		double Var1 = FrontRate * BackRate * (FrontAvg - BackAvg) * (FrontAvg - BackAvg);
//		if (Var1 > Var)Var = Var1, T = i;
//	}
//	return T;
//}
//
//
//void FLoodFill(Mat& Img, int x0, int y0)//���������ֵͼ��߽��ɫ����Ϊ��ɫ
//{
//	queue<pair<int, int>> q;
//	int move[8][2] = { {-1,-1},{-1,0},{-1,1},{0,1},{0,-1},{1,-1},{1,0},{1,1} };
//	Img.at<uchar>(x0, y0) = 0;
//	q.push({ x0,y0 });
//	while (q.size())
//	{
//		auto t = q.front();
//		q.pop();
//		for (int i = 0; i < 8; i++)
//		{
//			int x = t.first + move[i][0];
//			int y = t.second + move[i][1];
//			if (x >= 0 && x < Img.rows && y >= 0 &&
//				y < Img.cols && Img.at<uchar>(x, y) == 255)
//				q.push({ x,y }), Img.at<uchar>(x, y) = 0;
//		}
//	}
//}
//void ToBinary(Mat& Img, bool Invert = 1, bool FillEdege = 1)//���Ҷ�ͼ��ֵ���������б���ֵ����ͼ���Ƿ��࣬�Ƿ�����Ե
//{
//	int Threshold = GetOtusThreshold(Img);
//	int front = 255, back = 0;//Ĭ��ǰ��ɫΪ��ɫ����ɫΪ��ɫ
//	if (!Invert)front = 0, back = 255;
//	for (int i = 0; i < Img.rows; i++)
//		for (int j = 0; j < Img.cols; j++)
//			if (Img.at<uchar>(i, j) > Threshold)Img.at<uchar>(i, j) = back;
//			else Img.at<uchar>(i, j) = front;
//	if (!FillEdege)return;//����Ҫ����Ե���򷵻�
//	//��ֹIBSN���𣬶Ա�Ե�������
//	for (int i = Img.rows / 2; i < Img.rows; i++)
//	{
//		if (Img.at<uchar>(i, 0) == 255)FLoodFill(Img, i, 0);
//		if (Img.at<uchar>(i, Img.cols - 1) == 255)FLoodFill(Img, i, Img.cols - 1);
//	}
//	for (int i = 0; i < Img.cols; i++)
//	{
//		if (Img.at<uchar>(0, i) == 255)FLoodFill(Img, 0, i);
//		if (Img.at<uchar>(Img.rows - 1, i) == 255)FLoodFill(Img, Img.rows - 1, i);
//	}
//
//}
//
//void Rotate(Mat& Img, Mat& RotateMatrix, Size& NewSize)//��תͼƬ�����ʵ�λ��
//{
//	Mat Img_x;
//	Sobel(Img, Img_x, -1, 0, 1, 5);
//	vector<Vec2f>Lines;
//	HoughLines(Img_x, Lines, 1, CV_PI / 180, 180);
//	double angle = 0;
//	int cnt = 0;
//	for (auto i : Lines)
//		if (i[1] > CV_PI * 17.0 / 36 && i[1] < CV_PI * 5.0 / 9 && i[0] < Img.rows / 3)
//			//����ֱ�ߣ�����ڣ�85��,100�㣩
//			angle += i[1], cnt++;
//	angle /= cnt;
//
//	RotateMatrix = getRotationMatrix2D(Point(Img.rows / 2, Img.cols / 2), 180 * angle / CV_PI - 90, 1);
//	//��ʱ����ת�������ת���󣬸�����ת���󣬼�����ת��ͼ��Ĵ�С��Ϊ�˷�ֹ�߽��ISBN�����ֶ�ʧ
//	double cos = abs(RotateMatrix.at<double>(0, 0));
//	double sin = abs(RotateMatrix.at<double>(0, 1));
//	int nw = cos * Img.cols + sin * Img.rows;
//	int nh = sin * Img.cols + cos * Img.rows;
//	RotateMatrix.at<double>(0, 2) += (nw / 2 - Img.cols / 2);
//	RotateMatrix.at<double>(1, 2) += (nh / 2 - Img.rows / 2);
//	NewSize = { nw,nh };
//}
//
//int RowSum(Mat& Img, int RowIndex)//һ�����ػҶ�ֵ֮��
//{
//	int sum = 0;
//	for (int i = 0; i < Img.cols; i++)
//		if (Img.at<uchar>(RowIndex, i) == 255)sum++;
//	return sum;
//}
//int ColSum(Mat& Img, int ColIndex)//һ�����ػҶ�ֵ֮��
//{
//	int sum = 0;
//	for (int i = 0; i < Img.rows; i++)
//		if (Img.at<uchar>(i, ColIndex) == 255)sum++;
//	return sum;
//}
//int AllSum(Mat& Img)
//{
//	int sum = 0;
//	for (int i = 0; i < Img.rows; i++)
//		for (int j = 0; j < Img.cols; j++)
//			if (Img.at<uchar>(i, j) == 255)sum++;
//	return sum;
//}
//
//void GetISBNRow(Mat& Img)//���ISBN��������
//{
//	double width = 1500;
//	double height = width * Img.rows / Img.cols;
//	resize(Img, Img, Size(width, height));
//	ToGrey(Img);
//	RemoveNoise(Img);
//	ToBinary(Img);
//	Size newsize;
//	Mat m;
//	Rotate(Img, m, newsize);
//	warpAffine(Img, Img, m, newsize, INTER_LINEAR, 0);
//	//��ISBN�����е����½�
//	int RowIndex = 0, Upper_bound = 0, Lower_bound = 0, Height = 0;
//	while (RowIndex < Img.rows / 2)
//	{
//		while (RowIndex < Img.rows / 2 && RowSum(Img, RowIndex) < 10)RowIndex++;
//		int upper = RowIndex;
//		while (RowIndex < Img.rows / 2 && RowSum(Img, RowIndex) >= 10)RowIndex++;
//		int lower = RowIndex;
//		if (RowIndex < Img.rows / 2 && lower - upper > Height)
//			Upper_bound = upper, Lower_bound = lower, Height = lower - upper;
//	}
//	if (Upper_bound < Lower_bound)
//		Img = Mat(Img, Range(Upper_bound, Lower_bound), Range(0, Img.cols));
//}
//
//
//void GetMinRectangle(Mat& Img)//�����С����
//{
//	int Upper_bound, Lower_bound;
//	int RowIndex = 0;
//	while (!RowSum(Img, RowIndex))RowIndex++;
//	Upper_bound = RowIndex;
//	RowIndex = Img.rows - 1;
//	while (!RowSum(Img, RowIndex))RowIndex--;
//	Lower_bound = RowIndex;
//	if (Upper_bound < Lower_bound)
//		Img = Mat(Img, Range(Upper_bound, Lower_bound), Range(0, Img.cols));
//
//	int Left_bound, Right_bound;
//	int ColIndex = 0;
//	while (!ColSum(Img, ColIndex))ColIndex++;
//	Left_bound = ColIndex;
//	ColIndex = Img.cols - 1;
//	while (!ColSum(Img, ColIndex))ColIndex--;
//	Right_bound = ColIndex;
//	if (Left_bound < Right_bound)
//		Img = Mat(Img, Range(0, Img.rows), Range(Left_bound, Right_bound));
//
//}
//
//
//void SplitISBNRow(Mat& Img, vector<Mat>& Ch)//�ָ�ISBN�У��浽Ch��
//{
//	imshow("�з�ǰ��ͼƬ", Img);
//	waitKey(100);
//	int ColIndex = 0, Left_bound, Right_bound;
//	vector<Mat> ChCache;
//	int Height[30];
//	int Cnt = 0;
//	while (ColIndex < Img.cols)
//	{
//		while (ColIndex < Img.cols && !ColSum(Img, ColIndex))ColIndex++;
//		Left_bound = ColIndex;
//		while (ColIndex < Img.cols && ColSum(Img, ColIndex))ColIndex++;
//		Right_bound = ColIndex - 1;
//		if (Left_bound < Right_bound)
//		{
//			Mat Character = Mat(Img, Range(0, Img.rows), Range(Left_bound, Right_bound));
//			GetMinRectangle(Character);
//			ChCache.push_back(Character);
//			Height[Cnt++] = Character.rows;
//		}
//	}
//	int Mid = MedianFilter(Height, Cnt);
//	for (auto i : ChCache)
//		if (i.rows > 0.7 * Mid && i.rows < 1.3 * Mid) {
//			Ch.push_back(i);
//		}
//
//}
//
//bool Comp(pair<int, int>a, pair<int, int>b) {
//	return a.second < b.second;
//}
//int CalcImg(Mat inputImg) {
//	int nums = 0;
//	for (int i = 0; i < inputImg.rows; i++) {
//		for (int j = 0; j < inputImg.cols; j++) {
//			if (inputImg.at<uchar>(i, j) != 0) {
//				nums += inputImg.at<uchar>(i, j);
//			}
//		}
//	}
//	return nums;
//}
//
//char Compare(Mat TestImg, vector<pair<char, Mat>>& Mould) {
//	char best = '?';
//	double Max = 0;
//	resize(TestImg, TestImg, Size(40, 60));
//	//��ȡģ��ͼƬ
//	string sampleImgPath = "./ISBN/��������/*";
//	vector<String> sampleImgFN;
//	glob(sampleImgPath, sampleImgFN, false);
//	int sampleImgNums = sampleImgFN.size();
//	pair<int, int>* nums = new pair<int, int>[sampleImgNums];//first ��¼ģ��������ţ�second ��¼��ͼ��֮��
//	for (int i = 0; i < sampleImgNums; i++) {
//		nums[i].first = i;
//		Mat numImg = imread(sampleImgFN[i], 0);
//		Mat delImg;
//		resize(numImg, numImg, Size(40, 60));
//		absdiff(numImg, TestImg, delImg);
//		nums[i].second = CalcImg(delImg);
//	}
//	sort(nums, nums + sampleImgNums, Comp);//ѡ���ֵ��С��ģ��
//	//int index = nums[0].first / 2;
//	int index = nums[0].first;
//	return Mould[index].first;
//}
//
//int Judge(string& a, string& b)
//{
//	int f[50][50] = { 0 };
//	if (a[0] == b[0])f[0][0] = 1;
//	for (int i = 1; i < a.length(); i++)
//		for (int j = 1; j < b.length(); j++)
//			if (a[i] == b[j])f[i][j] = f[i - 1][j - 1] + 1;
//			else
//			{
//				f[i][j] = f[i - 1][j - 1];
//				f[i][j] = max(f[i][j], f[i - 1][j]);
//				f[i][j] = max(f[i][j], f[i][j - 1]);
//			}
//	return f[a.length() - 1][b.length() - 1];
//}
//
//void ReadTest(vector<String>& ImgFile)
//{
//	string testPath = "./ISBN/Train/*";
//	glob(testPath, ImgFile, false);
//}
//
//void ReadMould(vector<pair<char, Mat>>& Mould)
//{
//	vector<String> MouldPath;
//	string testPath = "./ISBN/��������/*";
//	glob(testPath, MouldPath, false);
//	for (auto i : MouldPath)
//	{
//		Mat MouldImg = imread(i, 0);
//		int p = i.find('\\');
//		ToBinary(MouldImg, 0, 0);
//		Mould.push_back({ i[p + 1],MouldImg });
//	}
//}
//
//int main()
//{
//	vector<String> TestFile;
//	ReadTest(TestFile);
//	vector<pair<char, Mat>> Mould;
//	ReadMould(Mould);
//	int OriginNumCnt = 0;
//	int RecogNumCnt = 0;
//	int Success = 0;
//	for (int i = 0; i < TestFile.size(); i++)
//	{
//		//��ͼ����ȡISBN�ַ���Ch
//		Mat Img = imread(TestFile[i]);
//		imshow("��ǰͼƬ", Img);
//		waitKey(100);
//		GetISBNRow(Img);
//		vector<Mat> Ch;
//		SplitISBNRow(Img, Ch);
//		//ͳ��ԭʼISBN�����ֵĸ���
//		int p1 = TestFile[i].find(' ');
//		int p2 = TestFile[i].rfind('.');
//		string OriginISBN = TestFile[i].substr(p1 + 1, p2 - p1 - 1);
//		for (int j = 0; j < OriginISBN.length(); j++)
//			if (isdigit(OriginISBN[j]))OriginNumCnt++;
//			else OriginISBN.erase(j, 1), j--;
//		//ʶ��ISBN�ַ���ͳ�Ƴɹ�ʶ�����ISBN�е����ָ���
//		string RecogISBN;
//		int Start = -1, Pos = 0;
//		int num = 0;
//		for (auto j : Ch)
//		{
//			num++;
//			char c = Compare(j, Mould);
//			if (!isdigit(c))continue;
//			if (num > 4) {
//				if (Start == -1 && (c == '7' || c == '9'))Start = Pos;
//				RecogISBN += c;
//				Pos++;
//			}
//		}
//		if (Start != -1)
//		{
//			int len = 13;
//			if (RecogISBN[0] == '7')len = MIN(10, RecogISBN.length() - Start);
//			if (RecogISBN[0] == '9')len = MIN(13, RecogISBN.length() - Start);
//			RecogISBN = RecogISBN.substr(Start, len);
//		}
//		RecogNumCnt += Judge(OriginISBN, RecogISBN);
//		//�жϸ�ISBN���Ƿ�ʶ��ɹ�
//		if (RecogISBN == OriginISBN) {
//			Success++, cout << OriginISBN << ' ' << RecogISBN << ' ' << "��ȷ" << endl;
//		}
//		else {
//			cout << OriginISBN << ' ' << RecogISBN << ' ' << "����" << endl;
//		}
//	}
//	cout << "��ʶ���ˣ�" << TestFile.size() << "��ͼƬ��" << endl;
//	cout << "��ȷ��Ϊ:" << fixed << setprecision(2) << Success * 100.0 / TestFile.size() << "%  ׼ȷ��Ϊ:" << fixed << setprecision(2) << RecogNumCnt * 100.0 / OriginNumCnt << "%" << endl;
//}
>>>>>>> c1abf96 (基础目录创建)
