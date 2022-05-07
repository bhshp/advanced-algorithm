#pragma once

#ifndef GLPK_WRAPPER_H_
#define GLPK_WRAPPER_H_

#include <glpk.h>

#include <cassert>
#include <limits>
#include <vector>

enum target_type { MIN = GLP_MIN, MAX = GLP_MAX };

enum bound_type {
    FREE = GLP_FR,
    LOWER_BOUND = GLP_LO,
    UPPER_BOUND = GLP_UP,
    DOUBLE_BOUND = GLP_DB,
    FIXED = GLP_FX
};

struct limit {
   public:
    limit(const bound_type& b, double l, double r);
    int type() const;
    double l() const;
    double r() const;

   private:
    bound_type type_;
    double left_, right_;
};

struct lin_prog {
   public:
    lin_prog(target_type type, const std::vector<std::vector<double>>& coef,
             const std::vector<double>& obj_coef,
             const std::vector<limit>& col_bnds,
             const std::vector<limit>& row_bnds);
    ~lin_prog();
    std::vector<double> solve() const;

   private:
    glp_prob* lp_;
    size_t col_;
};

// Implementation

limit::limit(const bound_type& b, double l, double r)
    : type_{b}, left_{l}, right_{r} {}

int limit::type() const { return static_cast<int>(type_); }

double limit::l() const { return left_; }

double limit::r() const { return right_; }

lin_prog::lin_prog(target_type type,
                   const std::vector<std::vector<double>>& coef,
                   const std::vector<double>& obj_coef,
                   const std::vector<limit>& col_bnds,
                   const std::vector<limit>& row_bnds) {
    assert(!coef.empty());
    size_t row = coef.size(), col = coef[0].size();
    assert(col == obj_coef.size());
    assert(col == col_bnds.size());
    assert(row == row_bnds.size());
    lp_ = glp_create_prob();
    glp_set_obj_dir(lp_, static_cast<int>(type));
    glp_add_cols(lp_, col);
    for (size_t i = 0; i < col; i++) {
        const limit& bnd = col_bnds[i];
        glp_set_obj_coef(lp_, i + 1, obj_coef[i]);
        glp_set_col_bnds(lp_, i + 1, bnd.type(), bnd.l(), bnd.r());
    }
    glp_add_rows(lp_, row);
    for (size_t i = 0; i < row; i++) {
        const limit& bnd = row_bnds[i];
        glp_set_row_bnds(lp_, i + 1, bnd.type(), bnd.l(), bnd.r());
    }
    size_t nums = row * col;
    std::vector<int> ia(nums), ja(nums);
    std::vector<double> ar(nums);
    for (size_t i = 0; i < row; i++) {
        size_t pre = i * col;
        for (size_t j = 0; j < col; j++) {
            ia[pre + j + 1] = i + 1;
            ja[pre + j + 1] = j + 1;
            ar[pre + j + 1] = coef[i][j];
        }
    }
    col_ = col;
    glp_load_matrix(lp_, nums, ia.data(), ja.data(), ar.data());
}

lin_prog::~lin_prog() { glp_delete_prob(lp_); }

std::vector<double> lin_prog::solve() const {
    glp_smcp controller = {
        GLP_MSG_OFF,  // most important one, others are
                      // default according to the documentation
        GLP_PRIMAL,
        GLP_PT_PSE,
        GLP_RT_HAR,
        1e-7,
        1e-7,
        1e-10,
        -std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max(),
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max(),
        500,
        0,
        GLP_ON,
        0,
        0,
        GLP_USE_AT,
        {}};
    glp_simplex(lp_, &controller);
    std::vector<double> result(col_ + 1, 0);
    result[0] = glp_get_obj_val(lp_);
    for (size_t i = 1; i < result.size(); i++) {
        result[i] = glp_get_col_prim(lp_, i);
    }
    return result;
}

#endif  // GLPK_WRAPPER_H_
