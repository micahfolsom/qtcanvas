// QTCanvas
#include "qtcanvas.hpp"
// Qt
// ROOT
// std

/*! Constructor. */
QTCanvas::QTCanvas(QWidget* parent):
  QWidget(parent),
  canvas(nullptr)
{
 setAttribute(Qt::WA_OpaquePaintEvent, true);
 setMinimumSize(600, 500);
 setUpdatesEnabled(kFALSE);
 setMouseTracking(kTRUE);

 // Register the QWidget in TVirtualX, giving its native window id
 int wid = gVirtualX->AddWindow((ULong_t)winId(), width(), height());

 // Create the ROOT Tcanvas, giving as argument the QWidget registered id
 canvas = new TCanvas("Root Canvas", width(), height(), wid);
 
 canvas->Clear();
 canvas->SetBorderMode(0);
 canvas->SetFillColor(0);
}

/*! Destructor. */
QTCanvas::~QTCanvas() {
  delete canvas;
}

/*! Get the pointer to the ROOT canvas. */
TCanvas* QTCanvas::getCanvas() const {
  return canvas;
}

/*! Switch the ROOT current directory to this canvas. */
void QTCanvas::cd(const int& ipad) {
  if (canvas) {
     canvas->cd(ipad);
  }
  return;
}

/*! Divide the canvas into multiple pads. Uses the same syntax as
 * TCanvas::Divide(). */
void QTCanvas::divide(const int& ncols, const int& nrows) {
  canvas->Divide(ncols, nrows);
  return;
}

/*! Force an update of this canvas. */
void QTCanvas::Update() {
  if (canvas) {
    canvas->Modified();
    canvas->Resize();
    canvas->Update();
  }
  return;
}

/*! Capture the mouse movement. */
void QTCanvas::mouseMoveEvent(QMouseEvent* e) {
  if (canvas) {
    if (e->buttons() & Qt::LeftButton) {
      canvas->HandleInput(kButton1Motion, e->x(), e->y());
    } else if (e->buttons() & Qt::MidButton) {
      canvas->HandleInput(kButton2Motion, e->x(), e->y());
    } else if (e->buttons() & Qt::RightButton) {
      canvas->HandleInput(kButton3Motion, e->x(), e->y());
    } else {
      canvas->HandleInput(kMouseMotion, e->x(), e->y());
    }
  }
  return;
}

/*! Capture the mouse clicks. */
void QTCanvas::mousePressEvent(QMouseEvent* e) {
  if (canvas) {
    switch (e->button()) {
      case Qt::LeftButton:
        canvas->HandleInput(kButton1Down, e->x(), e->y());
        break;
         
      case Qt::MidButton:
        canvas->HandleInput(kButton2Down, e->x(), e->y());
        break;

      case Qt::RightButton:
        canvas->HandleInput(kButton3Down, e->x(), e->y());
        break;

      default:
        break;
    }
  }
  return;
}

/*! Handle mouse releases. */
void QTCanvas::mouseReleaseEvent(QMouseEvent* e) {
  if (canvas) {
    switch (e->button()) {
      case Qt::LeftButton:
        canvas->HandleInput(kButton1Up, e->x(), e->y());
        break;
         
      case Qt::MidButton:
        canvas->HandleInput(kButton2Up, e->x(), e->y());
        break;

      case Qt::RightButton:
        canvas->HandleInput(kButton3Up, e->x(), e->y());
        break;

      default:
        break;
    }
  }
  return;
}

/*! Force an update when a new paint happens for this widget. */
void QTCanvas::paintEvent(QPaintEvent*) {
  if (canvas) {
    Update();
  }
  return;
}

/*! Force an update when a resize happens for this widget. */
void QTCanvas::resizeEvent(QResizeEvent*) {
  if (canvas) {
    Update();
  }
  return;
}

/*! Force an update when a change happens for this widget. */
void QTCanvas::changeEvent(QEvent*) {
  if (canvas) {
    Update();
  }
  return;
}
