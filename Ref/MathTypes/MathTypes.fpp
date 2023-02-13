module Ref {

  @ A math operation
  enum MathOp {
    ADD @< Addition
    SUB @< Subtraction
    MUL @< Multiplication
    DIV @< Division
  }

  @ A math error
  enum MathErr {
    NoErr @< Not an error
    DivByZero @< Division by zero
  }

}