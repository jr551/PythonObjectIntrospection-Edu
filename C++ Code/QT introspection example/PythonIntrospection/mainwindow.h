#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Python.h>
#include <QTreeWidgetItem>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool Introspection_IsFunction( PyObject *pContext, PyObject* pItem );
    void Introspection_ListFunctionParams( PyObject *pContext, PyObject* pItem , QTreeWidgetItem *qList);
    void Introspection_ListClassAttribs( PyObject *pContext, const char* sItem);
    QTreeWidgetItem *InsertTopLevelItem( const char *str );

private slots:
    void on_btnScanClass_clicked();
};

#endif // MAINWINDOW_H
