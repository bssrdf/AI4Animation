# if defined _WIN32 || defined __CYGWIN__
#   define EXPORT_API __declspec(dllexport)
# else
#   define EXPORT_API  __attribute__ ((visibility("default")))
# endif

#include <Eigen/Dense>

using namespace Eigen;

extern "C" {
    MatrixXf* Create(int rows, int cols) {
        return new MatrixXf(rows, cols);
    }

    void Destroy(MatrixXf* m) {
        delete m;
    }

    void Add(MatrixXf* lhs, MatrixXf* rhs, MatrixXf* result) {
        *result = *lhs + *rhs;
    }

    void Sub(MatrixXf* lhs, MatrixXf* rhs, MatrixXf* result) {
        *result = *lhs - *rhs;
    }

    void Multiply(MatrixXf* lhs, MatrixXf* rhs, MatrixXf* result) {
        *result = *lhs * *rhs;
    }

    void Scale(MatrixXf* lhs, float value, MatrixXf* result) {
        *result = *lhs * value;
    }

    void SetValue(MatrixXf* m, int row, int col, float value) {
        (*m)(row, col) = value;
    }

    float GetValue(MatrixXf* m, int row, int col) {
        return (*m)(row, col);
    }

    void PointwiseMultiply(MatrixXf* m, MatrixXf* value) {
        *m = (*m).cwiseProduct(*value);
    }

    void PointwiseDivide(MatrixXf* m, MatrixXf* value) {
        *m = (*m).cwiseQuotient(*value);
    }

    void ELU(MatrixXf* m) {
        int rows = (*m).rows();
        for(int i=0; i<rows; i++) {
            (*m)(i, 0) = std::max((*m)(i, 0), 0.0f) + std::exp(std::min((*m)(i, 0), 0.0f)) - 1.0f;
        }
    }

    void SoftMax(MatrixXf* m) {
        float frac = 0.0f;
        int rows = (*m).rows();
        for(int i=0; i<rows; i++) {
            (*m)(i, 0) = std::exp((*m)(i, 0));
            frac += (*m)(i, 0);
        }
        for(int i=0; i<rows; i++) {
            (*m)(i, 0) /= frac;
        }
    }

    void Clear(MatrixXf* m) {
        int rows = (*m).rows();
        int cols = (*m).cols();
        *m = (*m).Zero(rows, cols);
    }

    void Performance(int rows, int cols, int iterations) {
        MatrixXf a = MatrixXf(rows, cols);
        MatrixXf b = MatrixXf(rows, cols);
        MatrixXf c = MatrixXf(rows, cols);
        for(int i=0; i<iterations; i++) {
            c = a * b;
        }
    }
}







/*
//PFNN Class
class Test {
    int Value;

    public : void Update(int value) {
        Value += value;
    }

    public : int Get() {
        return Value;
    }

    //Initialise

    //Predict
};
*/

/*
Test* Create() {
    Test* obj = new Test();
    return obj;
}

void Destroy(Test* obj) {
    delete obj;
}

void UpdateValue(Test* obj, int value) {
    obj->Update(value);
}

int GetValue(Test* obj) {
    return obj->Get();
}
*/