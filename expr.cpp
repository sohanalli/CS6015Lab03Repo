#include "expr.h"
#include <stdexcept>

NumExpr::NumExpr(int val){
    this -> val = val;
}

int NumExpr::interp(){
    return this->val;
}

bool NumExpr::has_variable(){
    return false;
}
// for var and num create new
// return new for subsitute
Expr* NumExpr::subst(std::string s, Expr *e){
    return new NumExpr(this->val);
}

VarExpr::VarExpr(std::string val){
    this -> val = val;
}

int VarExpr::interp(){
    throw std::runtime_error("no value for variable");
}

bool VarExpr::has_variable(){
    return true;
}

Expr* VarExpr::subst(std::string s, Expr *e){
    if(this -> val == s){
        return e;
    } else{
        return new VarExpr(this->val);
    }
}

AddExpr::AddExpr(Expr *lhs, Expr *rhs){
    this -> lhs = lhs;
    this -> rhs = rhs;
}

int AddExpr::interp(){
    int result = 0;
    result = (this->lhs)->interp() + (this->rhs)->interp();
    return result;
}

bool AddExpr::has_variable(){
    return((this->lhs)->has_variable() || (this->rhs)->has_variable());
}

Expr* AddExpr::subst(std::string s, Expr *e){
    return new AddExpr((this->lhs)->subst(s,e), (this->rhs)->subst(s,e));
}

MultExpr::MultExpr(Expr *lhs, Expr *rhs){
    this -> lhs = lhs;
    this -> rhs = rhs;
}

int MultExpr::interp(){
    int result = 0;
    result = (this->lhs)->interp() * (this->rhs)->interp();
    return result;
}

bool MultExpr::has_variable(){
    return((this->lhs)->has_variable() || (this->rhs)->has_variable());
}

Expr* MultExpr::subst(std::string s, Expr *e){
    return new MultExpr((this->lhs)->subst(s,e), (this->rhs)->subst(s,e));
}

bool NumExpr::equals(Expr *e){
    NumExpr *n = dynamic_cast<NumExpr*>(e);
    if (n == NULL){
        return false;
    } else{
        return (this -> val == n -> val);
    }
}

bool VarExpr::equals(Expr *e){
    VarExpr *n = dynamic_cast<VarExpr*>(e);
    if (n == NULL){
        return false;
    } else{
        return (this -> val == n -> val);
    }
}

bool AddExpr::equals(Expr *e){
    AddExpr *n = dynamic_cast<AddExpr*>(e);
    if (n == NULL){
        return false;
    } else{
        return (this -> lhs -> equals(n -> lhs)  && this -> rhs -> equals(n -> rhs));
    }
}

bool MultExpr::equals(Expr *e){
    MultExpr *n = dynamic_cast<MultExpr*>(e);
    if (n == NULL){
        return false;
    } else{
        return (this -> lhs -> equals(n -> lhs)  && this -> rhs -> equals(n -> rhs));
    }
}

