# qml-promise

Promise implementation for JavaScript to C++ in Qt QML

To avoid deep callback chains when doing asynchronous work, use promises.

Before using promises register the QML Engine with Promise::setEngine()
(and probably qmlRegisterType)

**Requires C++11**

## Example

### C++

```cpp
QObject* Test::doubleIt(int i)
{
  Promise *promise = new Promise();
  QtConcurrent::run([promise, i] {
    int j = i * 2;
    promise->resolve({i, j});
  });
  return promise;
}
```

### JavaScript

```javasript
test.doubleIt(5).then(function (i, j) {
  console.log(i, j);
});
```


## TODO

* Add source code example
* Try to follow Promise specification somewhat  [Promises/A+](http://promises-aplus.github.io/promises-spec/)
* Memory management? Does promise objects get garbaged correctly by the JS GC?
* Performance?
