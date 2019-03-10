/* Project: QTCanvasDemo
 * Date:    March 9, 2019
 * Author:  Micah Folsom
 * Copyright (C) Micah Folsom, All Rights Reserved. */
#pragma once
// QTCanvas
#include "qtcanvas.hpp"
// Qt
#include <QGroupBox>
#include <TH1D.h>
// ROOT
// std

/*! \class PlotWindow
 * A window containing a TCanvas embedded in a QWidget. */
class PlotWindow: public QWidget {
  Q_OBJECT

  public:
    PlotWindow(const int& wid);
    ~PlotWindow();

    // Required for ROOT functionality
    void changeEvent(QEvent* e);

  private:
    int       winID;
    QTCanvas* canvas;
    TH1D*     histogram;

    // GUI items
    QGroupBox* createPlotBox();
};
