#include "matrix.hpp"

/*
	Quas' matrix tool suit

	made cuz i coudlnt stand GLM matrices.
*/

//█░█ █▀▀ █░░ █▀█ █▀▀ █▀█   █▀ █░█ █ ▀█▀
//█▀█ ██▄ █▄▄ █▀▀ ██▄ █▀▄   ▄█ █▀█ █ ░█░

// Rot mat 3 to EA
// https://learnopencv.com/rotation-matrix-to-euler-angles/
glm::vec3 Mat4::MatrixToEulerAngles(float Matrix[4][4]) {
	float sy = sqrt(Matrix[0][0] * Matrix[0][0] + Matrix[1][0] * Matrix[1][0]);

	bool singular = sy < 1e-6; // dk what this number does, dont ask me

	float x, y, z;
	if (!singular) {
		x = atan2(Matrix[2][1], Matrix[2][2]);
		y = atan2(Matrix[2][0], sy);
		z = atan2(Matrix[1][0], Matrix[0][0]);
	}
	else {
		x = atan2(Matrix[1][2], Matrix[1][1]);
		y = atan2(Matrix[2][0], sy);
		z = 0;
	}
	return glm::vec3(x, y, z);
}

float Mat4::GetScaleFromRow(glm::vec3 NormalizedRow, glm::vec3 Row) {
	float Scale;
	if (NormalizedRow.x != 0) {
		Scale = Row.x / NormalizedRow.x;
	}
	else if (NormalizedRow.y != 0) {
		Scale = Row.y / NormalizedRow.y;
	}
	else {
		Scale = Row.z / NormalizedRow.z;
	}

	return Scale;
}

glm::vec3 Mat4::MatrixToScale(float Matrix[4][4]) {
	glm::vec3 A_Row = glm::vec3(this->Matrice[0][0], this->Matrice[0][1], this->Matrice[0][2]);
	glm::vec3 B_Row = glm::vec3(this->Matrice[1][0], this->Matrice[1][1], this->Matrice[1][2]);
	glm::vec3 C_Row = glm::vec3(this->Matrice[2][0], this->Matrice[2][1], this->Matrice[2][2]);

	glm::vec3 A_Normal = glm::normalize(A_Row);
	glm::vec3 B_normal = glm::normalize(B_Row);
	glm::vec3 C_normal = glm::normalize(C_Row);

	glm::vec3 Scale = glm::vec3(this->GetScaleFromRow(A_Normal, A_Row)
							   ,this->GetScaleFromRow(B_normal, B_Row)
						       ,this->GetScaleFromRow(C_normal, C_Row));

	return Scale;
}

void Mat4::UpdateMatProps() {
	this->Entity = glm::mat4(glm::vec4(this->Matrice[0][0], this->Matrice[0][1], this->Matrice[0][2], this->Matrice[0][3])
						    ,glm::vec4(this->Matrice[1][0], this->Matrice[1][1], this->Matrice[1][2], this->Matrice[1][3])
						    ,glm::vec4(this->Matrice[2][0], this->Matrice[2][1], this->Matrice[2][2], this->Matrice[2][3])
						    ,glm::vec4(this->Matrice[3][0], this->Matrice[3][1], this->Matrice[3][2], this->Matrice[3][3]));

	float Matrice[4][4];
	memcpy(Matrice, this->Matrice, sizeof(Matrice));
	glm::vec3 EulerRot = this->MatrixToEulerAngles(Matrice);

	this->ScaleFactor = this->MatrixToScale(Matrice);
	this->Orientation = glm::vec3(glm::degrees(EulerRot.x), glm::degrees(EulerRot.y), glm::degrees(EulerRot.z));
	this->Translation = glm::vec3(this->Matrice[3][0], this->Matrice[3][1], this->Matrice[3][2]);
}					

//█▀▄▀█ ▄▀█ █ █▄░█
//█░▀░█ █▀█ █ █░▀█

Mat4::Mat4(float A) {
	const float Matrice[4][4] = {{A, 0, 0, 0}
								,{0, A, 0, 0}
								,{0, 0, A, 0}
								,{0, 0, 0, A} };
	memcpy(this->Matrice, Matrice, sizeof(this->Matrice));
	memcpy(this->FixedMatrice, this->Matrice, sizeof(this->FixedMatrice));

	this->UpdateMatProps();
}

