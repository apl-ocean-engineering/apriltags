//-*-c++-*-

#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <opencv2/core/core.hpp>

#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <ostream>
#include <utility>

// from math.h (via cmath, usually)
#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

namespace AprilTags {

std::ostream& operator<<(std::ostream &os, const std::pair<float,float> &pt);

//! Miscellaneous math utilities and fast exp functions.
class MathUtil {
public:

	//! Returns the square of a value.
	static inline float square(float x) { return x*x; }

	static inline cv::Point2f meanPoint( const cv::Point2f &a, const cv::Point2f &b)
	{
		return cv::Point2f( float(a.x+b.x)/2, float(a.y+b.y)/2 );
	}

	static inline float distance2Dsqr( const cv::Point2f &a, const cv::Point2f b )
	{
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		return (dx*dx + dy*dy);
	}

	static inline float distance2D(const std::pair<float,float> &p0, const std::pair<float,float> &p1) {
		float dx = p0.first - p1.first;
		float dy = p0.second - p1.second;
		return std::sqrt(dx*dx + dy*dy);
	}

	//! Returns a result in [-Pi, Pi]
	static inline float mod2pi(float vin) {
		const float twopi = 2 * (float)M_PI;
		const float twopi_inv = 1.f / (2.f * (float)M_PI);
		float absv = std::abs(vin);
		float q = absv*twopi_inv + 0.5f;
		int qi = (int) q;
		float r = absv - qi*twopi;
		return (vin<0) ? -r : r;
	}

	//! Returns a value of v wrapped such that ref and v differ by no more than +/- Pi
	static inline float mod2pi(float ref, float v) { return ref + mod2pi(v-ref); }

// lousy approximation of arctan function, but good enough for our purposes (about 4 degrees)
  static inline double fast_atan2(double y, double x) {
    double coeff_1 = M_PI/4;
    double coeff_2 = 3*coeff_1;
    double abs_y = fabs(y)+1e-10;      // kludge to prevent 0/0 condition

    double angle;

    if (x >= 0) {
      double r = (x - abs_y) / (x + abs_y);
      angle = coeff_1 - coeff_1 * r;
    } else {
      double r = (x + abs_y) / (abs_y - x);
      angle = coeff_2 - coeff_1 * r;
    }

    if (y < 0)
      return -angle;     // negate if in quad III or IV
    else
      return angle;
  }

};

// std::isnan() exists only from C++11 onwards
template <typename T>
bool isnan(T x)
{
  // a nan is not equal to anything, not even itself.
  // lets hope the compiler doesnt optimise this away...
  return x != x;
}

} // namespace

#endif
