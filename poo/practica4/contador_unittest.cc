// jugador_unittest.cc: Juan A. Romero
// A sample program demonstrating using Google C++ testing framework.
//
// This sample shows how to write a more complex unit test for a class
// that has multiple member functions.
//
// Usually, it's a good idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized.  You may also throw in additional tests as
// needed.

#include "contador.h"
#include "gtest/gtest.h"

TEST(Contador, Constructor1) {
  Contador c;
  EXPECT_EQ(0, c.get());
  Contador d(10);
  EXPECT_EQ(0, d.get());
  Contador e(10,20);
  EXPECT_EQ(0, e.get());
  Contador f(10,20,15);
  EXPECT_EQ(15, f.get());
  Contador g(-10,200,55);
  EXPECT_EQ(55, g.get());
  Contador h(-10,200,-3);
  EXPECT_EQ(-3, h.get());
}

TEST(Contador, Constructor2) {
  Contador c(10,-200,55);
  EXPECT_EQ(0, c.get());
  Contador d(10,200,300);
  EXPECT_EQ(0, d.get());
  Contador e(10,200,-300);
  EXPECT_EQ(0, e.get());
}

TEST(Contador, IncrementoPostfijo1) {
  Contador c;
  EXPECT_EQ(0, c.get());
  c++;
  EXPECT_EQ(1, c.get());
  c++;
  EXPECT_EQ(2, c.get());
}

TEST(Contador, IncrementoPostfijo2) {
  Contador c(1,10,9);
  EXPECT_EQ(9, c.get());
  c++;
  c++;
  EXPECT_EQ(10, c.get());
}

TEST(Contador, IncrementoPrefijo1) {
  Contador c;
  EXPECT_EQ(0, c.get());
  ++c;
  EXPECT_EQ(1, c.get());
  ++c;
  EXPECT_EQ(2, c.get());
}

TEST(Contador, IncrementoPrefijo2) {
  Contador c(1,10,9);
  EXPECT_EQ(9, c.get());
  ++c;
  ++c;
  EXPECT_EQ(10, c.get());
}

TEST(Contador, DecrementoPostfijo1) {
  Contador c;
  EXPECT_EQ(0, c.get());
  c--;
  EXPECT_EQ(0, c.get());
}

TEST(Contador, DecrementoPostfijo2) {
  Contador c(1,10,10);
  EXPECT_EQ(10, c.get());
  c--;
  EXPECT_EQ(9, c.get());
  c--;
  EXPECT_EQ(8, c.get());
}

TEST(Contador, DecrementoPostfijo3) {
  Contador c(1,10,2);
  EXPECT_EQ(2, c.get());
  c--;
  c--;
  EXPECT_EQ(1, c.get());
}

TEST(Contador, DecrementoPrefijo1) {
  Contador c;
  EXPECT_EQ(0, c.get());
  --c;
  EXPECT_EQ(0, c.get());
}

TEST(Contador, DecrementoPrefijo2) {
  Contador c(1,10,10);
  EXPECT_EQ(10, c.get());
  --c;
  EXPECT_EQ(9, c.get());
  --c;
  EXPECT_EQ(8, c.get());
}

TEST(Contador, DecrementoPrefijo3) {
  Contador c(1,10,2);
  EXPECT_EQ(2, c.get());
  --c;
  --c;
  EXPECT_EQ(1, c.get());
}

TEST(Contador, UndoValorDefecto) {
  Contador c;
  EXPECT_FALSE(c.undo());
  c++;
  EXPECT_TRUE(c.undo());
  EXPECT_EQ(0, c.get());
}

TEST(Contador, UndoValoresError) {
  Contador c;
  EXPECT_FALSE(c.undo(-1));
  EXPECT_FALSE(c.undo(-7));
  c++;c++;c++;
  EXPECT_FALSE(c.undo(4));
  EXPECT_TRUE(c.undo(3));
}

TEST(Contador, Undo1) {
  Contador c;
  EXPECT_FALSE(c.undo(1));
  c++;
  EXPECT_TRUE(c.undo(1));
  EXPECT_EQ(0, c.get());
}

TEST(Contador, Undo3) {
  Contador c;
  c++;c++;c++;
  EXPECT_TRUE(c.undo(3));
  EXPECT_EQ(0,c.get());
}

TEST(Contador, Asignacion1) {
  Contador c;
  c=10;
  EXPECT_EQ(10, c.get());
}

TEST(Contador, Asignacion2) {
  Contador c;  
  c=5555;
  EXPECT_EQ(1000, c.get()); // valor max es 1000
  c=-55555;
  EXPECT_EQ(0, c.get()); // valor min es 0
}

TEST(Contador, Asignacion3) {
  Contador c, d;
  c=10;
  d=c;
  EXPECT_EQ(10, d.get());
}

TEST(Contador, DevolucionUnarioPrefijo) {
  Contador c, d;
  c=10;
  EXPECT_EQ(10, c.get());
  d=++c;
  EXPECT_EQ(11, c.get());
  EXPECT_EQ(11, d.get());
  d=--c;
  EXPECT_EQ(10, c.get());
  EXPECT_EQ(10, d.get());
}

TEST(Contador, DevolucionUnarioPostfijo) {
  Contador c, d;
  c=10;
  EXPECT_EQ(10, c.get());
  d=c++;
  EXPECT_EQ(11, c.get());
  EXPECT_EQ(10, d.get());
  d=c--;
  EXPECT_EQ(10, c.get());
  EXPECT_EQ(11, d.get());
}


TEST(Contador, Suma1) {
  Contador c,d;
  c=d+10;
  EXPECT_EQ(10, c.get());
  c=c+15;
  EXPECT_EQ(25, c.get());
}

TEST(Contador, Suma2) {
  Contador c,d;
  c=10+d;
  EXPECT_EQ(10, c.get());
  c=15+c;
  EXPECT_EQ(25, c.get());
}

TEST(Contador, Suma3) {
  Contador c,d;
  c=d+5555;
  EXPECT_EQ(1000, c.get()); // valor máximo es 1000
  c=5555+d;
  EXPECT_EQ(1000, c.get()); // valor máximo es 1000

  Contador e(1000,3000,2000);
  e=e+5000;
  EXPECT_EQ(3000, e.get());// valor máximo es 3000
  e=5000+e;
  EXPECT_EQ(3000, e.get()); // valor máximo es 3000
}

TEST(Contador, Resta1) {
  Contador c(1,100,10), d(1,100,10);
  c=d-5;
  EXPECT_EQ(5, c.get());
  c=c-1;
  EXPECT_EQ(4, c.get());
}

TEST(Contador, Resta2) {
  Contador c(1,100,10), d(1,100,10);
  c=15-d;
  EXPECT_EQ(5, c.get());
  c=9-c;
  EXPECT_EQ(4, c.get());
}

TEST(Contador, Resta3) {
  Contador c(1,100,10), d(1,100,10);
  c=d-5555;
  EXPECT_EQ(1, c.get());// valor mínimo es 1
  c=1-d;
  EXPECT_EQ(1, c.get());// valor mínimo es 1
}