Mat4::Mat4(float X, float Y, float Z) {
	const float Matrice[4][4] = {{1, 0, 0, 0}
						        ,{0, 1, 0, 0}
						        ,{0, 0, 1, 0}
						        ,{X, Y, Z, 1}};
	memcpy(this->Matrice, Matrice, sizeof(this->Matrice));
	memcpy(this->FixedMatrice, this->Matrice, sizeof(this->FixedMatrice));

	this->UpdateMatProps();
}

Mat4::Mat4(glm::vec3 Vec) {
	const float Matrice[4][4] = {{1    , 0    , 0    , 0}
							    ,{0    , 1    , 0    , 0}
							    ,{0    , 0    , 1    , 0}
							    ,{Vec.x, Vec.y, Vec.z, 1}};
	memcpy(this->Matrice, Matrice, sizeof(this->Matrice));
	memcpy(this->FixedMatrice, this->Matrice, sizeof(this->FixedMatrice));

	this->UpdateMatProps();
}

Mat4::Mat4(glm::mat4 Matrix) {
	const float Matrice[4][4] = {{Matrix[0][0], Matrix[0][1], Matrix[0][2], Matrix[0][3]}
						        ,{Matrix[1][0], Matrix[1][1], Matrix[1][2], Matrix[1][3]}
								,{Matrix[2][0], Matrix[2][1], Matrix[2][2], Matrix[2][3]}
								,{Matrix[3][0], Matrix[3][1], Matrix[3][2], Matrix[3][3]}};
	memcpy(this->Matrice, Matrice, sizeof(this->Matrice));
	memcpy(this->FixedMatrice, this->Matrice, sizeof(this->FixedMatrice));

	this->UpdateMatProps();
}

Mat4::Mat4(float Matrix[4][4]) {
	const float Matrice[4][4] = {{Matrix[0][0], Matrix[0][1], Matrix[0][2], Matrix[0][3]}
								,{Matrix[1][0], Matrix[1][1], Matrix[1][2], Matrix[1][3]}
								,{Matrix[2][0], Matrix[2][1], Matrix[2][2], Matrix[2][3]}
								,{Matrix[3][0], Matrix[3][1], Matrix[3][2], Matrix[3][3]}};
	memcpy(this->Matrice, Matrice, sizeof(this->Matrice));

	this->ScaleFactor = this->MatrixToScale(this->Matrice);
	const float FixedMatrice[4][4] = {{Matrix[0][0] / ScaleFactor.x, Matrix[0][1] / ScaleFactor.x, Matrix[0][2] / ScaleFactor.x, Matrix[0][3] / ScaleFactor.x}
								     ,{Matrix[1][0] / ScaleFactor.y, Matrix[1][1] / ScaleFactor.y, Matrix[1][2] / ScaleFactor.y, Matrix[1][3] / ScaleFactor.y}
								     ,{Matrix[2][0] / ScaleFactor.z, Matrix[2][1] / ScaleFactor.z, Matrix[2][2] / ScaleFactor.z, Matrix[2][3] / ScaleFactor.z}
								     ,{Matrix[3][0]                , Matrix[3][1]                , Matrix[3][2]                , Matrix[3][3]                 }};
	memcpy(this->FixedMatrice, FixedMatrice, sizeof(this->FixedMatrice));

	this->UpdateMatProps();
}

// Translate

Mat4* Mat4::Translate(float X, float Y, float Z) {
	this->Matrice[3][0] = X;
	this->Matrice[3][1] = Y;
	this->Matrice[3][2] = Z;

	this->UpdateMatProps();

	return this;
}

Mat4* Mat4::Translate(glm::vec3 Vec) {
	this->Matrice[3][0] = Vec.x;
	this->Matrice[3][1] = Vec.y;
	this->Matrice[3][2] = Vec.z;

	this->UpdateMatProps();

	return this;
}

// Rotate

Mat4* Mat4::Orientate(float X, float Y, float Z) {
	// Convert The Axises into rotation matrix
	const float m11 = cos(Y) * cos(Z);
	const float m12 = -cos(Y) * sin(Z);
	const float m13 = sin(Y);
	const float m21 = cos(Z) * sin(X) * sin(Y) + cos(X) * sin(Z);
	const float m22 = cos(X) * cos(Z) - sin(X) * sin(Y) * sin(Z);
	const float m23 = -cos(Y) * sin(X);
	const float m31 = sin(X) * sin(Z) - cos(X) * cos(Z) * sin(Y);
	const float m32 = cos(Z) * sin(X) + cos(X) * sin(Y) * sin(Z);
	const float m33 = cos(X) * cos(Y);

	const float Matrix[4][4] = {{m11                , m12                , m13                , 0}
							   ,{m21                , m22                , m23                , 0}
							   ,{m31                , m32                , m33                , 0}
							   ,{this->Matrice[3][0], this->Matrice[3][1], this->Matrice[3][2], 1}};

	memcpy(this->Matrice, Matrix, sizeof(this->Matrice));
	this->UpdateMatProps();

	return this;
}

