/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2022 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: https://www.qcustomplot.com/                         **
**             Date: 06.11.22                                             **
**          Version: 2.1.1                                                **
****************************************************************************/

#include "qcustomplot.h"


/* including file 'src/vector2d.cpp'       */
/* modified 2022-11-06T12:45:56, size 7973 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPVector2D
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPVector2D
  \brief Represents two doubles as a mathematical 2D vector
  
  This class acts as a replacement for QVector2D with the advantage of double precision instead of
  single, and some convenience methods tailored for the QCustomPlot library.
*/

/* start documentation of inline functions */

/*! \fn void QCPVector2D::setX(double x)
  
  Sets the x coordinate of this vector to \a x.
  
  \see setY
*/

/*! \fn void QCPVector2D::setY(double y)
  
  Sets the y coordinate of this vector to \a y.
  
  \see setX
*/

/*! \fn double QCPVector2D::length() const
  
  Returns the length of this vector.
  
  \see lengthSquared
*/

/*! \fn double QCPVector2D::lengthSquared() const
  
  Returns the squared length of this vector. In some situations, e.g. when just trying to find the
  shortest vector of a group, this is faster than calculating \ref length, because it avoids
  calculation of a square root.
  
  \see length
*/

/*! \fn double QCPVector2D::angle() const
  
  Returns the angle of the vector in radians. The angle is measured between the positive x line and
  the vector, counter-clockwise in a mathematical coordinate system (y axis upwards positive). In
  screen/widget coordinates where the y axis is inverted, the angle appears clockwise.
*/

/*! \fn QPoint QCPVector2D::toPoint() const
  
  Returns a QPoint which has the x and y coordinates of this vector, truncating any floating point
  information.
  
  \see toPointF
*/

/*! \fn QPointF QCPVector2D::toPointF() const
  
  Returns a QPointF which has the x and y coordinates of this vector.
  
  \see toPoint
*/

/*! \fn bool QCPVector2D::isNull() const
  
  Returns whether this vector is null. A vector is null if \c qIsNull returns true for both x and y
  coordinates, i.e. if both are binary equal to 0.
*/

/*! \fn QCPVector2D QCPVector2D::perpendicular() const
  
  Returns a vector perpendicular to this vector, with the same length.
*/

/*! \fn double QCPVector2D::dot() const
  
  Returns the dot/scalar product of this vector with the specified vector \a vec.
*/

/* end documentation of inline functions */

/*!
  Creates a QCPVector2D object and initializes the x and y coordinates to 0.
*/
QCPVector2D::QCPVector2D() :
  mX(0),
  mY(0)
{
}

/*!
  Creates a QCPVector2D object and initializes the \a x and \a y coordinates with the specified
  values.
*/
QCPVector2D::QCPVector2D(double x, double y) :
  mX(x),
  mY(y)
{
}

/*!
  Creates a QCPVector2D object and initializes the x and y coordinates respective coordinates of
  the specified \a point.
*/
QCPVector2D::QCPVector2D(const QPoint &point) :
  mX(point.x()),
  mY(point.y())
{
}

/*!
  Creates a QCPVector2D object and initializes the x and y coordinates respective coordinates of
  the specified \a point.
*/
QCPVector2D::QCPVector2D(const QPointF &point) :
  mX(point.x()),
  mY(point.y())
{
}

/*!
  Normalizes this vector. After this operation, the length of the vector is equal to 1.
  
  If the vector has both entries set to zero, this method does nothing.
  
  \see normalized, length, lengthSquared
*/
void QCPVector2D::normalize()
{
  if (mX == 0.0 && mY == 0.0) return;
  const double lenInv = 1.0/length();
  mX *= lenInv;
  mY *= lenInv;
}

/*!
  Returns a normalized version of this vector. The length of the returned vector is equal to 1.
  
  If the vector has both entries set to zero, this method returns the vector unmodified.
  
  \see normalize, length, lengthSquared
*/
QCPVector2D QCPVector2D::normalized() const
{
  if (mX == 0.0 && mY == 0.0) return *this;
  const double lenInv = 1.0/length();
  return QCPVector2D(mX*lenInv, mY*lenInv);
}

/*! \overload
  
  Returns the squared shortest distance of this vector (interpreted as a point) to the finite line
  segment given by \a start and \a end.
  
  \see distanceToStraightLine
*/
double QCPVector2D::distanceSquaredToLine(const QCPVector2D &start, const QCPVector2D &end) const
{
  const QCPVector2D v(end-start);
  const double vLengthSqr = v.lengthSquared();
  if (!qFuzzyIsNull(vLengthSqr))
  {
    const double mu = v.dot(*this-start)/vLengthSqr;
    if (mu < 0)
      return (*this-start).lengthSquared();
    else if (mu > 1)
      return (*this-end).lengthSquared();
    else
      return ((start + mu*v)-*this).lengthSquared();
  } else
    return (*this-start).lengthSquared();
}

/*! \overload
  
  Returns the squared shortest distance of this vector (interpreted as a point) to the finite line
  segment given by \a line.
  
  \see distanceToStraightLine
*/
double QCPVector2D::distanceSquaredToLine(const QLineF &line) const
{
  return distanceSquaredToLine(QCPVector2D(line.p1()), QCPVector2D(line.p2()));
}

/*!
  Returns the shortest distance of this vector (interpreted as a point) to the infinite straight
  line given by a \a base point and a \a direction vector.
  
  \see distanceSquaredToLine
*/
double QCPVector2D::distanceToStraightLine(const QCPVector2D &base, const QCPVector2D &direction) const
{
  return qAbs((*this-base).dot(direction.perpendicular()))/direction.length();
}

/*!
  Scales this vector by the given \a factor, i.e. the x and y components are multiplied by \a
  factor.
*/
QCPVector2D &QCPVector2D::operator*=(double factor)
{
  mX *= factor;
  mY *= factor;
  return *this;
}

/*!
  Scales this vector by the given \a divisor, i.e. the x and y components are divided by \a
  divisor.
*/
QCPVector2D &QCPVector2D::operator/=(double divisor)
{
  mX /= divisor;
  mY /= divisor;
  return *this;
}

/*!
  Adds the given \a vector to this vector component-wise.
*/
QCPVector2D &QCPVector2D::operator+=(const QCPVector2D &vector)
{
  mX += vector.mX;
  mY += vector.mY;
  return *this;
}

/*!
  subtracts the given \a vector from this vector component-wise.
*/
QCPVector2D &QCPVector2D::operator-=(const QCPVector2D &vector)
{
  mX -= vector.mX;
  mY -= vector.mY;
  return *this;
}
/* end of 'src/vector2d.cpp' */


/* including file 'src/painter.cpp'        */
/* modified 2022-11-06T12:45:56, size 8656 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPPainter
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPPainter
  \brief QPainter subclass used internally
  
  This QPainter subclass is used to provide some extended functionality e.g. for tweaking position
  consistency between antialiased and non-antialiased painting. Further it provides workarounds
  for QPainter quirks.
  
  \warning This class intentionally hides non-virtual functions of QPainter, e.g. setPen, save and
  restore. So while it is possible to pass a QCPPainter instance to a function that expects a
  QPainter pointer, some of the workarounds and tweaks will be unavailable to the function (because
  it will call the base class implementations of the functions actually hidden by QCPPainter).
*/

/*!
  Creates a new QCPPainter instance and sets default values
*/
QCPPainter::QCPPainter() :
  mModes(pmDefault),
  mIsAntialiasing(false)
{
  // don't setRenderHint(QPainter::NonCosmeticDefautPen) here, because painter isn't active yet and
  // a call to begin() will follow
}

/*!
  Creates a new QCPPainter instance on the specified paint \a device and sets default values. Just
  like the analogous QPainter constructor, begins painting on \a device immediately.
  
  Like \ref begin, this method sets QPainter::NonCosmeticDefaultPen in Qt versions before Qt5.
*/
QCPPainter::QCPPainter(QPaintDevice *device) :
  QPainter(device),
  mModes(pmDefault),
  mIsAntialiasing(false)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0) // before Qt5, default pens used to be cosmetic if NonCosmeticDefaultPen flag isn't set. So we set it to get consistency across Qt versions.
  if (isActive())
    setRenderHint(QPainter::NonCosmeticDefaultPen);
#endif
}

/*!
  Sets the pen of the painter and applies certain fixes to it, depending on the mode of this
  QCPPainter.
  
  \note this function hides the non-virtual base class implementation.
*/
void QCPPainter::setPen(const QPen &pen)
{
  QPainter::setPen(pen);
  if (mModes.testFlag(pmNonCosmetic))
    makeNonCosmetic();
}

/*! \overload
  
  Sets the pen (by color) of the painter and applies certain fixes to it, depending on the mode of
  this QCPPainter.
  
  \note this function hides the non-virtual base class implementation.
*/
void QCPPainter::setPen(const QColor &color)
{
  QPainter::setPen(color);
  if (mModes.testFlag(pmNonCosmetic))
    makeNonCosmetic();
}

/*! \overload
  
  Sets the pen (by style) of the painter and applies certain fixes to it, depending on the mode of
  this QCPPainter.
  
  \note this function hides the non-virtual base class implementation.
*/
void QCPPainter::setPen(Qt::PenStyle penStyle)
{
  QPainter::setPen(penStyle);
  if (mModes.testFlag(pmNonCosmetic))
    makeNonCosmetic();
}

/*! \overload
  
  Works around a Qt bug introduced with Qt 4.8 which makes drawing QLineF unpredictable when
  antialiasing is disabled. Thus when antialiasing is disabled, it rounds the \a line to
  integer coordinates and then passes it to the original drawLine.
  
  \note this function hides the non-virtual base class implementation.
*/
void QCPPainter::drawLine(const QLineF &line)
{
  if (mIsAntialiasing || mModes.testFlag(pmVectorized))
    QPainter::drawLine(line);
  else
    QPainter::drawLine(line.toLine());
}

/*!
  Sets whether painting uses antialiasing or not. Use this method instead of using setRenderHint
  with QPainter::Antialiasing directly, as it allows QCPPainter to regain pixel exactness between
  antialiased and non-antialiased painting (Since Qt < 5.0 uses slightly different coordinate systems for
  AA/Non-AA painting).
*/
void QCPPainter::setAntialiasing(bool enabled)
{
  setRenderHint(QPainter::Antialiasing, enabled);
  if (mIsAntialiasing != enabled)
  {
    mIsAntialiasing = enabled;
    if (!mModes.testFlag(pmVectorized)) // antialiasing half-pixel shift only needed for rasterized outputs
    {
      if (mIsAntialiasing)
        translate(0.5, 0.5);
      else
        translate(-0.5, -0.5);
    }
  }
}

/*!
  Sets the mode of the painter. This controls whether the painter shall adjust its
  fixes/workarounds optimized for certain output devices.
*/
void QCPPainter::setModes(QCPPainter::PainterModes modes)
{
  mModes = modes;
}

/*!
  Sets the QPainter::NonCosmeticDefaultPen in Qt versions before Qt5 after beginning painting on \a
  device. This is necessary to get cosmetic pen consistency across Qt versions, because since Qt5,
  all pens are non-cosmetic by default, and in Qt4 this render hint must be set to get that
  behaviour.
  
  The Constructor \ref QCPPainter(QPaintDevice *device) which directly starts painting also sets
  the render hint as appropriate.
  
  \note this function hides the non-virtual base class implementation.
*/
bool QCPPainter::begin(QPaintDevice *device)
{
  bool result = QPainter::begin(device);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0) // before Qt5, default pens used to be cosmetic if NonCosmeticDefaultPen flag isn't set. So we set it to get consistency across Qt versions.
  if (result)
    setRenderHint(QPainter::NonCosmeticDefaultPen);
#endif
  return result;
}

/*! \overload
  
  Sets the mode of the painter. This controls whether the painter shall adjust its
  fixes/workarounds optimized for certain output devices.
*/
void QCPPainter::setMode(QCPPainter::PainterMode mode, bool enabled)
{
  if (!enabled && mModes.testFlag(mode))
    mModes &= ~mode;
  else if (enabled && !mModes.testFlag(mode))
    mModes |= mode;
}

/*!
  Saves the painter (see QPainter::save). Since QCPPainter adds some new internal state to
  QPainter, the save/restore functions are reimplemented to also save/restore those members.
  
  \note this function hides the non-virtual base class implementation.
  
  \see restore
*/
void QCPPainter::save()
{
  mAntialiasingStack.push(mIsAntialiasing);
  QPainter::save();
}

/*!
  Restores the painter (see QPainter::restore). Since QCPPainter adds some new internal state to
  QPainter, the save/restore functions are reimplemented to also save/restore those members.
  
  \note this function hides the non-virtual base class implementation.
  
  \see save
*/
void QCPPainter::restore()
{
  if (!mAntialiasingStack.isEmpty())
    mIsAntialiasing = mAntialiasingStack.pop();
  else
    qDebug() << Q_FUNC_INFO << "Unbalanced save/restore";
  QPainter::restore();
}

/*!
  Changes the pen width to 1 if it currently is 0. This function is called in the \ref setPen
  overrides when the \ref pmNonCosmetic mode is set.
*/
void QCPPainter::makeNonCosmetic()
{
  if (qFuzzyIsNull(pen().widthF()))
  {
    QPen p = pen();
    p.setWidth(1);
    QPainter::setPen(p);
  }
}
/* end of 'src/painter.cpp' */


/* including file 'src/paintbuffer.cpp'     */
/* modified 2022-11-06T12:45:56, size 18915 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPAbstractPaintBuffer
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPAbstractPaintBuffer
  \brief The abstract base class for paint buffers, which define the rendering backend

  This abstract base class defines the basic interface that a paint buffer needs to provide in
  order to be usable by QCustomPlot.

  A paint buffer manages both a surface to draw onto, and the matching paint device. The size of
  the surface can be changed via \ref setSize. External classes (\ref QCustomPlot and \ref
  QCPLayer) request a painter via \ref startPainting and then perform the draw calls. Once the
  painting is complete, \ref donePainting is called, so the paint buffer implementation can do
  clean up if necessary. Before rendering a frame, each paint buffer is usually filled with a color
  using \ref clear (usually the color is \c Qt::transparent), to remove the contents of the
  previous frame.

  The simplest paint buffer implementation is \ref QCPPaintBufferPixmap which allows regular
  software rendering via the raster engine. Hardware accelerated rendering via pixel buffers and
  frame buffer objects is provided by \ref QCPPaintBufferGlPbuffer and \ref QCPPaintBufferGlFbo.
  They are used automatically if \ref QCustomPlot::setOpenGl is enabled.
*/

/* start documentation of pure virtual functions */

/*! \fn virtual QCPPainter *QCPAbstractPaintBuffer::startPainting() = 0

  Returns a \ref QCPPainter which is ready to draw to this buffer. The ownership and thus the
  responsibility to delete the painter after the painting operations are complete is given to the
  caller of this method.

  Once you are done using the painter, delete the painter and call \ref donePainting.

  While a painter generated with this method is active, you must not call \ref setSize, \ref
  setDevicePixelRatio or \ref clear.

  This method may return 0, if a painter couldn't be activated on the buffer. This usually
  indicates a problem with the respective painting backend.
*/

/*! \fn virtual void QCPAbstractPaintBuffer::draw(QCPPainter *painter) const = 0

  Draws the contents of this buffer with the provided \a painter. This is the method that is used
  to finally join all paint buffers and draw them onto the screen.
*/

/*! \fn virtual void QCPAbstractPaintBuffer::clear(const QColor &color) = 0

  Fills the entire buffer with the provided \a color. To have an empty transparent buffer, use the
  named color \c Qt::transparent.

  This method must not be called if there is currently a painter (acquired with \ref startPainting)
  active.
*/

/*! \fn virtual void QCPAbstractPaintBuffer::reallocateBuffer() = 0

  Reallocates the internal buffer with the currently configured size (\ref setSize) and device
  pixel ratio, if applicable (\ref setDevicePixelRatio). It is called as soon as any of those
  properties are changed on this paint buffer.

  \note Subclasses of \ref QCPAbstractPaintBuffer must call their reimplementation of this method
  in their constructor, to perform the first allocation (this can not be done by the base class
  because calling pure virtual methods in base class constructors is not possible).
*/

/* end documentation of pure virtual functions */
/* start documentation of inline functions */

/*! \fn virtual void QCPAbstractPaintBuffer::donePainting()

  If you have acquired a \ref QCPPainter to paint onto this paint buffer via \ref startPainting,
  call this method as soon as you are done with the painting operations and have deleted the
  painter.

  paint buffer subclasses may use this method to perform any type of cleanup that is necessary. The
  default implementation does nothing.
*/

/* end documentation of inline functions */

/*!
  Creates a paint buffer and initializes it with the provided \a size and \a devicePixelRatio.

  Subclasses must call their \ref reallocateBuffer implementation in their respective constructors.
*/
QCPAbstractPaintBuffer::QCPAbstractPaintBuffer(const QSize &size, double devicePixelRatio) :
  mSize(size),
  mDevicePixelRatio(devicePixelRatio),
  mInvalidated(true)
{
}

QCPAbstractPaintBuffer::~QCPAbstractPaintBuffer()
{
}

/*!
  Sets the paint buffer size.

  The buffer is reallocated (by calling \ref reallocateBuffer), so any painters that were obtained
  by \ref startPainting are invalidated and must not be used after calling this method.

  If \a size is already the current buffer size, this method does nothing.
*/
void QCPAbstractPaintBuffer::setSize(const QSize &size)
{
  if (mSize != size)
  {
    mSize = size;
    reallocateBuffer();
  }
}

/*!
  Sets the invalidated flag to \a invalidated.

  This mechanism is used internally in conjunction with isolated replotting of \ref QCPLayer
  instances (in \ref QCPLayer::lmBuffered mode). If \ref QCPLayer::replot is called on a buffered
  layer, i.e. an isolated repaint of only that layer (and its dedicated paint buffer) is requested,
  QCustomPlot will decide depending on the invalidated flags of other paint buffers whether it also
  replots them, instead of only the layer on which the replot was called.

  The invalidated flag is set to true when \ref QCPLayer association has changed, i.e. if layers
  were added or removed from this buffer, or if they were reordered. It is set to false as soon as
  all associated \ref QCPLayer instances are drawn onto the buffer.

  Under normal circumstances, it is not necessary to manually call this method.
*/
void QCPAbstractPaintBuffer::setInvalidated(bool invalidated)
{
  mInvalidated = invalidated;
}

