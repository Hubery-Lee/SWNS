/********************************************************************************
** Form generated from reading UI file 'help.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Help
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *Help)
    {
        if (Help->objectName().isEmpty())
            Help->setObjectName(QString::fromUtf8("Help"));
        Help->resize(1328, 767);
        gridLayout = new QGridLayout(Help);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(Help);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);


        retranslateUi(Help);

        QMetaObject::connectSlotsByName(Help);
    } // setupUi

    void retranslateUi(QWidget *Help)
    {
        Help->setWindowTitle(QCoreApplication::translate("Help", "Form", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("Help", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/help_data/userGuide_01.png\" /><img src=\":/images/help_data/userGuide_02.png\" /><img src=\":/images/help_data/userGuide_03.png\" /><img src=\":/images/help_data/userGuide_04.png\" /><img src=\":/images/help_data/userGuide_05.png\" /><img src=\":/images/help_data/userGuide_06.png\" /><img src=\":/images/help_data/userGuide_07.png\" /><img src=\":/images/help_data/userGuide_08.png\" /><img src=\":/images/help_data/userGuide_09.png\" /><img src=\":/images/help_data/userGuide_10.png\" /><img src=\":/images/help_data/userGuide_11.png\" /><img src=\""
                        ":/images/help_data/userGuide_12.png\" /><img src=\":/images/help_data/userGuide_13.png\" /><img src=\":/images/help_data/userGuide_14.png\" /><img src=\":/images/help_data/userGuide_15.png\" /><img src=\":/images/help_data/userGuide_16.png\" /><img src=\":/images/help_data/userGuide_17.png\" /><img src=\":/images/help_data/userGuide_18.png\" /><img src=\":/images/help_data/userGuide_19.png\" /><img src=\":/images/help_data/userGuide_20.png\" /><img src=\":/images/help_data/userGuide_21.png\" /><img src=\":/images/help_data/userGuide_22.png\" /><img src=\":/images/help_data/userGuide_23.png\" /><img src=\":/images/help_data/userGuide_24.png\" /><img src=\":/images/help_data/userGuide_25.png\" /><img src=\":/images/help_data/userGuide_26.png\" /><img src=\":/images/help_data/userGuide_27.png\" /><img src=\":/images/help_data/userGuide_28.png\" /><img src=\":/images/help_data/userGuide_29.png\" /><img src=\":/images/help_data/userGuide_30.png\" /><img src=\":/images/help_data/userGuide_31.png\" /><img src=\":/ima"
                        "ges/help_data/userGuide_32.png\" /><img src=\":/images/help_data/userGuide_33.png\" /><img src=\":/images/help_data/userGuide_34.png\" /><img src=\":/images/help_data/userGuide_35.png\" /><img src=\":/images/help_data/userGuide_36.png\" /><img src=\":/images/help_data/userGuide_37.png\" /><img src=\":/images/help_data/userGuide_38.png\" /><img src=\":/images/help_data/userGuide_39.png\" /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Help: public Ui_Help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
