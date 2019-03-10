/* Project: QTCanvasDemo
 * Date:    March 9, 2019
 * Author:  Micah Folsom
 * Copyright (C) Micah Folsom, All Rights Reserved. */
#pragma once
// QTCanvas
// Qt
#include <QWidget>
#include <QTimer>
#include <QGroupBox>
#include <QPushButton>
// ROOT
// std

/*! \class MainWindow
 * Top level window. */
class MainWindow: public QWidget {
  Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);

  private:
    QTimer rootTimer;
    int    nPlotWindows;
    
    // GUI elements
    QGroupBox*   createPlotBox();
    QPushButton* plotButton;

    // Copy/pasted from rootlogon.C - sets canvas, hist styles, etc
    void setROOTLogon();

  private slots:
    // GUI interaction slots
    void handlePlotButtonClicked();
    // Must be run on a timer - forces update of ROOT event loop
    void handleROOTEvents();
};
