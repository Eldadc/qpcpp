//$file${.::blinky0.cpp} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: low-power.qm
// File:  ${.::blinky0.cpp}
//
// This code has been generated by QM 4.5.0 (https://www.state-machine.com/qm).
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
//$endhead${.::blinky0.cpp} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#include "qpcpp.h"
#include "low_power.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

//$declare${AOs::Blinky0} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//${AOs::Blinky0} ............................................................
class Blinky0 : public QP::QActive {
private:
    QP::QTimeEvt m_timeEvt0;

public:
    static Blinky0 instance;

private:
    uint8_t m_count;

public:
    Blinky0();

protected:
    Q_STATE_DECL(initial);
    Q_STATE_DECL(active);
    Q_STATE_DECL(on);
    Q_STATE_DECL(off);
    Q_STATE_DECL(inactive);
};
//$enddecl${AOs::Blinky0} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// Check for the minimum required QP version
#if (QP_VERSION < 650U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpcpp version 6.5.0 or higher required
#endif
//$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//$define${AOs::AO_Blinky0} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//${AOs::AO_Blinky0} .........................................................
QP::QActive * const AO_Blinky0 = &Blinky0::instance;
//$enddef${AOs::AO_Blinky0} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$define${AOs::Blinky0} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//${AOs::Blinky0} ............................................................
Blinky0 Blinky0::instance;
//${AOs::Blinky0::Blinky0} ...................................................
Blinky0::Blinky0()
: QActive(Q_STATE_CAST(&initial)),
  m_timeEvt0(this, TIMEOUT0_SIG, 0U)
{}

//${AOs::Blinky0::SM} ........................................................
Q_STATE_DEF(Blinky0, initial) {
    //${AOs::Blinky0::SM::initial}
    (void)e; // unused parameter
    subscribe(BTN_PRESSED_SIG);

    QS_FUN_DICTIONARY(&active);
    QS_FUN_DICTIONARY(&on);
    QS_FUN_DICTIONARY(&off);
    QS_FUN_DICTIONARY(&inactive);

    return tran(&active);
}
//${AOs::Blinky0::SM::active} ................................................
Q_STATE_DEF(Blinky0, active) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Blinky0::SM::active}
        case Q_ENTRY_SIG: {
            BSP_tickRate0_on();
            m_count = 4U;
            m_timeEvt0.armX(2U, 2U);
            status_ = Q_RET_HANDLED;
            break;
        }
        //${AOs::Blinky0::SM::active}
        case Q_EXIT_SIG: {
            m_timeEvt0.disarm();
            status_ = Q_RET_HANDLED;
            break;
        }
        //${AOs::Blinky0::SM::active::initial}
        case Q_INIT_SIG: {
            status_ = tran(&on);
            break;
        }
        default: {
            status_ = super(&top);
            break;
        }
    }
    return status_;
}
//${AOs::Blinky0::SM::active::on} ............................................
Q_STATE_DEF(Blinky0, on) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Blinky0::SM::active::on}
        case Q_ENTRY_SIG: {
            BSP_led0_on();
            status_ = Q_RET_HANDLED;
            break;
        }
        //${AOs::Blinky0::SM::active::on}
        case Q_EXIT_SIG: {
            BSP_led0_off();
            status_ = Q_RET_HANDLED;
            break;
        }
        //${AOs::Blinky0::SM::active::on::TIMEOUT0}
        case TIMEOUT0_SIG: {
            --m_count;
            //${AOs::Blinky0::SM::active::on::TIMEOUT0::[m_count>0]}
            if (m_count > 0) {
                status_ = tran(&off);
            }
            //${AOs::Blinky0::SM::active::on::TIMEOUT0::[else]}
            else {
                status_ = tran(&inactive);
            }
            break;
        }
        default: {
            status_ = super(&active);
            break;
        }
    }
    return status_;
}
//${AOs::Blinky0::SM::active::off} ...........................................
Q_STATE_DEF(Blinky0, off) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Blinky0::SM::active::off::TIMEOUT0}
        case TIMEOUT0_SIG: {
            status_ = tran(&on);
            break;
        }
        default: {
            status_ = super(&active);
            break;
        }
    }
    return status_;
}
//${AOs::Blinky0::SM::inactive} ..............................................
Q_STATE_DEF(Blinky0, inactive) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Blinky0::SM::inactive::BTN_PRESSED}
        case BTN_PRESSED_SIG: {
            status_ = tran(&active);
            break;
        }
        default: {
            status_ = super(&top);
            break;
        }
    }
    return status_;
}
//$enddef${AOs::Blinky0} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
