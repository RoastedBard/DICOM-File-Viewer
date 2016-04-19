#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DICOMFile.h"

#include <QTreeWidget>
#include <QtCore>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void _FillTreeViewWithValues(std::vector<AbstractDICOMDataElement *> elements);
    void _AddChild(QTreeWidgetItem *parent, std::vector<AbstractDICOMDataElement *> elements);

    QString _GetValueToString(AbstractDICOMDataElement* element);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openFileAction_triggered();

private:
    Ui::MainWindow *ui;

private:
    DICOMFile _dicomFile;
    int       _applicationId;
};

#endif // MAINWINDOW_H
