/****************************************************************************
** Meta object code from reading C++ file 'mymediaplayer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mymediaplayer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mymediaplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13MyMediaPlayerE_t {};
} // unnamed namespace

template <> constexpr inline auto MyMediaPlayer::qt_create_metaobjectdata<qt_meta_tag_ZN13MyMediaPlayerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MyMediaPlayer",
        "sigPlayMusicName",
        "",
        "sigPlayMusicMode",
        "sigPlayMusicState",
        "sigPlayMusicSize",
        "sigDurationChanged",
        "sigPositionChanged",
        "sigSliderVolumeChanged",
        "sigVolumeTextChanged",
        "slotPlayStateChanged",
        "QMediaPlayer::PlaybackState",
        "newState",
        "slotPositionChanged",
        "pos",
        "slotSetPosition",
        "slotVolumeUpTriggered",
        "slotVolumeDownTriggered"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sigPlayMusicName'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'sigPlayMusicMode'
        QtMocHelpers::SignalData<void(const QString &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'sigPlayMusicState'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'sigPlayMusicSize'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'sigDurationChanged'
        QtMocHelpers::SignalData<void(qint64)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::LongLong, 2 },
        }}),
        // Signal 'sigPositionChanged'
        QtMocHelpers::SignalData<void(qint64)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::LongLong, 2 },
        }}),
        // Signal 'sigSliderVolumeChanged'
        QtMocHelpers::SignalData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'sigVolumeTextChanged'
        QtMocHelpers::SignalData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Slot 'slotPlayStateChanged'
        QtMocHelpers::SlotData<void(QMediaPlayer::PlaybackState)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'slotPositionChanged'
        QtMocHelpers::SlotData<void(qint64)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 14 },
        }}),
        // Slot 'slotSetPosition'
        QtMocHelpers::SlotData<void(int)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 14 },
        }}),
        // Slot 'slotVolumeUpTriggered'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slotVolumeDownTriggered'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MyMediaPlayer, qt_meta_tag_ZN13MyMediaPlayerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MyMediaPlayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13MyMediaPlayerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13MyMediaPlayerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13MyMediaPlayerE_t>.metaTypes,
    nullptr
} };

void MyMediaPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MyMediaPlayer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sigPlayMusicName((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->sigPlayMusicMode((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->sigPlayMusicState((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->sigPlayMusicSize((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->sigDurationChanged((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 5: _t->sigPositionChanged((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 6: _t->sigSliderVolumeChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->sigVolumeTextChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->slotPlayStateChanged((*reinterpret_cast<std::add_pointer_t<QMediaPlayer::PlaybackState>>(_a[1]))); break;
        case 9: _t->slotPositionChanged((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 10: _t->slotSetPosition((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->slotVolumeUpTriggered(); break;
        case 12: _t->slotVolumeDownTriggered(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MyMediaPlayer::*)(const QString & )>(_a, &MyMediaPlayer::sigPlayMusicName, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyMediaPlayer::*)(const QString & )>(_a, &MyMediaPlayer::sigPlayMusicMode, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyMediaPlayer::*)(const QString & )>(_a, &MyMediaPlayer::sigPlayMusicState, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyMediaPlayer::*)(int )>(_a, &MyMediaPlayer::sigPlayMusicSize, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyMediaPlayer::*)(qint64 )>(_a, &MyMediaPlayer::sigDurationChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyMediaPlayer::*)(qint64 )>(_a, &MyMediaPlayer::sigPositionChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyMediaPlayer::*)(int )>(_a, &MyMediaPlayer::sigSliderVolumeChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyMediaPlayer::*)(int )>(_a, &MyMediaPlayer::sigVolumeTextChanged, 7))
            return;
    }
}

const QMetaObject *MyMediaPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyMediaPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13MyMediaPlayerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyMediaPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MyMediaPlayer::sigPlayMusicName(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void MyMediaPlayer::sigPlayMusicMode(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void MyMediaPlayer::sigPlayMusicState(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void MyMediaPlayer::sigPlayMusicSize(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void MyMediaPlayer::sigDurationChanged(qint64 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void MyMediaPlayer::sigPositionChanged(qint64 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void MyMediaPlayer::sigSliderVolumeChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void MyMediaPlayer::sigVolumeTextChanged(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}
QT_WARNING_POP