/*!
  Sets the device pixel ratio to \a ratio. This is useful to render on high-DPI output devices.
  The ratio is automatically set to the device pixel ratio used by the parent QCustomPlot instance.

  The buffer is reallocated (by calling \ref reallocateBuffer), so any painters that were obtained
  by \ref startPainting are invalidated and must not be used after calling this method.

  \note This method is only available for Qt versions 5.4 and higher.
*/
void QCPAbstractPaintBuffer::setDevicePixelRatio(double ratio)
{
  if (!qFuzzyCompare(ratio, mDevicePixelRatio))
  {
#ifdef QCP_DEVICEPIXELRATIO_SUPPORTED
    mDevicePixelRatio = ratio;
    reallocateBuffer();
#else
    qDebug() << Q_FUNC_INFO << "Device pixel ratios not supported for Qt versions before 5.4";
    mDevicePixelRatio = 1.0;
#endif
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPPaintBufferPixmap
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPPaintBufferPixmap
  \brief A paint buffer based on QPixmap, using software raster rendering

  This paint buffer is the default and fall-back paint buffer which uses software rendering and
  QPixmap as internal buffer. It is used if \ref QCustomPlot::setOpenGl is false.
*/

/*!
  Creates a pixmap paint buffer instancen with the specified \a size and \a devicePixelRatio, if
  applicable.
*/
QCPPaintBufferPixmap::QCPPaintBufferPixmap(const QSize &size, double devicePixelRatio) :
  QCPAbstractPaintBuffer(size, devicePixelRatio)
{
  QCPPaintBufferPixmap::reallocateBuffer();
}

QCPPaintBufferPixmap::~QCPPaintBufferPixmap()
{
}

/* inherits documentation from base class */
QCPPainter *QCPPaintBufferPixmap::startPainting()
{
  QCPPainter *result = new QCPPainter(&mBuffer);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  result->setRenderHint(QPainter::HighQualityAntialiasing);
#endif
  return result;
}

/* inherits documentation from base class */
void QCPPaintBufferPixmap::draw(QCPPainter *painter) const
{
  if (painter && painter->isActive())
    painter->drawPixmap(0, 0, mBuffer);
  else
    qDebug() << Q_FUNC_INFO << "invalid or inactive painter passed";
}

/* inherits documentation from base class */
void QCPPaintBufferPixmap::clear(const QColor &color)
{
  mBuffer.fill(color);
}

/* inherits documentation from base class */
void QCPPaintBufferPixmap::reallocateBuffer()
{
  setInvalidated();
  if (!qFuzzyCompare(1.0, mDevicePixelRatio))
  {
#ifdef QCP_DEVICEPIXELRATIO_SUPPORTED
    mBuffer = QPixmap(mSize*mDevicePixelRatio);
    mBuffer.setDevicePixelRatio(mDevicePixelRatio);
#else
    qDebug() << Q_FUNC_INFO << "Device pixel ratios not supported for Qt versions before 5.4";
    mDevicePixelRatio = 1.0;
    mBuffer = QPixmap(mSize);
#endif
  } else
  {
    mBuffer = QPixmap(mSize);
  }
}


#ifdef QCP_OPENGL_PBUFFER
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPPaintBufferGlPbuffer
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPPaintBufferGlPbuffer
  \brief A paint buffer based on OpenGL pixel buffers, using hardware accelerated rendering

  This paint buffer is one of the OpenGL paint buffers which facilitate hardware accelerated plot
  rendering. It is based on OpenGL pixel buffers (pbuffer) and is used in Qt versions before 5.0.
  (See \ref QCPPaintBufferGlFbo used in newer Qt versions.)

  The OpenGL paint buffers are used if \ref QCustomPlot::setOpenGl is set to true, and if they are
  supported by the system.
*/

/*!
  Creates a \ref QCPPaintBufferGlPbuffer instance with the specified \a size and \a
  devicePixelRatio, if applicable.

  The parameter \a multisamples defines how many samples are used per pixel. Higher values thus
  result in higher quality antialiasing. If the specified \a multisamples value exceeds the
  capability of the graphics hardware, the highest supported multisampling is used.
*/
QCPPaintBufferGlPbuffer::QCPPaintBufferGlPbuffer(const QSize &size, double devicePixelRatio, int multisamples) :
  QCPAbstractPaintBuffer(size, devicePixelRatio),
  mGlPBuffer(0),
  mMultisamples(qMax(0, multisamples))
{
  QCPPaintBufferGlPbuffer::reallocateBuffer();
}

QCPPaintBufferGlPbuffer::~QCPPaintBufferGlPbuffer()
{
  if (mGlPBuffer)
    delete mGlPBuffer;
}

/* inherits documentation from base class */
QCPPainter *QCPPaintBufferGlPbuffer::startPainting()
{
  if (!mGlPBuffer->isValid())
  {
    qDebug() << Q_FUNC_INFO << "OpenGL frame buffer object doesn't exist, reallocateBuffer was not called?";
    return 0;
  }
  
  QCPPainter *result = new QCPPainter(mGlPBuffer);
  result->setRenderHint(QPainter::HighQualityAntialiasing);
  return result;
}

/* inherits documentation from base class */
void QCPPaintBufferGlPbuffer::draw(QCPPainter *painter) const
{
  if (!painter || !painter->isActive())
  {
    qDebug() << Q_FUNC_INFO << "invalid or inactive painter passed";
    return;
  }
  if (!mGlPBuffer->isValid())
  {
    qDebug() << Q_FUNC_INFO << "OpenGL pbuffer isn't valid, reallocateBuffer was not called?";
    return;
  }
  painter->drawImage(0, 0, mGlPBuffer->toImage());
}

/* inherits documentation from base class */
void QCPPaintBufferGlPbuffer::clear(const QColor &color)
{
  if (mGlPBuffer->isValid())
  {
    mGlPBuffer->makeCurrent();
    glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mGlPBuffer->doneCurrent();
  } else
    qDebug() << Q_FUNC_INFO << "OpenGL pbuffer invalid or context not current";
}

/* inherits documentation from base class */
void QCPPaintBufferGlPbuffer::reallocateBuffer()
{
  if (mGlPBuffer)
    delete mGlPBuffer;
  
  QGLFormat format;
  format.setAlpha(true);
  format.setSamples(mMultisamples);
  mGlPBuffer = new QGLPixelBuffer(mSize, format);
}
#endif // QCP_OPENGL_PBUFFER


#ifdef QCP_OPENGL_FBO
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPPaintBufferGlFbo
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPPaintBufferGlFbo
  \brief A paint buffer based on OpenGL frame buffers objects, using hardware accelerated rendering

  This paint buffer is one of the OpenGL paint buffers which facilitate hardware accelerated plot
  rendering. It is based on OpenGL frame buffer objects (fbo) and is used in Qt versions 5.0 and
  higher. (See \ref QCPPaintBufferGlPbuffer used in older Qt versions.)

  The OpenGL paint buffers are used if \ref QCustomPlot::setOpenGl is set to true, and if they are
  supported by the system.
*/

/*!
  Creates a \ref QCPPaintBufferGlFbo instance with the specified \a size and \a devicePixelRatio,
  if applicable.

  All frame buffer objects shall share one OpenGL context and paint device, which need to be set up
  externally and passed via \a glContext and \a glPaintDevice. The set-up is done in \ref
  QCustomPlot::setupOpenGl and the context and paint device are managed by the parent QCustomPlot
  instance.
*/
QCPPaintBufferGlFbo::QCPPaintBufferGlFbo(const QSize &size, double devicePixelRatio, QWeakPointer<QOpenGLContext> glContext, QWeakPointer<QOpenGLPaintDevice> glPaintDevice) :
  QCPAbstractPaintBuffer(size, devicePixelRatio),
  mGlContext(glContext),
  mGlPaintDevice(glPaintDevice),
  mGlFrameBuffer(0)
{
  QCPPaintBufferGlFbo::reallocateBuffer();
}

QCPPaintBufferGlFbo::~QCPPaintBufferGlFbo()
{
  if (mGlFrameBuffer)
    delete mGlFrameBuffer;
}

/* inherits documentation from base class */
QCPPainter *QCPPaintBufferGlFbo::startPainting()
{
  QSharedPointer<QOpenGLPaintDevice> paintDevice = mGlPaintDevice.toStrongRef();
  QSharedPointer<QOpenGLContext> context = mGlContext.toStrongRef();
  if (!paintDevice)
  {
    qDebug() << Q_FUNC_INFO << "OpenGL paint device doesn't exist";
    return 0;
  }
  if (!context)
  {
    qDebug() << Q_FUNC_INFO << "OpenGL context doesn't exist";
    return 0;
  }
  if (!mGlFrameBuffer)
  {
    qDebug() << Q_FUNC_INFO << "OpenGL frame buffer object doesn't exist, reallocateBuffer was not called?";
    return 0;
  }
  
  if (QOpenGLContext::currentContext() != context.data())
    context->makeCurrent(context->surface());
  mGlFrameBuffer->bind();
  QCPPainter *result = new QCPPainter(paintDevice.data());
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  result->setRenderHint(QPainter::HighQualityAntialiasing);
#endif
  return result;
}

/* inherits documentation from base class */
void QCPPaintBufferGlFbo::donePainting()
{
  if (mGlFrameBuffer && mGlFrameBuffer->isBound())
    mGlFrameBuffer->release();
  else
    qDebug() << Q_FUNC_INFO << "Either OpenGL frame buffer not valid or was not bound";
}

/* inherits documentation from base class */
void QCPPaintBufferGlFbo::draw(QCPPainter *painter) const
{
  if (!painter || !painter->isActive())
  {
    qDebug() << Q_FUNC_INFO << "invalid or inactive painter passed";
    return;
  }
  if (!mGlFrameBuffer)
  {
    qDebug() << Q_FUNC_INFO << "OpenGL frame buffer object doesn't exist, reallocateBuffer was not called?";
    return;
  }
  painter->drawImage(0, 0, mGlFrameBuffer->toImage());
}

/* inherits documentation from base class */
void QCPPaintBufferGlFbo::clear(const QColor &color)
{
  QSharedPointer<QOpenGLContext> context = mGlContext.toStrongRef();
  if (!context)
  {
    qDebug() << Q_FUNC_INFO << "OpenGL context doesn't exist";
    return;
  }
  if (!mGlFrameBuffer)
  {
    qDebug() << Q_FUNC_INFO << "OpenGL frame buffer object doesn't exist, reallocateBuffer was not called?";
    return;
  }
  
  if (QOpenGLContext::currentContext() != context.data())
    context->makeCurrent(context->surface());
  mGlFrameBuffer->bind();
  glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  mGlFrameBuffer->release();
}

/* inherits documentation from base class */
void QCPPaintBufferGlFbo::reallocateBuffer()
{
  // release and delete possibly existing framebuffer:
  if (mGlFrameBuffer)
  {
    if (mGlFrameBuffer->isBound())
      mGlFrameBuffer->release();
    delete mGlFrameBuffer;
    mGlFrameBuffer = 0;
  }
  
  QSharedPointer<QOpenGLPaintDevice> paintDevice = mGlPaintDevice.toStrongRef();
  QSharedPointer<QOpenGLContext> context = mGlContext.toStrongRef();
  if (!paintDevice)
  {
    qDebug() << Q_FUNC_INFO << "OpenGL paint device doesn't exist";
    return;
  }
  if (!context)
  {
    qDebug() << Q_FUNC_INFO << "OpenGL context doesn't exist";
    return;
  }
  
  // create new fbo with appropriate size:
  context->makeCurrent(context->surface());
  QOpenGLFramebufferObjectFormat frameBufferFormat;
  frameBufferFormat.setSamples(context->format().samples());
  frameBufferFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
  mGlFrameBuffer = new QOpenGLFramebufferObject(mSize*mDevicePixelRatio, frameBufferFormat);
  if (paintDevice->size() != mSize*mDevicePixelRatio)
    paintDevice->setSize(mSize*mDevicePixelRatio);
#ifdef QCP_DEVICEPIXELRATIO_SUPPORTED
  paintDevice->setDevicePixelRatio(mDevicePixelRatio);
#endif
}
#endif // QCP_OPENGL_FBO
/* end of 'src/paintbuffer.cpp' */


/* including file 'src/layer.cpp'           */
/* modified 2022-11-06T12:45:56, size 37615 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPLayer
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPLayer
  \brief A layer that may contain objects, to control the rendering order

  The Layering system of QCustomPlot is the mechanism to control the rendering order of the
  elements inside the plot.

  It is based on the two classes QCPLayer and QCPLayerable. QCustomPlot holds an ordered list of
  one or more instances of QCPLayer (see QCustomPlot::addLayer, QCustomPlot::layer,
  QCustomPlot::moveLayer, etc.). When replotting, QCustomPlot goes through the list of layers
  bottom to top and successively draws the layerables of the layers into the paint buffer(s).

  A QCPLayer contains an ordered list of QCPLayerable instances. QCPLayerable is an abstract base
  class from which almost all visible objects derive, like axes, grids, graphs, items, etc.

  \section qcplayer-defaultlayers Default layers

  Initially, QCustomPlot has six layers: "background", "grid", "main", "axes", "legend" and
  "overlay" (in that order). On top is the "overlay" layer, which only contains the QCustomPlot's
  selection rect (\ref QCustomPlot::selectionRect). The next two layers "axes" and "legend" contain
  the default axes and legend, so they will be drawn above plottables. In the middle, there is the
  "main" layer. It is initially empty and set as the current layer (see
  QCustomPlot::setCurrentLayer). This means, all new plottables, items etc. are created on this
  layer by default. Then comes the "grid" layer which contains the QCPGrid instances (which belong
  tightly to QCPAxis, see \ref QCPAxis::grid). The Axis rect background shall be drawn behind
  everything else, thus the default QCPAxisRect instance is placed on the "background" layer. Of
  course, the layer affiliation of the individual objects can be changed as required (\ref
  QCPLayerable::setLayer).

  \section qcplayer-ordering Controlling the rendering order via layers

  Controlling the ordering of layerables in the plot is easy: Create a new layer in the position
  you want the layerable to be in, e.g. above "main", with \ref QCustomPlot::addLayer. Then set the
  current layer with \ref QCustomPlot::setCurrentLayer to that new layer and finally create the
  objects normally. They will be placed on the new layer automatically, due to the current layer
  setting. Alternatively you could have also ignored the current layer setting and just moved the
  objects with \ref QCPLayerable::setLayer to the desired layer after creating them.

  It is also possible to move whole layers. For example, If you want the grid to be shown in front
  of all plottables/items on the "main" layer, just move it above "main" with
  QCustomPlot::moveLayer.

  The rendering order within one layer is simply by order of creation or insertion. The item
  created last (or added last to the layer), is drawn on top of all other objects on that layer.

  When a layer is deleted, the objects on it are not deleted with it, but fall on the layer below
  the deleted layer, see QCustomPlot::removeLayer.

  \section qcplayer-buffering Replotting only a specific layer

  If the layer mode (\ref setMode) is set to \ref lmBuffered, you can replot only this specific
  layer by calling \ref replot. In certain situations this can provide better replot performance,
  compared with a full replot of all layers. Upon creation of a new layer, the layer mode is
  initialized to \ref lmLogical. The only layer that is set to \ref lmBuffered in a new \ref
  QCustomPlot instance is the "overlay" layer, containing the selection rect.
*/

/* start documentation of inline functions */

/*! \fn QList<QCPLayerable*> QCPLayer::children() const
  
  Returns a list of all layerables on this layer. The order corresponds to the rendering order:
  layerables with higher indices are drawn above layerables with lower indices.
*/

/*! \fn int QCPLayer::index() const
  
  Returns the index this layer has in the QCustomPlot. The index is the integer number by which this layer can be
  accessed via \ref QCustomPlot::layer.
  
  Layers with higher indices will be drawn above layers with lower indices.
*/

/* end documentation of inline functions */

/*!
  Creates a new QCPLayer instance.
  
  Normally you shouldn't directly instantiate layers, use \ref QCustomPlot::addLayer instead.
  
  \warning It is not checked that \a layerName is actually a unique layer name in \a parentPlot.
  This check is only performed by \ref QCustomPlot::addLayer.
*/
QCPLayer::QCPLayer(QCustomPlot *parentPlot, const QString &layerName) :
  QObject(parentPlot),
  mParentPlot(parentPlot),
  mName(layerName),
  mIndex(-1), // will be set to a proper value by the QCustomPlot layer creation function
  mVisible(true),
  mMode(lmLogical)
{
  // Note: no need to make sure layerName is unique, because layer
  // management is done with QCustomPlot functions.
}

QCPLayer::~QCPLayer()
{
  // If child layerables are still on this layer, detach them, so they don't try to reach back to this
  // then invalid layer once they get deleted/moved themselves. This only happens when layers are deleted
  // directly, like in the QCustomPlot destructor. (The regular layer removal procedure for the user is to
  // call QCustomPlot::removeLayer, which moves all layerables off this layer before deleting it.)
  
  while (!mChildren.isEmpty())
    mChildren.last()->setLayer(nullptr); // removes itself from mChildren via removeChild()
  
  if (mParentPlot->currentLayer() == this)
    qDebug() << Q_FUNC_INFO << "The parent plot's mCurrentLayer will be a dangling pointer. Should have been set to a valid layer or nullptr beforehand.";
}

/*!
  Sets whether this layer is visible or not. If \a visible is set to false, all layerables on this
  layer will be invisible.

  This function doesn't change the visibility property of the layerables (\ref
  QCPLayerable::setVisible), but the \ref QCPLayerable::realVisibility of each layerable takes the
  visibility of the parent layer into account.
*/
void QCPLayer::setVisible(bool visible)
{
  mVisible = visible;
}

/*!
  Sets the rendering mode of this layer.

  If \a mode is set to \ref lmBuffered for a layer, it will be given a dedicated paint buffer by
  the parent QCustomPlot instance. This means it may be replotted individually by calling \ref
  QCPLayer::replot, without needing to replot all other layers.

  Layers which are set to \ref lmLogical (the default) are used only to define the rendering order
  and can't be replotted individually.

  Note that each layer which is set to \ref lmBuffered requires additional paint buffers for the
  layers below, above and for the layer itself. This increases the memory consumption and
  (slightly) decreases the repainting speed because multiple paint buffers need to be joined. So
  you should carefully choose which layers benefit from having their own paint buffer. A typical
  example would be a layer which contains certain layerables (e.g. items) that need to be changed
  and thus replotted regularly, while all other layerables on other layers stay static. By default,
  only the topmost layer called "overlay" is in mode \ref lmBuffered, and contains the selection
  rect.

  \see replot
*/
void QCPLayer::setMode(QCPLayer::LayerMode mode)
{
  if (mMode != mode)
  {
    mMode = mode;
    if (QSharedPointer<QCPAbstractPaintBuffer> pb = mPaintBuffer.toStrongRef())
      pb->setInvalidated();
  }
}

/*! \internal

  Draws the contents of this layer with the provided \a painter.

  \see replot, drawToPaintBuffer
*/
void QCPLayer::draw(QCPPainter *painter)
{
  foreach (QCPLayerable *child, mChildren)
  {
    if (child->realVisibility())
    {
      painter->save();
      painter->setClipRect(child->clipRect().translated(0, -1));
      child->applyDefaultAntialiasingHint(painter);
      child->draw(painter);
      painter->restore();
    }
  }
}

/*! \internal

  Draws the contents of this layer into the paint buffer which is associated with this layer. The
  association is established by the parent QCustomPlot, which manages all paint buffers (see \ref
  QCustomPlot::setupPaintBuffers).

  \see draw
*/
void QCPLayer::drawToPaintBuffer()
{
  if (QSharedPointer<QCPAbstractPaintBuffer> pb = mPaintBuffer.toStrongRef())
  {
    if (QCPPainter *painter = pb->startPainting())
    {
      if (painter->isActive())
        draw(painter);
      else
        qDebug() << Q_FUNC_INFO << "paint buffer returned inactive painter";
      delete painter;
      pb->donePainting();
    } else
      qDebug() << Q_FUNC_INFO << "paint buffer returned nullptr painter";
  } else
    qDebug() << Q_FUNC_INFO << "no valid paint buffer associated with this layer";
}

/*!
  If the layer mode (\ref setMode) is set to \ref lmBuffered, this method allows replotting only
  the layerables on this specific layer, without the need to replot all other layers (as a call to
  \ref QCustomPlot::replot would do).

  QCustomPlot also makes sure to replot all layers instead of only this one, if the layer ordering
  or any layerable-layer-association has changed since the last full replot and any other paint
  buffers were thus invalidated.

  If the layer mode is \ref lmLogical however, this method simply calls \ref QCustomPlot::replot on
  the parent QCustomPlot instance.

  \see draw
*/
void QCPLayer::replot()
{
  if (mMode == lmBuffered && !mParentPlot->hasInvalidatedPaintBuffers())
  {
    if (QSharedPointer<QCPAbstractPaintBuffer> pb = mPaintBuffer.toStrongRef())
    {
      pb->clear(Qt::transparent);
      drawToPaintBuffer();
      pb->setInvalidated(false); // since layer is lmBuffered, we know only this layer is on buffer and we can reset invalidated flag
      mParentPlot->update();
    } else
      qDebug() << Q_FUNC_INFO << "no valid paint buffer associated with this layer";
  } else
    mParentPlot->replot();
}

/*! \internal
  
  Adds the \a layerable to the list of this layer. If \a prepend is set to true, the layerable will
  be prepended to the list, i.e. be drawn beneath the other layerables already in the list.
  
  This function does not change the \a mLayer member of \a layerable to this layer. (Use
  QCPLayerable::setLayer to change the layer of an object, not this function.)
  
  \see removeChild
*/
void QCPLayer::addChild(QCPLayerable *layerable, bool prepend)
{
  if (!mChildren.contains(layerable))
  {
    if (prepend)
      mChildren.prepend(layerable);
    else
      mChildren.append(layerable);
    if (QSharedPointer<QCPAbstractPaintBuffer> pb = mPaintBuffer.toStrongRef())
      pb->setInvalidated();
  } else
    qDebug() << Q_FUNC_INFO << "layerable is already child of this layer" << reinterpret_cast<quintptr>(layerable);
}

/*! \internal
  
  Removes the \a layerable from the list of this layer.
  
  This function does not change the \a mLayer member of \a layerable. (Use QCPLayerable::setLayer
  to change the layer of an object, not this function.)
  
  \see addChild
*/
void QCPLayer::removeChild(QCPLayerable *layerable)
{
  if (mChildren.removeOne(layerable))
  {
    if (QSharedPointer<QCPAbstractPaintBuffer> pb = mPaintBuffer.toStrongRef())
      pb->setInvalidated();
  } else
    qDebug() << Q_FUNC_INFO << "layerable is not child of this layer" << reinterpret_cast<quintptr>(layerable);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPLayerable
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPLayerable
  \brief Base class for all drawable objects
  
  This is the abstract base class most visible objects derive from, e.g. plottables, axes, grid
  etc.

  Every layerable is on a layer (QCPLayer) which allows controlling the rendering order by stacking
  the layers accordingly.
  
  For details about the layering mechanism, see the QCPLayer documentation.
*/

/* start documentation of inline functions */

/*! \fn QCPLayerable *QCPLayerable::parentLayerable() const
 
  Returns the parent layerable of this layerable. The parent layerable is used to provide
  visibility hierarchies in conjunction with the method \ref realVisibility. This way, layerables
  only get drawn if their parent layerables are visible, too.
  
  Note that a parent layerable is not necessarily also the QObject parent for memory management.
  Further, a layerable doesn't always have a parent layerable, so this function may return \c
  nullptr.
  
  A parent layerable is set implicitly when placed inside layout elements and doesn't need to be
  set manually by the user.
*/

/* end documentation of inline functions */
/* start documentation of pure virtual functions */

/*! \fn virtual void QCPLayerable::applyDefaultAntialiasingHint(QCPPainter *painter) const = 0
  \internal
  
  This function applies the default antialiasing setting to the specified \a painter, using the
  function \ref applyAntialiasingHint. It is the antialiasing state the painter is put in, when
  \ref draw is called on the layerable. If the layerable has multiple entities whose antialiasing
  setting may be specified individually, this function should set the antialiasing state of the
  most prominent entity. In this case however, the \ref draw function usually calls the specialized
  versions of this function before drawing each entity, effectively overriding the setting of the
  default antialiasing hint.
  
  <b>First example:</b> QCPGraph has multiple entities that have an antialiasing setting: The graph
  line, fills and scatters. Those can be configured via QCPGraph::setAntialiased,
  QCPGraph::setAntialiasedFill and QCPGraph::setAntialiasedScatters. Consequently, there isn't only
  the QCPGraph::applyDefaultAntialiasingHint function (which corresponds to the graph line's
  antialiasing), but specialized ones like QCPGraph::applyFillAntialiasingHint and
  QCPGraph::applyScattersAntialiasingHint. So before drawing one of those entities, QCPGraph::draw
  calls the respective specialized applyAntialiasingHint function.
  
  <b>Second example:</b> QCPItemLine consists only of a line so there is only one antialiasing
  setting which can be controlled with QCPItemLine::setAntialiased. (This function is inherited by
  all layerables. The specialized functions, as seen on QCPGraph, must be added explicitly to the
  respective layerable subclass.) Consequently it only has the normal
  QCPItemLine::applyDefaultAntialiasingHint. The \ref QCPItemLine::draw function doesn't need to
  care about setting any antialiasing states, because the default antialiasing hint is already set
  on the painter when the \ref draw function is called, and that's the state it wants to draw the
  line with.
*/

/*! \fn virtual void QCPLayerable::draw(QCPPainter *painter) const = 0
  \internal
  
  This function draws the layerable with the specified \a painter. It is only called by
  QCustomPlot, if the layerable is visible (\ref setVisible).
  
  Before this function is called, the painter's antialiasing state is set via \ref
  applyDefaultAntialiasingHint, see the documentation there. Further, the clipping rectangle was
  set to \ref clipRect.
*/

/* end documentation of pure virtual functions */
/* start documentation of signals */

/*! \fn void QCPLayerable::layerChanged(QCPLayer *newLayer);
  
  This signal is emitted when the layer of this layerable changes, i.e. this layerable is moved to
  a different layer.
  
  \see setLayer
*/

/* end documentation of signals */

/*!
  Creates a new QCPLayerable instance.
  
  Since QCPLayerable is an abstract base class, it can't be instantiated directly. Use one of the
  derived classes.
  
  If \a plot is provided, it automatically places itself on the layer named \a targetLayer. If \a
  targetLayer is an empty string, it places itself on the current layer of the plot (see \ref
  QCustomPlot::setCurrentLayer).
  
  It is possible to provide \c nullptr as \a plot. In that case, you should assign a parent plot at
  a later time with \ref initializeParentPlot.
  
  The layerable's parent layerable is set to \a parentLayerable, if provided. Direct layerable
  parents are mainly used to control visibility in a hierarchy of layerables. This means a
  layerable is only drawn, if all its ancestor layerables are also visible. Note that \a
  parentLayerable does not become the QObject-parent (for memory management) of this layerable, \a
  plot does. It is not uncommon to set the QObject-parent to something else in the constructors of
  QCPLayerable subclasses, to guarantee a working destruction hierarchy.
*/
QCPLayerable::QCPLayerable(QCustomPlot *plot, QString targetLayer, QCPLayerable *parentLayerable) :
  QObject(plot),
  mVisible(true),
  mParentPlot(plot),
  mParentLayerable(parentLayerable),
  mLayer(nullptr),
  mAntialiased(true)
{
  if (mParentPlot)
  {
    if (targetLayer.isEmpty())
      setLayer(mParentPlot->currentLayer());
    else if (!setLayer(targetLayer))
      qDebug() << Q_FUNC_INFO << "setting QCPlayerable initial layer to" << targetLayer << "failed.";
  }
}

QCPLayerable::~QCPLayerable()
{
  if (mLayer)
  {
    mLayer->removeChild(this);
    mLayer = nullptr;
  }
}

/*!
  Sets the visibility of this layerable object. If an object is not visible, it will not be drawn
  on the QCustomPlot surface, and user interaction with it (e.g. click and selection) is not
  possible.
*/
void QCPLayerable::setVisible(bool on)
{
  mVisible = on;
}

/*!
  Sets the \a layer of this layerable object. The object will be placed on top of the other objects
  already on \a layer.
  
  If \a layer is 0, this layerable will not be on any layer and thus not appear in the plot (or
  interact/receive events).
  
  Returns true if the layer of this layerable was successfully changed to \a layer.
*/
bool QCPLayerable::setLayer(QCPLayer *layer)
{
  return moveToLayer(layer, false);
}

/*! \overload
  Sets the layer of this layerable object by name
  
  Returns true on success, i.e. if \a layerName is a valid layer name.
*/
bool QCPLayerable::setLayer(const QString &layerName)
{
  if (!mParentPlot)
  {
    qDebug() << Q_FUNC_INFO << "no parent QCustomPlot set";
    return false;
  }
  if (QCPLayer *layer = mParentPlot->layer(layerName))
  {
    return setLayer(layer);
  } else
  {
    qDebug() << Q_FUNC_INFO << "there is no layer with name" << layerName;
    return false;
  }
}

/*!
  Sets whether this object will be drawn antialiased or not.
  
  Note that antialiasing settings may be overridden by QCustomPlot::setAntialiasedElements and
  QCustomPlot::setNotAntialiasedElements.
*/
void QCPLayerable::setAntialiased(bool enabled)
{
  mAntialiased = enabled;
}

/*!
  Returns whether this layerable is visible, taking the visibility of the layerable parent and the
  visibility of this layerable's layer into account. This is the method that is consulted to decide
  whether a layerable shall be drawn or not.
  
  If this layerable has a direct layerable parent (usually set via hierarchies implemented in
  subclasses, like in the case of \ref QCPLayoutElement), this function returns true only if this
  layerable has its visibility set to true and the parent layerable's \ref realVisibility returns
  true.
*/
bool QCPLayerable::realVisibility() const
{
  return mVisible && (!mLayer || mLayer->visible()) && (!mParentLayerable || mParentLayerable.data()->realVisibility());
}

/*!
  This function is used to decide whether a click hits a layerable object or not.

  \a pos is a point in pixel coordinates on the QCustomPlot surface. This function returns the
  shortest pixel distance of this point to the object. If the object is either invisible or the
  distance couldn't be determined, -1.0 is returned. Further, if \a onlySelectable is true and the
  object is not selectable, -1.0 is returned, too.

  If the object is represented not by single lines but by an area like a \ref QCPItemText or the
  bars of a \ref QCPBars plottable, a click inside the area should also be considered a hit. In
  these cases this function thus returns a constant value greater zero but still below the parent
  plot's selection tolerance. (typically the selectionTolerance multiplied by 0.99).
  
  Providing a constant value for area objects allows selecting line objects even when they are
  obscured by such area objects, by clicking close to the lines (i.e. closer than
  0.99*selectionTolerance).
  
  The actual setting of the selection state is not done by this function. This is handled by the
  parent QCustomPlot when the mouseReleaseEvent occurs, and the finally selected object is notified
  via the \ref selectEvent/\ref deselectEvent methods.
  
  \a details is an optional output parameter. Every layerable subclass may place any information
  in \a details. This information will be passed to \ref selectEvent when the parent QCustomPlot
  decides on the basis of this selectTest call, that the object was successfully selected. The
  subsequent call to \ref selectEvent will carry the \a details. This is useful for multi-part
  objects (like QCPAxis). This way, a possibly complex calculation to decide which part was clicked
  is only done once in \ref selectTest. The result (i.e. the actually clicked part) can then be
  placed in \a details. So in the subsequent \ref selectEvent, the decision which part was
  selected doesn't have to be done a second time for a single selection operation.
  
  In the case of 1D Plottables (\ref QCPAbstractPlottable1D, like \ref QCPGraph or \ref QCPBars) \a
  details will be set to a \ref QCPDataSelection, describing the closest data point to \a pos.
  
  You may pass \c nullptr as \a details to indicate that you are not interested in those selection
  details.
  
  \see selectEvent, deselectEvent, mousePressEvent, wheelEvent, QCustomPlot::setInteractions,
  QCPAbstractPlottable1D::selectTestRect
*/
double QCPLayerable::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const
{
  Q_UNUSED(pos)
  Q_UNUSED(onlySelectable)
  Q_UNUSED(details)
  return -1.0;
}

/*! \internal
  
  Sets the parent plot of this layerable. Use this function once to set the parent plot if you have
  passed \c nullptr in the constructor. It can not be used to move a layerable from one QCustomPlot
  to another one.
  
  Note that, unlike when passing a non \c nullptr parent plot in the constructor, this function
  does not make \a parentPlot the QObject-parent of this layerable. If you want this, call
  QObject::setParent(\a parentPlot) in addition to this function.
  
  Further, you will probably want to set a layer (\ref setLayer) after calling this function, to
  make the layerable appear on the QCustomPlot.
  
  The parent plot change will be propagated to subclasses via a call to \ref parentPlotInitialized
  so they can react accordingly (e.g. also initialize the parent plot of child layerables, like
  QCPLayout does).
*/
void QCPLayerable::initializeParentPlot(QCustomPlot *parentPlot)
{
  if (mParentPlot)
  {
    qDebug() << Q_FUNC_INFO << "called with mParentPlot already initialized";
    return;
  }
  
  if (!parentPlot)
    qDebug() << Q_FUNC_INFO << "called with parentPlot zero";
  
  mParentPlot = parentPlot;
  parentPlotInitialized(mParentPlot);
}

/*! \internal
  
  Sets the parent layerable of this layerable to \a parentLayerable. Note that \a parentLayerable does not
  become the QObject-parent (for memory management) of this layerable.
  
  The parent layerable has influence on the return value of the \ref realVisibility method. Only
  layerables with a fully visible parent tree will return true for \ref realVisibility, and thus be
  drawn.
  
  \see realVisibility
*/
void QCPLayerable::setParentLayerable(QCPLayerable *parentLayerable)
{
  mParentLayerable = parentLayerable;
}

/*! \internal
  
  Moves this layerable object to \a layer. If \a prepend is true, this object will be prepended to
  the new layer's list, i.e. it will be drawn below the objects already on the layer. If it is
  false, the object will be appended.
  
  Returns true on success, i.e. if \a layer is a valid layer.
*/
bool QCPLayerable::moveToLayer(QCPLayer *layer, bool prepend)
{
  if (layer && !mParentPlot)
  {
    qDebug() << Q_FUNC_INFO << "no parent QCustomPlot set";
    return false;
  }
  if (layer && layer->parentPlot() != mParentPlot)
  {
    qDebug() << Q_FUNC_INFO << "layer" << layer->name() << "is not in same QCustomPlot as this layerable";
    return false;
  }
  
  QCPLayer *oldLayer = mLayer;
  if (mLayer)
    mLayer->removeChild(this);
  mLayer = layer;
  if (mLayer)
    mLayer->addChild(this, prepend);
  if (mLayer != oldLayer)
    emit layerChanged(mLayer);
  return true;
}

/*! \internal

  Sets the QCPainter::setAntialiasing state on the provided \a painter, depending on the \a
  localAntialiased value as well as the overrides \ref QCustomPlot::setAntialiasedElements and \ref
  QCustomPlot::setNotAntialiasedElements. Which override enum this function takes into account is
  controlled via \a overrideElement.
*/
void QCPLayerable::applyAntialiasingHint(QCPPainter *painter, bool localAntialiased, QCP::AntialiasedElement overrideElement) const
{
  if (mParentPlot && mParentPlot->notAntialiasedElements().testFlag(overrideElement))
    painter->setAntialiasing(false);
  else if (mParentPlot && mParentPlot->antialiasedElements().testFlag(overrideElement))
    painter->setAntialiasing(true);
  else
    painter->setAntialiasing(localAntialiased);
}

/*! \internal

  This function is called by \ref initializeParentPlot, to allow subclasses to react on the setting
  of a parent plot. This is the case when \c nullptr was passed as parent plot in the constructor,
  and the parent plot is set at a later time.
  
  For example, QCPLayoutElement/QCPLayout hierarchies may be created independently of any
  QCustomPlot at first. When they are then added to a layout inside the QCustomPlot, the top level
  element of the hierarchy gets its parent plot initialized with \ref initializeParentPlot. To
  propagate the parent plot to all the children of the hierarchy, the top level element then uses
  this function to pass the parent plot on to its child elements.
  
  The default implementation does nothing.
  
  \see initializeParentPlot
*/
void QCPLayerable::parentPlotInitialized(QCustomPlot *parentPlot)
{
   Q_UNUSED(parentPlot)
}

/*! \internal

  Returns the selection category this layerable shall belong to. The selection category is used in
  conjunction with \ref QCustomPlot::setInteractions to control which objects are selectable and
  which aren't.
  
  Subclasses that don't fit any of the normal \ref QCP::Interaction values can use \ref
  QCP::iSelectOther. This is what the default implementation returns.
  
  \see QCustomPlot::setInteractions
*/
QCP::Interaction QCPLayerable::selectionCategory() const
{
  return QCP::iSelectOther;
}

/*! \internal
  
  Returns the clipping rectangle of this layerable object. By default, this is the viewport of the
  parent QCustomPlot. Specific subclasses may reimplement this function to provide different
  clipping rects.
  
  The returned clipping rect is set on the painter before the draw function of the respective
  object is called.
*/
QRect QCPLayerable::clipRect() const
{
  if (mParentPlot)
    return mParentPlot->viewport();
  else
    return {};
}

/*! \internal
  
  This event is called when the layerable shall be selected, as a consequence of a click by the
  user. Subclasses should react to it by setting their selection state appropriately. The default
  implementation does nothing.
  
  \a event is the mouse event that caused the selection. \a additive indicates, whether the user
  was holding the multi-select-modifier while performing the selection (see \ref
  QCustomPlot::setMultiSelectModifier). if \a additive is true, the selection state must be toggled
  (i.e. become selected when unselected and unselected when selected).
  
  Every selectEvent is preceded by a call to \ref selectTest, which has returned positively (i.e.
  returned a value greater than 0 and less than the selection tolerance of the parent QCustomPlot).
  The \a details data you output from \ref selectTest is fed back via \a details here. You may
  use it to transport any kind of information from the selectTest to the possibly subsequent
  selectEvent. Usually \a details is used to transfer which part was clicked, if it is a layerable
  that has multiple individually selectable parts (like QCPAxis). This way selectEvent doesn't need
  to do the calculation again to find out which part was actually clicked.
  
  \a selectionStateChanged is an output parameter. If the pointer is non-null, this function must
  set the value either to true or false, depending on whether the selection state of this layerable
  was actually changed. For layerables that only are selectable as a whole and not in parts, this
  is simple: if \a additive is true, \a selectionStateChanged must also be set to true, because the
  selection toggles. If \a additive is false, \a selectionStateChanged is only set to true, if the
  layerable was previously unselected and now is switched to the selected state.
  
  \see selectTest, deselectEvent
*/
void QCPLayerable::selectEvent(QMouseEvent *event, bool additive, const QVariant &details, bool *selectionStateChanged)
{
  Q_UNUSED(event)
  Q_UNUSED(additive)
  Q_UNUSED(details)
  Q_UNUSED(selectionStateChanged)
}

/*! \internal
  
  This event is called when the layerable shall be deselected, either as consequence of a user
  interaction or a call to \ref QCustomPlot::deselectAll. Subclasses should react to it by
  unsetting their selection appropriately.
  
  just as in \ref selectEvent, the output parameter \a selectionStateChanged (if non-null), must
  return true or false when the selection state of this layerable has changed or not changed,
  respectively.
  
  \see selectTest, selectEvent
*/
void QCPLayerable::deselectEvent(bool *selectionStateChanged)
{
  Q_UNUSED(selectionStateChanged)
}

/*!
  This event gets called when the user presses a mouse button while the cursor is over the
  layerable. Whether a cursor is over the layerable is decided by a preceding call to \ref
  selectTest.

  The current pixel position of the cursor on the QCustomPlot widget is accessible via \c
  event->pos(). The parameter \a details contains layerable-specific details about the hit, which
  were generated in the previous call to \ref selectTest. For example, One-dimensional plottables
  like \ref QCPGraph or \ref QCPBars convey the clicked data point in the \a details parameter, as
  \ref QCPDataSelection packed as QVariant. Multi-part objects convey the specific \c
  SelectablePart that was hit (e.g. \ref QCPAxis::SelectablePart in the case of axes).

  QCustomPlot uses an event propagation system that works the same as Qt's system. If your
  layerable doesn't reimplement the \ref mousePressEvent or explicitly calls \c event->ignore() in
  its reimplementation, the event will be propagated to the next layerable in the stacking order.

  Once a layerable has accepted the \ref mousePressEvent, it is considered the mouse grabber and
  will receive all following calls to \ref mouseMoveEvent or \ref mouseReleaseEvent for this mouse
  interaction (a "mouse interaction" in this context ends with the release).

  The default implementation does nothing except explicitly ignoring the event with \c
  event->ignore().

  \see mouseMoveEvent, mouseReleaseEvent, mouseDoubleClickEvent, wheelEvent
*/
void QCPLayerable::mousePressEvent(QMouseEvent *event, const QVariant &details)
{
  Q_UNUSED(details)
  event->ignore();
}

/*!
  This event gets called when the user moves the mouse while holding a mouse button, after this
  layerable has become the mouse grabber by accepting the preceding \ref mousePressEvent.

  The current pixel position of the cursor on the QCustomPlot widget is accessible via \c
  event->pos(). The parameter \a startPos indicates the position where the initial \ref
  mousePressEvent occurred, that started the mouse interaction.

  The default implementation does nothing.

  \see mousePressEvent, mouseReleaseEvent, mouseDoubleClickEvent, wheelEvent
*/
void QCPLayerable::mouseMoveEvent(QMouseEvent *event, const QPointF &startPos)
{
  Q_UNUSED(startPos)
  event->ignore();
}

/*!
  This event gets called when the user releases the mouse button, after this layerable has become
  the mouse grabber by accepting the preceding \ref mousePressEvent.

  The current pixel position of the cursor on the QCustomPlot widget is accessible via \c
  event->pos(). The parameter \a startPos indicates the position where the initial \ref
  mousePressEvent occurred, that started the mouse interaction.

  The default implementation does nothing.

  \see mousePressEvent, mouseMoveEvent, mouseDoubleClickEvent, wheelEvent
*/
void QCPLayerable::mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos)
{
  Q_UNUSED(startPos)
  event->ignore();
}

/*!
  This event gets called when the user presses the mouse button a second time in a double-click,
  while the cursor is over the layerable. Whether a cursor is over the layerable is decided by a
  preceding call to \ref selectTest.

  The \ref mouseDoubleClickEvent is called instead of the second \ref mousePressEvent. So in the
  case of a double-click, the event succession is
  <i>pressEvent &ndash; releaseEvent &ndash; doubleClickEvent &ndash; releaseEvent</i>.

  The current pixel position of the cursor on the QCustomPlot widget is accessible via \c
  event->pos(). The parameter \a details contains layerable-specific details about the hit, which
  were generated in the previous call to \ref selectTest. For example, One-dimensional plottables
  like \ref QCPGraph or \ref QCPBars convey the clicked data point in the \a details parameter, as
  \ref QCPDataSelection packed as QVariant. Multi-part objects convey the specific \c
  SelectablePart that was hit (e.g. \ref QCPAxis::SelectablePart in the case of axes).

  Similarly to \ref mousePressEvent, once a layerable has accepted the \ref mouseDoubleClickEvent,
  it is considered the mouse grabber and will receive all following calls to \ref mouseMoveEvent
  and \ref mouseReleaseEvent for this mouse interaction (a "mouse interaction" in this context ends
  with the release).

  The default implementation does nothing except explicitly ignoring the event with \c
  event->ignore().

  \see mousePressEvent, mouseMoveEvent, mouseReleaseEvent, wheelEvent
*/
void QCPLayerable::mouseDoubleClickEvent(QMouseEvent *event, const QVariant &details)
{
  Q_UNUSED(details)
  event->ignore();
}

/*!
  This event gets called when the user turns the mouse scroll wheel while the cursor is over the
  layerable. Whether a cursor is over the layerable is decided by a preceding call to \ref
  selectTest.

  The current pixel position of the cursor on the QCustomPlot widget is accessible via \c
  event->pos().

  The \c event->angleDelta() indicates how far the mouse wheel was turned, which is usually +/- 120
  for single rotation steps. However, if the mouse wheel is turned rapidly, multiple steps may
  accumulate to one event, making the delta larger. On the other hand, if the wheel has very smooth
  steps or none at all, the delta may be smaller.

  The default implementation does nothing.

  \see mousePressEvent, mouseMoveEvent, mouseReleaseEvent, mouseDoubleClickEvent
*/
void QCPLayerable::wheelEvent(QWheelEvent *event)
{
  event->ignore();
}
/* end of 'src/layer.cpp' */


/* including file 'src/axis/range.cpp'      */
/* modified 2022-11-06T12:45:56, size 12221 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPRange
////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \class QCPRange
  \brief Represents the range an axis is encompassing.
  
  contains a \a lower and \a upper double value and provides convenience input, output and
  modification functions.
  
  \see QCPAxis::setRange
*/

/* start of documentation of inline functions */

/*! \fn double QCPRange::size() const

  Returns the size of the range, i.e. \a upper-\a lower
*/

/*! \fn double QCPRange::center() const

  Returns the center of the range, i.e. (\a upper+\a lower)*0.5
*/

/*! \fn void QCPRange::normalize()

  Makes sure \a lower is numerically smaller than \a upper. If this is not the case, the values are
  swapped.
*/

/*! \fn bool QCPRange::contains(double value) const

  Returns true when \a value lies within or exactly on the borders of the range.
*/

/*! \fn QCPRange &QCPRange::operator+=(const double& value)

  Adds \a value to both boundaries of the range.
*/

/*! \fn QCPRange &QCPRange::operator-=(const double& value)

  Subtracts \a value from both boundaries of the range.
*/

/*! \fn QCPRange &QCPRange::operator*=(const double& value)

  Multiplies both boundaries of the range by \a value.
*/

/*! \fn QCPRange &QCPRange::operator/=(const double& value)

  Divides both boundaries of the range by \a value.
*/

/* end of documentation of inline functions */

/*!
  Minimum range size (\a upper - \a lower) the range changing functions will accept. Smaller
  intervals would cause errors due to the 11-bit exponent of double precision numbers,
  corresponding to a minimum magnitude of roughly 1e-308.

  \warning Do not use this constant to indicate "arbitrarily small" values in plotting logic (as
  values that will appear in the plot)! It is intended only as a bound to compare against, e.g. to
  prevent axis ranges from obtaining underflowing ranges.

  \see validRange, maxRange
*/
const double QCPRange::minRange = 1e-280;

/*!
  Maximum values (negative and positive) the range will accept in range-changing functions.
  Larger absolute values would cause errors due to the 11-bit exponent of double precision numbers,
  corresponding to a maximum magnitude of roughly 1e308.

  \warning Do not use this constant to indicate "arbitrarily large" values in plotting logic (as
  values that will appear in the plot)! It is intended only as a bound to compare against, e.g. to
  prevent axis ranges from obtaining overflowing ranges.

  \see validRange, minRange
*/
const double QCPRange::maxRange = 1e250;

/*!
  Constructs a range with \a lower and \a upper set to zero.
*/
QCPRange::QCPRange() :
  lower(0),
  upper(0)
{
}

/*! \overload

  Constructs a range with the specified \a lower and \a upper values.

  The resulting range will be normalized (see \ref normalize), so if \a lower is not numerically
  smaller than \a upper, they will be swapped.
*/
QCPRange::QCPRange(double lower, double upper) :
  lower(lower),
  upper(upper)
{
  normalize();
}

/*! \overload

  Expands this range such that \a otherRange is contained in the new range. It is assumed that both
  this range and \a otherRange are normalized (see \ref normalize).

  If this range contains NaN as lower or upper bound, it will be replaced by the respective bound
  of \a otherRange.

  If \a otherRange is already inside the current range, this function does nothing.

  \see expanded
*/
void QCPRange::expand(const QCPRange &otherRange)
{
  if (lower > otherRange.lower || qIsNaN(lower))
    lower = otherRange.lower;
  if (upper < otherRange.upper || qIsNaN(upper))
    upper = otherRange.upper;
}

/*! \overload

  Expands this range such that \a includeCoord is contained in the new range. It is assumed that
  this range is normalized (see \ref normalize).

  If this range contains NaN as lower or upper bound, the respective bound will be set to \a
  includeCoord.

  If \a includeCoord is already inside the current range, this function does nothing.

  \see expand
*/
void QCPRange::expand(double includeCoord)
{
  if (lower > includeCoord || qIsNaN(lower))
    lower = includeCoord;
  if (upper < includeCoord || qIsNaN(upper))
    upper = includeCoord;
}


/*! \overload

  Returns an expanded range that contains this and \a otherRange. It is assumed that both this
  range and \a otherRange are normalized (see \ref normalize).

  If this range contains NaN as lower or upper bound, the returned range's bound will be taken from
  \a otherRange.

  \see expand
*/
QCPRange QCPRange::expanded(const QCPRange &otherRange) const
{
  QCPRange result = *this;
  result.expand(otherRange);
  return result;
}

/*! \overload

  Returns an expanded range that includes the specified \a includeCoord. It is assumed that this
  range is normalized (see \ref normalize).

  If this range contains NaN as lower or upper bound, the returned range's bound will be set to \a
  includeCoord.

  \see expand
*/
QCPRange QCPRange::expanded(double includeCoord) const
{
  QCPRange result = *this;
  result.expand(includeCoord);
  return result;
}

/*!
  Returns this range, possibly modified to not exceed the bounds provided as \a lowerBound and \a
  upperBound. If possible, the size of the current range is preserved in the process.
  
  If the range shall only be bounded at the lower side, you can set \a upperBound to \ref
  QCPRange::maxRange. If it shall only be bounded at the upper side, set \a lowerBound to -\ref
  QCPRange::maxRange.
*/
QCPRange QCPRange::bounded(double lowerBound, double upperBound) const
{
  if (lowerBound > upperBound)
    qSwap(lowerBound, upperBound);
  
  QCPRange result(lower, upper);
  if (result.lower < lowerBound)
  {
    result.lower = lowerBound;
    result.upper = lowerBound + size();
    if (result.upper > upperBound || qFuzzyCompare(size(), upperBound-lowerBound))
      result.upper = upperBound;
  } else if (result.upper > upperBound)
  {
    result.upper = upperBound;
    result.lower = upperBound - size();
    if (result.lower < lowerBound || qFuzzyCompare(size(), upperBound-lowerBound))
      result.lower = lowerBound;
  }
  
  return result;
}

/*!
  Returns a sanitized version of the range. Sanitized means for logarithmic scales, that
  the range won't span the positive and negative sign domain, i.e. contain zero. Further
  \a lower will always be numerically smaller (or equal) to \a upper.
  
  If the original range does span positive and negative sign domains or contains zero,
  the returned range will try to approximate the original range as good as possible.
  If the positive interval of the original range is wider than the negative interval, the
  returned range will only contain the positive interval, with lower bound set to \a rangeFac or
  \a rangeFac *\a upper, whichever is closer to zero. Same procedure is used if the negative interval
  is wider than the positive interval, this time by changing the \a upper bound.
*/
QCPRange QCPRange::sanitizedForLogScale() const
{
  double rangeFac = 1e-3;
  QCPRange sanitizedRange(lower, upper);
  sanitizedRange.normalize();
  // can't have range spanning negative and positive values in log plot, so change range to fix it
  //if (qFuzzyCompare(sanitizedRange.lower+1, 1) && !qFuzzyCompare(sanitizedRange.upper+1, 1))
  if (sanitizedRange.lower == 0.0 && sanitizedRange.upper != 0.0)
  {
    // case lower is 0
    if (rangeFac < sanitizedRange.upper*rangeFac)
      sanitizedRange.lower = rangeFac;
    else
      sanitizedRange.lower = sanitizedRange.upper*rangeFac;
  } //else if (!qFuzzyCompare(lower+1, 1) && qFuzzyCompare(upper+1, 1))
  else if (sanitizedRange.lower != 0.0 && sanitizedRange.upper == 0.0)
  {
    // case upper is 0
    if (-rangeFac > sanitizedRange.lower*rangeFac)
      sanitizedRange.upper = -rangeFac;
    else
      sanitizedRange.upper = sanitizedRange.lower*rangeFac;
  } else if (sanitizedRange.lower < 0 && sanitizedRange.upper > 0)
  {
    // find out whether negative or positive interval is wider to decide which sign domain will be chosen
    if (-sanitizedRange.lower > sanitizedRange.upper)
    {
      // negative is wider, do same as in case upper is 0
      if (-rangeFac > sanitizedRange.lower*rangeFac)
        sanitizedRange.upper = -rangeFac;
      else
        sanitizedRange.upper = sanitizedRange.lower*rangeFac;
    } else
    {
      // positive is wider, do same as in case lower is 0
      if (rangeFac < sanitizedRange.upper*rangeFac)
        sanitizedRange.lower = rangeFac;
      else
        sanitizedRange.lower = sanitizedRange.upper*rangeFac;
    }
  }
  // due to normalization, case lower>0 && upper<0 should never occur, because that implies upper<lower
  return sanitizedRange;
}

/*!
  Returns a sanitized version of the range. Sanitized means for linear scales, that
  \a lower will always be numerically smaller (or equal) to \a upper.
*/
QCPRange QCPRange::sanitizedForLinScale() const
{
  QCPRange sanitizedRange(lower, upper);
  sanitizedRange.normalize();
  return sanitizedRange;
}

/*!
  Checks, whether the specified range is within valid bounds, which are defined
  as QCPRange::maxRange and QCPRange::minRange.
  A valid range means:
  \li range bounds within -maxRange and maxRange
  \li range size above minRange
  \li range size below maxRange
*/
bool QCPRange::validRange(double lower, double upper)
{
  return (lower > -maxRange &&
          upper < maxRange &&
          qAbs(lower-upper) > minRange &&
          qAbs(lower-upper) < maxRange &&
          !(lower > 0 && qIsInf(upper/lower)) &&
          !(upper < 0 && qIsInf(lower/upper)));
}

/*!
  \overload
  Checks, whether the specified range is within valid bounds, which are defined
  as QCPRange::maxRange and QCPRange::minRange.
  A valid range means:
  \li range bounds within -maxRange and maxRange
  \li range size above minRange
  \li range size below maxRange
*/
bool QCPRange::validRange(const QCPRange &range)
{
  return (range.lower > -maxRange &&
          range.upper < maxRange &&
          qAbs(range.lower-range.upper) > minRange &&
          qAbs(range.lower-range.upper) < maxRange &&
          !(range.lower > 0 && qIsInf(range.upper/range.lower)) &&
          !(range.upper < 0 && qIsInf(range.lower/range.upper)));
}
/* end of 'src/axis/range.cpp' */


/* including file 'src/selection.cpp'       */
/* modified 2022-11-06T12:45:56, size 21837 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPDataRange
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPDataRange
  \brief Describes a data range given by begin and end index
  
  QCPDataRange holds two integers describing the begin (\ref setBegin) and end (\ref setEnd) index
  of a contiguous set of data points. The \a end index corresponds to the data point just after the
  last data point of the data range, like in standard iterators.

  Data Ranges are not bound to a certain plottable, thus they can be freely exchanged, created and
  modified. If a non-contiguous data set shall be described, the class \ref QCPDataSelection is
  used, which holds and manages multiple instances of \ref QCPDataRange. In most situations, \ref
  QCPDataSelection is thus used.
  
  Both \ref QCPDataRange and \ref QCPDataSelection offer convenience methods to work with them,
  e.g. \ref bounded, \ref expanded, \ref intersects, \ref intersection, \ref adjusted, \ref
  contains. Further, addition and subtraction operators (defined in \ref QCPDataSelection) can be
  used to join/subtract data ranges and data selections (or mixtures), to retrieve a corresponding
  \ref QCPDataSelection.
  
  %QCustomPlot's \ref dataselection "data selection mechanism" is based on \ref QCPDataSelection and
  QCPDataRange.
  
  \note Do not confuse \ref QCPDataRange with \ref QCPRange. A \ref QCPRange describes an interval
  in floating point plot coordinates, e.g. the current axis range.
*/

/* start documentation of inline functions */

/*! \fn int QCPDataRange::size() const
  
  Returns the number of data points described by this data range. This is equal to the end index
  minus the begin index.
  
  \see length
*/

/*! \fn int QCPDataRange::length() const
  
  Returns the number of data points described by this data range. Equivalent to \ref size.
*/

/*! \fn void QCPDataRange::setBegin(int begin)
  
  Sets the begin of this data range. The \a begin index points to the first data point that is part
  of the data range.
  
  No checks or corrections are made to ensure the resulting range is valid (\ref isValid).
  
  \see setEnd
*/

/*! \fn void QCPDataRange::setEnd(int end)
  
  Sets the end of this data range. The \a end index points to the data point just after the last
  data point that is part of the data range.
  
  No checks or corrections are made to ensure the resulting range is valid (\ref isValid).
  
  \see setBegin
*/

/*! \fn bool QCPDataRange::isValid() const
  
  Returns whether this range is valid. A valid range has a begin index greater or equal to 0, and
  an end index greater or equal to the begin index.
  
  \note Invalid ranges should be avoided and are never the result of any of QCustomPlot's methods
  (unless they are themselves fed with invalid ranges). Do not pass invalid ranges to QCustomPlot's
  methods. The invalid range is not inherently prevented in QCPDataRange, to allow temporary
  invalid begin/end values while manipulating the range. An invalid range is not necessarily empty
  (\ref isEmpty), since its \ref length can be negative and thus non-zero.
*/

/*! \fn bool QCPDataRange::isEmpty() const
  
  Returns whether this range is empty, i.e. whether its begin index equals its end index.
  
  \see size, length
*/

/*! \fn QCPDataRange QCPDataRange::adjusted(int changeBegin, int changeEnd) const
  
  Returns a data range where \a changeBegin and \a changeEnd were added to the begin and end
  indices, respectively.
*/

/* end documentation of inline functions */

/*!
  Creates an empty QCPDataRange, with begin and end set to 0.
*/
QCPDataRange::QCPDataRange() :
  mBegin(0),
  mEnd(0)
{
}

/*!
  Creates a QCPDataRange, initialized with the specified \a begin and \a end.
  
  No checks or corrections are made to ensure the resulting range is valid (\ref isValid).
*/
QCPDataRange::QCPDataRange(int begin, int end) :
  mBegin(begin),
  mEnd(end)
{
}

/*!
  Returns a data range that matches this data range, except that parts exceeding \a other are
  excluded.
  
  This method is very similar to \ref intersection, with one distinction: If this range and the \a
  other range share no intersection, the returned data range will be empty with begin and end set
  to the respective boundary side of \a other, at which this range is residing. (\ref intersection
  would just return a range with begin and end set to 0.)
*/
QCPDataRange QCPDataRange::bounded(const QCPDataRange &other) const
{
  QCPDataRange result(intersection(other));
  if (result.isEmpty()) // no intersection, preserve respective bounding side of otherRange as both begin and end of return value
  {
    if (mEnd <= other.mBegin)
      result = QCPDataRange(other.mBegin, other.mBegin);
    else
      result = QCPDataRange(other.mEnd, other.mEnd);
  }
  return result;
}

/*!
  Returns a data range that contains both this data range as well as \a other.
*/
QCPDataRange QCPDataRange::expanded(const QCPDataRange &other) const
{
  return {qMin(mBegin, other.mBegin), qMax(mEnd, other.mEnd)};
}

/*!
  Returns the data range which is contained in both this data range and \a other.
  
  This method is very similar to \ref bounded, with one distinction: If this range and the \a other
  range share no intersection, the returned data range will be empty with begin and end set to 0.
  (\ref bounded would return a range with begin and end set to one of the boundaries of \a other,
  depending on which side this range is on.)
  
  \see QCPDataSelection::intersection
*/
QCPDataRange QCPDataRange::intersection(const QCPDataRange &other) const
{
  QCPDataRange result(qMax(mBegin, other.mBegin), qMin(mEnd, other.mEnd));
  if (result.isValid())
    return result;
  else
    return {};
}

/*!
  Returns whether this data range and \a other share common data points.
  
  \see intersection, contains
*/
bool QCPDataRange::intersects(const QCPDataRange &other) const
{
   return !( (mBegin > other.mBegin && mBegin >= other.mEnd) ||
             (mEnd <= other.mBegin && mEnd < other.mEnd) );
}

/*!
  Returns whether all data points of \a other are also contained inside this data range.
  
  \see intersects
*/
bool QCPDataRange::contains(const QCPDataRange &other) const
{
  return mBegin <= other.mBegin && mEnd >= other.mEnd;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPDataSelection
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPDataSelection
  \brief Describes a data set by holding multiple QCPDataRange instances
  
  QCPDataSelection manages multiple instances of QCPDataRange in order to represent any (possibly
  disjoint) set of data selection.
  
  The data selection can be modified with addition and subtraction operators which take
  QCPDataSelection and QCPDataRange instances, as well as methods such as \ref addDataRange and
  \ref clear. Read access is provided by \ref dataRange, \ref dataRanges, \ref dataRangeCount, etc.
  
  The method \ref simplify is used to join directly adjacent or even overlapping QCPDataRange
  instances. QCPDataSelection automatically simplifies when using the addition/subtraction
  operators. The only case when \ref simplify is left to the user, is when calling \ref
  addDataRange, with the parameter \a simplify explicitly set to false. This is useful if many data
  ranges will be added to the selection successively and the overhead for simplifying after each
  iteration shall be avoided. In this case, you should make sure to call \ref simplify after
  completing the operation.
  
  Use \ref enforceType to bring the data selection into a state complying with the constraints for
  selections defined in \ref QCP::SelectionType.
  
  %QCustomPlot's \ref dataselection "data selection mechanism" is based on QCPDataSelection and
  QCPDataRange.
  
  \section qcpdataselection-iterating Iterating over a data selection
  
  As an example, the following code snippet calculates the average value of a graph's data
  \ref QCPAbstractPlottable::selection "selection":
  
  \snippet documentation/doc-code-snippets/mainwindow.cpp qcpdataselection-iterating-1
  
*/

/* start documentation of inline functions */

/*! \fn int QCPDataSelection::dataRangeCount() const
  
  Returns the number of ranges that make up the data selection. The ranges can be accessed by \ref
  dataRange via their index.
  
  \see dataRange, dataPointCount
*/

/*! \fn QList<QCPDataRange> QCPDataSelection::dataRanges() const
  
  Returns all data ranges that make up the data selection. If the data selection is simplified (the
  usual state of the selection, see \ref simplify), the ranges are sorted by ascending data point
  index.
  
  \see dataRange
*/

/*! \fn bool QCPDataSelection::isEmpty() const
  
  Returns true if there are no data ranges, and thus no data points, in this QCPDataSelection
  instance.
  
  \see dataRangeCount
*/

/* end documentation of inline functions */

/*!
  Creates an empty QCPDataSelection.
*/
QCPDataSelection::QCPDataSelection()
{
}

/*!
  Creates a QCPDataSelection containing the provided \a range.
*/
QCPDataSelection::QCPDataSelection(const QCPDataRange &range)
{
  mDataRanges.append(range);
}

/*!
  Returns true if this selection is identical (contains the same data ranges with the same begin
  and end indices) to \a other.

  Note that both data selections must be in simplified state (the usual state of the selection, see
  \ref simplify) for this operator to return correct results.
*/
bool QCPDataSelection::operator==(const QCPDataSelection &other) const
{
  if (mDataRanges.size() != other.mDataRanges.size())
    return false;
  for (int i=0; i<mDataRanges.size(); ++i)
  {
    if (mDataRanges.at(i) != other.mDataRanges.at(i))
      return false;
  }
  return true;
}

/*!
  Adds the data selection of \a other to this data selection, and then simplifies this data
  selection (see \ref simplify).
*/
QCPDataSelection &QCPDataSelection::operator+=(const QCPDataSelection &other)
{
  mDataRanges << other.mDataRanges;
  simplify();
  return *this;
}

/*!
  Adds the data range \a other to this data selection, and then simplifies this data selection (see
  \ref simplify).
*/
QCPDataSelection &QCPDataSelection::operator+=(const QCPDataRange &other)
{
  addDataRange(other);
  return *this;
}

/*!
  Removes all data point indices that are described by \a other from this data selection.
*/
QCPDataSelection &QCPDataSelection::operator-=(const QCPDataSelection &other)
{
  for (int i=0; i<other.dataRangeCount(); ++i)
    *this -= other.dataRange(i);
  
  return *this;
}

/*!
  Removes all data point indices that are described by \a other from this data selection.
*/
QCPDataSelection &QCPDataSelection::operator-=(const QCPDataRange &other)
{
  if (other.isEmpty() || isEmpty())
    return *this;
  
  simplify();
  int i=0;
  while (i < mDataRanges.size())
  {
    const int thisBegin = mDataRanges.at(i).begin();
    const int thisEnd = mDataRanges.at(i).end();
    if (thisBegin >= other.end())
      break; // since data ranges are sorted after the simplify() call, no ranges which contain other will come after this
    
    if (thisEnd > other.begin()) // ranges which don't fulfill this are entirely before other and can be ignored
    {
      if (thisBegin >= other.begin()) // range leading segment is encompassed
      {
        if (thisEnd <= other.end()) // range fully encompassed, remove completely
        {
          mDataRanges.removeAt(i);
          continue;
        } else // only leading segment is encompassed, trim accordingly
          mDataRanges[i].setBegin(other.end());
      } else // leading segment is not encompassed
      {
        if (thisEnd <= other.end()) // only trailing segment is encompassed, trim accordingly
        {
          mDataRanges[i].setEnd(other.begin());
        } else // other lies inside this range, so split range
        {
          mDataRanges[i].setEnd(other.begin());
          mDataRanges.insert(i+1, QCPDataRange(other.end(), thisEnd));
          break; // since data ranges are sorted (and don't overlap) after simplify() call, we're done here
        }
      }
    }
    ++i;
  }
  
  return *this;
}

/*!
  Returns the total number of data points contained in all data ranges that make up this data
  selection.
*/
int QCPDataSelection::dataPointCount() const
{
  int result = 0;
  foreach (QCPDataRange dataRange, mDataRanges)
    result += dataRange.length();
  return result;
}

/*!
  Returns the data range with the specified \a index.
  
  If the data selection is simplified (the usual state of the selection, see \ref simplify), the
  ranges are sorted by ascending data point index.
  
  \see dataRangeCount
*/
QCPDataRange QCPDataSelection::dataRange(int index) const
{
  if (index >= 0 && index < mDataRanges.size())
  {
    return mDataRanges.at(index);
  } else
  {
    qDebug() << Q_FUNC_INFO << "index out of range:" << index;
    return {};
  }
}

/*!
  Returns a \ref QCPDataRange which spans the entire data selection, including possible
  intermediate segments which are not part of the original data selection.
*/
QCPDataRange QCPDataSelection::span() const
{
  if (isEmpty())
    return {};
  else
    return {mDataRanges.first().begin(), mDataRanges.last().end()};
}

/*!
  Adds the given \a dataRange to this data selection. This is equivalent to the += operator but
  allows disabling immediate simplification by setting \a simplify to false. This can improve
  performance if adding a very large amount of data ranges successively. In this case, make sure to
  call \ref simplify manually, after the operation.
*/
void QCPDataSelection::addDataRange(const QCPDataRange &dataRange, bool simplify)
{
  mDataRanges.append(dataRange);
  if (simplify)
    this->simplify();
}

/*!
  Removes all data ranges. The data selection then contains no data points.
  
  \ref isEmpty
*/
void QCPDataSelection::clear()
{
  mDataRanges.clear();
}

/*!
  Sorts all data ranges by range begin index in ascending order, and then joins directly adjacent
  or overlapping ranges. This can reduce the number of individual data ranges in the selection, and
  prevents possible double-counting when iterating over the data points held by the data ranges.

  This method is automatically called when using the addition/subtraction operators. The only case
  when \ref simplify is left to the user, is when calling \ref addDataRange, with the parameter \a
  simplify explicitly set to false.
*/
void QCPDataSelection::simplify()
{
  // remove any empty ranges:
  for (int i=mDataRanges.size()-1; i>=0; --i)
  {
    if (mDataRanges.at(i).isEmpty())
      mDataRanges.removeAt(i);
  }
  if (mDataRanges.isEmpty())
    return;
  
  // sort ranges by starting value, ascending:
  std::sort(mDataRanges.begin(), mDataRanges.end(), lessThanDataRangeBegin);
  
  // join overlapping/contiguous ranges:
  int i = 1;
  while (i < mDataRanges.size())
  {
    if (mDataRanges.at(i-1).end() >= mDataRanges.at(i).begin()) // range i overlaps/joins with i-1, so expand range i-1 appropriately and remove range i from list
    {
      mDataRanges[i-1].setEnd(qMax(mDataRanges.at(i-1).end(), mDataRanges.at(i).end()));
      mDataRanges.removeAt(i);
    } else
      ++i;
  }
}

/*!
  Makes sure this data selection conforms to the specified \a type selection type. Before the type
  is enforced, \ref simplify is called.
  
  Depending on \a type, enforcing means adding new data points that were previously not part of the
  selection, or removing data points from the selection. If the current selection already conforms
  to \a type, the data selection is not changed.
  
  \see QCP::SelectionType
*/
void QCPDataSelection::enforceType(QCP::SelectionType type)
{
  simplify();
  switch (type)
  {
    case QCP::stNone:
    {
      mDataRanges.clear();
      break;
    }
    case QCP::stWhole:
    {
      // whole selection isn't defined by data range, so don't change anything (is handled in plottable methods)
      break;
    }
    case QCP::stSingleData:
    {
      // reduce all data ranges to the single first data point:
      if (!mDataRanges.isEmpty())
      {
        if (mDataRanges.size() > 1)
          mDataRanges = QList<QCPDataRange>() << mDataRanges.first();
        if (mDataRanges.first().length() > 1)
          mDataRanges.first().setEnd(mDataRanges.first().begin()+1);
      }
      break;
    }
    case QCP::stDataRange:
    {
      if (!isEmpty())
        mDataRanges = QList<QCPDataRange>() << span();
      break;
    }
    case QCP::stMultipleDataRanges:
    {
      // this is the selection type that allows all concievable combinations of ranges, so do nothing
      break;
    }
  }
}

/*!
  Returns true if the data selection \a other is contained entirely in this data selection, i.e.
  all data point indices that are in \a other are also in this data selection.
  
  \see QCPDataRange::contains
*/
bool QCPDataSelection::contains(const QCPDataSelection &other) const
{
  if (other.isEmpty()) return false;
  
  int otherIndex = 0;
  int thisIndex = 0;
  while (thisIndex < mDataRanges.size() && otherIndex < other.mDataRanges.size())
  {
    if (mDataRanges.at(thisIndex).contains(other.mDataRanges.at(otherIndex)))
      ++otherIndex;
    else
      ++thisIndex;
  }
  return thisIndex < mDataRanges.size(); // if thisIndex ran all the way to the end to find a containing range for the current otherIndex, other is not contained in this
}

/*!
  Returns a data selection containing the points which are both in this data selection and in the
  data range \a other.

  A common use case is to limit an unknown data selection to the valid range of a data container,
  using \ref QCPDataContainer::dataRange as \a other. One can then safely iterate over the returned
  data selection without exceeding the data container's bounds.
*/
QCPDataSelection QCPDataSelection::intersection(const QCPDataRange &other) const
{
  QCPDataSelection result;
  foreach (QCPDataRange dataRange, mDataRanges)
    result.addDataRange(dataRange.intersection(other), false);
  result.simplify();
  return result;
}

/*!
  Returns a data selection containing the points which are both in this data selection and in the
  data selection \a other.
*/
QCPDataSelection QCPDataSelection::intersection(const QCPDataSelection &other) const
{
  QCPDataSelection result;
  for (int i=0; i<other.dataRangeCount(); ++i)
    result += intersection(other.dataRange(i));
  result.simplify();
  return result;
}

/*!
  Returns a data selection which is the exact inverse of this data selection, with \a outerRange
  defining the base range on which to invert. If \a outerRange is smaller than the \ref span of
  this data selection, it is expanded accordingly.

  For example, this method can be used to retrieve all unselected segments by setting \a outerRange
  to the full data range of the plottable, and calling this method on a data selection holding the
  selected segments.
*/
QCPDataSelection QCPDataSelection::inverse(const QCPDataRange &outerRange) const
{
  if (isEmpty())
    return QCPDataSelection(outerRange);
  QCPDataRange fullRange = outerRange.expanded(span());
  
  QCPDataSelection result;
  // first unselected segment:
  if (mDataRanges.first().begin() != fullRange.begin())
    result.addDataRange(QCPDataRange(fullRange.begin(), mDataRanges.first().begin()), false);
  // intermediate unselected segments:
  for (int i=1; i<mDataRanges.size(); ++i)
    result.addDataRange(QCPDataRange(mDataRanges.at(i-1).end(), mDataRanges.at(i).begin()), false);
  // last unselected segment:
  if (mDataRanges.last().end() != fullRange.end())
    result.addDataRange(QCPDataRange(mDataRanges.last().end(), fullRange.end()), false);
  result.simplify();
  return result;
}
/* end of 'src/selection.cpp' */


/* including file 'src/selectionrect.cpp'  */
/* modified 2022-11-06T12:45:56, size 9215 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPSelectionRect
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPSelectionRect
  \brief Provides rect/rubber-band data selection and range zoom interaction
  
  QCPSelectionRect is used by QCustomPlot when the \ref QCustomPlot::setSelectionRectMode is not
  \ref QCP::srmNone. When the user drags the mouse across the plot, the current selection rect
  instance (\ref QCustomPlot::setSelectionRect) is forwarded these events and makes sure an
  according rect shape is drawn. At the begin, during, and after completion of the interaction, it
  emits the corresponding signals \ref started, \ref changed, \ref canceled, and \ref accepted.
  
  The QCustomPlot instance connects own slots to the current selection rect instance, in order to
  react to an accepted selection rect interaction accordingly.
  
  \ref isActive can be used to check whether the selection rect is currently active. An ongoing
  selection interaction can be cancelled programmatically via calling \ref cancel at any time.
  
  The appearance of the selection rect can be controlled via \ref setPen and \ref setBrush.

  If you wish to provide custom behaviour, e.g. a different visual representation of the selection
  rect (\ref QCPSelectionRect::draw), you can subclass QCPSelectionRect and pass an instance of
  your subclass to \ref QCustomPlot::setSelectionRect.
*/

/* start of documentation of inline functions */

/*! \fn bool QCPSelectionRect::isActive() const
   
  Returns true if there is currently a selection going on, i.e. the user has started dragging a
  selection rect, but hasn't released the mouse button yet.
    
  \see cancel
*/

/* end of documentation of inline functions */
/* start documentation of signals */

/*! \fn void QCPSelectionRect::started(QMouseEvent *event);
   
  This signal is emitted when a selection rect interaction was initiated, i.e. the user just
  started dragging the selection rect with the mouse.
*/

/*! \fn void QCPSelectionRect::changed(const QRect &rect, QMouseEvent *event);
  
  This signal is emitted while the selection rect interaction is ongoing and the \a rect has
  changed its size due to the user moving the mouse.
  
  Note that \a rect may have a negative width or height, if the selection is being dragged to the
  upper or left side of the selection rect origin.
*/

/*! \fn void QCPSelectionRect::canceled(const QRect &rect, QInputEvent *event);
  
  This signal is emitted when the selection interaction was cancelled. Note that \a event is \c
  nullptr if the selection interaction was cancelled programmatically, by a call to \ref cancel.
  
  The user may cancel the selection interaction by pressing the escape key. In this case, \a event
  holds the respective input event.
  
  Note that \a rect may have a negative width or height, if the selection is being dragged to the
  upper or left side of the selection rect origin.
*/

/*! \fn void QCPSelectionRect::accepted(const QRect &rect, QMouseEvent *event);
  
  This signal is emitted when the selection interaction was completed by the user releasing the
  mouse button.
    
  Note that \a rect may have a negative width or height, if the selection is being dragged to the
  upper or left side of the selection rect origin.
*/

/* end documentation of signals */

/*!
  Creates a new QCPSelectionRect instance. To make QCustomPlot use the selection rect instance,
  pass it to \ref QCustomPlot::setSelectionRect. \a parentPlot should be set to the same
  QCustomPlot widget.
*/
QCPSelectionRect::QCPSelectionRect(QCustomPlot *parentPlot) :
  QCPLayerable(parentPlot),
  mPen(QBrush(Qt::gray), 0, Qt::DashLine),
  mBrush(Qt::NoBrush),
  mActive(false)
{
}

QCPSelectionRect::~QCPSelectionRect()
{
  cancel();
}

/*!
  A convenience function which returns the coordinate range of the provided \a axis, that this
  selection rect currently encompasses.
*/
QCPRange QCPSelectionRect::range(const QCPAxis *axis) const
{
  if (axis)
  {
    if (axis->orientation() == Qt::Horizontal)
      return {axis->pixelToCoord(mRect.left()), axis->pixelToCoord(mRect.left()+mRect.width())};
    else
      return {axis->pixelToCoord(mRect.top()+mRect.height()), axis->pixelToCoord(mRect.top())};
  } else
  {
    qDebug() << Q_FUNC_INFO << "called with axis zero";
    return {};
  }
}

/*!
  Sets the pen that will be used to draw the selection rect outline.
  
  \see setBrush
*/
void QCPSelectionRect::setPen(const QPen &pen)
{
  mPen = pen;
}

/*!
  Sets the brush that will be used to fill the selection rect. By default the selection rect is not
  filled, i.e. \a brush is <tt>Qt::NoBrush</tt>.
  
  \see setPen
*/
void QCPSelectionRect::setBrush(const QBrush &brush)
{
  mBrush = brush;
}

/*!
  If there is currently a selection interaction going on (\ref isActive), the interaction is
  canceled. The selection rect will emit the \ref canceled signal.
*/
void QCPSelectionRect::cancel()
{
  if (mActive)
  {
    mActive = false;
    emit canceled(mRect, nullptr);
  }
}

/*! \internal
  
  This method is called by QCustomPlot to indicate that a selection rect interaction was initiated.
  The default implementation sets the selection rect to active, initializes the selection rect
  geometry and emits the \ref started signal.
*/
void QCPSelectionRect::startSelection(QMouseEvent *event)
{
  mActive = true;
  mRect = QRect(event->pos(), event->pos());
  emit started(event);
}

/*! \internal
  
  This method is called by QCustomPlot to indicate that an ongoing selection rect interaction needs
  to update its geometry. The default implementation updates the rect and emits the \ref changed
  signal.
*/
void QCPSelectionRect::moveSelection(QMouseEvent *event)
{
  mRect.setBottomRight(event->pos());
  emit changed(mRect, event);
  layer()->replot();
}

/*! \internal
  
  This method is called by QCustomPlot to indicate that an ongoing selection rect interaction has
  finished by the user releasing the mouse button. The default implementation deactivates the
  selection rect and emits the \ref accepted signal.
*/
void QCPSelectionRect::endSelection(QMouseEvent *event)
{
  mRect.setBottomRight(event->pos());
  mActive = false;
  emit accepted(mRect, event);
}

/*! \internal
  
  This method is called by QCustomPlot when a key has been pressed by the user while the selection
  rect interaction is active. The default implementation allows to \ref cancel the interaction by
  hitting the escape key.
*/
void QCPSelectionRect::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape && mActive)
  {
    mActive = false;
    emit canceled(mRect, event);
  }
}

/* inherits documentation from base class */
void QCPSelectionRect::applyDefaultAntialiasingHint(QCPPainter *painter) const
{
  applyAntialiasingHint(painter, mAntialiased, QCP::aeOther);
}

/*! \internal
  
  If the selection rect is active (\ref isActive), draws the selection rect defined by \a mRect.
  
  \seebaseclassmethod
*/
void QCPSelectionRect::draw(QCPPainter *painter)
{
  if (mActive)
  {
    painter->setPen(mPen);
    painter->setBrush(mBrush);
    painter->drawRect(mRect);
  }
}
/* end of 'src/selectionrect.cpp' */


/* including file 'src/layout.cpp'          */
/* modified 2022-11-06T12:45:56, size 78863 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPMarginGroup
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPMarginGroup
  \brief A margin group allows synchronization of margin sides if working with multiple layout elements.
  
  QCPMarginGroup allows you to tie a margin side of two or more layout elements together, such that
  they will all have the same size, based on the largest required margin in the group.
  
  \n
  \image html QCPMarginGroup.png "Demonstration of QCPMarginGroup"
  \n
  
  In certain situations it is desirable that margins at specific sides are synchronized across
  layout elements. For example, if one QCPAxisRect is below another one in a grid layout, it will
  provide a cleaner look to the user if the left and right margins of the two axis rects are of the
  same size. The left axis of the top axis rect will then be at the same horizontal position as the
  left axis of the lower axis rect, making them appear aligned. The same applies for the right
  axes. This is what QCPMarginGroup makes possible.
  
  To add/remove a specific side of a layout element to/from a margin group, use the \ref
  QCPLayoutElement::setMarginGroup method. To completely break apart the margin group, either call
  \ref clear, or just delete the margin group.
  
  \section QCPMarginGroup-example Example
  
  First create a margin group:
  \snippet documentation/doc-code-snippets/mainwindow.cpp qcpmargingroup-creation-1
  Then set this group on the layout element sides:
  \snippet documentation/doc-code-snippets/mainwindow.cpp qcpmargingroup-creation-2
  Here, we've used the first two axis rects of the plot and synchronized their left margins with
  each other and their right margins with each other.
*/

/* start documentation of inline functions */

/*! \fn QList<QCPLayoutElement*> QCPMarginGroup::elements(QCP::MarginSide side) const
  
  Returns a list of all layout elements that have their margin \a side associated with this margin
  group.
*/

/* end documentation of inline functions */

/*!
  Creates a new QCPMarginGroup instance in \a parentPlot.
*/
QCPMarginGroup::QCPMarginGroup(QCustomPlot *parentPlot) :
  QObject(parentPlot),
  mParentPlot(parentPlot)
{
  mChildren.insert(QCP::msLeft, QList<QCPLayoutElement*>());
  mChildren.insert(QCP::msRight, QList<QCPLayoutElement*>());
  mChildren.insert(QCP::msTop, QList<QCPLayoutElement*>());
  mChildren.insert(QCP::msBottom, QList<QCPLayoutElement*>());
}

QCPMarginGroup::~QCPMarginGroup()
{
  clear();
}

/*!
  Returns whether this margin group is empty. If this function returns true, no layout elements use
  this margin group to synchronize margin sides.
*/
bool QCPMarginGroup::isEmpty() const
{
  QHashIterator<QCP::MarginSide, QList<QCPLayoutElement*> > it(mChildren);
  while (it.hasNext())
  {
    it.next();
    if (!it.value().isEmpty())
      return false;
  }
  return true;
}

/*!
  Clears this margin group. The synchronization of the margin sides that use this margin group is
  lifted and they will use their individual margin sizes again.
*/
void QCPMarginGroup::clear()
{
  // make all children remove themselves from this margin group:
  QHashIterator<QCP::MarginSide, QList<QCPLayoutElement*> > it(mChildren);
  while (it.hasNext())
  {
    it.next();
    const QList<QCPLayoutElement*> elements = it.value();
    for (int i=elements.size()-1; i>=0; --i)
      elements.at(i)->setMarginGroup(it.key(), nullptr); // removes itself from mChildren via removeChild
  }
}

/*! \internal
  
  Returns the synchronized common margin for \a side. This is the margin value that will be used by
  the layout element on the respective side, if it is part of this margin group.
  
  The common margin is calculated by requesting the automatic margin (\ref
  QCPLayoutElement::calculateAutoMargin) of each element associated with \a side in this margin
  group, and choosing the largest returned value. (QCPLayoutElement::minimumMargins is taken into
  account, too.)
*/
int QCPMarginGroup::commonMargin(QCP::MarginSide side) const
{
  // query all automatic margins of the layout elements in this margin group side and find maximum:
  int result = 0;
  foreach (QCPLayoutElement *el, mChildren.value(side))
  {
    if (!el->autoMargins().testFlag(side))
      continue;
    int m = qMax(el->calculateAutoMargin(side), QCP::getMarginValue(el->minimumMargins(), side));
    if (m > result)
      result = m;
  }
  return result;
}

/*! \internal
  
  Adds \a element to the internal list of child elements, for the margin \a side.
  
  This function does not modify the margin group property of \a element.
*/
void QCPMarginGroup::addChild(QCP::MarginSide side, QCPLayoutElement *element)
{
  if (!mChildren[side].contains(element))
    mChildren[side].append(element);
  else
    qDebug() << Q_FUNC_INFO << "element is already child of this margin group side" << reinterpret_cast<quintptr>(element);
}

/*! \internal
  
  Removes \a element from the internal list of child elements, for the margin \a side.
  
  This function does not modify the margin group property of \a element.
*/
void QCPMarginGroup::removeChild(QCP::MarginSide side, QCPLayoutElement *element)
{
  if (!mChildren[side].removeOne(element))
    qDebug() << Q_FUNC_INFO << "element is not child of this margin group side" << reinterpret_cast<quintptr>(element);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPLayoutElement
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPLayoutElement
  \brief The abstract base class for all objects that form \ref thelayoutsystem "the layout system".
  
  This is an abstract base class. As such, it can't be instantiated directly, rather use one of its subclasses.
  
  A Layout element is a rectangular object which can be placed in layouts. It has an outer rect
  (QCPLayoutElement::outerRect) and an inner rect (\ref QCPLayoutElement::rect). The difference
  between outer and inner rect is called its margin. The margin can either be set to automatic or
  manual (\ref setAutoMargins) on a per-side basis. If a side is set to manual, that margin can be
  set explicitly with \ref setMargins and will stay fixed at that value. If it's set to automatic,
  the layout element subclass will control the value itself (via \ref calculateAutoMargin).
  
  Layout elements can be placed in layouts (base class QCPLayout) like QCPLayoutGrid. The top level
  layout is reachable via \ref QCustomPlot::plotLayout, and is a \ref QCPLayoutGrid. Since \ref
  QCPLayout itself derives from \ref QCPLayoutElement, layouts can be nested.
  
  Thus in QCustomPlot one can divide layout elements into two categories: The ones that are
  invisible by themselves, because they don't draw anything. Their only purpose is to manage the
  position and size of other layout elements. This category of layout elements usually use
  QCPLayout as base class. Then there is the category of layout elements which actually draw
  something. For example, QCPAxisRect, QCPLegend and QCPTextElement are of this category. This does
  not necessarily mean that the latter category can't have child layout elements. QCPLegend for
  instance, actually derives from QCPLayoutGrid and the individual legend items are child layout
  elements in the grid layout.
*/

/* start documentation of inline functions */

/*! \fn QCPLayout *QCPLayoutElement::layout() const
  
  Returns the parent layout of this layout element.
*/

/*! \fn QRect QCPLayoutElement::rect() const
  
  Returns the inner rect of this layout element. The inner rect is the outer rect (\ref outerRect, \ref
  setOuterRect) shrinked by the margins (\ref setMargins, \ref setAutoMargins).
  
  In some cases, the area between outer and inner rect is left blank. In other cases the margin
  area is used to display peripheral graphics while the main content is in the inner rect. This is
  where automatic margin calculation becomes interesting because it allows the layout element to
  adapt the margins to the peripheral graphics it wants to draw. For example, \ref QCPAxisRect
  draws the axis labels and tick labels in the margin area, thus needs to adjust the margins (if
  \ref setAutoMargins is enabled) according to the space required by the labels of the axes.
  
  \see outerRect
*/

/*! \fn QRect QCPLayoutElement::outerRect() const
  
  Returns the outer rect of this layout element. The outer rect is the inner rect expanded by the
  margins (\ref setMargins, \ref setAutoMargins). The outer rect is used (and set via \ref
  setOuterRect) by the parent \ref QCPLayout to control the size of this layout element.
  
  \see rect
*/

/* end documentation of inline functions */

/*!
  Creates an instance of QCPLayoutElement and sets default values.
*/
QCPLayoutElement::QCPLayoutElement(QCustomPlot *parentPlot) :
  QCPLayerable(parentPlot), // parenthood is changed as soon as layout element gets inserted into a layout (except for top level layout)
  mParentLayout(nullptr),
  mMinimumSize(),
  mMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX),
  mSizeConstraintRect(scrInnerRect),
  mRect(0, 0, 0, 0),
  mOuterRect(0, 0, 0, 0),
  mMargins(0, 0, 0, 0),
  mMinimumMargins(0, 0, 0, 0),
  mAutoMargins(QCP::msAll)
{
}

QCPLayoutElement::~QCPLayoutElement()
{
  setMarginGroup(QCP::msAll, nullptr); // unregister at margin groups, if there are any
  // unregister at layout:
  if (qobject_cast<QCPLayout*>(mParentLayout)) // the qobject_cast is just a safeguard in case the layout forgets to call clear() in its dtor and this dtor is called by QObject dtor
    mParentLayout->take(this);
}

/*!
  Sets the outer rect of this layout element. If the layout element is inside a layout, the layout
  sets the position and size of this layout element using this function.
  
  Calling this function externally has no effect, since the layout will overwrite any changes to
  the outer rect upon the next replot.
  
  The layout element will adapt its inner \ref rect by applying the margins inward to the outer rect.
  
  \see rect
*/
void QCPLayoutElement::setOuterRect(const QRect &rect)
{
  if (mOuterRect != rect)
  {
    mOuterRect = rect;
    mRect = mOuterRect.adjusted(mMargins.left(), mMargins.top(), -mMargins.right(), -mMargins.bottom());
  }
}

/*!
  Sets the margins of this layout element. If \ref setAutoMargins is disabled for some or all
  sides, this function is used to manually set the margin on those sides. Sides that are still set
  to be handled automatically are ignored and may have any value in \a margins.
  
  The margin is the distance between the outer rect (controlled by the parent layout via \ref
  setOuterRect) and the inner \ref rect (which usually contains the main content of this layout
  element).
  
  \see setAutoMargins
*/
void QCPLayoutElement::setMargins(const QMargins &margins)
{
  if (mMargins != margins)
  {
    mMargins = margins;
    mRect = mOuterRect.adjusted(mMargins.left(), mMargins.top(), -mMargins.right(), -mMargins.bottom());
  }
}

/*!
  If \ref setAutoMargins is enabled on some or all margins, this function is used to provide
  minimum values for those margins.
  
  The minimum values are not enforced on margin sides that were set to be under manual control via
  \ref setAutoMargins.
  
  \see setAutoMargins
*/
void QCPLayoutElement::setMinimumMargins(const QMargins &margins)
{
  if (mMinimumMargins != margins)
  {
    mMinimumMargins = margins;
  }
}

/*!
  Sets on which sides the margin shall be calculated automatically. If a side is calculated
  automatically, a minimum margin value may be provided with \ref setMinimumMargins. If a side is
  set to be controlled manually, the value may be specified with \ref setMargins.
  
  Margin sides that are under automatic control may participate in a \ref QCPMarginGroup (see \ref
  setMarginGroup), to synchronize (align) it with other layout elements in the plot.
  
  \see setMinimumMargins, setMargins, QCP::MarginSide
*/
void QCPLayoutElement::setAutoMargins(QCP::MarginSides sides)
{
  mAutoMargins = sides;
}

/*!
  Sets the minimum size of this layout element. A parent layout tries to respect the \a size here
  by changing row/column sizes in the layout accordingly.
  
  If the parent layout size is not sufficient to satisfy all minimum size constraints of its child
  layout elements, the layout may set a size that is actually smaller than \a size. QCustomPlot
  propagates the layout's size constraints to the outside by setting its own minimum QWidget size
  accordingly, so violations of \a size should be exceptions.
  
  Whether this constraint applies to the inner or the outer rect can be specified with \ref
  setSizeConstraintRect (see \ref rect and \ref outerRect).
*/
void QCPLayoutElement::setMinimumSize(const QSize &size)
{
  if (mMinimumSize != size)
  {
    mMinimumSize = size;
    if (mParentLayout)
      mParentLayout->sizeConstraintsChanged();
  }
}

/*! \overload
  
  Sets the minimum size of this layout element.
  
  Whether this constraint applies to the inner or the outer rect can be specified with \ref
  setSizeConstraintRect (see \ref rect and \ref outerRect).
*/
void QCPLayoutElement::setMinimumSize(int width, int height)
{
  setMinimumSize(QSize(width, height));
}

/*!
  Sets the maximum size of this layout element. A parent layout tries to respect the \a size here
  by changing row/column sizes in the layout accordingly.
  
  Whether this constraint applies to the inner or the outer rect can be specified with \ref
  setSizeConstraintRect (see \ref rect and \ref outerRect).
*/
void QCPLayoutElement::setMaximumSize(const QSize &size)
{
  if (mMaximumSize != size)
  {
    mMaximumSize = size;
    if (mParentLayout)
      mParentLayout->sizeConstraintsChanged();
  }
}

/*! \overload
  
  Sets the maximum size of this layout element.
  
  Whether this constraint applies to the inner or the outer rect can be specified with \ref
  setSizeConstraintRect (see \ref rect and \ref outerRect).
*/
void QCPLayoutElement::setMaximumSize(int width, int height)
{
  setMaximumSize(QSize(width, height));
}

/*!
  Sets to which rect of a layout element the size constraints apply. Size constraints can be set
  via \ref setMinimumSize and \ref setMaximumSize.
  
  The outer rect (\ref outerRect) includes the margins (e.g. in the case of a QCPAxisRect the axis
  labels), whereas the inner rect (\ref rect) does not.
  
  \see setMinimumSize, setMaximumSize
*/
void QCPLayoutElement::setSizeConstraintRect(SizeConstraintRect constraintRect)
{
  if (mSizeConstraintRect != constraintRect)
  {
    mSizeConstraintRect = constraintRect;
    if (mParentLayout)
      mParentLayout->sizeConstraintsChanged();
  }
}

/*!
  Sets the margin \a group of the specified margin \a sides.
  
  Margin groups allow synchronizing specified margins across layout elements, see the documentation
  of \ref QCPMarginGroup.
  
  To unset the margin group of \a sides, set \a group to \c nullptr.
  
  Note that margin groups only work for margin sides that are set to automatic (\ref
  setAutoMargins).
  
  \see QCP::MarginSide
*/
void QCPLayoutElement::setMarginGroup(QCP::MarginSides sides, QCPMarginGroup *group)
{
  QVector<QCP::MarginSide> sideVector;
  if (sides.testFlag(QCP::msLeft)) sideVector.append(QCP::msLeft);
  if (sides.testFlag(QCP::msRight)) sideVector.append(QCP::msRight);
  if (sides.testFlag(QCP::msTop)) sideVector.append(QCP::msTop);
  if (sides.testFlag(QCP::msBottom)) sideVector.append(QCP::msBottom);
  
  foreach (QCP::MarginSide side, sideVector)
  {
    if (marginGroup(side) != group)
    {
      QCPMarginGroup *oldGroup = marginGroup(side);
      if (oldGroup) // unregister at old group
        oldGroup->removeChild(side, this);
      
      if (!group) // if setting to 0, remove hash entry. Else set hash entry to new group and register there
      {
        mMarginGroups.remove(side);
      } else // setting to a new group
      {
        mMarginGroups[side] = group;
        group->addChild(side, this);
      }
    }
  }
}

/*!
  Updates the layout element and sub-elements. This function is automatically called before every
  replot by the parent layout element. It is called multiple times, once for every \ref
  UpdatePhase. The phases are run through in the order of the enum values. For details about what
  happens at the different phases, see the documentation of \ref UpdatePhase.
  
  Layout elements that have child elements should call the \ref update method of their child
  elements, and pass the current \a phase unchanged.
  
  The default implementation executes the automatic margin mechanism in the \ref upMargins phase.
  Subclasses should make sure to call the base class implementation.
*/
void QCPLayoutElement::update(UpdatePhase phase)
{
  if (phase == upMargins)
  {
    if (mAutoMargins != QCP::msNone)
    {
      // set the margins of this layout element according to automatic margin calculation, either directly or via a margin group:
      QMargins newMargins = mMargins;
      const QList<QCP::MarginSide> allMarginSides = QList<QCP::MarginSide>() << QCP::msLeft << QCP::msRight << QCP::msTop << QCP::msBottom;
      foreach (QCP::MarginSide side, allMarginSides)
      {
        if (mAutoMargins.testFlag(side)) // this side's margin shall be calculated automatically
        {
          if (mMarginGroups.contains(side))
            QCP::setMarginValue(newMargins, side, mMarginGroups[side]->commonMargin(side)); // this side is part of a margin group, so get the margin value from that group
          else
            QCP::setMarginValue(newMargins, side, calculateAutoMargin(side)); // this side is not part of a group, so calculate the value directly
          // apply minimum margin restrictions:
          if (QCP::getMarginValue(newMargins, side) < QCP::getMarginValue(mMinimumMargins, side))
            QCP::setMarginValue(newMargins, side, QCP::getMarginValue(mMinimumMargins, side));
        }
      }
      setMargins(newMargins);
    }
  }
}

/*!
  Returns the suggested minimum size this layout element (the \ref outerRect) may be compressed to,
  if no manual minimum size is set.
  
  if a minimum size (\ref setMinimumSize) was not set manually, parent layouts use the returned size
  (usually indirectly through \ref QCPLayout::getFinalMinimumOuterSize) to determine the minimum
  allowed size of this layout element.

  A manual minimum size is considered set if it is non-zero.
  
  The default implementation simply returns the sum of the horizontal margins for the width and the
  sum of the vertical margins for the height. Reimplementations may use their detailed knowledge
  about the layout element's content to provide size hints.
*/
QSize QCPLayoutElement::minimumOuterSizeHint() const
{
  return {mMargins.left()+mMargins.right(), mMargins.top()+mMargins.bottom()};
}

/*!
  Returns the suggested maximum size this layout element (the \ref outerRect) may be expanded to,
  if no manual maximum size is set.
  
  if a maximum size (\ref setMaximumSize) was not set manually, parent layouts use the returned
  size (usually indirectly through \ref QCPLayout::getFinalMaximumOuterSize) to determine the
  maximum allowed size of this layout element.

  A manual maximum size is considered set if it is smaller than Qt's \c QWIDGETSIZE_MAX.
  
  The default implementation simply returns \c QWIDGETSIZE_MAX for both width and height, implying
  no suggested maximum size. Reimplementations may use their detailed knowledge about the layout
  element's content to provide size hints.
*/
QSize QCPLayoutElement::maximumOuterSizeHint() const
{
  return {QWIDGETSIZE_MAX, QWIDGETSIZE_MAX};
}

/*!
  Returns a list of all child elements in this layout element. If \a recursive is true, all
  sub-child elements are included in the list, too.
  
  \warning There may be \c nullptr entries in the returned list. For example, QCPLayoutGrid may
  have empty cells which yield \c nullptr at the respective index.
*/
QList<QCPLayoutElement*> QCPLayoutElement::elements(bool recursive) const
{
  Q_UNUSED(recursive)
  return QList<QCPLayoutElement*>();
}

/*!
  Layout elements are sensitive to events inside their outer rect. If \a pos is within the outer
  rect, this method returns a value corresponding to 0.99 times the parent plot's selection
  tolerance. However, layout elements are not selectable by default. So if \a onlySelectable is
  true, -1.0 is returned.
  
  See \ref QCPLayerable::selectTest for a general explanation of this virtual method.
  
  QCPLayoutElement subclasses may reimplement this method to provide more specific selection test
  behaviour.
*/
double QCPLayoutElement::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const
{
  Q_UNUSED(details)
  
  if (onlySelectable)
    return -1;
  
  if (QRectF(mOuterRect).contains(pos))
  {
    if (mParentPlot)
      return mParentPlot->selectionTolerance()*0.99;
    else
    {
      qDebug() << Q_FUNC_INFO << "parent plot not defined";
      return -1;
    }
  } else
    return -1;
}

/*! \internal
  
  propagates the parent plot initialization to all child elements, by calling \ref
  QCPLayerable::initializeParentPlot on them.
*/
void QCPLayoutElement::parentPlotInitialized(QCustomPlot *parentPlot)
{
  foreach (QCPLayoutElement *el, elements(false))
  {
    if (!el->parentPlot())
      el->initializeParentPlot(parentPlot);
  }
}

/*! \internal
  
  Returns the margin size for this \a side. It is used if automatic margins is enabled for this \a
  side (see \ref setAutoMargins). If a minimum margin was set with \ref setMinimumMargins, the
  returned value will not be smaller than the specified minimum margin.
  
  The default implementation just returns the respective manual margin (\ref setMargins) or the
  minimum margin, whichever is larger.
*/
int QCPLayoutElement::calculateAutoMargin(QCP::MarginSide side)
{
  return qMax(QCP::getMarginValue(mMargins, side), QCP::getMarginValue(mMinimumMargins, side));
}

/*! \internal
  
  This virtual method is called when this layout element was moved to a different QCPLayout, or
  when this layout element has changed its logical position (e.g. row and/or column) within the
  same QCPLayout. Subclasses may use this to react accordingly.
  
  Since this method is called after the completion of the move, you can access the new parent
  layout via \ref layout().
  
  The default implementation does nothing.
*/
void QCPLayoutElement::layoutChanged()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPLayout
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPLayout
  \brief The abstract base class for layouts
  
  This is an abstract base class for layout elements whose main purpose is to define the position
  and size of other child layout elements. In most cases, layouts don't draw anything themselves
  (but there are exceptions to this, e.g. QCPLegend).
  
  QCPLayout derives from QCPLayoutElement, and thus can itself be nested in other layouts.
  
  QCPLayout introduces a common interface for accessing and manipulating the child elements. Those
  functions are most notably \ref elementCount, \ref elementAt, \ref takeAt, \ref take, \ref
  simplify, \ref removeAt, \ref remove and \ref clear. Individual subclasses may add more functions
  to this interface which are more specialized to the form of the layout. For example, \ref
  QCPLayoutGrid adds functions that take row and column indices to access cells of the layout grid
  more conveniently.
  
  Since this is an abstract base class, you can't instantiate it directly. Rather use one of its
  subclasses like QCPLayoutGrid or QCPLayoutInset.
  
  For a general introduction to the layout system, see the dedicated documentation page \ref
  thelayoutsystem "The Layout System".
*/

/* start documentation of pure virtual functions */

/*! \fn virtual int QCPLayout::elementCount() const = 0
  
  Returns the number of elements/cells in the layout.
  
  \see elements, elementAt
*/

/*! \fn virtual QCPLayoutElement* QCPLayout::elementAt(int index) const = 0
  
  Returns the element in the cell with the given \a index. If \a index is invalid, returns \c
  nullptr.
  
  Note that even if \a index is valid, the respective cell may be empty in some layouts (e.g.
  QCPLayoutGrid), so this function may return \c nullptr in those cases. You may use this function
  to check whether a cell is empty or not.
  
  \see elements, elementCount, takeAt
*/

/*! \fn virtual QCPLayoutElement* QCPLayout::takeAt(int index) = 0
  
  Removes the element with the given \a index from the layout and returns it.
  
  If the \a index is invalid or the cell with that index is empty, returns \c nullptr.
  
  Note that some layouts don't remove the respective cell right away but leave an empty cell after
  successful removal of the layout element. To collapse empty cells, use \ref simplify.
  
  \see elementAt, take
*/

/*! \fn virtual bool QCPLayout::take(QCPLayoutElement* element) = 0
  
  Removes the specified \a element from the layout and returns true on success.
  
  If the \a element isn't in this layout, returns false.
  
  Note that some layouts don't remove the respective cell right away but leave an empty cell after
  successful removal of the layout element. To collapse empty cells, use \ref simplify.
  
  \see takeAt
*/

/* end documentation of pure virtual functions */

/*!
  Creates an instance of QCPLayout and sets default values. Note that since QCPLayout
  is an abstract base class, it can't be instantiated directly.
*/
QCPLayout::QCPLayout()
{
}

/*!
  If \a phase is \ref upLayout, calls \ref updateLayout, which subclasses may reimplement to
  reposition and resize their cells.
  
  Finally, the call is propagated down to all child \ref QCPLayoutElement "QCPLayoutElements".
  
  For details about this method and the update phases, see the documentation of \ref
  QCPLayoutElement::update.
*/
void QCPLayout::update(UpdatePhase phase)
{
  QCPLayoutElement::update(phase);
  
  // set child element rects according to layout:
  if (phase == upLayout)
    updateLayout();
  
  // propagate update call to child elements:
  const int elCount = elementCount();
  for (int i=0; i<elCount; ++i)
  {
    if (QCPLayoutElement *el = elementAt(i))
      el->update(phase);
  }
}

/* inherits documentation from base class */
QList<QCPLayoutElement*> QCPLayout::elements(bool recursive) const
{
  const int c = elementCount();
  QList<QCPLayoutElement*> result;
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
  result.reserve(c);
#endif
  for (int i=0; i<c; ++i)
    result.append(elementAt(i));
  if (recursive)
  {
    for (int i=0; i<c; ++i)
    {
      if (result.at(i))
        result << result.at(i)->elements(recursive);
    }
  }
  return result;
}

/*!
  Simplifies the layout by collapsing empty cells. The exact behavior depends on subclasses, the
  default implementation does nothing.
  
  Not all layouts need simplification. For example, QCPLayoutInset doesn't use explicit
  simplification while QCPLayoutGrid does.
*/
void QCPLayout::simplify()
{
}

/*!
  Removes and deletes the element at the provided \a index. Returns true on success. If \a index is
  invalid or points to an empty cell, returns false.
  
  This function internally uses \ref takeAt to remove the element from the layout and then deletes
  the returned element. Note that some layouts don't remove the respective cell right away but leave an
  empty cell after successful removal of the layout element. To collapse empty cells, use \ref
  simplify.
  
  \see remove, takeAt
*/
bool QCPLayout::removeAt(int index)
{
  if (QCPLayoutElement *el = takeAt(index))
  {
    delete el;
    return true;
  } else
    return false;
}

/*!
  Removes and deletes the provided \a element. Returns true on success. If \a element is not in the
  layout, returns false.
  
  This function internally uses \ref takeAt to remove the element from the layout and then deletes
  the element. Note that some layouts don't remove the respective cell right away but leave an
  empty cell after successful removal of the layout element. To collapse empty cells, use \ref
  simplify.
  
  \see removeAt, take
*/
bool QCPLayout::remove(QCPLayoutElement *element)
{
  if (take(element))
  {
    delete element;
    return true;
  } else
    return false;
}

/*!
  Removes and deletes all layout elements in this layout. Finally calls \ref simplify to make sure
  all empty cells are collapsed.
  
  \see remove, removeAt
*/
void QCPLayout::clear()
{
  for (int i=elementCount()-1; i>=0; --i)
  {
    if (elementAt(i))
      removeAt(i);
  }
  simplify();
}

/*!
  Subclasses call this method to report changed (minimum/maximum) size constraints.
  
  If the parent of this layout is again a QCPLayout, forwards the call to the parent's \ref
  sizeConstraintsChanged. If the parent is a QWidget (i.e. is the \ref QCustomPlot::plotLayout of
  QCustomPlot), calls QWidget::updateGeometry, so if the QCustomPlot widget is inside a Qt QLayout,
  it may update itself and resize cells accordingly.
*/
void QCPLayout::sizeConstraintsChanged() const
{
  if (QWidget *w = qobject_cast<QWidget*>(parent()))
    w->updateGeometry();
  else if (QCPLayout *l = qobject_cast<QCPLayout*>(parent()))
    l->sizeConstraintsChanged();
}

/*! \internal
  
  Subclasses reimplement this method to update the position and sizes of the child elements/cells
  via calling their \ref QCPLayoutElement::setOuterRect. The default implementation does nothing.
  
  The geometry used as a reference is the inner \ref rect of this layout. Child elements should stay
  within that rect.
  
  \ref getSectionSizes may help with the reimplementation of this function.
  
  \see update
*/
void QCPLayout::updateLayout()
{
}


/*! \internal
  
  Associates \a el with this layout. This is done by setting the \ref QCPLayoutElement::layout, the
  \ref QCPLayerable::parentLayerable and the QObject parent to this layout.
  
  Further, if \a el didn't previously have a parent plot, calls \ref
  QCPLayerable::initializeParentPlot on \a el to set the paret plot.
  
  This method is used by subclass specific methods that add elements to the layout. Note that this
  method only changes properties in \a el. The removal from the old layout and the insertion into
  the new layout must be done additionally.
*/
void QCPLayout::adoptElement(QCPLayoutElement *el)
{
  if (el)
  {
    el->mParentLayout = this;
    el->setParentLayerable(this);
    el->setParent(this);
    if (!el->parentPlot())
      el->initializeParentPlot(mParentPlot);
    el->layoutChanged();
  } else
    qDebug() << Q_FUNC_INFO << "Null element passed";
}

/*! \internal
  
  Disassociates \a el from this layout. This is done by setting the \ref QCPLayoutElement::layout
  and the \ref QCPLayerable::parentLayerable to zero. The QObject parent is set to the parent
  QCustomPlot.
  
  This method is used by subclass specific methods that remove elements from the layout (e.g. \ref
  take or \ref takeAt). Note that this method only changes properties in \a el. The removal from
  the old layout must be done additionally.
*/
void QCPLayout::releaseElement(QCPLayoutElement *el)
{
  if (el)
  {
    el->mParentLayout = nullptr;
    el->setParentLayerable(nullptr);
    el->setParent(mParentPlot);
    // Note: Don't initializeParentPlot(0) here, because layout element will stay in same parent plot
  } else
    qDebug() << Q_FUNC_INFO << "Null element passed";
}

/*! \internal
  
  This is a helper function for the implementation of \ref updateLayout in subclasses.
  
  It calculates the sizes of one-dimensional sections with provided constraints on maximum section
  sizes, minimum section sizes, relative stretch factors and the final total size of all sections.
  
  The QVector entries refer to the sections. Thus all QVectors must have the same size.
  
  \a maxSizes gives the maximum allowed size of each section. If there shall be no maximum size
  imposed, set all vector values to Qt's QWIDGETSIZE_MAX.
  
  \a minSizes gives the minimum allowed size of each section. If there shall be no minimum size
  imposed, set all vector values to zero. If the \a minSizes entries add up to a value greater than
  \a totalSize, sections will be scaled smaller than the proposed minimum sizes. (In other words,
  not exceeding the allowed total size is taken to be more important than not going below minimum
  section sizes.)
  
  \a stretchFactors give the relative proportions of the sections to each other. If all sections
  shall be scaled equally, set all values equal. If the first section shall be double the size of
  each individual other section, set the first number of \a stretchFactors to double the value of
  the other individual values (e.g. {2, 1, 1, 1}).
  
  \a totalSize is the value that the final section sizes will add up to. Due to rounding, the
  actual sum may differ slightly. If you want the section sizes to sum up to exactly that value,
  you could distribute the remaining difference on the sections.
  
  The return value is a QVector containing the section sizes.
*/
QVector<int> QCPLayout::getSectionSizes(QVector<int> maxSizes, QVector<int> minSizes, QVector<double> stretchFactors, int totalSize) const
{
  if (maxSizes.size() != minSizes.size() || minSizes.size() != stretchFactors.size())
  {
    qDebug() << Q_FUNC_INFO << "Passed vector sizes aren't equal:" << maxSizes << minSizes << stretchFactors;
    return QVector<int>();
  }
  if (stretchFactors.isEmpty())
    return QVector<int>();
  int sectionCount = stretchFactors.size();
  QVector<double> sectionSizes(sectionCount);
  // if provided total size is forced smaller than total minimum size, ignore minimum sizes (squeeze sections):
  int minSizeSum = 0;
  for (int i=0; i<sectionCount; ++i)
    minSizeSum += minSizes.at(i);
  if (totalSize < minSizeSum)
  {
    // new stretch factors are minimum sizes and minimum sizes are set to zero:
    for (int i=0; i<sectionCount; ++i)
    {
      stretchFactors[i] = minSizes.at(i);
      minSizes[i] = 0;
    }
  }
  
  QList<int> minimumLockedSections;
  QList<int> unfinishedSections;
  for (int i=0; i<sectionCount; ++i)
    unfinishedSections.append(i);
  double freeSize = totalSize;
  
  int outerIterations = 0;
  while (!unfinishedSections.isEmpty() && outerIterations < sectionCount*2) // the iteration check ist just a failsafe in case something really strange happens
  {
    ++outerIterations;
    int innerIterations = 0;
    while (!unfinishedSections.isEmpty() && innerIterations < sectionCount*2) // the iteration check ist just a failsafe in case something really strange happens
    {
      ++innerIterations;
      // find section that hits its maximum next:
      int nextId = -1;
      double nextMax = 1e12;
      foreach (int secId, unfinishedSections)
      {
        double hitsMaxAt = (maxSizes.at(secId)-sectionSizes.at(secId))/stretchFactors.at(secId);
        if (hitsMaxAt < nextMax)
        {
          nextMax = hitsMaxAt;
          nextId = secId;
        }
      }
      // check if that maximum is actually within the bounds of the total size (i.e. can we stretch all remaining sections so far that the found section
      // actually hits its maximum, without exceeding the total size when we add up all sections)
      double stretchFactorSum = 0;
      foreach (int secId, unfinishedSections)
        stretchFactorSum += stretchFactors.at(secId);
      double nextMaxLimit = freeSize/stretchFactorSum;
      if (nextMax < nextMaxLimit) // next maximum is actually hit, move forward to that point and fix the size of that section
      {
        foreach (int secId, unfinishedSections)
        {
          sectionSizes[secId] += nextMax*stretchFactors.at(secId); // increment all sections
          freeSize -= nextMax*stretchFactors.at(secId);
        }
        unfinishedSections.removeOne(nextId); // exclude the section that is now at maximum from further changes
      } else // next maximum isn't hit, just distribute rest of free space on remaining sections
      {
        foreach (int secId, unfinishedSections)
          sectionSizes[secId] += nextMaxLimit*stretchFactors.at(secId); // increment all sections
        unfinishedSections.clear();
      }
    }
    if (innerIterations == sectionCount*2)
      qDebug() << Q_FUNC_INFO << "Exceeded maximum expected inner iteration count, layouting aborted. Input was:" << maxSizes << minSizes << stretchFactors << totalSize;
    
    // now check whether the resulting section sizes violate minimum restrictions:
    bool foundMinimumViolation = false;
    for (int i=0; i<sectionSizes.size(); ++i)
    {
      if (minimumLockedSections.contains(i))
        continue;
      if (sectionSizes.at(i) < minSizes.at(i)) // section violates minimum
      {
        sectionSizes[i] = minSizes.at(i); // set it to minimum
        foundMinimumViolation = true; // make sure we repeat the whole optimization process
        minimumLockedSections.append(i);
      }
    }
    if (foundMinimumViolation)
    {
      freeSize = totalSize;
      for (int i=0; i<sectionCount; ++i)
      {
        if (!minimumLockedSections.contains(i)) // only put sections that haven't hit their minimum back into the pool
          unfinishedSections.append(i);
        else
          freeSize -= sectionSizes.at(i); // remove size of minimum locked sections from available space in next round
      }
      // reset all section sizes to zero that are in unfinished sections (all others have been set to their minimum):
      foreach (int secId, unfinishedSections)
        sectionSizes[secId] = 0;
    }
  }
  if (outerIterations == sectionCount*2)
    qDebug() << Q_FUNC_INFO << "Exceeded maximum expected outer iteration count, layouting aborted. Input was:" << maxSizes << minSizes << stretchFactors << totalSize;
  
  QVector<int> result(sectionCount);
  for (int i=0; i<sectionCount; ++i)
    result[i] = qRound(sectionSizes.at(i));
  return result;
}

/*! \internal
  
  This is a helper function for the implementation of subclasses.
  
  It returns the minimum size that should finally be used for the outer rect of the passed layout
  element \a el.
  
  It takes into account whether a manual minimum size is set (\ref
  QCPLayoutElement::setMinimumSize), which size constraint is set (\ref
  QCPLayoutElement::setSizeConstraintRect), as well as the minimum size hint, if no manual minimum
  size was set (\ref QCPLayoutElement::minimumOuterSizeHint).
*/
QSize QCPLayout::getFinalMinimumOuterSize(const QCPLayoutElement *el)
{
  QSize minOuterHint = el->minimumOuterSizeHint();
  QSize minOuter = el->minimumSize(); // depending on sizeConstraitRect this might be with respect to inner rect, so possibly add margins in next four lines (preserving unset minimum of 0)
  if (minOuter.width() > 0 && el->sizeConstraintRect() == QCPLayoutElement::scrInnerRect)
    minOuter.rwidth() += el->margins().left() + el->margins().right();
  if (minOuter.height() > 0 && el->sizeConstraintRect() == QCPLayoutElement::scrInnerRect)
    minOuter.rheight() += el->margins().top() + el->margins().bottom();
  
  return {minOuter.width() > 0 ? minOuter.width() : minOuterHint.width(),
               minOuter.height() > 0 ? minOuter.height() : minOuterHint.height()};
}

/*! \internal
  
  This is a helper function for the implementation of subclasses.
  
  It returns the maximum size that should finally be used for the outer rect of the passed layout
  element \a el.
  
  It takes into account whether a manual maximum size is set (\ref
  QCPLayoutElement::setMaximumSize), which size constraint is set (\ref
  QCPLayoutElement::setSizeConstraintRect), as well as the maximum size hint, if no manual maximum
  size was set (\ref QCPLayoutElement::maximumOuterSizeHint).
*/
QSize QCPLayout::getFinalMaximumOuterSize(const QCPLayoutElement *el)
{
  QSize maxOuterHint = el->maximumOuterSizeHint();
  QSize maxOuter = el->maximumSize(); // depending on sizeConstraitRect this might be with respect to inner rect, so possibly add margins in next four lines (preserving unset maximum of QWIDGETSIZE_MAX)
  if (maxOuter.width() < QWIDGETSIZE_MAX && el->sizeConstraintRect() == QCPLayoutElement::scrInnerRect)
    maxOuter.rwidth() += el->margins().left() + el->margins().right();
  if (maxOuter.height() < QWIDGETSIZE_MAX && el->sizeConstraintRect() == QCPLayoutElement::scrInnerRect)
    maxOuter.rheight() += el->margins().top() + el->margins().bottom();
  
  return {maxOuter.width() < QWIDGETSIZE_MAX ? maxOuter.width() : maxOuterHint.width(),
               maxOuter.height() < QWIDGETSIZE_MAX ? maxOuter.height() : maxOuterHint.height()};
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPLayoutGrid
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPLayoutGrid
  \brief A layout that arranges child elements in a grid

  Elements are laid out in a grid with configurable stretch factors (\ref setColumnStretchFactor,
  \ref setRowStretchFactor) and spacing (\ref setColumnSpacing, \ref setRowSpacing).

  Elements can be added to cells via \ref addElement. The grid is expanded if the specified row or
  column doesn't exist yet. Whether a cell contains a valid layout element can be checked with \ref
  hasElement, that element can be retrieved with \ref element. If rows and columns that only have
  empty cells shall be removed, call \ref simplify. Removal of elements is either done by just
  adding the element to a different layout or by using the QCPLayout interface \ref take or \ref
  remove.

  If you use \ref addElement(QCPLayoutElement*) without explicit parameters for \a row and \a
  column, the grid layout will choose the position according to the current \ref setFillOrder and
  the wrapping (\ref setWrap).

  Row and column insertion can be performed with \ref insertRow and \ref insertColumn.
*/

/* start documentation of inline functions */

/*! \fn int QCPLayoutGrid::rowCount() const

  Returns the number of rows in the layout.

  \see columnCount
*/

/*! \fn int QCPLayoutGrid::columnCount() const

  Returns the number of columns in the layout.

  \see rowCount
*/

/* end documentation of inline functions */

/*!
  Creates an instance of QCPLayoutGrid and sets default values.
*/
QCPLayoutGrid::QCPLayoutGrid() :
  mColumnSpacing(5),
  mRowSpacing(5),
  mWrap(0),
  mFillOrder(foColumnsFirst)
{
}

QCPLayoutGrid::~QCPLayoutGrid()
{
  // clear all child layout elements. This is important because only the specific layouts know how
  // to handle removing elements (clear calls virtual removeAt method to do that).
  clear();
}

/*!
  Returns the element in the cell in \a row and \a column.
  
  Returns \c nullptr if either the row/column is invalid or if the cell is empty. In those cases, a
  qDebug message is printed. To check whether a cell exists and isn't empty, use \ref hasElement.
  
  \see addElement, hasElement
*/
QCPLayoutElement *QCPLayoutGrid::element(int row, int column) const
{
  if (row >= 0 && row < mElements.size())
  {
    if (column >= 0 && column < mElements.first().size())
    {
      if (QCPLayoutElement *result = mElements.at(row).at(column))
        return result;
      else
        qDebug() << Q_FUNC_INFO << "Requested cell is empty. Row:" << row << "Column:" << column;
    } else
      qDebug() << Q_FUNC_INFO << "Invalid column. Row:" << row << "Column:" << column;
  } else
    qDebug() << Q_FUNC_INFO << "Invalid row. Row:" << row << "Column:" << column;
  return nullptr;
}


/*! \overload

  Adds the \a element to cell with \a row and \a column. If \a element is already in a layout, it
  is first removed from there. If \a row or \a column don't exist yet, the layout is expanded
  accordingly.

  Returns true if the element was added successfully, i.e. if the cell at \a row and \a column
  didn't already have an element.

  Use the overload of this method without explicit row/column index to place the element according
  to the configured fill order and wrapping settings.

  \see element, hasElement, take, remove
*/
bool QCPLayoutGrid::addElement(int row, int column, QCPLayoutElement *element)
{
  if (!hasElement(row, column))
  {
    if (element && element->layout()) // remove from old layout first
      element->layout()->take(element);
    expandTo(row+1, column+1);
    mElements[row][column] = element;
    if (element)
      adoptElement(element);
    return true;
  } else
    qDebug() << Q_FUNC_INFO << "There is already an element in the specified row/column:" << row << column;
  return false;
}

/*! \overload

  Adds the \a element to the next empty cell according to the current fill order (\ref
  setFillOrder) and wrapping (\ref setWrap). If \a element is already in a layout, it is first
  removed from there. If necessary, the layout is expanded to hold the new element.

  Returns true if the element was added successfully.

  \see setFillOrder, setWrap, element, hasElement, take, remove
*/
bool QCPLayoutGrid::addElement(QCPLayoutElement *element)
{
  int rowIndex = 0;
  int colIndex = 0;
  if (mFillOrder == foColumnsFirst)
  {
    while (hasElement(rowIndex, colIndex))
    {
      ++colIndex;
      if (colIndex >= mWrap && mWrap > 0)
      {
        colIndex = 0;
        ++rowIndex;
      }
    }
  } else
  {
    while (hasElement(rowIndex, colIndex))
    {
      ++rowIndex;
      if (rowIndex >= mWrap && mWrap > 0)
      {
        rowIndex = 0;
        ++colIndex;
      }
    }
  }
  return addElement(rowIndex, colIndex, element);
}

/*!
  Returns whether the cell at \a row and \a column exists and contains a valid element, i.e. isn't
  empty.
  
  \see element
*/
bool QCPLayoutGrid::hasElement(int row, int column)
{
  if (row >= 0 && row < rowCount() && column >= 0 && column < columnCount())
    return mElements.at(row).at(column);
  else
    return false;
}

/*!
  Sets the stretch \a factor of \a column.
  
  Stretch factors control the relative sizes of rows and columns. Cells will not be resized beyond
  their minimum and maximum widths/heights, regardless of the stretch factor. (see \ref
  QCPLayoutElement::setMinimumSize, \ref QCPLayoutElement::setMaximumSize, \ref
  QCPLayoutElement::setSizeConstraintRect.)
  
  The default stretch factor of newly created rows/columns is 1.
  
  \see setColumnStretchFactors, setRowStretchFactor
*/
void QCPLayoutGrid::setColumnStretchFactor(int column, double factor)
{
  if (column >= 0 && column < columnCount())
  {
    if (factor > 0)
      mColumnStretchFactors[column] = factor;
    else
      qDebug() << Q_FUNC_INFO << "Invalid stretch factor, must be positive:" << factor;
  } else
    qDebug() << Q_FUNC_INFO << "Invalid column:" << column;
}

/*!
  Sets the stretch \a factors of all columns. \a factors must have the size \ref columnCount.
  
  Stretch factors control the relative sizes of rows and columns. Cells will not be resized beyond
  their minimum and maximum widths/heights, regardless of the stretch factor. (see \ref
  QCPLayoutElement::setMinimumSize, \ref QCPLayoutElement::setMaximumSize, \ref
  QCPLayoutElement::setSizeConstraintRect.)
  
  The default stretch factor of newly created rows/columns is 1.
  
  \see setColumnStretchFactor, setRowStretchFactors
*/
void QCPLayoutGrid::setColumnStretchFactors(const QList<double> &factors)
{
  if (factors.size() == mColumnStretchFactors.size())
  {
    mColumnStretchFactors = factors;
    for (int i=0; i<mColumnStretchFactors.size(); ++i)
    {
      if (mColumnStretchFactors.at(i) <= 0)
      {
        qDebug() << Q_FUNC_INFO << "Invalid stretch factor, must be positive:" << mColumnStretchFactors.at(i);
        mColumnStretchFactors[i] = 1;
      }
    }
  } else
    qDebug() << Q_FUNC_INFO << "Column count not equal to passed stretch factor count:" << factors;
}

/*!
  Sets the stretch \a factor of \a row.
  
  Stretch factors control the relative sizes of rows and columns. Cells will not be resized beyond
  their minimum and maximum widths/heights, regardless of the stretch factor. (see \ref
  QCPLayoutElement::setMinimumSize, \ref QCPLayoutElement::setMaximumSize, \ref
  QCPLayoutElement::setSizeConstraintRect.)
  
  The default stretch factor of newly created rows/columns is 1.
  
  \see setColumnStretchFactors, setRowStretchFactor
*/
void QCPLayoutGrid::setRowStretchFactor(int row, double factor)
{
  if (row >= 0 && row < rowCount())
  {
    if (factor > 0)
      mRowStretchFactors[row] = factor;
    else
      qDebug() << Q_FUNC_INFO << "Invalid stretch factor, must be positive:" << factor;
  } else
    qDebug() << Q_FUNC_INFO << "Invalid row:" << row;
}

/*!
  Sets the stretch \a factors of all rows. \a factors must have the size \ref rowCount.
  
  Stretch factors control the relative sizes of rows and columns. Cells will not be resized beyond
  their minimum and maximum widths/heights, regardless of the stretch factor. (see \ref
  QCPLayoutElement::setMinimumSize, \ref QCPLayoutElement::setMaximumSize, \ref
  QCPLayoutElement::setSizeConstraintRect.)
  
  The default stretch factor of newly created rows/columns is 1.
  
  \see setRowStretchFactor, setColumnStretchFactors
*/
void QCPLayoutGrid::setRowStretchFactors(const QList<double> &factors)
{
  if (factors.size() == mRowStretchFactors.size())
  {
    mRowStretchFactors = factors;
    for (int i=0; i<mRowStretchFactors.size(); ++i)
    {
      if (mRowStretchFactors.at(i) <= 0)
      {
        qDebug() << Q_FUNC_INFO << "Invalid stretch factor, must be positive:" << mRowStretchFactors.at(i);
        mRowStretchFactors[i] = 1;
      }
    }
  } else
    qDebug() << Q_FUNC_INFO << "Row count not equal to passed stretch factor count:" << factors;
}

/*!
  Sets the gap that is left blank between columns to \a pixels.
  
  \see setRowSpacing
*/
void QCPLayoutGrid::setColumnSpacing(int pixels)
{
  mColumnSpacing = pixels;
}

/*!
  Sets the gap that is left blank between rows to \a pixels.
  
  \see setColumnSpacing
*/
void QCPLayoutGrid::setRowSpacing(int pixels)
{
  mRowSpacing = pixels;
}

/*!
  Sets the maximum number of columns or rows that are used, before new elements added with \ref
  addElement(QCPLayoutElement*) will start to fill the next row or column, respectively. It depends
  on \ref setFillOrder, whether rows or columns are wrapped.

  If \a count is set to zero, no wrapping will ever occur.
  
  If you wish to re-wrap the elements currently in the layout, call \ref setFillOrder with \a
  rearrange set to true (the actual fill order doesn't need to be changed for the rearranging to be
  done).

  Note that the method \ref addElement(int row, int column, QCPLayoutElement *element) with
  explicitly stated row and column is not subject to wrapping and can place elements even beyond
  the specified wrapping point.

  \see setFillOrder
*/
void QCPLayoutGrid::setWrap(int count)
{
  mWrap = qMax(0, count);
}

/*!
  Sets the filling order and wrapping behaviour that is used when adding new elements with the
  method \ref addElement(QCPLayoutElement*).

  The specified \a order defines whether rows or columns are filled first. Using \ref setWrap, you
  can control at which row/column count wrapping into the next column/row will occur. If you set it
  to zero, no wrapping will ever occur. Changing the fill order also changes the meaning of the
  linear index used e.g. in \ref elementAt and \ref takeAt. The default fill order for \ref
  QCPLayoutGrid is \ref foColumnsFirst.

  If you want to have all current elements arranged in the new order, set \a rearrange to true. The
  elements will be rearranged in a way that tries to preserve their linear index. However, empty
  cells are skipped during build-up of the new cell order, which shifts the succeeding element's
  index. The rearranging is performed even if the specified \a order is already the current fill
  order. Thus this method can be used to re-wrap the current elements.

  If \a rearrange is false, the current element arrangement is not changed, which means the
  linear indexes change (because the linear index is dependent on the fill order).

  Note that the method \ref addElement(int row, int column, QCPLayoutElement *element) with
  explicitly stated row and column is not subject to wrapping and can place elements even beyond
  the specified wrapping point.

  \see setWrap, addElement(QCPLayoutElement*)
*/
void QCPLayoutGrid::setFillOrder(FillOrder order, bool rearrange)
{
  // if rearranging, take all elements via linear index of old fill order:
  const int elCount = elementCount();
  QVector<QCPLayoutElement*> tempElements;
  if (rearrange)
  {
    tempElements.reserve(elCount);
    for (int i=0; i<elCount; ++i)
    {
      if (elementAt(i))
        tempElements.append(takeAt(i));
    }
    simplify();
  }
  // change fill order as requested:
  mFillOrder = order;
  // if rearranging, re-insert via linear index according to new fill order:
  if (rearrange)
  {
    foreach (QCPLayoutElement *tempElement, tempElements)
      addElement(tempElement);
  }
}

/*!
  Expands the layout to have \a newRowCount rows and \a newColumnCount columns. So the last valid
  row index will be \a newRowCount-1, the last valid column index will be \a newColumnCount-1.
  
  If the current column/row count is already larger or equal to \a newColumnCount/\a newRowCount,
  this function does nothing in that dimension.
  
  Newly created cells are empty, new rows and columns have the stretch factor 1.
  
  Note that upon a call to \ref addElement, the layout is expanded automatically to contain the
  specified row and column, using this function.
  
  \see simplify
*/
void QCPLayoutGrid::expandTo(int newRowCount, int newColumnCount)
{
  // add rows as necessary:
  while (rowCount() < newRowCount)
  {
    mElements.append(QList<QCPLayoutElement*>());
    mRowStretchFactors.append(1);
  }
  // go through rows and expand columns as necessary:
  int newColCount = qMax(columnCount(), newColumnCount);
  for (int i=0; i<rowCount(); ++i)
  {
    while (mElements.at(i).size() < newColCount)
      mElements[i].append(nullptr);
  }
  while (mColumnStretchFactors.size() < newColCount)
    mColumnStretchFactors.append(1);
}

/*!
  Inserts a new row with empty cells at the row index \a newIndex. Valid values for \a newIndex
  range from 0 (inserts a row at the top) to \a rowCount (appends a row at the bottom).
  
  \see insertColumn
*/
void QCPLayoutGrid::insertRow(int newIndex)
{
  if (mElements.isEmpty() || mElements.first().isEmpty()) // if grid is completely empty, add first cell
  {
    expandTo(1, 1);
    return;
  }
  
  if (newIndex < 0)
    newIndex = 0;
  if (newIndex > rowCount())
    newIndex = rowCount();
  
  mRowStretchFactors.insert(newIndex, 1);
  QList<QCPLayoutElement*> newRow;
  for (int col=0; col<columnCount(); ++col)
    newRow.append(nullptr);
  mElements.insert(newIndex, newRow);
}

/*!
  Inserts a new column with empty cells at the column index \a newIndex. Valid values for \a
  newIndex range from 0 (inserts a column at the left) to \a columnCount (appends a column at the
  right).
  
  \see insertRow
*/
void QCPLayoutGrid::insertColumn(int newIndex)
{
  if (mElements.isEmpty() || mElements.first().isEmpty()) // if grid is completely empty, add first cell
  {
    expandTo(1, 1);
    return;
  }
  
  if (newIndex < 0)
    newIndex = 0;
  if (newIndex > columnCount())
    newIndex = columnCount();
  
  mColumnStretchFactors.insert(newIndex, 1);
  for (int row=0; row<rowCount(); ++row)
    mElements[row].insert(newIndex, nullptr);
}

/*!
  Converts the given \a row and \a column to the linear index used by some methods of \ref
  QCPLayoutGrid and \ref QCPLayout.

  The way the cells are indexed depends on \ref setFillOrder. If it is \ref foRowsFirst, the
  indices increase left to right and then top to bottom. If it is \ref foColumnsFirst, the indices
  increase top to bottom and then left to right.

  For the returned index to be valid, \a row and \a column must be valid indices themselves, i.e.
  greater or equal to zero and smaller than the current \ref rowCount/\ref columnCount.

  \see indexToRowCol
*/
int QCPLayoutGrid::rowColToIndex(int row, int column) const
{
  if (row >= 0 && row < rowCount())
  {
    if (column >= 0 && column < columnCount())
    {
      switch (mFillOrder)
      {
        case foRowsFirst: return column*rowCount() + row;
        case foColumnsFirst: return row*columnCount() + column;
      }
    } else
      qDebug() << Q_FUNC_INFO << "row index out of bounds:" << row;
  } else
    qDebug() << Q_FUNC_INFO << "column index out of bounds:" << column;
  return 0;
}

/*!
  Converts the linear index to row and column indices and writes the result to \a row and \a
  column.

  The way the cells are indexed depends on \ref setFillOrder. If it is \ref foRowsFirst, the
  indices increase left to right and then top to bottom. If it is \ref foColumnsFirst, the indices
  increase top to bottom and then left to right.

  If there are no cells (i.e. column or row count is zero), sets \a row and \a column to -1.

  For the retrieved \a row and \a column to be valid, the passed \a index must be valid itself,
  i.e. greater or equal to zero and smaller than the current \ref elementCount.

  \see rowColToIndex
*/
void QCPLayoutGrid::indexToRowCol(int index, int &row, int &column) const
{
  row = -1;
  column = -1;
  const int nCols = columnCount();
  const int nRows = rowCount();
  if (nCols == 0 || nRows == 0)
    return;
  if (index < 0 || index >= elementCount())
  {
    qDebug() << Q_FUNC_INFO << "index out of bounds:" << index;
    return;
  }
  
  switch (mFillOrder)
  {
    case foRowsFirst:
    {
      column = index / nRows;
      row = index % nRows;
      break;
    }
    case foColumnsFirst:
    {
      row = index / nCols;
      column = index % nCols;
      break;
    }
  }
}

/* inherits documentation from base class */
void QCPLayoutGrid::updateLayout()
{
  QVector<int> minColWidths, minRowHeights, maxColWidths, maxRowHeights;
  getMinimumRowColSizes(&minColWidths, &minRowHeights);
  getMaximumRowColSizes(&maxColWidths, &maxRowHeights);
  
  int totalRowSpacing = (rowCount()-1) * mRowSpacing;
  int totalColSpacing = (columnCount()-1) * mColumnSpacing;
  QVector<int> colWidths = getSectionSizes(maxColWidths, minColWidths, mColumnStretchFactors.toVector(), mRect.width()-totalColSpacing);
  QVector<int> rowHeights = getSectionSizes(maxRowHeights, minRowHeights, mRowStretchFactors.toVector(), mRect.height()-totalRowSpacing);
  
  // go through cells and set rects accordingly:
  int yOffset = mRect.top();
  for (int row=0; row<rowCount(); ++row)
  {
    if (row > 0)
      yOffset += rowHeights.at(row-1)+mRowSpacing;
    int xOffset = mRect.left();
    for (int col=0; col<columnCount(); ++col)
    {
      if (col > 0)
        xOffset += colWidths.at(col-1)+mColumnSpacing;
      if (mElements.at(row).at(col))
        mElements.at(row).at(col)->setOuterRect(QRect(xOffset, yOffset, colWidths.at(col), rowHeights.at(row)));
    }
  }
}

/*!
  \seebaseclassmethod

  Note that the association of the linear \a index to the row/column based cells depends on the
  current setting of \ref setFillOrder.

  \see rowColToIndex
*/
QCPLayoutElement *QCPLayoutGrid::elementAt(int index) const
{
  if (index >= 0 && index < elementCount())
  {
    int row, col;
    indexToRowCol(index, row, col);
    return mElements.at(row).at(col);
  } else
    return nullptr;
}

/*!
  \seebaseclassmethod

  Note that the association of the linear \a index to the row/column based cells depends on the
  current setting of \ref setFillOrder.

  \see rowColToIndex
*/
QCPLayoutElement *QCPLayoutGrid::takeAt(int index)
{
  if (QCPLayoutElement *el = elementAt(index))
  {
    releaseElement(el);
    int row, col;
    indexToRowCol(index, row, col);
    mElements[row][col] = nullptr;
    return el;
  } else
  {
    qDebug() << Q_FUNC_INFO << "Attempt to take invalid index:" << index;
    return nullptr;
  }
}

/* inherits documentation from base class */
bool QCPLayoutGrid::take(QCPLayoutElement *element)
{
  if (element)
  {
    for (int i=0; i<elementCount(); ++i)
    {
      if (elementAt(i) == element)
      {
        takeAt(i);
        return true;
      }
    }
    qDebug() << Q_FUNC_INFO << "Element not in this layout, couldn't take";
  } else
    qDebug() << Q_FUNC_INFO << "Can't take nullptr element";
  return false;
}

/* inherits documentation from base class */
QList<QCPLayoutElement*> QCPLayoutGrid::elements(bool recursive) const
{
  QList<QCPLayoutElement*> result;
  const int elCount = elementCount();
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
  result.reserve(elCount);
#endif
  for (int i=0; i<elCount; ++i)
    result.append(elementAt(i));
  if (recursive)
  {
    for (int i=0; i<elCount; ++i)
    {
      if (result.at(i))
        result << result.at(i)->elements(recursive);
    }
  }
  return result;
}

/*!
  Simplifies the layout by collapsing rows and columns which only contain empty cells.
*/
void QCPLayoutGrid::simplify()
{
  // remove rows with only empty cells:
  for (int row=rowCount()-1; row>=0; --row)
  {
    bool hasElements = false;
    for (int col=0; col<columnCount(); ++col)
    {
      if (mElements.at(row).at(col))
      {
        hasElements = true;
        break;
      }
    }
    if (!hasElements)
    {
      mRowStretchFactors.removeAt(row);
      mElements.removeAt(row);
      if (mElements.isEmpty()) // removed last element, also remove stretch factor (wouldn't happen below because also columnCount changed to 0 now)
        mColumnStretchFactors.clear();
    }
  }
  
  // remove columns with only empty cells:
  for (int col=columnCount()-1; col>=0; --col)
  {
    bool hasElements = false;
    for (int row=0; row<rowCount(); ++row)
    {
      if (mElements.at(row).at(col))
      {
        hasElements = true;
        break;
      }
    }
    if (!hasElements)
    {
      mColumnStretchFactors.removeAt(col);
      for (int row=0; row<rowCount(); ++row)
        mElements[row].removeAt(col);
    }
  }
}

/* inherits documentation from base class */
QSize QCPLayoutGrid::minimumOuterSizeHint() const
{
  QVector<int> minColWidths, minRowHeights;
  getMinimumRowColSizes(&minColWidths, &minRowHeights);
  QSize result(0, 0);
  foreach (int w, minColWidths)
    result.rwidth() += w;
  foreach (int h, minRowHeights)
    result.rheight() += h;
  result.rwidth() += qMax(0, columnCount()-1) * mColumnSpacing;
  result.rheight() += qMax(0, rowCount()-1) * mRowSpacing;
  result.rwidth() += mMargins.left()+mMargins.right();
  result.rheight() += mMargins.top()+mMargins.bottom();
  return result;
}

/* inherits documentation from base class */
QSize QCPLayoutGrid::maximumOuterSizeHint() const
{
  QVector<int> maxColWidths, maxRowHeights;
  getMaximumRowColSizes(&maxColWidths, &maxRowHeights);
  
  QSize result(0, 0);
  foreach (int w, maxColWidths)
    result.setWidth(qMin(result.width()+w, QWIDGETSIZE_MAX));
  foreach (int h, maxRowHeights)
    result.setHeight(qMin(result.height()+h, QWIDGETSIZE_MAX));
  result.rwidth() += qMax(0, columnCount()-1) * mColumnSpacing;
  result.rheight() += qMax(0, rowCount()-1) * mRowSpacing;
  result.rwidth() += mMargins.left()+mMargins.right();
  result.rheight() += mMargins.top()+mMargins.bottom();
  if (result.height() > QWIDGETSIZE_MAX)
    result.setHeight(QWIDGETSIZE_MAX);
  if (result.width() > QWIDGETSIZE_MAX)
    result.setWidth(QWIDGETSIZE_MAX);
  return result;
}

/*! \internal
  
  Places the minimum column widths and row heights into \a minColWidths and \a minRowHeights
  respectively.
  
  The minimum height of a row is the largest minimum height of any element's outer rect in that
  row. The minimum width of a column is the largest minimum width of any element's outer rect in
  that column.
  
  This is a helper function for \ref updateLayout.
  
  \see getMaximumRowColSizes
*/
void QCPLayoutGrid::getMinimumRowColSizes(QVector<int> *minColWidths, QVector<int> *minRowHeights) const
{
  *minColWidths = QVector<int>(columnCount(), 0);
  *minRowHeights = QVector<int>(rowCount(), 0);
  for (int row=0; row<rowCount(); ++row)
  {
    for (int col=0; col<columnCount(); ++col)
    {
      if (QCPLayoutElement *el = mElements.at(row).at(col))
      {
        QSize minSize = getFinalMinimumOuterSize(el);
        if (minColWidths->at(col) < minSize.width())
          (*minColWidths)[col] = minSize.width();
        if (minRowHeights->at(row) < minSize.height())
          (*minRowHeights)[row] = minSize.height();
      }
    }
  }
}

/*! \internal
  
  Places the maximum column widths and row heights into \a maxColWidths and \a maxRowHeights
  respectively.
  
  The maximum height of a row is the smallest maximum height of any element's outer rect in that
  row. The maximum width of a column is the smallest maximum width of any element's outer rect in
  that column.
  
  This is a helper function for \ref updateLayout.
  
  \see getMinimumRowColSizes
*/
void QCPLayoutGrid::getMaximumRowColSizes(QVector<int> *maxColWidths, QVector<int> *maxRowHeights) const
{
  *maxColWidths = QVector<int>(columnCount(), QWIDGETSIZE_MAX);
  *maxRowHeights = QVector<int>(rowCount(), QWIDGETSIZE_MAX);
  for (int row=0; row<rowCount(); ++row)
  {
    for (int col=0; col<columnCount(); ++col)
    {
      if (QCPLayoutElement *el = mElements.at(row).at(col))
      {
        QSize maxSize = getFinalMaximumOuterSize(el);
        if (maxColWidths->at(col) > maxSize.width())
          (*maxColWidths)[col] = maxSize.width();
        if (maxRowHeights->at(row) > maxSize.height())
          (*maxRowHeights)[row] = maxSize.height();
      }
    }
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPLayoutInset
////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \class QCPLayoutInset
  \brief A layout that places child elements aligned to the border or arbitrarily positioned
  
  Elements are placed either aligned to the border or at arbitrary position in the area of the
  layout. Which placement applies is controlled with the \ref InsetPlacement (\ref
  setInsetPlacement).

  Elements are added via \ref addElement(QCPLayoutElement *element, Qt::Alignment alignment) or
  addElement(QCPLayoutElement *element, const QRectF &rect). If the first method is used, the inset
  placement will default to \ref ipBorderAligned and the element will be aligned according to the
  \a alignment parameter. The second method defaults to \ref ipFree and allows placing elements at
  arbitrary position and size, defined by \a rect.
  
  The alignment or rect can be set via \ref setInsetAlignment or \ref setInsetRect, respectively.
  
  This is the layout that every QCPAxisRect has as \ref QCPAxisRect::insetLayout.
*/

/* start documentation of inline functions */

/*! \fn virtual void QCPLayoutInset::simplify()
  
  The QCPInsetLayout does not need simplification since it can never have empty cells due to its
  linear index structure. This method does nothing.
*/

/* end documentation of inline functions */

/*!
  Creates an instance of QCPLayoutInset and sets default values.
*/
QCPLayoutInset::QCPLayoutInset()
{
}

QCPLayoutInset::~QCPLayoutInset()
{
  // clear all child layout elements. This is important because only the specific layouts know how
  // to handle removing elements (clear calls virtual removeAt method to do that).
  clear();
}

/*!
  Returns the placement type of the element with the specified \a index.
*/
QCPLayoutInset::InsetPlacement QCPLayoutInset::insetPlacement(int index) const
{
  if (elementAt(index))
    return mInsetPlacement.at(index);
  else
  {
    qDebug() << Q_FUNC_INFO << "Invalid element index:" << index;
    return ipFree;
  }
}

/*!
  Returns the alignment of the element with the specified \a index. The alignment only has a
  meaning, if the inset placement (\ref setInsetPlacement) is \ref ipBorderAligned.
*/
Qt::Alignment QCPLayoutInset::insetAlignment(int index) const
{
  if (elementAt(index))
    return mInsetAlignment.at(index);
  else
  {
    qDebug() << Q_FUNC_INFO << "Invalid element index:" << index;
#if QT_VERSION < QT_VERSION_CHECK(5, 2, 0)
    return nullptr;
#else
    return {};
#endif
  }
}

/*!
  Returns the rect of the element with the specified \a index. The rect only has a
  meaning, if the inset placement (\ref setInsetPlacement) is \ref ipFree.
*/
QRectF QCPLayoutInset::insetRect(int index) const
{
  if (elementAt(index))
    return mInsetRect.at(index);
  else
  {
    qDebug() << Q_FUNC_INFO << "Invalid element index:" << index;
    return {};
  }
}

/*!
  Sets the inset placement type of the element with the specified \a index to \a placement.
  
  \see InsetPlacement
*/
void QCPLayoutInset::setInsetPlacement(int index, QCPLayoutInset::InsetPlacement placement)
{
  if (elementAt(index))
    mInsetPlacement[index] = placement;
  else
    qDebug() << Q_FUNC_INFO << "Invalid element index:" << index;
}

/*!
  If the inset placement (\ref setInsetPlacement) is \ref ipBorderAligned, this function
  is used to set the alignment of the element with the specified \a index to \a alignment.
  
  \a alignment is an or combination of the following alignment flags: Qt::AlignLeft,
  Qt::AlignHCenter, Qt::AlighRight, Qt::AlignTop, Qt::AlignVCenter, Qt::AlignBottom. Any other
  alignment flags will be ignored.
*/
void QCPLayoutInset::setInsetAlignment(int index, Qt::Alignment alignment)
{
  if (elementAt(index))
    mInsetAlignment[index] = alignment;
  else
    qDebug() << Q_FUNC_INFO << "Invalid element index:" << index;
}

/*!
  If the inset placement (\ref setInsetPlacement) is \ref ipFree, this function is used to set the
  position and size of the element with the specified \a index to \a rect.
  
  \a rect is given in fractions of the whole inset layout rect. So an inset with rect (0, 0, 1, 1)
  will span the entire layout. An inset with rect (0.6, 0.1, 0.35, 0.35) will be in the top right
  corner of the layout, with 35% width and height of the parent layout.
  
  Note that the minimum and maximum sizes of the embedded element (\ref
  QCPLayoutElement::setMinimumSize, \ref QCPLayoutElement::setMaximumSize) are enforced.
*/
void QCPLayoutInset::setInsetRect(int index, const QRectF &rect)
{
  if (elementAt(index))
    mInsetRect[index] = rect;
  else
    qDebug() << Q_FUNC_INFO << "Invalid element index:" << index;
}

/* inherits documentation from base class */
void QCPLayoutInset::updateLayout()
{
  for (int i=0; i<mElements.size(); ++i)
  {
    QCPLayoutElement *el = mElements.at(i);
    QRect insetRect;
    QSize finalMinSize = getFinalMinimumOuterSize(el);
    QSize finalMaxSize = getFinalMaximumOuterSize(el);
    if (mInsetPlacement.at(i) == ipFree)
    {
      insetRect = QRect(int( rect().x()+rect().width()*mInsetRect.at(i).x() ),
                        int( rect().y()+rect().height()*mInsetRect.at(i).y() ),
                        int( rect().width()*mInsetRect.at(i).width() ),
                        int( rect().height()*mInsetRect.at(i).height() ));
      if (insetRect.size().width() < finalMinSize.width())
        insetRect.setWidth(finalMinSize.width());
      if (insetRect.size().height() < finalMinSize.height())
        insetRect.setHeight(finalMinSize.height());
      if (insetRect.size().width() > finalMaxSize.width())
        insetRect.setWidth(finalMaxSize.width());
      if (insetRect.size().height() > finalMaxSize.height())
        insetRect.setHeight(finalMaxSize.height());
    } else if (mInsetPlacement.at(i) == ipBorderAligned)
    {
      insetRect.setSize(finalMinSize);
      Qt::Alignment al = mInsetAlignment.at(i);
      if (al.testFlag(Qt::AlignLeft)) insetRect.moveLeft(rect().x());
      else if (al.testFlag(Qt::AlignRight)) insetRect.moveRight(rect().x()+rect().width());
      else insetRect.moveLeft(int( rect().x()+rect().width()*0.5-finalMinSize.width()*0.5 )); // default to Qt::AlignHCenter
      if (al.testFlag(Qt::AlignTop)) insetRect.moveTop(rect().y());
      else if (al.testFlag(Qt::AlignBottom)) insetRect.moveBottom(rect().y()+rect().height());
      else insetRect.moveTop(int( rect().y()+rect().height()*0.5-finalMinSize.height()*0.5 )); // default to Qt::AlignVCenter
    }
    mElements.at(i)->setOuterRect(insetRect);
  }
}

/* inherits documentation from base class */
int QCPLayoutInset::elementCount() const
{
  return mElements.size();
}

/* inherits documentation from base class */
QCPLayoutElement *QCPLayoutInset::elementAt(int index) const
{
  if (index >= 0 && index < mElements.size())
    return mElements.at(index);
  else
    return nullptr;
}

/* inherits documentation from base class */
QCPLayoutElement *QCPLayoutInset::takeAt(int index)
{
  if (QCPLayoutElement *el = elementAt(index))
  {
    releaseElement(el);
    mElements.removeAt(index);
    mInsetPlacement.removeAt(index);
    mInsetAlignment.removeAt(index);
    mInsetRect.removeAt(index);
    return el;
  } else
  {
    qDebug() << Q_FUNC_INFO << "Attempt to take invalid index:" << index;
    return nullptr;
  }
}

/* inherits documentation from base class */
bool QCPLayoutInset::take(QCPLayoutElement *element)
{
  if (element)
  {
    for (int i=0; i<elementCount(); ++i)
    {
      if (elementAt(i) == element)
      {
        takeAt(i);
        return true;
      }
    }
    qDebug() << Q_FUNC_INFO << "Element not in this layout, couldn't take";
  } else
    qDebug() << Q_FUNC_INFO << "Can't take nullptr element";
  return false;
}

/*!
  The inset layout is sensitive to events only at areas where its (visible) child elements are
  sensitive. If the selectTest method of any of the child elements returns a positive number for \a
  pos, this method returns a value corresponding to 0.99 times the parent plot's selection
  tolerance. The inset layout is not selectable itself by default. So if \a onlySelectable is true,
  -1.0 is returned.
  
  See \ref QCPLayerable::selectTest for a general explanation of this virtual method.
*/
double QCPLayoutInset::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const
{
  Q_UNUSED(details)
  if (onlySelectable)
    return -1;
  
  foreach (QCPLayoutElement *el, mElements)
  {
    // inset layout shall only return positive selectTest, if actually an inset object is at pos
    // else it would block the entire underlying QCPAxisRect with its surface.
    if (el->realVisibility() && el->selectTest(pos, onlySelectable) >= 0)
      return mParentPlot->selectionTolerance()*0.99;
  }
  return -1;
}

/*!
  Adds the specified \a element to the layout as an inset aligned at the border (\ref
  setInsetAlignment is initialized with \ref ipBorderAligned). The alignment is set to \a
  alignment.
  
  \a alignment is an or combination of the following alignment flags: Qt::AlignLeft,
  Qt::AlignHCenter, Qt::AlighRight, Qt::AlignTop, Qt::AlignVCenter, Qt::AlignBottom. Any other
  alignment flags will be ignored.
  
  \see addElement(QCPLayoutElement *element, const QRectF &rect)
*/
void QCPLayoutInset::addElement(QCPLayoutElement *element, Qt::Alignment alignment)
{
  if (element)
  {
    if (element->layout()) // remove from old layout first
      element->layout()->take(element);
    mElements.append(element);
    mInsetPlacement.append(ipBorderAligned);
    mInsetAlignment.append(alignment);
    mInsetRect.append(QRectF(0.6, 0.6, 0.4, 0.4));
    adoptElement(element);
  } else
    qDebug() << Q_FUNC_INFO << "Can't add nullptr element";
}

/*!
  Adds the specified \a element to the layout as an inset with free positioning/sizing (\ref
  setInsetAlignment is initialized with \ref ipFree). The position and size is set to \a
  rect.
  
  \a rect is given in fractions of the whole inset layout rect. So an inset with rect (0, 0, 1, 1)
  will span the entire layout. An inset with rect (0.6, 0.1, 0.35, 0.35) will be in the top right
  corner of the layout, with 35% width and height of the parent layout.
  
  \see addElement(QCPLayoutElement *element, Qt::Alignment alignment)
*/
void QCPLayoutInset::addElement(QCPLayoutElement *element, const QRectF &rect)
{
  if (element)
  {
    if (element->layout()) // remove from old layout first
      element->layout()->take(element);
    mElements.append(element);
    mInsetPlacement.append(ipFree);
    mInsetAlignment.append(Qt::AlignRight|Qt::AlignTop);
    mInsetRect.append(rect);
    adoptElement(element);
  } else
    qDebug() << Q_FUNC_INFO << "Can't add nullptr element";
}
/* end of 'src/layout.cpp' */


/* including file 'src/lineending.cpp'      */
/* modified 2022-11-06T12:45:56, size 11189 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPLineEnding
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPLineEnding
  \brief Handles the different ending decorations for line-like items
  
  \image html QCPLineEnding.png "The various ending styles currently supported"
  
  For every ending a line-like item has, an instance of this class exists. For example, QCPItemLine
  has two endings which can be set with QCPItemLine::setHead and QCPItemLine::setTail.
 
  The styles themselves are defined via the enum QCPLineEnding::EndingStyle. Most decorations can
  be modified regarding width and length, see \ref setWidth and \ref setLength. The direction of
  the ending decoration (e.g. direction an arrow is pointing) is controlled by the line-like item.
  For example, when both endings of a QCPItemLine are set to be arrows, they will point to opposite
  directions, e.g. "outward". This can be changed by \ref setInverted, which would make the
  respective arrow point inward.
  
  Note that due to the overloaded QCPLineEnding constructor, you may directly specify a
  QCPLineEnding::EndingStyle where actually a QCPLineEnding is expected, e.g.
  \snippet documentation/doc-code-snippets/mainwindow.cpp qcplineending-sethead
*/

/*!
  Creates a QCPLineEnding instance with default values (style \ref esNone).
*/
QCPLineEnding::QCPLineEnding() :
  mStyle(esNone),
  mWidth(8),
  mLength(10),
  mInverted(false)
{
}

/*!
  Creates a QCPLineEnding instance with the specified values.
*/
QCPLineEnding::QCPLineEnding(QCPLineEnding::EndingStyle style, double width, double length, bool inverted) :
  mStyle(style),
  mWidth(width),
  mLength(length),
  mInverted(inverted)
{
}

/*!
  Sets the style of the ending decoration.
*/
void QCPLineEnding::setStyle(QCPLineEnding::EndingStyle style)
{
  mStyle = style;
}

/*!
  Sets the width of the ending decoration, if the style supports it. On arrows, for example, the
  width defines the size perpendicular to the arrow's pointing direction.
  
  \see setLength
*/
void QCPLineEnding::setWidth(double width)
{
  mWidth = width;
}

/*!
  Sets the length of the ending decoration, if the style supports it. On arrows, for example, the
  length defines the size in pointing direction.
  
  \see setWidth
*/
void QCPLineEnding::setLength(double length)
{
  mLength = length;
}

/*!
  Sets whether the ending decoration shall be inverted. For example, an arrow decoration will point
  inward when \a inverted is set to true.

  Note that also the \a width direction is inverted. For symmetrical ending styles like arrows or
  discs, this doesn't make a difference. However, asymmetric styles like \ref esHalfBar are
  affected by it, which can be used to control to which side the half bar points to.
*/
void QCPLineEnding::setInverted(bool inverted)
{
  mInverted = inverted;
}

/*! \internal
  
  Returns the maximum pixel radius the ending decoration might cover, starting from the position
  the decoration is drawn at (typically a line ending/\ref QCPItemPosition of an item).
  
  This is relevant for clipping. Only omit painting of the decoration when the position where the
  decoration is supposed to be drawn is farther away from the clipping rect than the returned
  distance.
*/
double QCPLineEnding::boundingDistance() const
{
  switch (mStyle)
  {
    case esNone:
      return 0;
      
    case esFlatArrow:
    case esSpikeArrow:
    case esLineArrow:
    case esSkewedBar:
      return qSqrt(mWidth*mWidth+mLength*mLength); // items that have width and length
      
    case esDisc:
    case esSquare:
    case esDiamond:
    case esBar:
    case esHalfBar:
      return mWidth*1.42; // items that only have a width -> width*sqrt(2)

  }
  return 0;
}

/*!
  Starting from the origin of this line ending (which is style specific), returns the length
  covered by the line ending symbol, in backward direction.
  
  For example, the \ref esSpikeArrow has a shorter real length than a \ref esFlatArrow, even if
  both have the same \ref setLength value, because the spike arrow has an inward curved back, which
  reduces the length along its center axis (the drawing origin for arrows is at the tip).
  
  This function is used for precise, style specific placement of line endings, for example in
  QCPAxes.
*/
double QCPLineEnding::realLength() const
{
  switch (mStyle)
  {
    case esNone:
    case esLineArrow:
    case esSkewedBar:
    case esBar:
    case esHalfBar:
      return 0;
      
    case esFlatArrow:
      return mLength;
      
    case esDisc:
    case esSquare:
    case esDiamond:
      return mWidth*0.5;
      
    case esSpikeArrow:
      return mLength*0.8;
  }
  return 0;
}

/*! \internal
  
  Draws the line ending with the specified \a painter at the position \a pos. The direction of the
  line ending is controlled with \a dir.
*/
void QCPLineEnding::draw(QCPPainter *painter, const QCPVector2D &pos, const QCPVector2D &dir) const
{
  if (mStyle == esNone)
    return;
  
  QCPVector2D lengthVec = dir.normalized() * mLength*(mInverted ? -1 : 1);
  if (lengthVec.isNull())
    lengthVec = QCPVector2D(1, 0);
  QCPVector2D widthVec = dir.normalized().perpendicular() * mWidth*0.5*(mInverted ? -1 : 1);
  
  QPen penBackup = painter->pen();
  QBrush brushBackup = painter->brush();
  QPen miterPen = penBackup;
  miterPen.setJoinStyle(Qt::MiterJoin); // to make arrow heads spikey
  QBrush brush(painter->pen().color(), Qt::SolidPattern);
  switch (mStyle)
  {
    case esNone: break;
    case esFlatArrow:
    {
      QPointF points[3] = {pos.toPointF(),
                           (pos-lengthVec+widthVec).toPointF(),
                           (pos-lengthVec-widthVec).toPointF()
                          };
      painter->setPen(miterPen);
      painter->setBrush(brush);
      painter->drawConvexPolygon(points, 3);
      painter->setBrush(brushBackup);
      painter->setPen(penBackup);
      break;
    }
    case esSpikeArrow:
    {
      QPointF points[4] = {pos.toPointF(),
                           (pos-lengthVec+widthVec).toPointF(),
                           (pos-lengthVec*0.8).toPointF(),
                           (pos-lengthVec-widthVec).toPointF()
                          };
      painter->setPen(miterPen);
      painter->setBrush(brush);
      painter->drawConvexPolygon(points, 4);
      painter->setBrush(brushBackup);
      painter->setPen(penBackup);
      break;
    }
    case esLineArrow:
    {
      QPointF points[3] = {(pos-lengthVec+widthVec).toPointF(),
                           pos.toPointF(),
                           (pos-lengthVec-widthVec).toPointF()
                          };
      painter->setPen(miterPen);
      painter->drawPolyline(points, 3);
      painter->setPen(penBackup);
      break;
    }
    case esDisc:
    {
      painter->setBrush(brush);
      painter->drawEllipse(pos.toPointF(),  mWidth*0.5, mWidth*0.5);
      painter->setBrush(brushBackup);
      break;
    }
    case esSquare:
    {
      QCPVector2D widthVecPerp = widthVec.perpendicular();
      QPointF points[4] = {(pos-widthVecPerp+widthVec).toPointF(),
                           (pos-widthVecPerp-widthVec).toPointF(),
                           (pos+widthVecPerp-widthVec).toPointF(),
                           (pos+widthVecPerp+widthVec).toPointF()
                          };
      painter->setPen(miterPen);
      painter->setBrush(brush);
      painter->drawConvexPolygon(points, 4);
      painter->setBrush(brushBackup);
      painter->setPen(penBackup);
      break;
    }
    case esDiamond:
    {
      QCPVector2D widthVecPerp = widthVec.perpendicular();
      QPointF points[4] = {(pos-widthVecPerp).toPointF(),
                           (pos-widthVec).toPointF(),
                           (pos+widthVecPerp).toPointF(),
                           (pos+widthVec).toPointF()
                          };
      painter->setPen(miterPen);
      painter->setBrush(brush);
      painter->drawConvexPolygon(points, 4);
      painter->setBrush(brushBackup);
      painter->setPen(penBackup);
      break;
    }
    case esBar:
    {
      painter->drawLine((pos+widthVec).toPointF(), (pos-widthVec).toPointF());
      break;
    }
    case esHalfBar:
    {
      painter->drawLine((pos+widthVec).toPointF(), pos.toPointF());
      break;
    }
    case esSkewedBar:
    {
      QCPVector2D shift;
      if (!qFuzzyIsNull(painter->pen().widthF()) || painter->modes().testFlag(QCPPainter::pmNonCosmetic))
        shift = dir.normalized()*qMax(qreal(1.0), painter->pen().widthF())*qreal(0.5);
      // if drawing with thick (non-cosmetic) pen, shift bar a little in line direction to prevent line from sticking through bar slightly
      painter->drawLine((pos+widthVec+lengthVec*0.2*(mInverted?-1:1)+shift).toPointF(),
                        (pos-widthVec-lengthVec*0.2*(mInverted?-1:1)+shift).toPointF());
      break;
    }
  }
}

/*! \internal
  \overload
  
  Draws the line ending. The direction is controlled with the \a angle parameter in radians.
*/
void QCPLineEnding::draw(QCPPainter *painter, const QCPVector2D &pos, double angle) const
{
  draw(painter, pos, QCPVector2D(qCos(angle), qSin(angle)));
}
/* end of 'src/lineending.cpp' */


/* including file 'src/axis/labelpainter.cpp' */
/* modified 2022-11-06T12:45:56, size 27519   */


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPLabelPainterPrivate
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPLabelPainterPrivate

  \internal
  \brief (Private)
  
  This is a private class and not part of the public QCustomPlot interface.
  
*/

const QChar QCPLabelPainterPrivate::SymbolDot(183);
const QChar QCPLabelPainterPrivate::SymbolCross(215);

/*!
  Constructs a QCPLabelPainterPrivate instance. Make sure to not create a new
  instance on every redraw, to utilize the caching mechanisms.
  
  the \a parentPlot does not take ownership of the label painter. Make sure
  to delete it appropriately.
*/
QCPLabelPainterPrivate::QCPLabelPainterPrivate(QCustomPlot *parentPlot) :
  mAnchorMode(amRectangular),
  mAnchorSide(asLeft),
  mAnchorReferenceType(artNormal),
  mColor(Qt::black),
  mPadding(0),
  mRotation(0),
  mSubstituteExponent(true),
  mMultiplicationSymbol(QChar(215)),
  mAbbreviateDecimalPowers(false),
  mParentPlot(parentPlot),
  mLabelCache(16)
{
  analyzeFontMetrics();
}

QCPLabelPainterPrivate::~QCPLabelPainterPrivate()
{
}

void QCPLabelPainterPrivate::setAnchorSide(AnchorSide side)
{
  mAnchorSide = side;
}

void QCPLabelPainterPrivate::setAnchorMode(AnchorMode mode)
{
  mAnchorMode = mode;
}

void QCPLabelPainterPrivate::setAnchorReference(const QPointF &pixelPoint)
{
  mAnchorReference = pixelPoint;
}

void QCPLabelPainterPrivate::setAnchorReferenceType(AnchorReferenceType type)
{
  mAnchorReferenceType = type;
}

void QCPLabelPainterPrivate::setFont(const QFont &font)
{
  if (mFont != font)
  {
    mFont = font;
    analyzeFontMetrics();
  }
}

void QCPLabelPainterPrivate::setColor(const QColor &color)
{
  mColor = color;
}

void QCPLabelPainterPrivate::setPadding(int padding)
{
  mPadding = padding;
}

void QCPLabelPainterPrivate::setRotation(double rotation)
{
  mRotation = qBound(-90.0, rotation, 90.0);
}

void QCPLabelPainterPrivate::setSubstituteExponent(bool enabled)
{
  mSubstituteExponent = enabled;
}

void QCPLabelPainterPrivate::setMultiplicationSymbol(QChar symbol)
{
  mMultiplicationSymbol = symbol;
}

void QCPLabelPainterPrivate::setAbbreviateDecimalPowers(bool enabled)
{
  mAbbreviateDecimalPowers = enabled;
}

void QCPLabelPainterPrivate::setCacheSize(int labelCount)
{
  mLabelCache.setMaxCost(labelCount);
}

int QCPLabelPainterPrivate::cacheSize() const
{
  return mLabelCache.maxCost();
}

void QCPLabelPainterPrivate::drawTickLabel(QCPPainter *painter, const QPointF &tickPos, const QString &text)
{
  double realRotation = mRotation;
  
  AnchorSide realSide = mAnchorSide;
  // for circular axes, the anchor side is determined depending on the quadrant of tickPos with respect to mCircularReference
  if (mAnchorMode == amSkewedUpright)
  {
    realSide = skewedAnchorSide(tickPos, 0.2, 0.3); 
  } else if (mAnchorMode == amSkewedRotated) // in this mode every label is individually rotated to match circle tangent
  {
    realSide = skewedAnchorSide(tickPos, 0, 0);
    realRotation += QCPVector2D(tickPos-mAnchorReference).angle()/M_PI*180.0;
    if (realRotation > 90) realRotation -= 180;
    else if (realRotation < -90) realRotation += 180;
  }
  
  realSide = rotationCorrectedSide(realSide, realRotation); // rotation angles may change the true anchor side of the label
  drawLabelMaybeCached(painter, mFont, mColor, getAnchorPos(tickPos), realSide, realRotation, text);
}

/*! \internal
  
  Returns the size ("margin" in QCPAxisRect context, so measured perpendicular to the axis backbone
  direction) needed to fit the axis.
*/
/* TODO: needed?
int QCPLabelPainterPrivate::size() const
{
  int result = 0;
  // get length of tick marks pointing outwards:
  if (!tickPositions.isEmpty())
    result += qMax(0, qMax(tickLengthOut, subTickLengthOut));
  
  // calculate size of tick labels:
  if (tickLabelSide == QCPAxis::lsOutside)
  {
    QSize tickLabelsSize(0, 0);
    if (!tickLabels.isEmpty())
    {
      for (int i=0; i<tickLabels.size(); ++i)
        getMaxTickLabelSize(tickLabelFont, tickLabels.at(i), &tickLabelsSize);
      result += QCPAxis::orientation(type) == Qt::Horizontal ? tickLabelsSize.height() : tickLabelsSize.width();
    result += tickLabelPadding;
    }
  }
  
  // calculate size of axis label (only height needed, because left/right labels are rotated by 90 degrees):
  if (!label.isEmpty())
  {
    QFontMetrics fontMetrics(labelFont);
    QRect bounds;
    bounds = fontMetrics.boundingRect(0, 0, 0, 0, Qt::TextDontClip | Qt::AlignHCenter | Qt::AlignVCenter, label);
    result += bounds.height() + labelPadding;
  }

  return result;
}
*/

/*! \internal
  
  Clears the internal label cache. Upon the next \ref draw, all labels will be created new. This
  method is called automatically if any parameters have changed that invalidate the cached labels,
  such as font, color, etc. Usually you won't need to call this method manually.
*/
void QCPLabelPainterPrivate::clearCache()
{
  mLabelCache.clear();
}

/*! \internal
  
  Returns a hash that allows uniquely identifying whether the label parameters have changed such
  that the cached labels must be refreshed (\ref clearCache). It is used in \ref draw. If the
  return value of this method hasn't changed since the last redraw, the respective label parameters
  haven't changed and cached labels may be used.
*/
QByteArray QCPLabelPainterPrivate::generateLabelParameterHash() const
{
  QByteArray result;
  result.append(QByteArray::number(mParentPlot->bufferDevicePixelRatio()));
  result.append(QByteArray::number(mRotation));
  //result.append(QByteArray::number(int(tickLabelSide))); TODO: check whether this is really a cache-invalidating property
  result.append(QByteArray::number(int(mSubstituteExponent)));
  result.append(QString(mMultiplicationSymbol).toUtf8());
  result.append(mColor.name().toLatin1()+QByteArray::number(mColor.alpha(), 16));
  result.append(mFont.toString().toLatin1());
  return result;
}

/*! \internal
  
  Draws a single tick label with the provided \a painter, utilizing the internal label cache to
  significantly speed up drawing of labels that were drawn in previous calls. The tick label is
  always bound to an axis, the distance to the axis is controllable via \a distanceToAxis in
  pixels. The pixel position in the axis direction is passed in the \a position parameter. Hence
  for the bottom axis, \a position would indicate the horizontal pixel position (not coordinate),
  at which the label should be drawn.
  
  In order to later draw the axis label in a place that doesn't overlap with the tick labels, the
  largest tick label size is needed. This is acquired by passing a \a tickLabelsSize to the \ref
  drawTickLabel calls during the process of drawing all tick labels of one axis. In every call, \a
  tickLabelsSize is expanded, if the drawn label exceeds the value \a tickLabelsSize currently
  holds.
  
  The label is drawn with the font and pen that are currently set on the \a painter. To draw
  superscripted powers, the font is temporarily made smaller by a fixed factor (see \ref
  getTickLabelData).
*/
void QCPLabelPainterPrivate::drawLabelMaybeCached(QCPPainter *painter, const QFont &font, const QColor &color, const QPointF &pos, AnchorSide side, double rotation, const QString &text)
{
  // warning: if you change anything here, also adapt getMaxTickLabelSize() accordingly!
  if (text.isEmpty()) return;
  QSize finalSize;

  if (mParentPlot->plottingHints().testFlag(QCP::phCacheLabels) && !painter->modes().testFlag(QCPPainter::pmNoCaching)) // label caching enabled
  {
    QByteArray key = cacheKey(text, color, rotation, side);
    CachedLabel *cachedLabel = mLabelCache.take(QString::fromUtf8(key)); // attempt to take label from cache (don't use object() because we want ownership/prevent deletion during our operations, we re-insert it afterwards)
    if (!cachedLabel)  // no cached label existed, create it
    {
      LabelData labelData = getTickLabelData(font, color, rotation, side, text);
      cachedLabel = createCachedLabel(labelData);
    }
    // if label would be partly clipped by widget border on sides, don't draw it (only for outside tick labels):
    bool labelClippedByBorder = false;
    /*
    if (tickLabelSide == QCPAxis::lsOutside)
    {
      if (QCPAxis::orientation(type) == Qt::Horizontal)
        labelClippedByBorder = labelAnchor.x()+cachedLabel->offset.x()+cachedLabel->pixmap.width()/mParentPlot->bufferDevicePixelRatio() > viewportRect.right() || labelAnchor.x()+cachedLabel->offset.x() < viewportRect.left();
      else
        labelClippedByBorder = labelAnchor.y()+cachedLabel->offset.y()+cachedLabel->pixmap.height()/mParentPlot->bufferDevicePixelRatio() > viewportRect.bottom() || labelAnchor.y()+cachedLabel->offset.y() < viewportRect.top();
    }
    */
    if (!labelClippedByBorder)
    {
      painter->drawPixmap(pos+cachedLabel->offset, cachedLabel->pixmap);
      finalSize = cachedLabel->pixmap.size()/mParentPlot->bufferDevicePixelRatio(); // TODO: collect this in a member rect list?
    }
    mLabelCache.insert(QString::fromUtf8(key), cachedLabel);
  } else // label caching disabled, draw text directly on surface:
  {
    LabelData labelData = getTickLabelData(font, color, rotation, side, text);
    // if label would be partly clipped by widget border on sides, don't draw it (only for outside tick labels):
     bool labelClippedByBorder = false;
     /*
    if (tickLabelSide == QCPAxis::lsOutside)
    {
      if (QCPAxis::orientation(type) == Qt::Horizontal)
        labelClippedByBorder = finalPosition.x()+(labelData.rotatedTotalBounds.width()+labelData.rotatedTotalBounds.left()) > viewportRect.right() || finalPosition.x()+labelData.rotatedTotalBounds.left() < viewportRect.left();
      else
        labelClippedByBorder = finalPosition.y()+(labelData.rotatedTotalBounds.height()+labelData.rotatedTotalBounds.top()) > viewportRect.bottom() || finalPosition.y()+labelData.rotatedTotalBounds.top() < viewportRect.top();
    }
    */
    if (!labelClippedByBorder)
    {
      drawText(painter, pos, labelData);
      finalSize = labelData.rotatedTotalBounds.size();
    }
  }
  /*
  // expand passed tickLabelsSize if current tick label is larger:
  if (finalSize.width() > tickLabelsSize->width())
    tickLabelsSize->setWidth(finalSize.width());
  if (finalSize.height() > tickLabelsSize->height())
    tickLabelsSize->setHeight(finalSize.height());
  */
}

QPointF QCPLabelPainterPrivate::getAnchorPos(const QPointF &tickPos)
{
  switch (mAnchorMode)
  {
    case amRectangular:
    {
      switch (mAnchorSide)
      {
        case asLeft:   return tickPos+QPointF(mPadding, 0);
        case asRight:  return tickPos+QPointF(-mPadding, 0);
        case asTop:    return tickPos+QPointF(0, mPadding);
        case asBottom: return tickPos+QPointF(0, -mPadding);
        case asTopLeft:     return tickPos+QPointF(mPadding*M_SQRT1_2, mPadding*M_SQRT1_2);
        case asTopRight:    return tickPos+QPointF(-mPadding*M_SQRT1_2, mPadding*M_SQRT1_2);
        case asBottomRight: return tickPos+QPointF(-mPadding*M_SQRT1_2, -mPadding*M_SQRT1_2);
        case asBottomLeft:  return tickPos+QPointF(mPadding*M_SQRT1_2, -mPadding*M_SQRT1_2);
        default: qDebug() << Q_FUNC_INFO << "invalid mode for anchor side: " << mAnchorSide; break;
      }
      break;
    }
    case amSkewedUpright:
      // fall through
    case amSkewedRotated:
    {
      QCPVector2D anchorNormal(tickPos-mAnchorReference);
      if (mAnchorReferenceType == artTangent)
        anchorNormal = anchorNormal.perpendicular();
      anchorNormal.normalize();
      return tickPos+(anchorNormal*mPadding).toPointF();
    }
    default: qDebug() << Q_FUNC_INFO << "invalid mode for anchor mode: " << mAnchorMode; break;
  }
  return tickPos;
}

/*! \internal
  
  This is a \ref placeTickLabel helper function.
  
  Draws the tick label specified in \a labelData with \a painter at the pixel positions \a x and \a
  y. This function is used by \ref placeTickLabel to create new tick labels for the cache, or to
  directly draw the labels on the QCustomPlot surface when label caching is disabled, i.e. when
  QCP::phCacheLabels plotting hint is not set.
*/
void QCPLabelPainterPrivate::drawText(QCPPainter *painter, const QPointF &pos, const LabelData &labelData) const
{
  // backup painter settings that we're about to change:
  QTransform oldTransform = painter->transform();
  QFont oldFont = painter->font();
  QPen oldPen = painter->pen();
  
  // transform painter to position/rotation:
  painter->translate(pos);
  painter->setTransform(labelData.transform, true);
  
  // draw text:
  painter->setFont(labelData.baseFont);
  painter->setPen(QPen(labelData.color));
  if (!labelData.expPart.isEmpty()) // use superscripted exponent typesetting
  {
    painter->drawText(0, 0, 0, 0, Qt::TextDontClip, labelData.basePart);
    if (!labelData.suffixPart.isEmpty())
      painter->drawText(labelData.baseBounds.width()+1+labelData.expBounds.width(), 0, 0, 0, Qt::TextDontClip, labelData.suffixPart);
    painter->setFont(labelData.expFont);
    painter->drawText(labelData.baseBounds.width()+1, 0, labelData.expBounds.width(), labelData.expBounds.height(), Qt::TextDontClip,  labelData.expPart);
  } else
  {
    painter->drawText(0, 0, labelData.totalBounds.width(), labelData.totalBounds.height(), Qt::TextDontClip | Qt::AlignHCenter, labelData.basePart);
  }
  
  /* Debug code to draw label bounding boxes, baseline, and capheight
  painter->save();
  painter->setPen(QPen(QColor(0, 0, 0, 150)));
  painter->drawRect(labelData.totalBounds);
  const int baseline = labelData.totalBounds.height()-mLetterDescent;
  painter->setPen(QPen(QColor(255, 0, 0, 150)));
  painter->drawLine(QLineF(0, baseline, labelData.totalBounds.width(), baseline));
  painter->setPen(QPen(QColor(0, 0, 255, 150)));
  painter->drawLine(QLineF(0, baseline-mLetterCapHeight, labelData.totalBounds.width(), baseline-mLetterCapHeight));
  painter->restore();
  */
  
  // reset painter settings to what it was before:
  painter->setTransform(oldTransform);
  painter->setFont(oldFont);
  painter->setPen(oldPen);
}

/*! \internal
  
  This is a \ref placeTickLabel helper function.
  
  Transforms the passed \a text and \a font to a tickLabelData structure that can then be further
  processed by \ref getTickLabelDrawOffset and \ref drawTickLabel. It splits the text into base and
  exponent if necessary (member substituteExponent) and calculates appropriate bounding boxes.
*/
QCPLabelPainterPrivate::LabelData QCPLabelPainterPrivate::getTickLabelData(const QFont &font, const QColor &color, double rotation, AnchorSide side, const QString &text) const
{
  LabelData result;
  result.rotation = rotation;
  result.side = side;
  result.color = color;
  
  // determine whether beautiful decimal powers should be used
  bool useBeautifulPowers = false;
  int ePos = -1; // first index of exponent part, text before that will be basePart, text until eLast will be expPart
  int eLast = -1; // last index of exponent part, rest of text after this will be suffixPart
  if (mSubstituteExponent)
  {
    ePos = text.indexOf(QLatin1Char('e'));
    if (ePos > 0 && text.at(ePos-1).isDigit())
    {
      eLast = ePos;
      while (eLast+1 < text.size() && (text.at(eLast+1) == QLatin1Char('+') || text.at(eLast+1) == QLatin1Char('-') || text.at(eLast+1).isDigit()))
        ++eLast;
      if (eLast > ePos) // only if also to right of 'e' is a digit/+/- interpret it as beautifiable power
        useBeautifulPowers = true;
    }
  }
  
  // calculate text bounding rects and do string preparation for beautiful decimal powers:
  result.baseFont = font;
  if (result.baseFont.pointSizeF() > 0) // might return -1 if specified with setPixelSize, in that case we can't do correction in next line
    result.baseFont.setPointSizeF(result.baseFont.pointSizeF()+0.05); // QFontMetrics.boundingRect has a bug for exact point sizes that make the results oscillate due to internal rounding
  
  QFontMetrics baseFontMetrics(result.baseFont);
  if (useBeautifulPowers)
  {
    // split text into parts of number/symbol that will be drawn normally and part that will be drawn as exponent:
    result.basePart = text.left(ePos);
    result.suffixPart = text.mid(eLast+1); // also drawn normally but after exponent
    // in log scaling, we want to turn "1*10^n" into "10^n", else add multiplication sign and decimal base:
    if (mAbbreviateDecimalPowers && result.basePart == QLatin1String("1"))
      result.basePart = QLatin1String("10");
    else
      result.basePart += QString(mMultiplicationSymbol) + QLatin1String("10");
    result.expPart = text.mid(ePos+1, eLast-ePos);
    // clip "+" and leading zeros off expPart:
    while (result.expPart.length() > 2 && result.expPart.at(1) == QLatin1Char('0')) // length > 2 so we leave one zero when numberFormatChar is 'e'
      result.expPart.remove(1, 1);
    if (!result.expPart.isEmpty() && result.expPart.at(0) == QLatin1Char('+'))
      result.expPart.remove(0, 1);
    // prepare smaller font for exponent:
    result.expFont = font;
    if (result.expFont.pointSize() > 0)
      result.expFont.setPointSize(result.expFont.pointSize()*0.75);
    else
      result.expFont.setPixelSize(result.expFont.pixelSize()*0.75);
    // calculate bounding rects of base part(s), exponent part and total one:
    result.baseBounds = baseFontMetrics.boundingRect(0, 0, 0, 0, Qt::TextDontClip, result.basePart);
    result.expBounds = QFontMetrics(result.expFont).boundingRect(0, 0, 0, 0, Qt::TextDontClip, result.expPart);
    if (!result.suffixPart.isEmpty())
      result.suffixBounds = QFontMetrics(result.baseFont).boundingRect(0, 0, 0, 0, Qt::TextDontClip, result.suffixPart);
    result.totalBounds = result.baseBounds.adjusted(0, 0, result.expBounds.width()+result.suffixBounds.width()+2, 0); // +2 consists of the 1 pixel spacing between base and exponent (see drawTickLabel) and an extra pixel to include AA
  } else // useBeautifulPowers == false
  {
    result.basePart = text;
    result.totalBounds = baseFontMetrics.boundingRect(0, 0, 0, 0, Qt::TextDontClip | Qt::AlignHCenter, result.basePart);
  }
  result.totalBounds.moveTopLeft(QPoint(0, 0));
  applyAnchorTransform(result);
  result.rotatedTotalBounds = result.transform.mapRect(result.totalBounds);
  
  return result;
}

void QCPLabelPainterPrivate::applyAnchorTransform(LabelData &labelData) const
{
  if (!qFuzzyIsNull(labelData.rotation))
    labelData.transform.rotate(labelData.rotation); // rotates effectively clockwise (due to flipped y axis of painter vs widget coordinate system)
  
  // from now on we translate in rotated label-local coordinate system.
  // shift origin of coordinate system to appropriate point on label:
  labelData.transform.translate(0, -labelData.totalBounds.height()+mLetterDescent+mLetterCapHeight); // shifts origin to true top of capital (or number) characters
  
  if (labelData.side == asLeft || labelData.side == asRight) // anchor is centered vertically
    labelData.transform.translate(0, -mLetterCapHeight/2.0);
  else if (labelData.side == asTop || labelData.side == asBottom) // anchor is centered horizontally
    labelData.transform.translate(-labelData.totalBounds.width()/2.0, 0);
  
  if (labelData.side == asTopRight || labelData.side == asRight || labelData.side == asBottomRight) // anchor is at right
    labelData.transform.translate(-labelData.totalBounds.width(), 0);
  if (labelData.side == asBottomLeft || labelData.side == asBottom || labelData.side == asBottomRight) // anchor is at bottom (no elseif!)
    labelData.transform.translate(0, -mLetterCapHeight);
}

/*! \internal
  
  Simulates the steps done by \ref placeTickLabel by calculating bounding boxes of the text label
  to be drawn, depending on number format etc. Since only the largest tick label is wanted for the
  margin calculation, the passed \a tickLabelsSize is only expanded, if it's currently set to a
  smaller width/height.
*/
/*
void QCPLabelPainterPrivate::getMaxTickLabelSize(const QFont &font, const QString &text,  QSize *tickLabelsSize) const
{
  // note: this function must return the same tick label sizes as the placeTickLabel function.
  QSize finalSize;
  if (mParentPlot->plottingHints().testFlag(QCP::phCacheLabels) && mLabelCache.contains(text)) // label caching enabled and have cached label
  {
    const CachedLabel *cachedLabel = mLabelCache.object(text);
    finalSize = cachedLabel->pixmap.size()/mParentPlot->bufferDevicePixelRatio();
  } else // label caching disabled or no label with this text cached:
  {
    // TODO: LabelData labelData = getTickLabelData(font, text);
    // TODO: finalSize = labelData.rotatedTotalBounds.size();
  }
  
  // expand passed tickLabelsSize if current tick label is larger:
  if (finalSize.width() > tickLabelsSize->width())
    tickLabelsSize->setWidth(finalSize.width());
  if (finalSize.height() > tickLabelsSize->height())
    tickLabelsSize->setHeight(finalSize.height());
}
*/

QCPLabelPainterPrivate::CachedLabel *QCPLabelPainterPrivate::createCachedLabel(const LabelData &labelData) const
{
  CachedLabel *result = new CachedLabel;
  
  // allocate pixmap with the correct size and pixel ratio:
  if (!qFuzzyCompare(1.0, mParentPlot->bufferDevicePixelRatio()))
  {
    result->pixmap = QPixmap(labelData.rotatedTotalBounds.size()*mParentPlot->bufferDevicePixelRatio());
#ifdef QCP_DEVICEPIXELRATIO_SUPPORTED
#  ifdef QCP_DEVICEPIXELRATIO_FLOAT
    result->pixmap.setDevicePixelRatio(mParentPlot->devicePixelRatioF());
#  else
    result->pixmap.setDevicePixelRatio(mParentPlot->devicePixelRatio());
#  endif
#endif
  } else
    result->pixmap = QPixmap(labelData.rotatedTotalBounds.size());
  result->pixmap.fill(Qt::transparent);
  
  // draw the label into the pixmap
  // offset is between label anchor and topleft of cache pixmap, so pixmap can be drawn at pos+offset to make the label anchor appear at pos.
  // We use rotatedTotalBounds.topLeft() because rotatedTotalBounds is in a coordinate system where the label anchor is at (0, 0)
  result->offset = labelData.rotatedTotalBounds.topLeft();
  QCPPainter cachePainter(&result->pixmap);
  drawText(&cachePainter, -result->offset, labelData);
  return result;
}

QByteArray QCPLabelPainterPrivate::cacheKey(const QString &text, const QColor &color, double rotation, AnchorSide side) const
{
  return text.toUtf8()+
      QByteArray::number(color.red()+256*color.green()+65536*color.blue(), 36)+
      QByteArray::number(color.alpha()+256*int(side), 36)+
      QByteArray::number(int(rotation*100), 36);
}

QCPLabelPainterPrivate::AnchorSide QCPLabelPainterPrivate::skewedAnchorSide(const QPointF &tickPos, double sideExpandHorz, double sideExpandVert) const
{
  QCPVector2D anchorNormal = QCPVector2D(tickPos-mAnchorReference);
  if (mAnchorReferenceType == artTangent)
    anchorNormal = anchorNormal.perpendicular();
  const double radius = anchorNormal.length();
  const double sideHorz = sideExpandHorz*radius;
  const double sideVert = sideExpandVert*radius;
  if (anchorNormal.x() > sideHorz)
  {
    if (anchorNormal.y() > sideVert) return asTopLeft;
    else if (anchorNormal.y() < -sideVert) return asBottomLeft;
    else return asLeft;
  } else if (anchorNormal.x() < -sideHorz)
  {
    if (anchorNormal.y() > sideVert) return asTopRight;
    else if (anchorNormal.y() < -sideVert) return asBottomRight;
    else return asRight;
  } else
  {
    if (anchorNormal.y() > 0) return asTop;
    else return asBottom;
  }
  return asBottom; // should never be reached
}

QCPLabelPainterPrivate::AnchorSide QCPLabelPainterPrivate::rotationCorrectedSide(AnchorSide side, double rotation) const
{
  AnchorSide result = side;
  const bool rotateClockwise = rotation > 0;
  if (!qFuzzyIsNull(rotation))
  {
    if (!qFuzzyCompare(qAbs(rotation), 90)) // avoid graphical collision with anchor tangent (e.g. axis line) when rotating, so change anchor side appropriately:
    {
      if (side == asTop) result = rotateClockwise ? asLeft : asRight;
      else if (side == asBottom) result = rotateClockwise ? asRight : asLeft;
      else if (side == asTopLeft) result = rotateClockwise ? asLeft : asTop;
      else if (side == asTopRight) result = rotateClockwise ? asTop : asRight;
      else if (side == asBottomLeft) result = rotateClockwise ? asBottom : asLeft;
      else if (side == asBottomRight) result = rotateClockwise ? asRight : asBottom;
    } else // for full rotation by +/-90 degrees, other sides are more appropriate for centering on anchor:
    {
      if (side == asLeft) result = rotateClockwise ? asBottom : asTop;
      else if (side == asRight) result = rotateClockwise ? asTop : asBottom;
      else if (side == asTop) result = rotateClockwise ? asLeft : asRight;
      else if (side == asBottom) result = rotateClockwise ? asRight : asLeft;
      else if (side == asTopLeft) result = rotateClockwise ? asBottomLeft : asTopRight;
      else if (side == asTopRight) result = rotateClockwise ? asTopLeft : asBottomRight;
      else if (side == asBottomLeft) result = rotateClockwise ? asBottomRight : asTopLeft;
      else if (side == asBottomRight) result = rotateClockwise ? asTopRight : asBottomLeft;
    }
  }
  return result;
}

void QCPLabelPainterPrivate::analyzeFontMetrics()
{
  const QFontMetrics fm(mFont);
  mLetterCapHeight = fm.tightBoundingRect(QLatin1String("8")).height(); // this method is slow, that's why we query it only upon font change
  mLetterDescent = fm.descent();
}
/* end of 'src/axis/labelpainter.cpp' */


/* including file 'src/axis/axisticker.cpp' */
/* modified 2022-11-06T12:45:56, size 18693 */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPAxisTicker
////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \class QCPAxisTicker
  \brief The base class tick generator used by QCPAxis to create tick positions and tick labels
  
  Each QCPAxis has an internal QCPAxisTicker (or a subclass) in order to generate tick positions
  and tick labels for the current axis range. The ticker of an axis can be set via \ref
  QCPAxis::setTicker. Since that method takes a <tt>QSharedPointer<QCPAxisTicker></tt>, multiple
  axes can share the same ticker instance.
  
  This base class generates normal tick coordinates and numeric labels for linear axes. It picks a
  reasonable tick step (the separation between ticks) which results in readable tick labels. The
  number of ticks that should be approximately generated can be set via \ref setTickCount.
  Depending on the current tick step strategy (\ref setTickStepStrategy), the algorithm either
  sacrifices readability to better match the specified tick count (\ref
  QCPAxisTicker::tssMeetTickCount) or relaxes the tick count in favor of better tick steps (\ref
  QCPAxisTicker::tssReadability), which is the default.
  
  The following more specialized axis ticker subclasses are available, see details in the
  respective class documentation:
  
  <center>
  <table>
  <tr><td style="text-align:right; padding: 0 1em">QCPAxisTickerFixed</td><td>\image html axisticker-fixed.png</td></tr>
  <tr><td style="text-align:right; padding: 0 1em">QCPAxisTickerLog</td><td>\image html axisticker-log.png</td></tr>
  <tr><td style="text-align:right; padding: 0 1em">QCPAxisTickerPi</td><td>\image html axisticker-pi.png</td></tr>
  <tr><td style="text-align:right; padding: 0 1em">QCPAxisTickerText</td><td>\image html axisticker-text.png</td></tr>
  <tr><td style="text-align:right; padding: 0 1em">QCPAxisTickerDateTime</td><td>\image html axisticker-datetime.png</td></tr>
  <tr><td style="text-align:right; padding: 0 1em">QCPAxisTickerTime</td><td>\image html axisticker-time.png
    \image html axisticker-time2.png</td></tr>
  </table>
  </center>
  
  \section axisticker-subclassing Creating own axis tickers
  
  Creating own axis tickers can be achieved very easily by sublassing QCPAxisTicker and
  reimplementing some or all of the available virtual methods.

  In the simplest case you might wish to just generate different tick steps than the other tickers,
  so you only reimplement the method \ref getTickStep. If you additionally want control over the
  string that will be shown as tick label, reimplement \ref getTickLabel.
  
  If you wish to have complete control, you can generate the tick vectors and tick label vectors
  yourself by reimplementing \ref createTickVector and \ref createLabelVector. The default
  implementations use the previously mentioned virtual methods \ref getTickStep and \ref
  getTickLabel, but your reimplementations don't necessarily need to do so. For example in the case
  of unequal tick steps, the method \ref getTickStep loses its usefulness and can be ignored.
  
  The sub tick count between major ticks can be controlled with \ref getSubTickCount. Full sub tick
  placement control is obtained by reimplementing \ref createSubTickVector.
  
  See the documentation of all these virtual methods in QCPAxisTicker for detailed information
  about the parameters and expected return values.
*/

/*!
  Constructs the ticker and sets reasonable default values. Axis tickers are commonly created
  managed by a QSharedPointer, which then can be passed to QCPAxis::setTicker.
*/
QCPAxisTicker::QCPAxisTicker() :
  mTickStepStrategy(tssReadability),
  mTickCount(5),
  mTickOrigin(0)
{
}

QCPAxisTicker::~QCPAxisTicker()
{
  
}

/*!
  Sets which strategy the axis ticker follows when choosing the size of the tick step. For the
  available strategies, see \ref TickStepStrategy.
*/
void QCPAxisTicker::setTickStepStrategy(QCPAxisTicker::TickStepStrategy strategy)
{
  mTickStepStrategy = strategy;
}

/*!
  Sets how many ticks this ticker shall aim to generate across the axis range. Note that \a count
  is not guaranteed to be matched exactly, as generating readable tick intervals may conflict with
  the requested number of ticks.

  Whether the readability has priority over meeting the requested \a count can be specified with
  \ref setTickStepStrategy.
*/
void QCPAxisTicker::setTickCount(int count)
{
  if (count > 0)
    mTickCount = count;
  else
    qDebug() << Q_FUNC_INFO << "tick count must be greater than zero:" << count;
}

/*!
  Sets the mathematical coordinate (or "offset") of the zeroth tick. This tick coordinate is just a
  concept and doesn't need to be inside the currently visible axis range.
  
  By default \a origin is zero, which for example yields ticks {-5, 0, 5, 10, 15,...} when the tick
  step is five. If \a origin is now set to 1 instead, the correspondingly generated ticks would be
  {-4, 1, 6, 11, 16,...}.
*/
void QCPAxisTicker::setTickOrigin(double origin)
{
  mTickOrigin = origin;
}

/*!
  This is the method called by QCPAxis in order to actually generate tick coordinates (\a ticks),
  tick label strings (\a tickLabels) and sub tick coordinates (\a subTicks).
  
  The ticks are generated for the specified \a range. The generated labels typically follow the
  specified \a locale, \a formatChar and number \a precision, however this might be different (or
  even irrelevant) for certain QCPAxisTicker subclasses.
  
  The output parameter \a ticks is filled with the generated tick positions in axis coordinates.
  The output parameters \a subTicks and \a tickLabels are optional (set them to \c nullptr if not
  needed) and are respectively filled with sub tick coordinates, and tick label strings belonging
  to \a ticks by index.
*/
void QCPAxisTicker::generate(const QCPRange &range, const QLocale &locale, QChar formatChar, int precision, QVector<double> &ticks, QVector<double> *subTicks, QVector<QString> *tickLabels)
{
  // generate (major) ticks:
  double tickStep = getTickStep(range);
  ticks = createTickVector(tickStep, range);
  trimTicks(range, ticks, true); // trim ticks to visible range plus one outer tick on each side (incase a subclass createTickVector creates more)
  
  // generate sub ticks between major ticks:
  if (subTicks)
  {
    if (!ticks.isEmpty())
    {
      *subTicks = createSubTickVector(getSubTickCount(tickStep), ticks);
      trimTicks(range, *subTicks, false);
    } else
      *subTicks = QVector<double>();
  }
  
  // finally trim also outliers (no further clipping happens in axis drawing):
  trimTicks(range, ticks, false);
  // generate labels for visible ticks if requested:
  if (tickLabels)
    *tickLabels = createLabelVector(ticks, locale, formatChar, precision);
}

/*! \internal
  
  Takes the entire currently visible axis range and returns a sensible tick step in
  order to provide readable tick labels as well as a reasonable number of tick counts (see \ref
  setTickCount, \ref setTickStepStrategy).
  
  If a QCPAxisTicker subclass only wants a different tick step behaviour than the default
  implementation, it should reimplement this method. See \ref cleanMantissa for a possible helper
  function.
*/
double QCPAxisTicker::getTickStep(const QCPRange &range)
{
  double exactStep = range.size()/double(mTickCount+1e-10); // mTickCount ticks on average, the small addition is to prevent jitter on exact integers
  return cleanMantissa(exactStep);
}

/*! \internal
  
  Takes the \a tickStep, i.e. the distance between two consecutive ticks, and returns
  an appropriate number of sub ticks for that specific tick step.
  
  Note that a returned sub tick count of e.g. 4 will split each tick interval into 5 sections.
*/
int QCPAxisTicker::getSubTickCount(double tickStep)
{
  int result = 1; // default to 1, if no proper value can be found
  
  // separate integer and fractional part of mantissa:
  double epsilon = 0.01;
  double intPartf;
  int intPart;
  double fracPart = modf(getMantissa(tickStep), &intPartf);
  intPart = int(intPartf);
  
  // handle cases with (almost) integer mantissa:
  if (fracPart < epsilon || 1.0-fracPart < epsilon)
  {
    if (1.0-fracPart < epsilon)
      ++intPart;
    switch (intPart)
    {
      case 1: result = 4; break; // 1.0 -> 0.2 substep
      case 2: result = 3; break; // 2.0 -> 0.5 substep
      case 3: result = 2; break; // 3.0 -> 1.0 substep
      case 4: result = 3; break; // 4.0 -> 1.0 substep
      case 5: result = 4; break; // 5.0 -> 1.0 substep
      case 6: result = 2; break; // 6.0 -> 2.0 substep
      case 7: result = 6; break; // 7.0 -> 1.0 substep
      case 8: result = 3; break; // 8.0 -> 2.0 substep
      case 9: result = 2; break; // 9.0 -> 3.0 substep
    }
  } else
  {
    // handle cases with significantly fractional mantissa:
    if (qAbs(fracPart-0.5) < epsilon) // *.5 mantissa
    {
      switch (intPart)
      {
        case 1: result = 2; break; // 1.5 -> 0.5 substep
        case 2: result = 4; break; // 2.5 -> 0.5 substep
        case 3: result = 4; break; // 3.5 -> 0.7 substep
        case 4: result = 2; break; // 4.5 -> 1.5 substep
        case 5: result = 4; break; // 5.5 -> 1.1 substep (won't occur with default getTickStep from here on)
        case 6: result = 4; break; // 6.5 -> 1.3 substep
        case 7: result = 2; break; // 7.5 -> 2.5 substep
        case 8: result = 4; break; // 8.5 -> 1.7 substep
        case 9: result = 4; break; // 9.5 -> 1.9 substep
      }
    }
    // if mantissa fraction isn't 0.0 or 0.5, don't bother finding good sub tick marks, leave default
  }
  
  return result;
}

/*! \internal
  
  This method returns the tick label string as it should be printed under the \a tick coordinate.
  If a textual number is returned, it should respect the provided \a locale, \a formatChar and \a
  precision.
  
  If the returned value contains exponentials of the form "2e5" and beautifully typeset powers is
  enabled in the QCPAxis number format (\ref QCPAxis::setNumberFormat), the exponential part will
  be formatted accordingly using multiplication symbol and superscript during rendering of the
  label automatically.
*/
QString QCPAxisTicker::getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision)
{
  return locale.toString(tick, formatChar.toLatin1(), precision);
}

/*! \internal
  
  Returns a vector containing all coordinates of sub ticks that should be drawn. It generates \a
  subTickCount sub ticks between each tick pair given in \a ticks.
  
  If a QCPAxisTicker subclass needs maximal control over the generated sub ticks, it should
  reimplement this method. Depending on the purpose of the subclass it doesn't necessarily need to
  base its result on \a subTickCount or \a ticks.
*/
QVector<double> QCPAxisTicker::createSubTickVector(int subTickCount, const QVector<double> &ticks)
{
  QVector<double> result;
  if (subTickCount <= 0 || ticks.size() < 2)
    return result;
  
  result.reserve((ticks.size()-1)*subTickCount);
  for (int i=1; i<ticks.size(); ++i)
  {
    double subTickStep = (ticks.at(i)-ticks.at(i-1))/double(subTickCount+1);
    for (int k=1; k<=subTickCount; ++k)
      result.append(ticks.at(i-1) + k*subTickStep);
  }
  return result;
}

/*! \internal
  
  Returns a vector containing all coordinates of ticks that should be drawn. The default
  implementation generates ticks with a spacing of \a tickStep (mathematically starting at the tick
  step origin, see \ref setTickOrigin) distributed over the passed \a range.
  
  In order for the axis ticker to generate proper sub ticks, it is necessary that the first and
  last tick coordinates returned by this method are just below/above the provided \a range.
  Otherwise the outer intervals won't contain any sub ticks.
  
  If a QCPAxisTicker subclass needs maximal control over the generated ticks, it should reimplement
  this method. Depending on the purpose of the subclass it doesn't necessarily need to base its
  result on \a tickStep, e.g. when the ticks are spaced unequally like in the case of
  QCPAxisTickerLog.
*/
QVector<double> QCPAxisTicker::createTickVector(double tickStep, const QCPRange &range)
{
  QVector<double> result;
  // Generate tick positions according to tickStep:
  qint64 firstStep = qint64(floor((range.lower-mTickOrigin)/tickStep)); // do not use qFloor here, or we'll lose 64 bit precision
  qint64 lastStep = qint64(ceil((range.upper-mTickOrigin)/tickStep)); // do not use qCeil here, or we'll lose 64 bit precision
  int tickcount = int(lastStep-firstStep+1);
  if (tickcount < 0) tickcount = 0;
  result.resize(tickcount);
  for (int i=0; i<tickcount; ++i)
    result[i] = mTickOrigin + (firstStep+i)*tickStep;
  return result;
}

/*! \internal
  
  Returns a vector containing all tick label strings corresponding to the tick coordinates provided
  in \a ticks. The default implementation calls \ref getTickLabel to generate the respective
  strings.
  
  It is possible but uncommon for QCPAxisTicker subclasses to reimplement this method, as
  reimplementing \ref getTickLabel often achieves the intended result easier.
*/
QVector<QString> QCPAxisTicker::createLabelVector(const QVector<double> &ticks, const QLocale &locale, QChar formatChar, int precision)
{
  QVector<QString> result;
  result.reserve(ticks.size());
  foreach (double tickCoord, ticks)
    result.append(getTickLabel(tickCoord, locale, formatChar, precision));
  return result;
}

/*! \internal
  
  Removes tick coordinates from \a ticks which lie outside the specified \a range. If \a
  keepOneOutlier is true, it preserves one tick just outside the range on both sides, if present.
  
  The passed \a ticks must be sorted in ascending order.
*/
void QCPAxisTicker::trimTicks(const QCPRange &range, QVector<double> &ticks, bool keepOneOutlier) const
{
  bool lowFound = false;
  bool highFound = false;
  int lowIndex = 0;
  int highIndex = -1;
  
  for (int i=0; i < ticks.size(); ++i)
  {
    if (ticks.at(i) >= range.lower)
    {
      lowFound = true;
      lowIndex = i;
      break;
    }
  }
  for (int i=ticks.size()-1; i >= 0; --i)
  {
    if (ticks.at(i) <= range.upper)
    {
      highFound = true;
      highIndex = i;
      break;
    }
  }
  
  if (highFound && lowFound)
  {
    int trimFront = qMax(0, lowIndex-(keepOneOutlier ? 1 : 0));
    int trimBack = qMax(0, ticks.size()-(keepOneOutlier ? 2 : 1)-highIndex);
    if (trimFront > 0 || trimBack > 0)
      ticks = ticks.mid(trimFront, ticks.size()-trimFront-trimBack);
  } else // all ticks are either all below or all above the range
    ticks.clear();
}

/*! \internal
  
  Returns the coordinate contained in \a candidates which is closest to the provided \a target.
  
  This method assumes \a candidates is not empty and sorted in ascending order.
*/
double QCPAxisTicker::pickClosest(double target, const QVector<double> &candidates) const
{
  if (candidates.size() == 1)
    return candidates.first();
  QVector<double>::const_iterator it = std::lower_bound(candidates.constBegin(), candidates.constEnd(), target);
  if (it == candidates.constEnd())
    return *(it-1);
  else if (it == candidates.constBegin())
    return *it;
  else
    return target-*(it-1) < *it-target ? *(it-1) : *it;
}

/*! \internal
  
  Returns the decimal mantissa of \a input. Optionally, if \a magnitude is not set to zero, it also
  returns the magnitude of \a input as a power of 10.
  
  For example, an input of 142.6 will return a mantissa of 1.426 and a magnitude of 100.
*/
double QCPAxisTicker::getMantissa(double input, double *magnitude) const
{
  const double mag = std::pow(10.0, std::floor(std::log10(input)));
  if (magnitude) *magnitude = mag;
  return input/mag;
}

/*! \internal
  
  Returns a number that is close to \a input but has a clean, easier human readable mantissa. How
  strongly the mantissa is altered, and thus how strong the result deviates from the original \a
  input, depends on the current tick step strategy (see \ref setTickStepStrategy).
*/
double QCPAxisTicker::cleanMantissa(double input) const
{
  double magnitude;
  const double mantissa = getMantissa(input, &magnitude);
  switch (mTickStepStrategy)
  {
    case tssReadability:
    {
      return pickClosest(mantissa, QVector<double>() << 1.0 << 2.0 << 2.5 << 5.0 << 10.0)*magnitude;
    }
    case tssMeetTickCount:
    {
      // this gives effectively a mantissa of 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 8.0, 10.0
      if (mantissa <= 5.0)
        return int(mantissa*2)/2.0*magnitude; // round digit after decimal point to 0.5
      else
        return int(mantissa/2.0)*2.0*magnitude; // round to first digit in multiples of 2
    }
  }
  return input;
}
/* end of 'src/axis/axisticker.cpp' */


/* including file 'src/axis/axistickerdatetime.cpp' */
/* modified 2022-11-06T12:45:56, size 18829         */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPAxisTickerDateTime
////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \class QCPAxisTickerDateTime
  \brief Specialized axis ticker for calendar dates and times as axis ticks
  
  \image html axisticker-datetime.png
  
  This QCPAxisTicker subclass generates ticks that correspond to real calendar dates and times. The
  plot axis coordinate is interpreted as Unix Time, so seconds since Epoch (January 1, 1970, 00:00
  UTC). This is also used for example by QDateTime in the <tt>toTime_t()/setTime_t()</tt> methods
  with a precision of one second. Since Qt 4.7, millisecond accuracy can be obtained from QDateTime
  by using <tt>QDateTime::fromMSecsSinceEpoch()/1000.0</tt>. The static methods \ref dateTimeToKey
  and \ref keyToDateTime conveniently perform this conversion achieving a precision of one
  millisecond on all Qt versions.
  
  The format of the date/time display in the tick labels is controlled with \ref setDateTimeFormat.
  If a different time spec or time zone shall be used for the tick label appearance, see \ref
  setDateTimeSpec or \ref setTimeZone, respectively.
  
  This ticker produces unequal tick spacing in order to provide intuitive date and time-of-day
  ticks. For example, if the axis range spans a few years such that there is one tick per year,
  ticks will be positioned on 1. January of every year. This is intuitive but, due to leap years,
  will result in slightly unequal tick intervals (visually unnoticeable). The same can be seen in
  the image above: even though the number of days varies month by month, this ticker generates
  ticks on the same day of each month.
  
  If you would like to change the date/time that is used as a (mathematical) starting date for the
  ticks, use the \ref setTickOrigin(const QDateTime &origin) method overload, which takes a
  QDateTime. If you pass 15. July, 9:45 to this method, the yearly ticks will end up on 15. July at
  9:45 of every year.
  
  The ticker can be created and assigned to an axis like this:
  \snippet documentation/doc-image-generator/mainwindow.cpp axistickerdatetime-creation
  
  \note If you rather wish to display relative times in terms of days, hours, minutes, seconds and
  milliseconds, and are not interested in the intricacies of real calendar dates with months and
  (leap) years, have a look at QCPAxisTickerTime instead.
*/

/*!
  Constructs the ticker and sets reasonable default values. Axis tickers are commonly created
  managed by a QSharedPointer, which then can be passed to QCPAxis::setTicker.
*/
QCPAxisTickerDateTime::QCPAxisTickerDateTime() :
  mDateTimeFormat(QLatin1String("hh:mm:ss\ndd.MM.yy")),
  mDateTimeSpec(Qt::LocalTime),
  mDateStrategy(dsNone)
{
  setTickCount(4);
}

/*!
  Sets the format in which dates and times are displayed as tick labels. For details about the \a
  format string, see the documentation of QDateTime::toString().
  
  Typical expressions are
  <table>
    <tr><td>\c d</td><td>The day as a number without a leading zero (1 to 31)</td></tr>
    <tr><td>\c dd</td><td>The day as a number with a leading zero (01 to 31)</td></tr>
    <tr><td>\c ddd</td><td>The abbreviated localized day name (e.g. 'Mon' to 'Sun'). Uses the system locale to localize the name, i.e. QLocale::system().</td></tr>
    <tr><td>\c dddd</td><td>The long localized day name (e.g. 'Monday' to 'Sunday'). Uses the system locale to localize the name, i.e. QLocale::system().</td></tr>
    <tr><td>\c M</td><td>The month as a number without a leading zero (1 to 12)</td></tr>
    <tr><td>\c MM</td><td>The month as a number with a leading zero (01 to 12)</td></tr>
    <tr><td>\c MMM</td><td>The abbreviated localized month name (e.g. 'Jan' to 'Dec'). Uses the system locale to localize the name, i.e. QLocale::system().</td></tr>
    <tr><td>\c MMMM</td><td>The long localized month name (e.g. 'January' to 'December'). Uses the system locale to localize the name, i.e. QLocale::system().</td></tr>
    <tr><td>\c yy</td><td>The year as a two digit number (00 to 99)</td></tr>
    <tr><td>\c yyyy</td><td>The year as a four digit number. If the year is negative, a minus sign is prepended, making five characters.</td></tr>
    <tr><td>\c h</td><td>The hour without a leading zero (0 to 23 or 1 to 12 if AM/PM display)</td></tr>
    <tr><td>\c hh</td><td>The hour with a leading zero (00 to 23 or 01 to 12 if AM/PM display)</td></tr>
    <tr><td>\c H</td><td>The hour without a leading zero (0 to 23, even with AM/PM display)</td></tr>
    <tr><td>\c HH</td><td>The hour with a leading zero (00 to 23, even with AM/PM display)</td></tr>
    <tr><td>\c m</td><td>The minute without a leading zero (0 to 59)</td></tr>
    <tr><td>\c mm</td><td>The minute with a leading zero (00 to 59)</td></tr>
    <tr><td>\c s</td><td>The whole second, without any leading zero (0 to 59)</td></tr>
    <tr><td>\c ss</td><td>The whole second, with a leading zero where applicable (00 to 59)</td></tr>
    <tr><td>\c z</td><td>The fractional part of the second, to go after a decimal point, without trailing zeroes (0 to 999). Thus "s.z" reports the seconds to full available (millisecond) precision without trailing zeroes.</td></tr>
    <tr><td>\c zzz</td><td>The fractional part of the second, to millisecond precision, including trailing zeroes where applicable (000 to 999).</td></tr>
    <tr><td>\c AP or \c A</td><td>Use AM/PM display. A/AP will be replaced by an upper-case version of either QLocale::amText() or QLocale::pmText().</td></tr>
    <tr><td>\c ap or \c a</td><td>Use am/pm display. a/ap will be replaced by a lower-case version of either QLocale::amText() or QLocale::pmText().</td></tr>
    <tr><td>\c t</td><td>The timezone (for example "CEST")</td></tr>
  </table>
  
  Newlines can be inserted with \c "\n", literal strings (even when containing above expressions)
  by encapsulating them using single-quotes. A literal single quote can be generated by using two
  consecutive single quotes in the format.
  
  \see setDateTimeSpec, setTimeZone
*/
void QCPAxisTickerDateTime::setDateTimeFormat(const QString &format)
{
  mDateTimeFormat = format;
}

/*!
  Sets the time spec that is used for creating the tick labels from corresponding dates/times.

  The default value of QDateTime objects (and also QCPAxisTickerDateTime) is
  <tt>Qt::LocalTime</tt>. However, if the displayed tick labels shall be given in UTC, set \a spec
  to <tt>Qt::UTC</tt>.
  
  Tick labels corresponding to other time zones can be achieved with \ref setTimeZone (which sets
  \a spec to \c Qt::TimeZone internally). Note that if \a spec is afterwards set to not be \c
  Qt::TimeZone again, the \ref setTimeZone setting will be ignored accordingly.
  
  \see setDateTimeFormat, setTimeZone
*/
void QCPAxisTickerDateTime::setDateTimeSpec(Qt::TimeSpec spec)
{
  mDateTimeSpec = spec;
}

# if QT_VERSION >= QT_VERSION_CHECK(5, 2, 0)
/*!
  Sets the time zone that is used for creating the tick labels from corresponding dates/times. The
  time spec (\ref setDateTimeSpec) is set to \c Qt::TimeZone.
  
  \see setDateTimeFormat, setTimeZone
*/
void QCPAxisTickerDateTime::setTimeZone(const QTimeZone &zone)
{
  mTimeZone = zone;
  mDateTimeSpec = Qt::TimeZone;
}
#endif

/*!
  Sets the tick origin (see \ref QCPAxisTicker::setTickOrigin) in seconds since Epoch (1. Jan 1970,
  00:00 UTC). For the date time ticker it might be more intuitive to use the overload which
  directly takes a QDateTime, see \ref setTickOrigin(const QDateTime &origin).
  
  This is useful to define the month/day/time recurring at greater tick interval steps. For
  example, If you pass 15. July, 9:45 to this method and the tick interval happens to be one tick
  per year, the ticks will end up on 15. July at 9:45 of every year.
*/
void QCPAxisTickerDateTime::setTickOrigin(double origin)
{
  QCPAxisTicker::setTickOrigin(origin);
}

/*!
  Sets the tick origin (see \ref QCPAxisTicker::setTickOrigin) as a QDateTime \a origin.
  
  This is useful to define the month/day/time recurring at greater tick interval steps. For
  example, If you pass 15. July, 9:45 to this method and the tick interval happens to be one tick
  per year, the ticks will end up on 15. July at 9:45 of every year.
*/
void QCPAxisTickerDateTime::setTickOrigin(const QDateTime &origin)
{
  setTickOrigin(dateTimeToKey(origin));
}

/*! \internal
  
  Returns a sensible tick step with intervals appropriate for a date-time-display, such as weekly,
  monthly, bi-monthly, etc.
  
  Note that this tick step isn't used exactly when generating the tick vector in \ref
  createTickVector, but only as a guiding value requiring some correction for each individual tick
  interval. Otherwise this would lead to unintuitive date displays, e.g. jumping between first day
  in the month to the last day in the previous month from tick to tick, due to the non-uniform
  length of months. The same problem arises with leap years.
  
  \seebaseclassmethod
*/
double QCPAxisTickerDateTime::getTickStep(const QCPRange &range)
{
  double result = range.size()/double(mTickCount+1e-10); // mTickCount ticks on average, the small addition is to prevent jitter on exact integers
  
  mDateStrategy = dsNone; // leaving it at dsNone means tick coordinates will not be tuned in any special way in createTickVector
  if (result < 1) // ideal tick step is below 1 second -> use normal clean mantissa algorithm in units of seconds
  {
    result = cleanMantissa(result);
  } else if (result < 86400*30.4375*12) // below a year
  {
    result = pickClosest(result, QVector<double>()
                             << 1 << 2.5 << 5 << 10 << 15 << 30 << 60 << 2.5*60 << 5*60 << 10*60 << 15*60 << 30*60 << 60*60 // second, minute, hour range
                             << 3600*2 << 3600*3 << 3600*6 << 3600*12 << 3600*24 // hour to day range
                             << 86400*2 << 86400*5 << 86400*7 << 86400*14 << 86400*30.4375 << 86400*30.4375*2 << 86400*30.4375*3 << 86400*30.4375*6 << 86400*30.4375*12); // day, week, month range (avg. days per month includes leap years)
    if (result > 86400*30.4375-1) // month tick intervals or larger
      mDateStrategy = dsUniformDayInMonth;
    else if (result > 3600*24-1) // day tick intervals or larger
      mDateStrategy = dsUniformTimeInDay;
  } else // more than a year, go back to normal clean mantissa algorithm but in units of years
  {
    const double secondsPerYear = 86400*30.4375*12; // average including leap years
    result = cleanMantissa(result/secondsPerYear)*secondsPerYear;
    mDateStrategy = dsUniformDayInMonth;
  }
  return result;
}

/*! \internal
  
  Returns a sensible sub tick count with intervals appropriate for a date-time-display, such as weekly,
  monthly, bi-monthly, etc.
  
  \seebaseclassmethod
*/
int QCPAxisTickerDateTime::getSubTickCount(double tickStep)
{
  int result = QCPAxisTicker::getSubTickCount(tickStep);
  switch (qRound(tickStep)) // hand chosen subticks for specific minute/hour/day/week/month range (as specified in getTickStep)
  {
    case 5*60: result = 4; break;
    case 10*60: result = 1; break;
    case 15*60: result = 2; break;
    case 30*60: result = 1; break;
    case 60*60: result = 3; break;
    case 3600*2: result = 3; break;
    case 3600*3: result = 2; break;
    case 3600*6: result = 1; break;
    case 3600*12: result = 3; break;
    case 3600*24: result = 3; break;
    case 86400*2: result = 1; break;
    case 86400*5: result = 4; break;
    case 86400*7: result = 6; break;
    case 86400*14: result = 1; break;
    case int(86400*30.4375+0.5): result = 3; break;
    case int(86400*30.4375*2+0.5): result = 1; break;
    case int(86400*30.4375*3+0.5): result = 2; break;
    case int(86400*30.4375*6+0.5): result = 5; break;
    case int(86400*30.4375*12+0.5): result = 3; break;
  }
  return result;
}

/*! \internal
  
  Generates a date/time tick label for tick coordinate \a tick, based on the currently set format
  (\ref setDateTimeFormat), time spec (\ref setDateTimeSpec), and possibly time zone (\ref
  setTimeZone).
  
  \seebaseclassmethod
*/
QString QCPAxisTickerDateTime::getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision)
{
  Q_UNUSED(precision)
  Q_UNUSED(formatChar)
# if QT_VERSION >= QT_VERSION_CHECK(5, 2, 0)
  if (mDateTimeSpec == Qt::TimeZone)
    return locale.toString(keyToDateTime(tick).toTimeZone(mTimeZone), mDateTimeFormat);
  else
    return locale.toString(keyToDateTime(tick).toTimeSpec(mDateTimeSpec), mDateTimeFormat);
# else
  return locale.toString(keyToDateTime(tick).toTimeSpec(mDateTimeSpec), mDateTimeFormat);
# endif
}

/*! \internal
  
  Uses the passed \a tickStep as a guiding value and applies corrections in order to obtain
  non-uniform tick intervals but intuitive tick labels, e.g. falling on the same day of each month.
  
  \seebaseclassmethod
*/
QVector<double> QCPAxisTickerDateTime::createTickVector(double tickStep, const QCPRange &range)
{
  QVector<double> result = QCPAxisTicker::createTickVector(tickStep, range);
  if (!result.isEmpty())
  {
    if (mDateStrategy == dsUniformTimeInDay)
    {
      QDateTime uniformDateTime = keyToDateTime(mTickOrigin); // the time of this datetime will be set for all other ticks, if possible
      QDateTime tickDateTime;
      for (int i=0; i<result.size(); ++i)
      {
        tickDateTime = keyToDateTime(result.at(i));
        tickDateTime.setTime(uniformDateTime.time());
        result[i] = dateTimeToKey(tickDateTime);
      }
    } else if (mDateStrategy == dsUniformDayInMonth)
    {
      QDateTime uniformDateTime = keyToDateTime(mTickOrigin); // this day (in month) and time will be set for all other ticks, if possible
      QDateTime tickDateTime;
      for (int i=0; i<result.size(); ++i)
      {
        tickDateTime = keyToDateTime(result.at(i));
        tickDateTime.setTime(uniformDateTime.time());
        int thisUniformDay = uniformDateTime.date().day() <= tickDateTime.date().daysInMonth() ? uniformDateTime.date().day() : tickDateTime.date().daysInMonth(); // don't exceed month (e.g. try to set day 31 in February)
        if (thisUniformDay-tickDateTime.date().day() < -15) // with leap years involved, date month may jump backwards or forwards, and needs to be corrected before setting day
          tickDateTime = tickDateTime.addMonths(1);
        else if (thisUniformDay-tickDateTime.date().day() > 15) // with leap years involved, date month may jump backwards or forwards, and needs to be corrected before setting day
          tickDateTime = tickDateTime.addMonths(-1);
        tickDateTime.setDate(QDate(tickDateTime.date().year(), tickDateTime.date().month(), thisUniformDay));
        result[i] = dateTimeToKey(tickDateTime);
      }
    }
  }
  return result;
}

/*!
  A convenience method which turns \a key (in seconds since Epoch 1. Jan 1970, 00:00 UTC) into a
  QDateTime object. This can be used to turn axis coordinates to actual QDateTimes.
  
  The accuracy achieved by this method is one millisecond, irrespective of the used Qt version (it
  works around the lack of a QDateTime::fromMSecsSinceEpoch in Qt 4.6)
  
  \see dateTimeToKey
*/
QDateTime QCPAxisTickerDateTime::keyToDateTime(double key)
{
# if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  return QDateTime::fromTime_t(key).addMSecs((key-(qint64)key)*1000);
# else
  return QDateTime::fromMSecsSinceEpoch(qint64(key*1000.0));
# endif
}

/*! \overload
  
  A convenience method which turns a QDateTime object into a double value that corresponds to
  seconds since Epoch (1. Jan 1970, 00:00 UTC). This is the format used as axis coordinates by
  QCPAxisTickerDateTime.
  
  The accuracy achieved by this method is one millisecond, irrespective of the used Qt version (it
  works around the lack of a QDateTime::toMSecsSinceEpoch in Qt 4.6)
  
  \see keyToDateTime
*/
double QCPAxisTickerDateTime::dateTimeToKey(const QDateTime &dateTime)
{
# if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  return dateTime.toTime_t()+dateTime.time().msec()/1000.0;
# else
  return dateTime.toMSecsSinceEpoch()/1000.0;
# endif
}

/*! \overload
  
  A convenience method which turns a QDate object into a double value that corresponds to seconds
  since Epoch (1. Jan 1970, 00:00 UTC). This is the format used
  as axis coordinates by QCPAxisTickerDateTime.
  
  The returned value will be the start of the passed day of \a date, interpreted in the given \a
  timeSpec.
  
  \see keyToDateTime
*/
double QCPAxisTickerDateTime::dateTimeToKey(const QDate &date, Qt::TimeSpec timeSpec)
{
# if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  return QDateTime(date, QTime(0, 0), timeSpec).toTime_t();
# elif QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
  return QDateTime(date, QTime(0, 0), timeSpec).toMSecsSinceEpoch()/1000.0;
# else
  return date.startOfDay(timeSpec).toMSecsSinceEpoch()/1000.0;
# endif
}
/* end of 'src/axis/axistickerdatetime.cpp' */


/* including file 'src/axis/axistickertime.cpp' */
/* modified 2022-11-06T12:45:56, size 11745     */

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPAxisTickerTime
////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \class QCPAxisTickerTime
  \brief Specialized axis ticker for time spans in units of milliseconds to days
  
  \image html axisticker-time.png
  
  This QCPAxisTicker subclass generates ticks that corresponds to time intervals.
  
  The format of the time display in the tick labels is controlled with \ref setTimeFormat and \ref
  setFieldWidth. The time coordinate is in the unit of seconds with respect to the time coordinate
  zero. Unlike with QCPAxisTickerDateTime, the ticks don't correspond to a specific calendar date
  and time.
  
  The time can be displayed in milliseconds, seconds, minutes, hours and days. Depending on the
  largest available unit in the format specified with \ref setTimeFormat, any time spans above will
  be carried in that largest unit. So for example if the format string is "%m:%s" and a tick at
  coordinate value 7815 (being 2 hours, 10 minutes and 15 seconds) is created, the resulting tick
  label will show "130:15" (130 minutes, 15 seconds). If the format string is "%h:%m:%s", the hour
  unit will be used and the label will thus be "02:10:15". Negative times with respect to the axis
  zero will carry a leading minus sign.
  
  The ticker can be created and assigned to an axis like this:
  \snippet documentation/doc-image-generator/mainwindow.cpp axistickertime-creation
  
  Here is an example of a time axis providing time information in days, hours and minutes. Due to
  the axis range spanning a few days and the wanted tick count (\ref setTickCount), the ticker
  decided to use tick steps of 12 hours:
  
  \image html axisticker-time2.png
  
  The format string for this example is
  \snippet documentation/doc-image-generator/mainwindow.cpp axistickertime-creation-2
  
  \note If you rather wish to display calendar dates and times, have a look at QCPAxisTickerDateTime
  instead.
*/

/*!
  Constructs the ticker and sets reasonable default values. Axis tickers are commonly created
  managed by a QSharedPointer, which then can be passed to QCPAxis::setTicker.
*/
QCPAxisTickerTime::QCPAxisTickerTime() :
  mTimeFormat(QLatin1String("%h:%m:%s")),
  mSmallestUnit(tuSeconds),
  mBiggestUnit(tuHours)
{
  setTickCount(4);
  mFieldWidth[tuMilliseconds] = 3;
  mFieldWidth[tuSeconds] = 2;
  mFieldWidth[tuMinutes] = 2;
  mFieldWidth[tuHours] = 2;
  mFieldWidth[tuDays] = 1;
  
  mFormatPattern[tuMilliseconds] = QLatin1String("%z");
  mFormatPattern[tuSeconds] = QLatin1String("%s");
  mFormatPattern[tuMinutes] = QLatin1String("%m");
  mFormatPattern[tuHours] = QLatin1String("%h");
  mFormatPattern[tuDays] = QLatin1String("%d");
}

/*!
  Sets the format that will be used to display time in the tick labels.
  
  The available patterns are:
  - %%z for milliseconds
  - %%s for seconds
  - %%m for minutes
  - %%h for hours
  - %%d for days
  
  The field width (zero padding) can be controlled for each unit with \ref setFieldWidth.
  
  The largest unit that appears in \a format will carry all the remaining time of a certain tick
  coordinate, even if it overflows the natural limit of the unit. For example, if %%m is the
  largest unit it might become larger than 59 in order to consume larger time values. If on the
  other hand %%h is available, the minutes will wrap around to zero after 59 and the time will
  carry to the hour digit.
*/
void QCPAxisTickerTime::setTimeFormat(const QString &format)
{
  mTimeFormat = format;
  
  // determine smallest and biggest unit in format, to optimize unit replacement and allow biggest
  // unit to consume remaining time of a tick value and grow beyond its modulo (e.g. min > 59)
  mSmallestUnit = tuMilliseconds;
  mBiggestUnit = tuMilliseconds;
  bool hasSmallest = false;
  for (int i = tuMilliseconds; i <= tuDays; ++i)
  {
    TimeUnit unit = static_cast<TimeUnit>(i);
    if (mTimeFormat.contains(mFormatPattern.value(unit)))
    {
      if (!hasSmallest)
      {
        mSmallestUnit = unit;
        hasSmallest = true;
      }
      mBiggestUnit = unit;
    }
  }
}

/*!
  Sets the field widh of the specified \a unit to be \a width digits, when displayed in the tick
  label. If the number for the specific unit is shorter than \a width, it will be padded with an
  according number of zeros to the left in order to reach the field width.
  
  \see setTimeFormat
*/
void QCPAxisTickerTime::setFieldWidth(QCPAxisTickerTime::TimeUnit unit, int width)
{
  mFieldWidth[unit] = qMax(width, 1);
}

/*! \internal

  Returns the tick step appropriate for time displays, depending on the provided \a range and the
  smallest available time unit in the current format (\ref setTimeFormat). For example if the unit
  of seconds isn't available in the format, this method will not generate steps (like 2.5 minutes)
  that require sub-minute precision to be displayed correctly.
  
  \seebaseclassmethod
*/
double QCPAxisTickerTime::getTickStep(const QCPRange &range)
{
  double result = range.size()/double(mTickCount+1e-10); // mTickCount ticks on average, the small addition is to prevent jitter on exact integers
  
  if (result < 1) // ideal tick step is below 1 second -> use normal clean mantissa algorithm in units of seconds
  {
    if (mSmallestUnit == tuMilliseconds)
      result = qMax(cleanMantissa(result), 0.001); // smallest tick step is 1 millisecond
    else // have no milliseconds available in format, so stick with 1 second tickstep
      result = 1.0;
  } else if (result < 3600*24) // below a day
  {
    // the filling of availableSteps seems a bit contorted but it fills in a sorted fashion and thus saves a post-fill sorting run
    QVector<double> availableSteps;
    // seconds range:
    if (mSmallestUnit <= tuSeconds)
      availableSteps << 1;
    if (mSmallestUnit == tuMilliseconds)
      availableSteps << 2.5; // only allow half second steps if milliseconds are there to display it
    else if (mSmallestUnit == tuSeconds)
      availableSteps << 2;
    if (mSmallestUnit <= tuSeconds)
      availableSteps << 5 << 10 << 15 << 30;
    // minutes range:
    if (mSmallestUnit <= tuMinutes)
      availableSteps << 1*60;
    if (mSmallestUnit <= tuSeconds)
      availableSteps << 2.5*60; // only allow half minute steps if seconds are there to display it
    else if (mSmallestUnit == tuMinutes)
      availableSteps << 2*60;
    if (mSmallestUnit <= tuMinutes)
      availableSteps << 5*60 << 10*60 << 15*60 << 30*60;
    // hours range:
    if (mSmallestUnit <= tuHours)
      availableSteps << 1*3600 << 2*3600 << 3*3600 << 6*3600 << 12*3600 << 24*3600;
    // pick available step that is most appropriate to approximate ideal step:
    result = pickClosest(result, availableSteps);
  } else // more than a day, go back to normal clean mantissa algorithm but in units of days
  {
    const double secondsPerDay = 3600*24;
    result = cleanMantissa(result/secondsPerDay)*secondsPerDay;
  }
  return result;
}

/*! \internal

  Returns the sub tick count appropriate for the provided \a tickStep and time displays.
  
  \seebaseclassmethod
*/
int QCPAxisTickerTime::getSubTickCount(double tickStep)
{
  int result = QCPAxisTicker::getSubTickCount(tickStep);
  switch (qRound(tickStep)) // hand chosen subticks for specific minute/hour/day range (as specified in getTickStep)
  {
    case 5*60: result = 4; break;
    case 10*60: result = 1; break;
    case 15*60: result = 2; break;
    case 30*60: result = 1; break;
    case 60*60: result = 3; break;
    case 3600*2: result = 3; break;
    case 3600*3: result = 2; break;
    case 3600*6: result = 1; break;
    case 3600*12: result = 3; break;
    case 3600*24: result = 3; break;
  }
  return result;
}

/*! \internal
  
  Returns the tick label corresponding to the provided \a tick and the configured format and field
  widths (\ref setTimeFormat, \ref setFieldWidth).
  
  \seebaseclassmethod
*/
QString QCPAxisTickerTime::getTickLabel(double tick, const QLocale &locale, QChar formatChar, int precision)
{
  Q_UNUSED(precision)
  Q_UNUSED(formatChar)
  Q_UNUSED(locale)
  bool negative = tick < 0;
  if (negative) tick *= -1;
  double values[tuDays+1]; // contains the msec/sec/min/... value with its respective modulo (e.g. minute 0..59)
  double restValues[tuDays+1]; // contains the msec/sec/min/... value as if it's the largest available unit and thus consumes the remaining time
  
  restValues[tuMilliseconds] = tick*1000;
  values[tuMilliseconds] = modf(restValues[tuMilliseconds]/1000, &restValues[tuSeconds])*1000;
  values[tuSeconds] = modf(restValues[tuSeconds]/60, &restValues[tuMinutes])*60;
  values[tuMinutes] = modf(restValues[tuMinutes]/60, &restValues[tuHours])*60;
  values[tuHours] = modf(restValues[tuHours]/24, &restValues[tuDays])*24;
  // no need to set values[tuDays] because days are always a rest value (there is no higher unit so it consumes all remaining time)
  
  QString result = mTimeFormat;
  for (int i = mSmallestUnit; i <= mBiggestUnit; ++i)
  {
    TimeUnit iUnit = static_cast<TimeUnit>(i);
    replaceUnit(result, iUnit, qRound(iUnit == mBiggestUnit ? restValues[iUnit] : values[iUnit]));
  }
  if (negative)
    result.prepend(QLatin1Char('-'));
  return result;
}

/*! \internal
  
  Replaces all occurrences of the format pattern belonging to \a unit in \a text with the specified
  \a value, using the field width as specified with \ref setFieldWidth for the \a unit.
*/
void QCPAxisTickerTime::replaceUnit(QString &text, QCPAxisTickerTime::TimeUnit unit, int value) const
{
  QString valueStr = QString::number(value);
  while (va
