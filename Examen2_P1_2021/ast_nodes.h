#define Prg new Ast::Prog
#define Func new Ast::Function

#define Num(n) new Ast::NumExpr(n)
#define Var(v) new Ast::VarExpr(v)

#define Add new Ast::AddExpr
#define And new Ast::AndExpr
#define Or new Ast::OrExpr
#define Xor new Ast::XorExpr
#define LessThan new Ast::LessThan

#define Assign new Ast::AssignStmt
#define Block new Ast::SeqStmt
#define Print new Ast::PrintStmt
#define Call new Ast::Call
#define If new Ast::IfStmt
#define While new Ast::WhileStmt

#define ParamByVal(p) new Ast::ParamByVal(p)
#define ParamByRef(p) new Ast::ParamByRef(p)