Mat4* Mat4::Orientate(glm::vec3 Vec) {
	// Convert The Axises into rotation matrix
	const float m11 = cos(Vec.y) * cos(Vec.z);
	const float m12 = -cos(Vec.y) * sin(Vec.z);
	const float m13 = sin(Vec.y);
	const float m21 = cos(Vec.z) * sin(Vec.x) * sin(Vec.y) + cos(Vec.x) * sin(Vec.z);
	const float m22 = cos(Vec.x) * cos(Vec.z) - sin(Vec.x) * sin(Vec.y) * sin(Vec.z);
	const float m23 = -cos(Vec.y) * sin(Vec.x);
	const float m31 = sin(Vec.x) * sin(Vec.z) - cos(Vec.x) * cos(Vec.z) * sin(Vec.y);
	const float m32 = cos(Vec.z) * sin(Vec.x) + cos(Vec.x) * sin(Vec.y) * sin(Vec.z);
	const float m33 = cos(Vec.x) * cos(Vec.y);

	const float Matrix[4][4] = {{m11                , m12                , m13                , 0}
							   ,{m21                , m22                , m23                , 0}
							   ,{m31                , m32                , m33                , 0}
							   ,{this->Matrice[3][0], this->Matrice[3][1], this->Matrice[3][2], 1}};

	memcpy(this->Matrice, Matrix, sizeof(this->Matrice));
	memcpy(this->FixedMatrice, Matrix, sizeof(this->FixedMatrice));
	this->UpdateMatProps();

	return this;
}

// Scale

Mat4* Mat4::Scale(float X, float Y, float Z) {
	const float Matrice[4][4] = {{this->FixedMatrice[0][0] * X, this->FixedMatrice[0][1] * X, this->FixedMatrice[0][2] * X, this->FixedMatrice[0][3] * X}
								,{this->FixedMatrice[1][0] * Y, this->FixedMatrice[1][1] * Y, this->FixedMatrice[1][2] * Y, this->FixedMatrice[1][3] * Y}
								,{this->FixedMatrice[2][0] * Z, this->FixedMatrice[2][1] * Z, this->FixedMatrice[2][2] * Z, this->FixedMatrice[2][3] * Z}
								,{this->FixedMatrice[3][0]    , this->FixedMatrice[3][1]    , this->FixedMatrice[3][2]    , this->FixedMatrice[3][3]    } };

	memcpy(this->Matrice, Matrice, sizeof(this->Matrice));
	this->UpdateMatProps();

	return this;
}

Mat4* Mat4::Scale(glm::vec3 Vec) {
	const float Matrice[4][4] = {{this->FixedMatrice[0][0] * Vec.x, this->FixedMatrice[0][1] * Vec.x, this->FixedMatrice[0][2] * Vec.x, this->FixedMatrice[0][3] * Vec.x}
								,{this->FixedMatrice[1][0] * Vec.y, this->FixedMatrice[1][1] * Vec.y, this->FixedMatrice[1][2] * Vec.y, this->FixedMatrice[1][3] * Vec.y}
								,{this->FixedMatrice[2][0] * Vec.z, this->FixedMatrice[2][1] * Vec.z, this->FixedMatrice[2][2] * Vec.z, this->FixedMatrice[2][3] * Vec.z}
								,{this->FixedMatrice[3][0]        , this->FixedMatrice[3][1]        , this->FixedMatrice[3][2]        , this->FixedMatrice[3][3]        }};

	memcpy(this->Matrice, Matrice, sizeof(this->Matrice));
	this->UpdateMatProps();

	return this;
}

// Direct Matrices

Mat4* Mat4::Matrix(float Matrix[4][4]) {
	const float Matrice[4][4] = { {Matrix[0][0], Matrix[0][1], Matrix[0][2], Matrix[0][3]}
							,{Matrix[1][0], Matrix[1][1], Matrix[1][2], Matrix[1][3]}
							,{Matrix[2][0], Matrix[2][1], Matrix[2][2], Matrix[2][3]}
							,{Matrix[3][0], Matrix[3][1], Matrix[3][2], Matrix[3][3]} };
	memcpy(this->Matrice, Matrice, sizeof(this->Matrice));

	this->UpdateMatProps();

	return this;
}

