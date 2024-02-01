#include "catch.h"
#include "expr.h"

TEST_CASE("variable tests") {
    CHECK((new VarExpr("x"))->equals(new VarExpr("x")) == true);
    CHECK((new VarExpr("x"))->equals(new VarExpr("y")) == false);
    CHECK((new VarExpr("x"))->equals(new NumExpr(1)) == false);  
    CHECK_THROWS_WITH(
        (new VarExpr("x"))->subst("x", new VarExpr("y"))->interp(),
        "no value for variable"
    );  // Test substitution with an unassigned variable
}

TEST_CASE("number tests") {
    CHECK((new NumExpr(10))->equals(new NumExpr(10)) == true);
    CHECK((new NumExpr(10))->equals(new NumExpr(-10)) == false);
    CHECK((new NumExpr(0))->equals(new VarExpr("x")) == false);  
    CHECK((new NumExpr(-5))->interp() == -5);
}

TEST_CASE("add tests") {
    CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new NumExpr(2), new NumExpr(3))) == true);
    CHECK((new AddExpr(new NumExpr(2), new NumExpr(3)))->equals(new AddExpr(new NumExpr(3), new NumExpr(2))) == false);
    CHECK((new AddExpr(new VarExpr("x"), new NumExpr(5)))->has_variable() == true);
}

TEST_CASE("multiply tests") {
    CHECK((new MultExpr(new NumExpr(2), new NumExpr(3)))->equals(new MultExpr(new NumExpr(2), new NumExpr(3))) == true);
    CHECK((new MultExpr(new NumExpr(2), new NumExpr(3)))->equals(new MultExpr(new NumExpr(3), new NumExpr(2))) == false);
    CHECK((new MultExpr(new VarExpr("x"), new NumExpr(5)))->has_variable() == true);
}

TEST_CASE("interp number test") {
    CHECK((new NumExpr(99))->interp() == 99);
    CHECK((new NumExpr(-79))->interp() == -79);
    CHECK((new NumExpr(0))->interp() == 0);
}

TEST_CASE("interp Variable test") {
    CHECK_THROWS_WITH((new VarExpr("x"))->interp(), "no value for variable");
}

TEST_CASE("interp Multiplication test") {
    CHECK_THROWS_WITH(
        (new MultExpr(new VarExpr("x"), new NumExpr(2)))->interp(),
        "no value for variable"
    );
}

TEST_CASE("interp Addition test") {
    CHECK_THROWS_WITH(
        (new AddExpr(new NumExpr(5), new VarExpr("x")))->interp(),
        "no value for variable"
    );
}

TEST_CASE("has variable tests") {
    CHECK((new AddExpr(new VarExpr("x"), new NumExpr(1)))->has_variable() == true);
    CHECK((new AddExpr(new VarExpr("y"), new NumExpr(1)))->has_variable() == true);
    CHECK((new AddExpr(new VarExpr("z"), new NumExpr(1)))->has_variable() == true);
    CHECK((new MultExpr(new NumExpr(2), new NumExpr(1)))->has_variable() == false);
    CHECK((new VarExpr("x"))->subst("x", new NumExpr(5))->has_variable() == false);
}

TEST_CASE("substituting tests") {
    CHECK((new AddExpr(new VarExpr("x"), new NumExpr(7)))
        ->subst("x", new VarExpr("y"))
        ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));
    
    CHECK((new VarExpr("x"))
        ->subst("x", new AddExpr(new VarExpr("y"), new NumExpr(7)))
        ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))));
    
    CHECK_THROWS_WITH(
        (new AddExpr(new VarExpr("x"), new NumExpr(7)))
        ->subst("y", new NumExpr(5))
        ->interp(),
        "no value for variable"
    );
}
