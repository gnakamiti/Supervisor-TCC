/********************************************************************************
** Form generated from reading UI file 'Gmaps.ui'
**
** Created: Mon 1. Oct 20:57:33 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GMAPS_H
#define UI_GMAPS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_gMapsForm
{
public:
    QWebView *webView;

    void setupUi(QWidget *gMapsForm)
    {
        if (gMapsForm->objectName().isEmpty())
            gMapsForm->setObjectName(QString::fromUtf8("gMapsForm"));
        gMapsForm->setWindowModality(Qt::WindowModal);
        gMapsForm->resize(1128, 788);
        QIcon icon;
        icon.addFile(QString::fromUtf8("map2.png"), QSize(), QIcon::Normal, QIcon::Off);
        gMapsForm->setWindowIcon(icon);
        webView = new QWebView(gMapsForm);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setGeometry(QRect(-1, -1, 1131, 791));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(webView->sizePolicy().hasHeightForWidth());
        webView->setSizePolicy(sizePolicy);
        webView->setAutoFillBackground(false);
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        retranslateUi(gMapsForm);

        QMetaObject::connectSlotsByName(gMapsForm);
    } // setupUi

    void retranslateUi(QWidget *gMapsForm)
    {
        gMapsForm->setWindowTitle(QApplication::translate("gMapsForm", "Supervisor - Map", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class gMapsForm: public Ui_gMapsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GMAPS_H
