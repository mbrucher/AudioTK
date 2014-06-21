Extending Audio ToolKit
=======================

Extending ATK is supposed to be easy. There are a few methods to override to
create a new filter that can be used in any pipeline.

Creating a new filter
#####################

Creating a new filter means that you derive from **ATK::TypedBaseFilter<>**.
This class handles getting data in and out of the pipeline.

The class constructor takes two arguments, the number of input ports and the
number of output ports. This will indicate to the pipeline what can be
connected.

The two methods that should be overriden are:

* **setup** is called whenever a filter parameter is changed (mainly sampling rate, but also by all other parameter change). You should call the parent **setup** first.

* **process_impl** is the main function of the filter. It is in charge of taking data from **converted_inputs** and populate **outputs** accordingly. Their size is function of the number of ports.

In addition to these functions, there are two attributes that will dictate the
arrays' behavior, namely **in_delay** and **out_delay**. These attributes will
make the arrays valid for negative values as well. It is mainly used when your
filter needs past values (input and output) to compute values. This way, you
don't need to store last values in another buffer by yourself.

Creating a new IIR filter
#########################

The creation of an IIR filter is straightforward, as the **process_impl** is
already implemented. In the **setup** method, you need to place:

* **in_order** and **out_order**, which indicate how many coefficients there are in the two polynomials
* **coefficients_in** and **coefficients_out** contain the two polynomials, **coefficients_in** having **in_order** +1 coefficients, stored in reverse order, and **coefficients_out** having **out_order** coefficients, in reverse order, the last implied coefficient having a value of **-1**.

Then, use the class as a template argument for **IIRFilter<>**.

Creating a new overdrive filter
###############################

The overall goal of the following class is to solve **y=f(x, t)**, and more
precisely **y[n]=f(x[n])**. The overdrive filters in ATK are based on a Newton
Raphson algorithm. It is thus possible to implement other filters in the same
way. The trick is to implement a new class that will implement a specific cost
function and pass it to the **ScalarNewtonRaphson** class.

This function is a functor that will get 4 arguments, **x0** and **x1**, the
input values of the system, as well as **y0** and **y1** the output values. The
functor will then return a pair containing the remaining cost and the gradient
for this pair.

The NR algorithm will then use history (**x0** and corresponding output **y0**)
to compute **y1** from the new input **x1**. This will be done for each sample
in the original array, at the sampling rate.
