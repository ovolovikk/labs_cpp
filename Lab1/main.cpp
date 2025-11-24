#include <cstdlib>
#include <iostream>

#include "Experiment.h"

int main(int argc, char* argv[]) {
  if (argc < 4) {
    Experiment::printUsage(argv[0]);
    return 1;
  }

  try {
    // TODO(@k1rillshevchenko): use program options from boost in the industry
    const auto n = std::atoi(argv[1]);
    const auto k = std::atoi(argv[2]);
    const auto trials = std::atoi(argv[3]);

    const auto seed = (argc > 4) ? std::strtoul(argv[4], nullptr, 10) : 42;

    if (argc > 5 && std::string(argv[5]) == "--sweep") {
      if (argc < 9) {
        std::cerr << "Error: Not enough arguments for sweep mode.\n";
        Experiment::printUsage(argv[0]);
        return 1;
      }

      const auto k_max = std::atoi(argv[6]);
      const auto step = std::atoi(argv[7]);
      const std::string output_file = argv[8];

      Experiment::runSweep(n, trials, seed, k_max, step, output_file);
    } else {
      Experiment::runSingle(n, k, trials, seed);
    }
  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return 1;
  }

  return 0;
}