//█▀█ █▀█ █▀▀ █▀█ ▄▀█ ▀█▀ █▀█ █▀█ █▀
//█▄█ █▀▀ ██▄ █▀▄ █▀█ ░█░ █▄█ █▀▄ ▄█

Mat4 Mat4::operator* (Mat4 Matrix) {
	const std::array<float, 12> Mat01Components = Mt4::GetComponents(*this);
	const std::array<float, 12> Mat02Components = Mt4::GetComponents(Matrix);

	// Mat 01 Vecs
	const glm::vec3 V0a1 = glm::vec3(Mat01Components[3], Mat01Components[4], Mat01Components[5]);
	const glm::vec3 V0a2 = glm::vec3(Mat01Components[6], Mat01Components[7], Mat01Components[8]);
	const glm::vec3 V0a3 = glm::vec3(Mat01Components[9], Mat01Components[10], Mat01Components[11]);
	const glm::vec3 V0aP = glm::vec3(Mat01Components[0], Mat01Components[1], Mat01Components[2]);
	// Mat 02 Vecs
	const glm::vec3 V1a1 = glm::vec3(Mat02Components[3], Mat02Components[6], Mat02Components[9]);
	const glm::vec3 V1a2 = glm::vec3(Mat02Components[4], Mat02Components[7], Mat02Components[10]);
	const glm::vec3 V1a3 = glm::vec3(Mat02Components[5], Mat02Components[8], Mat02Components[11]);
	const glm::vec3 V1aP = glm::vec3(Mat02Components[0], Mat02Components[1], Mat02Components[2]);

	const Mat4 MultipliedMatrix = Mat4({{glm::dot(V0a1,V1a1)         , glm::dot(V0a1,V1a2)         , glm::dot(V0a1,V1a3)            , 0}
									   ,{glm::dot(V0a2,V1a1)         , glm::dot(V0a2,V1a2)         , glm::dot(V0a2,V1a3)            , 0}
									   ,{glm::dot(V0a3,V1a1)         , glm::dot(V0a3,V1a2)         , glm::dot(V0a3,V1a3)            , 0}
									   ,{glm::dot(V1aP,V1a1) + V0aP.x, glm::dot(V1aP,V1a2) + V0aP.y, glm::dot(V1aP,V1a3) + V0aP.z   , 1}});
	return MultipliedMatrix;
}




std::array<float, 12> Mt4::GetComponents(Mat4 Matrix) {
	std::array<float, 12> Components = {Matrix.Matrice[3][0], Matrix.Matrice[3][1], Matrix.Matrice[3][2]
									   ,Matrix.Matrice[0][0], Matrix.Matrice[0][1], Matrix.Matrice[0][2]
									   ,Matrix.Matrice[1][0], Matrix.Matrice[1][1], Matrix.Matrice[1][2]
									   ,Matrix.Matrice[2][0], Matrix.Matrice[2][1], Matrix.Matrice[2][2] };
	return Components;
}

SpatialVectors Mt4::GetSpatialVectors(Mat4* Matrix) {
	struct SpatialVectors SpatialVectors;
	SpatialVectors.FrontVector = glm::vec3((Matrix->Entity)[0][2]
										  ,(Matrix->Entity)[1][2]
										  ,(Matrix->Entity)[2][2]);
	SpatialVectors.RightVector = glm::vec3((Matrix->Entity)[0][0]
										  ,(Matrix->Entity)[1][0]
										  ,(Matrix->Entity)[2][0]);
	SpatialVectors.UpVector = glm::vec3((Matrix->Entity)[0][1]
								       ,(Matrix->Entity)[1][1]
								       ,(Matrix->Entity)[2][1]);
	return SpatialVectors;
}

Mat4 Mt4::Transpose(Mat4 Matrix) {
	float InveresedMatrix[4][4] = {{Matrix.Matrice[0][0], Matrix.Matrice[1][0], Matrix.Matrice[2][0], Matrix.Matrice[3][0]}
								  ,{Matrix.Matrice[0][1], Matrix.Matrice[1][1], Matrix.Matrice[2][1], Matrix.Matrice[3][1]}
								  ,{Matrix.Matrice[0][2], Matrix.Matrice[1][2], Matrix.Matrice[2][2], Matrix.Matrice[3][2]}
								  ,{Matrix.Matrice[0][3], Matrix.Matrice[1][3], Matrix.Matrice[2][3], Matrix.Matrice[3][3]}};
	Mat4 ReformedMatrix = Mat4(InveresedMatrix);
	return ReformedMatrix;
}