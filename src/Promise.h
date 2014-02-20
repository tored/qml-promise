// -*- mode: C++; tab-width: 2; indent-tabs-mode: nil; coding: unix -*-

#pragma once

#include <initializer_list>
#include <QJSValue>
#include <QObject>
#include <QVariant>

class QQmlEngine;

class Promise : public QObject
{
  Q_OBJECT
public:
  enum class State {
    PENDING,
    FULFILLED,
    REJECTED
  };

  explicit Promise(QObject *parent = 0);
  static void setEngine(QQmlEngine* engine);
  Q_INVOKABLE void then(QJSValue onResolve, QJSValue onReject = QJSValue());
  void resolve(const std::initializer_list<QVariant> &arguments);
  void reject(const std::initializer_list<QVariant> &arguments);
protected:
  void complete(QJSValue fn, const std::initializer_list<QVariant> &arguments);
  bool isSettled() const;
private:
  static QQmlEngine* mEngine;
  State mState;
  QJSValue mOnResolve;
  QJSValue mOnReject;
};
