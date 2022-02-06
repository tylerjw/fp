# Chaining monadic functions

In this tutorial you'll learn to chain the result of functions that return a `Result<T>` into a result.

## Example Functions

Here are two example functions for use in this tutorial.

```cpp
Result<int> convert_small_values(double x) {
  if (x > 10.0)
    return tl::make_unexpected(fp::OutOfRange(fp::format("{} > 10", x)));
  return static_cast<int>(x);
}

Result<double> square_positive(double x) {
  if (x < 0)
    return tl::make_unexpected(fp::OutOfRange(fp::format("{} < 0", x)));
  return x * x;
}
```

## The monadic bind function

This library contains a function that enables you to chain calls together.
It does this by taking an input `Result<T1>` and a function that takes an argument of type `T1` and returns a result of the type `Result<T2>` where that is the return type of the function.

```
mbind     : (Result<T1>, T1 → Result<T2>) → Result<T2>
```

If the passed in `Result<T1>` is an error it stores that error in the return type `Result<T2>`.
If the passed in `Result<T1>` contains a value it calls the function that you passed in and returns it's result.
Here is an example of how you could use it to call the two example functions.

```cpp
auto const result
  = fp::mbind(
      fp::mbind(fp::make_result(2), square_positive),
      convert_small_values
    );
```

This will first calculate the result of `square_positive(2)` and then the result of that (if successful) will be sent to the second function `convert_small_values`.

## The operator| overload

This syntax is rather cumbersome so we have implemented an overload for the `operator|` that makes it using it much nicer.
This creates syntax that resembles the shell pipe syntax where one operation is chained into the next if it succeeds.

```cpp
auto const result = fp::make_result(2) | square_positive | convert_small_values;
```

Aternatively you can call the first function instead of using the `fp::make_result` function.

```cpp
auto const result = square_positive(2) | convert_small_values;
```

## The FP extensions from tl::expected

Because the `Result<T>` type is just an alias for `tl::expected<T, Error>` you can use the interface of `tl::expected<T, E>` to chain calls.
The five functions are:

| Function | Description |
|---|---|
| has_value | Returns whether or not *this is in the expected state. |
| value_or | If *this is in the expected state, returns the expected value. Otherwise returns u. |
| and_then | Used to compose functions which return a tl::expected. If *this is in the expected state, applies f to the expected value and returns the result. Otherwise returns *this (i.e. the unexpected value bubbles up).  Requires: Calling the given function with the expected value must return a specialization of tl::expected. |
| map | Apply a function to change the expected value (and possibly the type). If *this is in the expected state, applies f to the expected value and returns the result wrapped in a tl::expected<ResultType, E>. Otherwise returns *this (i.e. the unexpected value bubbles up). |
| transform | Alias for map. |
| map_error | Apply a function to change the unexpected value (and possibly the type). If *this is in the unexpected state, applies f to the unexpected value and returns the result wrapped in a tl::expected<T, ResultType>. Otherwise returns *this (i.e. the expected value bubbles up). |
| or_else | If *this is in the unexpected state, calls f(this->error()) and returns the result. Otherwise returns *this.  Requires: std::invoke_result_t<F> must be void or convertible to tl::expected<T,E>. |

[See the full API documentation for these functions here.](https://tl.tartanllama.xyz/en/latest/api/expected.html#_CPPv4I0ENKR8expected8value_orE1TRR1U)

An example of using `and_then` to do the same thing as above.

```cpp
auto const result = square_positive(2).and_then(convert_small_values);
```

## Composing monadic function

A final thing that you might want to do is construct a function that combines calling various functions in sequence.
To make this easier we've implemented the `mcompose` function that takes n number of functions that chain together and constructs a function that represents the result of calling them in order.

```cpp
auto constexpr launch_satelite = mcompose(
  build_rocket,
  insert_satelite,
  tranport_to_launch_pad,
  launch,
  recover_rocket,
  verify_satelite_in_orbit);
```

Then later you could use this function like this:

```cpp
auto const result = launch_satelite(SpaceCamera{});
```

## Summary

In this tutorial we learned how to chain calls to functions that can fail and how we can chain those functions into a resulting function we could call.

## Next Tutorial

[Tools for Validating](doc/4_validating.md)
