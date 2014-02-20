// -*- mode: C++; tab-width: 2; indent-tabs-mode: nil; coding: unix -*-

#include <QQmlEngine>

#include "Promise.h"

QQmlEngine* Promise::mEngine = nullptr;

Promise::Promise(QObject *parent) :
QObject(parent),
mState(State::PENDING)
{
}

void Promise::setEngine(QQmlEngine* engine)
{
  mEngine = engine;
}

void Promise::then(QJSValue onResolve, QJSValue onReject)
{
 mOnResolve = onResolve;
 mOnReject = onReject;
}

void Promise::resolve(const std::initializer_list<QVariant> &arguments)
{
  if (!isSettled()) {
    mState = State::FULFILLED;
    complete(mOnResolve, arguments);
  }
}

void Promise::reject(const std::initializer_list<QVariant> &arguments)
{
  if (!isSettled()) {
    mState = State::REJECTED;
    complete(mOnReject, arguments);
  }
}

bool Promise::isSettled() const
{
  return mState == State::PENDING ? false: true;
}


void Promise::complete(QJSValue fn, const std::initializer_list<QVariant> &arguments)
{
  QJSValueList list;
  for (const QVariant &item : arguments) {
    list << mEngine->toScriptValue(item);
  }

  if (fn.isCallable()) {
    fn.call(list);
  }
}
