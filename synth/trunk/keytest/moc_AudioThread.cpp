/****************************************************************************
** Meta object code from reading C++ file 'AudioThread.h'
**
** Created: Sun Mar 4 00:42:44 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "AudioThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_AudioThread[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_AudioThread[] = {
    "AudioThread\0"
};

const QMetaObject AudioThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_AudioThread,
      qt_meta_data_AudioThread, 0 }
};

const QMetaObject *AudioThread::metaObject() const
{
    return &staticMetaObject;
}

void *AudioThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioThread))
	return static_cast<void*>(const_cast<AudioThread*>(this));
    return QThread::qt_metacast(_clname);
}

int AudioThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
