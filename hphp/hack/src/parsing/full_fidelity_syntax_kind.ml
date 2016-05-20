(**
 * Copyright (c) 2016, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the "hack" directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 *)

type t =
| Token
| Error
| Missing
| SyntaxList

(* Declarations *)
| ScriptHeader
| Script
| FunctionDeclaration
| ParameterDeclaration
| DefaultArgumentSpecifier

(* Statements *)
| CompoundStatement
| ExpressionStatement

(* Expressions *)
| LiteralExpression
| VariableExpression
| QualifiedNameExpression
| PrefixUnaryOperator
| PostfixUnaryOperator
| BinaryOperator
| ParenthesizedExpression

(* Types *)
| SimpleTypeSpecifier
| TypeConstant
| GenericTypeSpecifier

let to_string kind =
  match kind with
  | Missing -> "missing"
  | Token -> "token"
  | LiteralExpression -> "literal"
  | VariableExpression -> "variable"
  | QualifiedNameExpression -> "variable"
  | Error -> "error"
  | SyntaxList -> "list"
  | ScriptHeader -> "header"
  | Script -> "script"
  | FunctionDeclaration -> "function_declaration"
  | ParameterDeclaration -> "parameter_declaration"
  | CompoundStatement -> "compound_statement"
  | ExpressionStatement -> "expression_statement"
  | PrefixUnaryOperator -> "prefix_unary_operator"
  | PostfixUnaryOperator -> "postfix_unary_operator"
  | BinaryOperator -> "binary_operator"
  | ParenthesizedExpression -> "parenthesized_expression"
  | TypeConstant -> "type_constant"
  | SimpleTypeSpecifier -> "simple_type_specifier "
  | GenericTypeSpecifier -> "generic_type_specifier"
  | DefaultArgumentSpecifier -> "default_argument_specifier"
