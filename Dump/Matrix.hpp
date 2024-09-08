#include <iostream>
#include <array>
#include <glm/glm.hpp>

class Mat4 {
public:
	Mat4(float A);
	Mat4(float X, float Y, float Z);
	Mat4(glm::vec3 Vec);
	Mat4(glm::mat4 Matrix);
	Mat4(float Matrix[4][4]);

	Mat4* Translate(float X, float Y, float Z);
	Mat4* Translate(glm::vec3 Vec);

	Mat4* Orientate(float X, float Y, float Z);
	Mat4* Orientate(glm::vec3 Vec);
	
	Mat4* Scale(float X, float Y, float Z);
	Mat4* Scale(glm::vec3 Vec);

	Mat4* Matrix(float Matrix[4][4]);

	Mat4 operator * (Mat4 Matrix);

	glm::vec3 Translation = glm::vec3(0, 0, 0);
	glm::vec3 Orientation = glm::vec3(0, 0, 0);
	glm::vec3 ScaleFactor = glm::vec3(0, 0, 0);

	float Matrice[4][4] = {{1, 0, 0, 0} // Basic Identity Mat
						  ,{0, 1, 0, 0}
						  ,{0, 0, 1, 0}
						  ,{0, 0, 0, 1}};

	glm::mat4 Entity = glm::mat4(1.0f);
private:
	void UpdateMatProps();
	float GetScaleFromRow(glm::vec3 NormalizedRow, glm::vec3 Row);
	glm::vec3 MatrixToScale(float Matrix[4][4]);
	glm::vec3 MatrixToEulerAngles(float Matrix[4][4]);

	float FixedMatrice[4][4] = {{1, 0, 0, 0} // Fixed size matrice.. so mat4 without the scale
							   ,{0, 1, 0, 0}
							   ,{0, 0, 1, 0}
							   ,{0, 0, 0, 1}};
};

struct SpatialVectors {
	glm::vec3 FrontVector;
	glm::vec3 UpVector;
	glm::vec3 RightVector;
};

namespace Mt4 {
	std::array<float, 12> GetComponents(Mat4 Matrix);
	
	SpatialVectors GetSpatialVectors(Mat4* Matrix);

	Mat4 Transpose(Mat4 Matrix);
}