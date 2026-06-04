#pragma once

#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <vector>
#include <unordered_map>

class MNA{
public:
    using Matrix = Eigen::SparseMatrix<double>;
    using Triplet = Eigen::Triplet<double>;

    MNA() = default;

    void resize(int n){
        n_ = n;

        A_.resize(n,n);

        b_.resize(n);
        x_.resize(n);

        b_.setZero(n);
        x_.setZero(n);
    }

    int size() const { return n_; }

    void addPattern(int row, int col){
        pattern_.emplace_back(row, col, 0.0);
    }

    void build(){
        A_.setFromTriplets(
            pattern_.begin(),
            pattern_.end()
        );

        A_.makeCompressed();

        buildLocator();
    }

    double* ptr(int row, int col){
        auto it = locator_.find(key(row, col));

        if(it == locator_.end()){
            throw std::runtime_error("MNA::ptr(): entry not found");
        }

        return &A_.valuePtr()[it->second];
    }

    double& rhs(int row){
        return b_[row];
    }

    const Eigen::VectorXd& rhs() const{
        return b_;
    }

    void clearMatrix(){
        std::fill(
            A_.valuePtr(),
            A_.valuePtr()+A_.nonZeros(),
            0.0
        );
    }

    void clearRhs(){
        b_.setZero();
    }

    void clear(){
        clearMatrix();
        clearRhs();
    }

    bool solve(){
        solver_.compute(A_);

        if(solver_.info()!=Eigen::Success){
            return false;
        }

        x_ = solver_.solve(b_);

        return solver_.info() == Eigen::Success;
    }

    const Eigen::VectorXd& solution() const{
        return x_;
    }

    double voltage(int node) const{
        return x_[node];
    }

private:
    int n_ = 0;

    Matrix A_;

    Eigen::VectorXd b_;

    Eigen::VectorXd x_;

    Eigen::SparseLU<Matrix> solver_;

    std::vector<Triplet> pattern_;

    std::unordered_map<uint64_t, int> locator_;

    static uint64_t key(int row, int col){
        return
            (uint64_t(row)<<32)
            |
            uint32_t(col);
    }

    void buildLocator(){
        locator_.clear();

        const int* outer = A_.outerIndexPtr();
        const int* inner = A_.innerIndexPtr();

        const int cols = A_.cols();

        for(int col = 0; col < cols; ++col){
            for(int k = outer[col+1];
                k < outer[col+1];
                ++k)
            {
                int row = inner[k];
                locator_[key(row, col)] = k;
            }
        }
    }
};