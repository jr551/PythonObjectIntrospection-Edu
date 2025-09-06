#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QList>
#include <QTreeWidgetItem>

#include <Python.h>


bool MainWindow::Introspection_IsFunction( PyObject *pContext, PyObject* pItem )
{
    PyObject *pAttribute = PyObject_GetAttr(pContext, pItem);
    return (PyObject_HasAttrString(pAttribute, "__call__") == 1);
}

void MainWindow::Introspection_ListFunctionParams( PyObject *pContext, PyObject* pItem, QTreeWidgetItem *qList )
{
    PyObject *p1 = PyObject_GetAttr(pContext, pItem);
    PyObject *p2 = PyObject_GetAttrString(p1, "func_code");
    PyObject *p3 = PyObject_GetAttrString(p2, "co_varnames");

    int listSize = PyTuple_Size(p3);

    for (int i = 0; i < listSize; i++) {

        PyObject *item = PyTuple_GetItem(p3, i);
        char *sItem;
        PyArg_Parse( item, "s", &sItem );

        QTreeWidgetItem *ite = new QTreeWidgetItem();
        ite->setText(0, QString(sItem));
        ite->setIcon(0, QIcon("/home/john/Downloads/icons/banana.ico") );
        qList->addChild( ite );
    }

}

void MainWindow::Introspection_ListClassAttribs( PyObject *pContext, const char* sItem)
{
    PyObject *pAttribute = PyObject_GetAttrString(pContext, sItem);
    PyObject *pAttributeList = PyObject_Dir(pAttribute);

    int listSize = PyList_Size(pAttributeList);

    QTreeWidgetItem *classTree = InsertTopLevelItem(sItem);

    for (int i = 0; i < listSize; i++) {

        PyObject *item = PyList_GetItem(pAttributeList, i);
        char *sItem;
        PyArg_Parse( item, "s", &sItem );
        if ( Introspection_IsFunction( pAttribute, item ) )
        {
            QTreeWidgetItem *ite = new QTreeWidgetItem();
            ite->setText(0, QString(sItem));
            ite->setIcon(0, QIcon("/home/john/Downloads/icons/toast2.ico") );
            classTree->addChild( ite );
           Introspection_ListFunctionParams(pAttribute, item, ite);
        }
        else
        {
            QTreeWidgetItem *ite = new QTreeWidgetItem();
            ite->setText(0, QString(sItem));
            ite->setIcon(0, QIcon("/home/john/Downloads/icons/toast.ico") );
            classTree->addChild( ite );
        }
    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnScanClass_clicked()
{

     Py_Initialize();
     PyObject *demoCodeModule   = PyImport_ImportModule("demo_john");
     if (demoCodeModule == NULL)
     {
         printf("Can't load 'demo_john' module!");
         return;
     }

    Introspection_ListClassAttribs(demoCodeModule, ui->txtValue->toPlainText().toAscii());
    ui->lstItems->expandAll();
    Py_Finalize();

}

QTreeWidgetItem *MainWindow::InsertTopLevelItem( const char *str )
{
    QColor grey(51,51,51,255);
    QBrush greyBrush( grey );

    QTreeWidgetItem *mainTree = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(str)) );
    mainTree->setForeground(0, greyBrush );

    mainTree->setIcon(0, QIcon("/home/john/Downloads/icons/grapes.ico") );
    ui->lstItems->insertTopLevelItem(0, mainTree);
    ui->lstItems->expandAll();
    return mainTree;
}
