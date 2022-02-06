# Combining Result<T>s

This tutorial will show you how to write functions that combine Result<T>s.
A common reason for this is you are building a struct and the construction of the various operations you do to build that struct could fail.
One common place where you might write code like this is when loading ROS parameters.

## Calling the functions that can fail

For this example lets assume we have a function that loads ros parameters with this interface.

```cpp
template<typename T>
Result<T> load_parameter(std::string const& name, T default_value);
```

And you have a struct that represents your parameters that you'd like to load.

```cpp
struct Parameters {
  std::string input_topic = "input";
  std::string output_topic = "output";
  double rate = 100.0;
};
```

The function we want to write will have this signature:

```cpp
Result<Parameters> load_parameters();
```

The first we will do in our function is load our three values.

```cpp
auto const default_values = Parameters{};
auto const input_topic = load_parameter("input_topic", default_values.input_topic);
auto const output_topic = load_parameter("output_topic", default_values.output_topic);
auto const rate = load_parameter("rate", default_values.rate);
```

### Testing if any of them failed

Next we need to check if any of these failed before we can construct the result.
To do this we use the helper function `fp::maybe_error`.

```cpp
if(auto const error = fp::maybe_error(input_topic, output_topic, rate); error) {
  return tl::make_unexpected(error.value());
}
```

In this case the `error` variable is a `std::optional<fp::Error>` which means that if it contains a value of type `fp::Error` it will be `true` when cast to bool.
The statement inside the if statement is needed to create a `Result<Parameters>` type containing the error that we received.

### Using the valid results

Now that we are past that if statement we know that all our results are valid and we can use them to construct the `Parameters` struct.

```cpp
return Parameters{*input_topic, *output_topic, *rate};
```

## Summary

In this tutorial you learned about a convenience function ``fp::maybe_error`` you can use to check many results before using them.

## Next Tutorial

[Chaining functions that return Result<T>](doc/3_chaining_functions.md)
