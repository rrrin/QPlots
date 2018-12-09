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
		ans.x[i] = (x2 - x1) * i / (N - 1) + x1;
		ans.y[i] = sqrt(1-pow(ans.x[i],2));
	}
	return ans;
};

void MainWindow::MyPlot1(QCustomPlot *customPlot, const MyData & d, const int n)
{
	QVector<double> x1(d.x.size()), y1(d.x.size()), x2(d.x.size()), y2(d.x.size()), x3(n), y3(n);
	//double ax = 1., bx = 0., ay = 1., by = 0.;
	for (int i = 0; i < d.x.size(); i++)
	{
		x1[i] = d.x[i];
		y1[i] = d.y[i];
		x2[i] = d.x[i];
		y2[i] = -d.y[i];

	}
	auto x2_range = std::minmax_element(x2.begin(), x2.end());
	auto y2_range = std::minmax_element(y2.begin(), y2.end());
	auto x1_range = std::minmax_element(x1.begin(), x1.end());
	auto y1_range = std::minmax_element(y1.begin(), y1.end());
	auto x_min = std::min(*x1_range.first, *x2_range.first);
	auto y_min = std::min(*y1_range.first, *y2_range.first);
	auto x_max = std::max(*x1_range.second, *x2_range.second);
	auto y_max = std::max(*y1_range.second, *y2_range.second);
	customPlot->addGraph(); 
	customPlot->addGraph(); 
	customPlot->addGraph();
	assert(customPlot->graphCount() == 3);
	customPlot->graph(0)->setData(x1, y1);
	customPlot->graph(1)->setData(x2, y2);
	customPlot->graph(2)->setData(x3, y3);
	customPlot->xAxis->setLabel("x");
	customPlot->yAxis->setLabel("y");
	if (n % 2 == 0)
	{
		for (int i = 0; i < n/2; i++)
		{
			x3[i] = x_min + i * (x_max - x_min)*2 / n;
			y3[i] = sqrt(1 - pow(x3[i], 2));
		}
	}
	else
	{
		x3[0] = x_min;
		y3[0] = 0;
		for (int i = 1; i <= n / 2; i++)
		{
			x3[i] = x_min + i * (x_max - x_min) * 2 / (n-1);
			y3[i] = sqrt(1 - pow(x3[i], 2));
		}
	}
	customPlot->xAxis->setRange(x_min-0.1, x_max+0.1);
	customPlot->yAxis->setRange(y_min - 0.1, y_max + 0.1);

	//customPlot->legend->setVisible(true);
	//customPlot->graph(0)->setName("sin(x)");
	//customPlot->graph(1)->setName("a*x*x+b");

	customPlot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
	customPlot->graph(1)->setPen(QPen(QColor(255, 100, 0)));
	auto pen = customPlot->graph(0)->pen();
	pen.setWidth(3);
	customPlot->graph(0)->setPen(pen);
	auto pen2 = customPlot->graph(1)->pen();
	pen2.setWidth(3);
	customPlot->graph(1)->setPen(pen2);
	customPlot->graph(2)->setPen(QColor(50, 50, 50, 255));
	customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
	customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

}
void MainWindow::MyDemo1(QCustomPlot *customPlot)
{
	demoName = "MyDemo1";
	int N = 101;
	double x1 =  1.;
	double x2 =  -1.;
	
	auto d = MyFunc(N, x1, x2);
	MyPlot1(customPlot, d, 2);
}



bool MainWindow::saveToPNG(QCustomPlot *customPlot)
{
	QString fileName = demoName + ".png";
	bool ans = customPlot->savePng(fileName, 600, 400);
	return ans;
}





















