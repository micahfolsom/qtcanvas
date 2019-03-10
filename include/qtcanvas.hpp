/* Project: QTCanvasDemo
 * Date:    March 9, 2019
 * Author:  Micah Folsom
 * Copyright (C) Micah Folsom, All Rights Reserved. */
#pragma once
// QTCanvas
// Qt
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
// ROOT
#include <TCanvas.h>
// std

/*! \class QTCanvas
 * Wrapper class that wraps a QWidget around ROOT's TCanvas. */
class QTCanvas: public QWidget {
  Q_OBJECT

  public:
    QTCanvas(QWidget* parent = nullptr);
    ~QTCanvas();

    TCanvas* getCanvas() const;

    // TCanvas wrapper functions
    void cd(const int& ipad=0);
    void divide(const int& ncols, const int& nrows);
    void Update(); // uppercase to avoid conflict with QWidget::update()

  private:
    TCanvas* canvas;

    // Functions to capture QWidget events and pass them to ROOT
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void changeEvent(QEvent*);
};
