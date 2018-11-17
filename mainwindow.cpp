/***************************************************************************
**
** Обучалка работы с графическим пакетом QCustomPlot
**
*************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
//#include <QScreen>
#include <QMessageBox>
#include <assert.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setGeometry(400, 250, 542, 390);
  
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

MyData MyFunc(int N, double x1, double x2, double a)
{
	assert(N > 1);
	MyData ans(N);
	for (int i = 0; i < N; ++i)
	{
		ans.x[i] = (x2-x1) * i / (N-1) + x1; // x от x1 до x2
		ans.y[i] =  a *ans.x[i] * ans.x[i];  // парабола
	}
	return ans;
};

void MainWindow::MyPlot1(QCustomPlot *customPlot, const MyData & data)
{
// create graph and assign data to it:
	customPlot->addGraph();
	customPlot->graph(0)->setData(data.x, data.y);
	// give the axes some labels:
	customPlot->xAxis->setLabel("x");
	customPlot->yAxis->setLabel("y");
	// set axes ranges, so we see all data:
	customPlot->xAxis->setRange(-1, 1);
	customPlot->yAxis->setRange(0, 1);

	customPlot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
	customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
	customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
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
  // generate some data:
  int N = 101;
  double x1 = -1;
  double x2 = 1;
  double a = 2;
  auto data = MyFunc(N, x1, x2, a);

  MyPlot1(customPlot, data);


}



bool MainWindow::saveToPNG(QCustomPlot *customPlot)
{
	QString fileName = demoName + ".png";
	bool ans = customPlot->savePng(fileName,600,400);
	return ans;
}






































