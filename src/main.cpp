#include <iostream>
#include <iomanip>
#include "runner.h"

int main() {
    for (size_t n_threads = 4; n_threads <= 4; ++n_threads) {
        for (int x : {0, 10, 50}) {
            Runner runner(n_threads, x, 1, 100'000);
            runner.Prepopulate();
            std::cout << std::setprecision(15) << runner.RunAndCalcThroughput() << " ";
            if (config::DEBUG) {
                auto& tree = runner.GetTree();
                auto [valid, keys] = TreeValidationUtil::ValidateStructureAndCollectKeys(tree);
                if (!valid) {
                    std::cout << "! ";
                }
            }
        }
        std::cout << std::endl;
    }

}
