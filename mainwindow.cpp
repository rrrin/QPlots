/***************************************************************************
**
** Обучалка работы с графическим пакетом QCustomPlot
**
*************************************************************************************************************/
#include "stdafx.h"
/*#if 0
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
//#include <QScreen>
#include <QMessageBox>
#include <assert.h>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setGeometry(100, 250, 542, 390);
  
  MyDemo1(ui->customPlot);
  setWindowTitle("Plot: " + demoName);
//  statusBar()->clearMessage();
  ui->customPlot->replot();
  saveToPNG(ui->customPlot);
}
MainWindow::~MainWindow()
{
	delete ui;
}

//данные для рисования
struct MyData
{
	QVector<double> x, y;
	MyData(int N)
		: x(N), y(N)
	{}
	MyData() = default;
};

MyData MyFunc(int N, double x1, double x2)
{
	assert(N > 1);
	MyData ans(N);
	for (int i = 0; i < N; ++i)
	{
		ans.x[i] = (x2-x1) * i / (N-1) + x1; 
		ans.y[i] = sin(ans.x[i]);
	}
	return ans;
};

void MainWindow::MyPlot1(QCustomPlot *customPlot, const MyData & data)
{
	customPlot->addGraph();
	QVector<double> x(data.x.size()), y(data.x.size());
	double ax = 1., bx = 0., ay = 1., by = 0.;
	for (int i = 0; i < data.x.size(); i++)
	{
		x[i] = ax * data.x[i] + bx;
		y[i] = ay * data.y[i]+by;
	}
	customPlot->graph(0)->setData(x, y);
	customPlot->xAxis->setLabel("x");
	customPlot->yAxis->setLabel("y");
	auto x_range = std::minmax_element(x.begin(), x.end());
	auto y_range = std::minmax_element(y.begin(), y.end());
	assert(*x_range.first <= *x_range.second);
//	customPlot->xAxis->setRange(-2*M_PI, 2*M_PI);
	customPlot->xAxis->setRange(*x_range.first-0.1, *x_range.second+0.1);
	customPlot->yAxis->setRange(*y_range.first-0.1, *y_range.second+0.1);

	customPlot->graph(0)->setPen(QPen(QColor(255, 100, 0)));

	auto pen = customPlot->graph(0)->pen();
	pen.setWidth(3);
	customPlot->graph(0)->setPen(pen);
#if 0
	// give the axes some labels:
	customPlot->xAxis->setLabel("x");
	customPlot->yAxis->setLabel("y");
	// set axes ranges, so we see all data:
	customPlot->xAxis->setRange(-1.1, 1.1);
	customPlot->yAxis->setRange(-0.1, 1.1);
	customPlot->xAxis->ticker()->setTickCount(5);
	customPlot->yAxis->ticker()->setTickCount(5);
#endif


}
void MainWindow::MyDemo1(QCustomPlot *customPlot)
{
  demoName = "MyDemo1";
  int N = 101;
  double x1 = -4*M_PI;
  double x2 = 4*M_PI;
  double a = 2;
  auto data = MyFunc(N, x1, x2);

  MyPlot1(customPlot, data);


}



bool MainWindow::saveToPNG(QCustomPlot *customPlot)
{
	QString fileName = demoName + ".png";
	bool ans = customPlot->savePng(fileName,600,400);
	return ans;
}
#else*/
/*
/***************************************************************************
**
** Обучалка работы с графическим пакетом QCustomPlot
**
*************************************************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>

#include <QMessageBox>
#include <assert.h>
#include <math.h>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setGeometry(100, 50, 742, 590);
	

	MyDemo1(ui->customPlot);
	setWindowTitle("Plot: " + demoName);
	//  statusBar()->clearMessage();
	ui->customPlot->replot();
	saveToPNG(ui->customPlot);
}
MainWindow::~MainWindow()
{
	delete ui;
}
using namespace std;
typedef vector<vector<double>> mat_t;
mat_t create_mat(size_t nX, size_t nY) //создаю матрицу 
{
	mat_t ans;
	ans.resize(nY);

	for (size_t i = 0; i < nY; i++)
	{
		ans[i].resize(nX);
	}

	return ans;
}

//double func_u(double x)
//{
//	return pow(x, 4) / 8. - 7. / 24.*x*x;
//}
//double func_diff(double x)
//{
//	return pow(x, 3) / 2 - 7. / 12.*x;
//}

double func_u(double x)
{
	return 1. / (1. + 25.*x*x);
}
double func_diff(double x)
{
	return -50.*x / pow(1. + 25.*x*x, 2);
}

vector<double> progonka(const mat_t &coeff, int n, double a0, double b0, double an, double bn)
{
	vector<double> y(n + 1), p(n + 1), x(n + 1);

	y[1] = a0;
	p[1] = b0;
	for (int i = 1; i <= n - 1; i++)
	{
		y[i + 1] = -coeff[i][2] / (coeff[i][0] * y[i] + coeff[i][1]);
		p[i + 1] = (coeff[i][3] - coeff[i][0] * p[i]) / (coeff[i][0] * y[i] + coeff[i][1]);
	}

	x[n] = (bn + p[n] * an) / (1. - y[n] * an);
	for (int i = n - 1; i >= 0; i--)
	{
		x[i] = y[i + 1] * x[i + 1] + p[i + 1];
	}
	return x;
}

double splain(double x, vector<double> m, vector<double> h, vector<double> xi, vector<double> y )
{
	int i = 1;
	while (x<xi[i - 1] || x>xi[i])
		i++;
	double a = m[i - 1] * pow(xi[i] - x, 3) / 6. / h[i];
	double b = m[i] * pow(x - xi[i - 1], 3) / 6. / h[i];
	double c = (xi[i] - x) / h[i] * (y[i - 1] - m[i - 1] * h[i] * h[i] / 6.);
	double d = (x - xi[i - 1]) / h[i] * (y[i] - m[i] * h[i] * h[i] / 6.);
	return a+b+c+d;
}

vector<double> splain_coeff( int n, vector<double> x, vector<double> h, double f_diff_0, double f_diff_n, vector<double> y)
{

	mat_t coeff = create_mat(4, n + 1);
	for (int i = 1; i < n; i++)
	{
		coeff[i][0] = h[i] / 6.;
		coeff[i][1] = 2*(h[i]+h[i+1]) / 6.;
		coeff[i][2] = h[i+1] / 6.;
		coeff[i][3] = (h[i]*y[i + 1] - (h[i]+h[i+1]) * y[i] + h[i+1]*y[i-1]) / (h[i+1]*h[i]);
	}
	double b0 = 3. * (y[1] - y[0]) / (h[1]*h[1]) - 3.*f_diff_0 / h[1];
	double bn = 3.*f_diff_n / h[n] - 3.*(y[n] - y[n-1]) / (h[n] *h[n]);
	return progonka(coeff, n, -0.5, b0, -0.5, bn);

	//cout << splain(2, M, h, x) << endl;
}

//данные для рисования
struct MyData
{
	QVector<double> x, y, z, M, h;
	MyData(int N)
		: x(N), y(N), z(N), M(N), h(N)
	{}
	MyData() = default;
};

MyData MyFunc(int N, double x1, double x2, vector<double> M, vector<double> h, vector<double> x, vector<double> y)
{
	assert(N > 1);
	MyData ans(N);
	for (int i = 0; i < N; ++i)
	{
		ans.x[i] = (x2 - x1) * i / (N - 1) + x1;
		ans.y[i] = splain(ans.x[i], M, h, x, y);
		ans.z[i] = func_u(ans.x[i]);
	}
	return ans;
};

void MainWindow::MyPlot1(QCustomPlot *customPlot, const MyData & d, const int n, double x, double y)
{
	QVector<double> x1(d.x.size()), y1(d.x.size()), x2(d.x.size()), y2(d.x.size()), x3(n), y3(n);
	//double ax = 1., bx = 0., ay = 1., by = 0.;
	for (int i = 0; i < d.x.size(); i++)
	{
		x1[i] = d.x[i];
		y1[i] = d.y[i];
		//x2[i] = d.x[i];
		//y2[i] = d.z[i];

	}
	//auto x2_range = std::minmax_element(x2.begin(), x2.end());
	//auto y2_range = std::minmax_element(y2.begin(), y2.end());
	auto x1_range = std::minmax_element(x1.begin(), x1.end());
	auto y1_range = std::minmax_element(y1.begin(), y1.end());
	/*auto x_min = std::min(*x1_range.first, *x2_range.first);
	auto y_min = std::min(*y1_range.first, *y2_range.first);
	auto x_max = std::max(*x1_range.second, *x2_range.second);
	auto y_max = std::max(*y1_range.second, *y2_range.second);
	customPlot->addGraph(); */
	customPlot->addGraph(); 
	//assert(customPlot->graphCount() == 2);
	customPlot->graph(0)->setData(x1, y1);
	//customPlot->graph(1)->setData(x2, y2);

	customPlot->xAxis->setLabel("x");
	customPlot->yAxis->setLabel("y");
	
	customPlot->xAxis->setRange(*x1_range.first-0.1, *x1_range.second+0.1);
	customPlot->yAxis->setRange(*y1_range.first - 0.1, *y1_range.second + 0.1);

	QCPItemText *textLabel = new QCPItemText(customPlot);
	textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
	textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
	textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
	QString a=QString::number(x);
	QString b = QString::number(y);
	textLabel->setText("x="+a+ " y=" + b);
	//textLabel->setText("y=" + b);
	textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
	textLabel->setPen(QPen(Qt::black)); // show black border around text

										// add the arrow:
	QCPItemLine *arrow = new QCPItemLine(customPlot);
	arrow->start->setParentAnchor(textLabel->bottom);
	arrow->end->setCoords(x, y); // point to (4, 1.6) in x-y-plot coordinates
	arrow->setHead(QCPLineEnding::esSpikeArrow);

	//customPlot->legend->setVisible(true);
	//customPlot->graph(0)->setName("sin(x)");
	//customPlot->graph(1)->setName("a*x*x+b");

	customPlot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
	//customPlot->graph(1)->setPen(QPen(QColor(200, 0, 100)));
	auto pen = customPlot->graph(0)->pen();
	pen.setWidth(3);
	customPlot->graph(0)->setPen(pen);
	//auto pen2 = customPlot->graph(1)->pen();
	//pen2.setWidth(3);
	//customPlot->graph(1)->setPen(pen2);
	///*customPlot->graph(2)->setPen(QColor(50, 50, 50, 255));
	//customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
	//customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

}
void MainWindow::MyDemo1(QCustomPlot *customPlot)
{
	demoName = "MyDemo1";
	ifstream file_in;
	vector<double> x, y;
	double r;
	file_in.open("text.txt");
	file_in >> r;
	int n = r;
	while ((file_in >> r)&&(x.size()!=n))
	{
		x.push_back(r);
		file_in >> r;
		y.push_back(r);
	}
	double f_diff1 = r;
	file_in >> r; 
	double f_diff2 = r;
	int N = 201;
	//int n = x.size();
	vector<double> h(n);
	for (int i = 1; i < n; i++)
		h[i]=x[i] - x[i-1];
	vector<double> M = splain_coeff(n-1, x, h, f_diff1, f_diff2, y);
	auto d = MyFunc(N, x[0], x[n - 1], M, h, x, y);
	double a = -0.5;
	double b = splain(a, M, h, x, y);
	MyPlot1(customPlot, d, 2, a, b);
}
bool MainWindow::saveToPNG(QCustomPlot *customPlot)
{
	QString fileName = demoName + ".png";
	bool ans = customPlot->savePng(fileName, 600, 400);
	return ans;
}





















