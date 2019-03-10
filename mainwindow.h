/***************************************************************************
**
** Обучалка работы с графическим пакетом QCustomPlot 
**
*************************************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTimer>
#include "QCustomPlot/qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.

namespace Ui {
class MainWindow;
}
struct MyData;

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void MyDemo1(QCustomPlot *customPlot);
  void MyPlot1(QCustomPlot *customPlot, const MyData & data, const int n, double x, double y);
  bool saveToPNG(QCustomPlot *customPlot);
private slots:
  
private:
  Ui::MainWindow *ui;
  QString demoName;
 };

#endif // MAINWINDOW_H
