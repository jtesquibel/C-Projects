/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      29,   11,   11,   11, 0x0a,
      50,   11,   11,   11, 0x0a,
      62,   11,   11,   11, 0x0a,
      74,   11,   11,   11, 0x0a,
      94,   11,   11,   11, 0x0a,
     137,  123,  111,   11, 0x0a,
     166,   11,   11,   11, 0x0a,
     178,   11,   11,   11, 0x0a,
     188,   11,   11,   11, 0x0a,
     201,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0openCartWindow()\0"
    "addSearchedProduct()\0showAdded()\0"
    "sortAlpha()\0sortAverageRating()\0"
    "displayReviews()\0std::string\0productString\0"
    "findProductName(std::string)\0addReview()\0"
    "addCart()\0changeUser()\0saveCart()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->openCartWindow(); break;
        case 1: _t->addSearchedProduct(); break;
        case 2: _t->showAdded(); break;
        case 3: _t->sortAlpha(); break;
        case 4: _t->sortAverageRating(); break;
        case 5: _t->displayReviews(); break;
        case 6: { std::string _r = _t->findProductName((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = _r; }  break;
        case 7: _t->addReview(); break;
        case 8: _t->addCart(); break;
        case 9: _t->changeUser(); break;
        case 10: _t->saveCart(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
