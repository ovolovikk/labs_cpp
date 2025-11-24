// TODO(@k1rillshevchenko): use standard include guards
#ifndef STATISTICS_H
#define STATISTICS_H

#include <utility>
#include <vector>

class Statistics {
 public:
  // TODO(@k1rillshevchenko): should be free functions (in some namespace)
  static double calculateMean(const std::vector<int>& values);
  static double calculateMedian(std::vector<int>& values);

  // TODO(@k1rillshevchenko): should be in Expemriment class
  static std::pair<double, double> runExperiment(int n, int k, int trials,
                                                 unsigned int seed);
};

#endif  // STATISTICS_H
