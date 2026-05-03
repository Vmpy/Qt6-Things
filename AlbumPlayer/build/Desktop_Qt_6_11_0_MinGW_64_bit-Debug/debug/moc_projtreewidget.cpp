/****************************************************************************
** Meta object code from reading C++ file 'projtreewidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../projtreewidget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projtreewidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14ProjTreeWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto ProjTreeWidget::qt_create_metaobjectdata<qt_meta_tag_ZN14ProjTreeWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ProjTreeWidget",
        "sigCanceledImportProgressThread",
        "",
        "sigCanceledOpenProgressThread",
        "sigUpdateSelected",
        "sigClearSelected",
        "slotItemPressed",
        "QTreeWidgetItem*",
        "item",
        "column",
        "slotItemDoubleClicked",
        "slotImport",
        "slotUpdateImportProgress",
        "w",
        "slotFinishImportProgress",
        "slotCanceledImportProgress",
        "slotSetActive",
        "slotCloseProj",
        "slotSildeShow",
        "slotUpdateOpenProgress",
        "slotFinishOpenProgress",
        "slotCanceledOpenProgress",
        "slotOpenProj",
        "path",
        "slotPrevBtnClicked",
        "slotNextBtnClicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sigCanceledImportProgressThread'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sigCanceledOpenProgressThread'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sigUpdateSelected'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'sigClearSelected'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slotItemPressed'
        QtMocHelpers::SlotData<void(QTreeWidgetItem *, int)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::Int, 9 },
        }}),
        // Slot 'slotItemDoubleClicked'
        QtMocHelpers::SlotData<void(QTreeWidgetItem *, int)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 7, 8 }, { QMetaType::Int, 9 },
        }}),
        // Slot 'slotImport'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slotUpdateImportProgress'
        QtMocHelpers::SlotData<void(int)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Slot 'slotFinishImportProgress'
        QtMocHelpers::SlotData<void(int)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Slot 'slotCanceledImportProgress'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slotSetActive'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slotCloseProj'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slotSildeShow'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slotUpdateOpenProgress'
        QtMocHelpers::SlotData<void(int)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Slot 'slotFinishOpenProgress'
        QtMocHelpers::SlotData<void(int)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 13 },
        }}),
        // Slot 'slotCanceledOpenProgress'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slotOpenProj'
        QtMocHelpers::SlotData<void(const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 23 },
        }}),
        // Slot 'slotPrevBtnClicked'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slotNextBtnClicked'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ProjTreeWidget, qt_meta_tag_ZN14ProjTreeWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ProjTreeWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QTreeWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ProjTreeWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ProjTreeWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14ProjTreeWidgetE_t>.metaTypes,
    nullptr
} };

void ProjTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ProjTreeWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sigCanceledImportProgressThread(); break;
        case 1: _t->sigCanceledOpenProgressThread(); break;
        case 2: _t->sigUpdateSelected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->sigClearSelected(); break;
        case 4: _t->slotItemPressed((*reinterpret_cast<std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->slotItemDoubleClicked((*reinterpret_cast<std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->slotImport(); break;
        case 7: _t->slotUpdateImportProgress((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->slotFinishImportProgress((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->slotCanceledImportProgress(); break;
        case 10: _t->slotSetActive(); break;
        case 11: _t->slotCloseProj(); break;
        case 12: _t->slotSildeShow(); break;
        case 13: _t->slotUpdateOpenProgress((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->slotFinishOpenProgress((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->slotCanceledOpenProgress(); break;
        case 16: _t->slotOpenProj((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->slotPrevBtnClicked(); break;
        case 18: _t->slotNextBtnClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ProjTreeWidget::*)()>(_a, &ProjTreeWidget::sigCanceledImportProgressThread, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProjTreeWidget::*)()>(_a, &ProjTreeWidget::sigCanceledOpenProgressThread, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProjTreeWidget::*)(const QString & )>(_a, &ProjTreeWidget::sigUpdateSelected, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProjTreeWidget::*)()>(_a, &ProjTreeWidget::sigClearSelected, 3))
            return;
    }
}

const QMetaObject *ProjTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ProjTreeWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QTreeWidget::qt_metacast(_clname);
}

int ProjTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void ProjTreeWidget::sigCanceledImportProgressThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ProjTreeWidget::sigCanceledOpenProgressThread()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ProjTreeWidget::sigUpdateSelected(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ProjTreeWidget::sigClearSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
