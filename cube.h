#include <glm/vec3.hpp>
#include <vector>

class Cube {
public:
    glm::vec3 pos;
    float dim;

    Cube(float x, float y, float z, float _dimention) {
        pos = glm::vec3(x, y, z);
        dim = _dimention;
    };

    std::vector<Cube> generate_carpet() {
        std::vector<Cube> carpet;
        for (int i = -1; i<2; i++) {
            for (int j = -1; j<2; j++) {
                for (int k = -1; k<2; k++) {
                    int sum = abs(i) + abs(j) + abs(k);
                    float newDim = dim / 3;
                    if (sum > 1) {
                        Cube cube(pos.x + i * newDim, pos.y + j * newDim, pos.z + k * newDim, newDim);
                        carpet.push_back(cube);
                    }
                }
            }
        }
	return carpet;
}
};
