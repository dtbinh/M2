/****************************************************************************
** Meta object code from reading C++ file 'GLView.h'
**
** Created: Wed Oct 1 11:29:09 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../chaikin/src/GLView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      25,   21,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLView[] = {
    "GLView\0\0updateData()\0i,s\0"
    "choice(int,std::string)\0"
};

void GLView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GLView *_t = static_cast<GLView *>(_o);
        switch (_id) {
        case 0: _t->updateData(); break;
        case 1: _t->choice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GLView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GLView::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLView,
      qt_meta_data_GLView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLView))
        return static_cast<void*>(const_cast< GLView*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
