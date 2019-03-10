/* Project: QTCanvasDemo
 * Date:    March 9, 2019
 * Author:  Micah Folsom
 * Copyright (C) Micah Folsom, All Rights Reserved. */
// QTCanvas
#include "mainwindow.hpp"
// Qt
#include <QApplication>
// ROOT
#include <TApplication.h>
// std

/*! QTCanvasDemo main entry point. */
int main(int argc, char* argv[]) {
  // Must be heap-allocated, else we run into strange segfaults. Needed for
  // ROOT's event loop to run
  new TApplication("QTCanvas Demo", &argc, argv);

  // Qt event loop and such
  QApplication qtapp(argc, argv);

  // Make a window - show() is called in the constructor
  MainWindow win;

  // Starts Qt's main event loop
  return qtapp.exec();
}
