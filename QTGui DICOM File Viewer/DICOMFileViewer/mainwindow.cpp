#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "AT_Element.h"
#include "CS_Element.h"
#include "SQ_Element.h"
#include "StringElement.h"
#include "SignedIntElement.h"
#include "UnsignedIntElement.h"
#include "FloatElement.h"
#include "DoubleElement.h"
#include "ByteElement.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Initialization */
    MC_STATUS status = MC_Library_Initialization(NULL, NULL, NULL);

    /* Registration */
    status = MC_Register_Application(&_applicationId, "My_DICOM_App");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileAction_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open DICOM file..."));

    if(filename == "")
        return;

    ui->dicomTagsViewWidget->clear();

    setWindowTitle("DICOM File Viewer - " + filename);

    try
    {
        /* Read data from file */
        _dicomFile.OpenFile(filename.toUtf8().data(), _applicationId);
    }
    catch(std::invalid_argument ex)
    {
        QMessageBox::information(this, tr("Error"), tr(ex.what()));
    }
    catch(std::runtime_error ex)
    {
        QMessageBox::information(this, tr("Error"), tr(ex.what()));
    }

    _FillTreeViewWithValues(_dicomFile.GetElements());
}

void MainWindow::_FillTreeViewWithValues(std::vector<AbstractDICOMDataElement*> elements)
{
    for(int i = 0; i < elements.size(); ++i)
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem(ui->dicomTagsViewWidget);

        QString tag = "(" + QString::fromStdString(elements[i]->GetTag().group) + "," + QString::fromStdString(elements[i]->GetTag().element + ")");
        itm->setText(0, tag);
        itm->setText(1, QString::fromStdString(elements[i]->GetValueRepresentationString()));
        itm->setText(2, elements[i]->GetDescription());

        QString values = _GetValueToString(elements[i]);

        itm->setText(3, values);

        if(elements[i]->GetValueRepresentation() == MC_VR::SQ)
            _AddChild(itm, static_cast<SQ_Element*>(elements[i])->sqAttributes);
    }
}

void MainWindow::_AddChild(QTreeWidgetItem *parent, std::vector<AbstractDICOMDataElement*> elements)
{
    for(int i = 0; i < elements.size(); ++i)
    {
        QTreeWidgetItem *itm = new QTreeWidgetItem();

        QString tag = "(" + QString::fromStdString(elements[i]->GetTag().group) + QString::fromStdString(elements[i]->GetTag().element + ")");
        itm->setText(0, tag);
        itm->setText(1, QString::fromStdString(elements[i]->GetValueRepresentationString()));
        itm->setText(2, elements[i]->GetDescription());

        QString values = _GetValueToString(elements[i]);

        itm->setText(3, values);

        parent->addChild(itm);

        if(elements[i]->GetValueRepresentation() == MC_VR::SQ)
            _AddChild(itm, static_cast<SQ_Element*>(elements[i])->sqAttributes);
    }
}

QString MainWindow::_GetValueToString(AbstractDICOMDataElement *element)
{
    QString values = "< ";

    switch(element->GetValueRepresentation())
    {
    case AE:case AS:case CS:case DA:case DS:case DT:case IS:case LO:case LT:case PN:case SH:case ST:case TM:case UT:case UI:case UC:case UR:
    {
        StringElement *sEl = static_cast<StringElement*>(element);
        for(int i = 0; i < element->GetNumberOfValues(); ++i)
        {
            values += QString::fromStdString(sEl->values[i]);

            /* Insert delimeter '\' between elements if attribute have multiple values */
            if(i != sEl->values.size() - 1)
                values += "\\";
        }
        values += " >";
        break;
    }
    case SS:case SL:
    {
        SignedIntElement *sIntEl = static_cast<SignedIntElement*>(element);
        for(int i = 0; i < element->GetNumberOfValues(); ++i)
        {
            values +=  QString::number(sIntEl->values[i]);

            /* Insert delimeter '\' between elements if attribute have multiple values */
            if(i != sIntEl->values.size() - 1)
                values += "\\";
        }
        values += " >";
        break;
    }
    case US: case UL:
    {
        UnsignedIntElement *uIntEl = static_cast<UnsignedIntElement*>(element);
        for(int i = 0; i < element->GetNumberOfValues(); ++i)
        {
            values +=  QString::number(uIntEl->values[i]);

            /* Insert delimeter '\' between elements if attribute have multiple values */
            if(i != uIntEl->values.size() - 1)
                values += "\\";
        }
        values += " >";
        break;
    }
    case FL:
    {
        FloatElement *fEl = static_cast<FloatElement*>(element);
        for(int i = 0; i < element->GetNumberOfValues(); ++i)
        {
            values +=  QString::number(fEl->values[i]);

            /* Insert delimeter '\' between elements if attribute have multiple values */
            if(i != fEl->values.size() - 1)
                values += "\\";
        }
        values += " >";
        break;
    }

    case FD:
    {
        DoubleElement *dEl = static_cast<DoubleElement*>(element);
        for(int i = 0; i < element->GetNumberOfValues(); ++i)
        {
            values +=  QString::number(dEl->values[i]);

            /* Insert delimeter '\' between elements if attribute have multiple values */
            if(i != dEl->values.size() - 1)
                values += "\\";
        }
        values += " >";
        break;
    }

    case OB:case OW:case OF:case OD:case OL:
    {
        ByteElement *bEl = static_cast<ByteElement*>(element);
        for(int i = 0; i < bEl->value.size(); ++i)
            values += QString::asprintf("(#%02x)", bEl->value[i] & 0xff);
        values += " >";
        break;
    }
    case SQ:
    {
        SQ_Element *sqEl = static_cast<SQ_Element*>(element);
        values +=  QString::number(sqEl->value);
        values += " >";
        break;
    }
    case AT:
    {
        AT_Element* atEl = static_cast<AT_Element*>(element);
        for(int i = 0; i < atEl->values.size(); ++i)
            values += "(" + QString::fromStdString(atEl->values[i].group) + "," + QString::fromStdString(atEl->values[i].element) + ")";
        values += " >";
        break;
    }

    case UNKNOWN_VR:
        values += "UNKNOWN VALUE";
        values += " >";
        break;
    }
    return values;
}
