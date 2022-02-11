# Tools for Validating

The `fp` library contains some functions to validate values.
These validation functions are useful for tasks such as validating ROS parameters.

## Validate in

`fp::validate_in` can be used to validate a value is within a set of values.

```cpp
auto const day = "monday";
auto const weekends = std::vector<std::string>{"saturday", "sunday"};
auto const result = fp::validate_in(weekends, day, "day");
fmt::print("Is \'{}\' in {}?\n{}\n", day, weekends, result);
```

This this example will generate this result:

```
Is 'monday' in {"saturday", "sunday"}?
[Result<T>: [Error: [OutOfRange] monday is not in {"saturday", "sunday"}]]
```

## Validate range

`fp::validate_range` is a struct that can be used to validate numbers are within a range defined by these struct member variables.

| Variable | Default | Description |
|---|---|---|
| from | -inf | The minimum |
| to | +inf | The maximum |
| step | nothing | The step |
| step_threshold | 1e-3 | The threshold to use when evaluating if value is at step |

An example of using this if you have c++20 to test if a value is in the [-2,inf,3].

```cpp
auto const result = fp::validate_range<double>{.from=-2,.step=3}(value);
```

If you instead only have C++17 you can use it like this:

```cpp
auto const result = []{
  fp::validate_range<double> ret;
  ret.from = 2;
  ret.step = 3;
  return ret;
}()(value);
```

## Validating multiple items

You can combine these functions with the `fp::maybe_error` function to validate a set of values.
This is useful when validating a struct of ROS parameters.

```cpp
Result<Parameters> validate(Parameters const& params)
{
  if (auto const error = fp::maybe_error(
        fp::validate_in(valid_modes(), params.mode, "mode"),
        fp::validate_range<size_t>{.from = 2}(params.population_size, "population_size"),
        fp::validate_range<size_t>{.from = 2}(params.elite_count, "elite_count")
      ); error) {
    return tl::make_unexpected(error.value());
  }

  return params;
}
```

## Summary

In this tutorial you learned about the functions in `fp` for validating values and how to combine them into a function that validates a set of values.
