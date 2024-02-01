#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

class Expr{
    public:
        virtual bool equals(Expr *e)=0;
        virtual int interp()=0;
        virtual bool has_variable()=0;
        virtual Expr* subst(std::string s, Expr *e)=0;
};

class VarExpr : public Expr{
    public:
        std::string val;
        VarExpr(std::string val);
        bool equals(Expr *e);
        int interp();
        bool has_variable();
        Expr* subst(std::string s, Expr *e);
};

class NumExpr : public Expr{
    public:
        int val;
        NumExpr(int val);
        bool equals(Expr *e);
        int interp();
        bool has_variable();
        Expr* subst(std::string s, Expr *e);
};

class AddExpr : public Expr{
    public:
        Expr *lhs;
        Expr *rhs;
        AddExpr(Expr *lhs, Expr *rhs);
        bool equals(Expr *e);
        int interp();
        bool has_variable();
        Expr* subst(std::string s, Expr *e);
};

class MultExpr : public Expr{
    public:
        Expr *lhs;
        Expr *rhs;
        MultExpr(Expr *lhs, Expr *rhs);
        bool equals(Expr *e);
        int interp();
        bool has_variable();
        Expr* subst(std::string s, Expr *e);
};