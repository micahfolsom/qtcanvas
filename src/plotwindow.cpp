/* Project: QTCanvasDemo
 * Date:    March 9, 2019
 * Author:  Micah Folsom
 * Copyright (C) Micah Folsom, All Rights Reserved. */
// QTCanvas
#include "plotwindow.hpp"
// Qt
#include <QGridLayout>
// ROOT
#include <TRandom3.h>
// std
#include <string>

/*! Constructor. */
PlotWindow::PlotWindow(const int& wid):
  QWidget(nullptr),
  winID(wid)
{
  // Window properties
  setMinimumSize(800, 600);
  std::string title = "Plot " + std::to_string(wid);
  setWindowTitle(title.c_str());
  
  // GUI elements
  auto grid = new QGridLayout(this);
  grid->addWidget(createPlotBox(), 0, 0, 7, 1);
  setLayout(grid);
  resize(1000, 800);

  show();

  // Tell the QTCanvas to Update *after* we have placed all the widgets and
  // displayed the window to make sure it draws/draws correctly
  canvas->Update();
}

/*! Destructor. */
PlotWindow::~PlotWindow() {
  delete histogram;
}

/*! Propagate changes to the window's state to ROOT for interactivity. */
void PlotWindow::changeEvent(QEvent* e) {
  if (e->type() == QEvent::WindowStateChange) {
    auto event = static_cast<QWindowStateChangeEvent*>(e);
    if ((event->oldState() & Qt::WindowMaximized)
        || (event->oldState() & Qt::WindowMinimized)
        || (event->oldState() == Qt::WindowNoState
            && this->windowState() == Qt::WindowMaximized)) {
      if (canvas->getCanvas()) {
        canvas->getCanvas()->Resize();
        canvas->getCanvas()->Update();
      }
    }
  }
  return;
}

/*! Create the Plot box. */
QGroupBox* PlotWindow::createPlotBox() {
  auto gbox = new QGroupBox(tr("Plot"));
  auto grid = new QGridLayout(gbox);

  // Canvas
  canvas = new QTCanvas;
  // grid becomes the parent of QTCanvas - no need to worry about cleaning
  // it up
  grid->addWidget(canvas);

  // Create a histogram to draw in the canvas
  canvas->cd();
  // Seed with winID so we don't just generate the same plot over and over
  TRandom3 r(winID);
  // Generate a name unique to this window to avoid histogram name collision
  std::string hname = "hGaus" + std::to_string(winID);
  histogram = new TH1D(hname.c_str(), "Gaussian Distribution", 100, 0, 100);
  for (int i=0;i < 10000;i++) {
    histogram->Fill(r.Gaus(50.0, 5.0));
  }
  histogram->Draw("hist");
  return gbox;
}
