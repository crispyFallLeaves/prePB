#pragma once

/**
 * @brief Applies a curve function to the input value.
 *
 * This function applies a custom curve to the input value `x` based on the time `t`.
 * The curve is defined by an exponential decay and a second exponential term.
 *
 * @param x The input value to be curved.
 * @param t The time parameter that influences the curve.
 * @return The curved value.
 */
double curveFunction(int x, double t);