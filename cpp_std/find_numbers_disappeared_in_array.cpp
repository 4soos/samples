#include <vector>

#include <cstdlib>

class FAD {

public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        std::vector<int> ans;

        for (const int& num: nums) {
            int pos = abs(num) - 1;
            if (nums[pos])
        }


        return ans;
    }

private:

};

int main(int argc, char* argv[]) {

}
