# Functions that can fail

In this tutorial you'll learn to use fp to write functions that can fail.

## Returning a Result<T>

In an ideal world we can create pure functions that cannot fail.
However when writing functions that can fail it is good practice to use a return type that can contain this error.

> Good interfaces anticipate mistakes people might make, and make them difficult—ideally, impossible—to commit.

`fp` provides a type called `Result<T>` that is either the type `T` or the type `fp::Error`.
This construct is called a 'sum type' which builds the possibility of the error into the interface of your function.

Here is an example of how to write a function that returns a `Result<T>`:

```cpp
fp::Result<double> divide_4_by(double x) {
  if (x == 0.0)
    return tl::make_unexpected(fp::InvalidArgument("divide by 0"));
  return 4.0 / x;
}
```

### tl::make_unexpected

The first thing you'll notice is that to return an error type we have to wrap it in a call to `tl::make_unexpected`.
This is because `fp::Result<T>` is an alias of `tl::expected<T, fp::Error>`.
`fp` vendors the [library tl::expected](https://tl.tartanllama.xyz/en/latest/api/expected.html#tl-expected) which is a library that is proposed to be added the the stl.
To create a `fp::Result<T>` that contains the error type we have to use the function `tl::make_unexpected`.

### Error Types

The `fp::Error` type contains two things, a enum code and a string.
To make it easier to create the errors `fp` contains a set of constexpr lambdas that will construct an error of a specific type.
The available types are:

| Error Type         | Description                                  |
|--------------------|----------------------------------------------|
| Unknown            | The default type of Error                    |
| Cancelled          | The operation was cancelled                  |
| InvalidArgument    | Input argument is invalid                    |
| Timeout            | The operation timed out                      |
| NotFound           | Something was not found                      |
| AlreadyExists      | Something already exists                     |
| PermissionDenied   | Caller does not have the correct permissions |
| ResourceExhausted  | A resource has been exhausted                |
| FailedPrecondition | A precondition test failed                   |
| Aborted            | The operation aborted                        |
| OutOfRange         | A value is out of range                      |
| Unimplemented      | Behavior is unimplemented                    |
| Internal           | Internal error                               |
| Unavailable        | A resource is unavailable                    |
| DataLoss           | Data loss was encountered                    |
| Unauthenticated    | Authentication failed                        |
| Exception          | An exception was caught                      |

### Returning a value type

By default your normal returns are converted into a result type.
You don't have to change how you would normally return a value.

## Calling a function that returns a Result<T>

When you call a function that returns a `Result<T>` there are a handful of different ways you can deal with it.
The first is to call the function `value()`.
If the result does contains an error and you call `value()` it will throw and exception.

```cpp
// Throws an exception
double const result = divide_4_by(0.0).value();
```

Similar to calling value you can also use the dereference operator `*` to get the value.
This has the same behavior where it will throw an exception if the result is an Error.

```cpp
// Throws an exception
double const result = *divide_4_by(0.0);
```

Typically though what you want to do is check if the result is an Error and write a different code path to handle that condition.

```cpp
auto const result = divide_4_by(0.0);
if (result) {
  // result is a value
  double const y = result.value();
} else {
  // result is an error
  fmt::print("{}", result.error());
}
```

In the above example there are a couple more important pieces of the `Result<T>` interface.
If you cast it to a bool as is done in the if statement it will return `true` if it is a value and `false` if it is a Error.
Secondly, to get the Error type you can call the function `error()` on the result.
Finally, the error type can be formatted into a human readable string using the `fmt` library.

## Helper functions

`fp` implements a few helper functions that can be used to simplify some code.
You will see uses of these functions in later tutorials.

| Function                                                  | Description                                                                |
|-----------------------------------------------------------|----------------------------------------------------------------------------|
| make_result(T) -> Result<T>                               | Creates a Result<T> from a value of type T                                 |
| has_error(tl::expected<T, E>) -> bool                     | Returns true if the parameter is a Error                                   |
| maybe_error(tl::expected<Args, E>...) -> std::optional<E> | Returns the first error found in the parameters or nothing                 |
| try_to_result(F f) -> Result<Ret>                         | Lifts a function that throws and returns T to one that returns a Result<T> |

## Summary

In this tutorial you learned to write functions that can fail and how to call those functions.

## Next Tutorial

[Combining Result<T>s](doc/2_combining.md)
