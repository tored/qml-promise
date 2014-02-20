# qml-promise

Promise implementation for JavaScript to C++ in Qt QML

To avoid deep callback chains use promises.

Before using promises register the QML Engine with Promise::setEngine()
(and probably qmlRegisterType)

## Example

```cpp
QObject* Test::double(int i)
{
  Promise *promise = new Promise();
  QtConcurrent::run([promise, i] {
    int j = i * 2;
    promise->resolve({i, j});
  });
  return promise;
}
```

```javasript
test.double(5).then(function (i, j) {
  console.log(i, j);
});
```


## TODO

* Add source code example
* Try to follow Promise specification somewhat
* Memory management? Does promise objects get garbaged correctly by the JS GC?
* Performance?
