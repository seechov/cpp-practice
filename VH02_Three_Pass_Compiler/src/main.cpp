#include <bits/stdc++.h>

#include <vector>
#include <string>
#include <regex>

using namespace std;

// start solution

struct AST {
    AST* a;
    AST* b;
    std::string op;
    int n;

    AST(const std::string& op, AST* a, AST* b) {
        this->op = op;
        this->n = 0;
        this->a = a;
        this->b = b;
    }
    AST(const std::string& op, const int n) {
        this->op = op;
        this->n = n;
        this->a = nullptr;
        this->b = nullptr;
    }
};

struct Compiler {

    AST* abstract_syntax_tree = nullptr;
    std::map<std::string, int> arguments;

    vector <string> compile (string program) {
        return pass3 (pass2 (pass1 (program)));
    }

    // Turn a program string into a vector of tokens.  Each token
    // is either '[', ']', '(', ')', '+', '-', '*', '/', a variable
    // name or a number (as a string)
    vector <string> tokenize (string program) {
        static regex re ("[-+*/()[\\]]|[A-Za-z]+|\\d+");
        sregex_token_iterator it (program.begin (), program.end (), re);
        return vector <string> (it, sregex_token_iterator ());
    }

    inline bool isInteger(const std::string& s) {
        if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

        char* p;
        strtol(s.c_str(), &p, 10);

        return (*p == 0);
    }

    void PrintDebugAstInfo(AST* ast, int depth = 0) {
        std::cout << "[Debug PrintDebugAstInfo] ast=" << ast<< " depth=" << depth << " lhs=" << ast->a << " rhs=" << ast->b << " op=" << ast->op << " n=" << ast->n << std::endl;
        if (ast->a != nullptr) {
            PrintDebugAstInfo(ast->a, depth + 1);
        }
        if (ast->b != nullptr) {
            PrintDebugAstInfo(ast->b, depth + 1);
        }
    }

    // [ a b ] ((1 - 3 * (2 - 4)) / (5 - 1) * 3 - 2 - a - b)
    // [ a b ] (1 - a) * (2 + b)
    // [ a b ] a*a + b*b
    // [ first second ] (first + second) / 2 * 3
    // [ first second ] (first + second) / 2
    // [ a b ] (a + b) / 2 - (a + b)/(a - b * 2)
    // [ a b ] a + b
    // [ a b ] a + b * 2
    // [ a b ] a * 2 + b
    // [ a b ] a * 2 + b / 3
    // [ a b ] (a + b) / 2 - (a + b) / (a - b * 2)

    const int plus_minus_priority = 0;
    const int multiply_divide_priority = 1;
    const int parenthesis_priority = 2;
    AST* parse_body_token (std::vector<std::string> tokens) {
        int minimum_priority = parenthesis_priority;
        int minimum_priority_token_index = 0;
        int parenthesis_opened = 0;

        // check for unnecessary parenthesis
        if ((tokens[0] == "(") && (tokens[tokens.size()-1] == ")")) {
            int parenthesis_minimum_level = 1;
            int parenthesis_level = 1;
            for (int i = 1; i < tokens.size()-1; ++i) {
                if (tokens[i] == "(") {
                    if (parenthesis_minimum_level > ++parenthesis_level)
                        parenthesis_minimum_level = parenthesis_level;
                }
                if (tokens[i] == ")") {
                    if (parenthesis_minimum_level > --parenthesis_level)
                        parenthesis_minimum_level = parenthesis_level;
                }
            }
            if (parenthesis_minimum_level == 1) {
                tokens = vector<std::string> {tokens.begin() + 1, tokens.end() - 1};
            }
        }

        const int tokens_size = tokens.size();

        std::cout << "[Debug] start parsing tokens ";
        for (int i = 0; i < tokens_size; ++i) {
            std::cout << tokens[i] << " ";
        }
        std::cout << std::endl;

        if (tokens_size == 1) {
            if (isInteger(tokens[0])) {
                return new AST(std::string("imm"), std::stoi(tokens[0]));
            } else {
                return new AST(std::string("arg"), arguments.at(tokens[0]));
            }
        }

        for (int i = 0; i < tokens_size; ++i) {
            std::cout << "[Debug] function token (" << i << ") = " << tokens[i] << std::endl;
            if (tokens[i] == "(") {
                ++parenthesis_opened;
                std::cout << "[Debug] Operation ++parenthesis_opened. parenthesis_opened = " << parenthesis_opened << std::endl;
                continue;
            } else if (tokens[i] == ")") {
                --parenthesis_opened;
                std::cout << "[Debug] Operation --parenthesis_opened. parenthesis_opened = " << parenthesis_opened << std::endl;
                continue;
            }
            if (((tokens[i] == "*") || (tokens[i] == "/")) &&
                    (minimum_priority >= multiply_divide_priority) &&
                    (parenthesis_opened == 0)) {
                minimum_priority = multiply_divide_priority;
                minimum_priority_token_index = i;
                continue;
            }
            if (((tokens[i] == "+") || (tokens[i] == "-")) &&
                    (minimum_priority >= plus_minus_priority) &&
                    (parenthesis_opened == 0)) {
                minimum_priority = plus_minus_priority;
                minimum_priority_token_index = i;
                continue;
            }
        }

        std::cout << "[Debug] minimum_priority = " << minimum_priority << std::endl;
        std::cout << "[Debug] minimum_priority_token_index = " << minimum_priority_token_index << std::endl;
        std::cout << "[Debug] tokens[minimum_priority_token_index] = " << tokens[minimum_priority_token_index] << std::endl;

        const std::string operation(tokens[minimum_priority_token_index]);
        std::vector<std::string> lhs_tokens;
        std::vector<std::string> rhs_tokens;
        for (int i = 0; i < tokens_size; ++i) {
            if (i < minimum_priority_token_index) {
                lhs_tokens.push_back(tokens[i]);
            }
            if (i > minimum_priority_token_index) {
                rhs_tokens.push_back(tokens[i]);
            }
        }
        return new AST(operation, parse_body_token(lhs_tokens), parse_body_token(rhs_tokens));
    }

    // Returns an un-optimized AST
    AST* pass1 (string program) {
        auto tokens = tokenize (program);
        bool parsing_arguments = false;
        bool parsing_function = false;
        int parsing_arguments_counter = 0;
        std::cout << "[Debug] number of tokens - " << tokens.size() << std::endl;
        for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
            std::cout << "[Debug] program token " << *it << std::endl;
            if (!parsing_function) {
                if (*it == "[") {
                    parsing_arguments = true;
                    std::cout << "[Debug] parsing_arguments = true;" << std::endl;
                } else if (*it == "]") {
                    parsing_arguments = false;
                    parsing_function = true;
                    std::cout << "[Debug] parsing_arguments = false;" << std::endl;
                    std::cout << "[Debug] parsing_function = true;" << std::endl;
                }
                if (parsing_arguments && (*it != "[")) {
                    arguments.insert(std::pair<std::string, int>(*it, parsing_arguments_counter++));
                    std::cout << "[Debug] arguments insert " << *it << " as argument number " << (parsing_arguments_counter - 1) << std::endl;
                }
            } else {
                vector<std::string> functions_tokens = {it, tokens.end()};
                return parse_body_token(functions_tokens);
            }
        }
        return nullptr;
    }

    // Returns an AST with constant expressions reduced
    AST* pass2 (AST* ast) {
        if ((ast->a->op == "arg") && (ast->b->op == "arg")) {
            return ast;
        }
        if ((ast->a->op == "arg") && (ast->b->op == "imm")) {
            return ast;
        }
        if ((ast->a->op == "imm") && (ast->b->op == "arg")) {
            return ast;
        }

        // + () a
        if ((ast->a->op != "imm") && (ast->a->op != "arg") && (ast->b->op == "arg")) {
            AST* new_ast = new AST(ast->op, pass2(ast->a), ast->b);
            delete ast;
            return new_ast;
        }
        // a () +
        if ((ast->b->op != "imm") && (ast->b->op != "arg") && (ast->a->op == "arg")) {
            AST* new_ast = new AST(ast->op, ast->a, pass2(ast->b));
            delete ast;
            return new_ast;
        }
        // + () 5
        if ((ast->a->op != "imm") && (ast->a->op != "arg") && (ast->b->op == "imm")) {
            AST* temp_ast = pass2(ast->a);
            if (temp_ast->op == "imm") {
                AST* new_ast = new AST(ast->op, temp_ast, ast->b);
                delete ast;
                return pass2(new_ast);
            }
            return ast;
        }
        // 5 () +
        if ((ast->b->op != "imm") && (ast->b->op != "arg") && (ast->a->op == "imm")) {
            AST* temp_ast = pass2(ast->b);
            if (temp_ast->op == "imm") {
                AST* new_ast = new AST(ast->op, ast->a, temp_ast);
                delete ast;
                return pass2(new_ast);
            }
            return ast;
        }
        // + () +
        if ((ast->a->op != "imm") && (ast->a->op != "arg") && (ast->b->op != "imm") && (ast->b->op != "imm")) {
            AST* lhs_temp_ast = pass2(ast->a);
            AST* rhs_temp_ast = pass2(ast->b);
            AST* new_ast = new AST(ast->op, lhs_temp_ast, rhs_temp_ast);
            delete ast;
            if ((lhs_temp_ast->op == "imm") && (rhs_temp_ast->op == "imm")) {
                return pass2(new_ast);
            } else {
                return new_ast;
            }
        }
        // 5 () 5
        if ((ast->a->op == "imm") && (ast->b->op == "imm")) {
            AST* new_ast;
            if (ast->op == "+") {
                new_ast = new AST(std::string("imm"), ast->a->n + ast->b->n);
            } else if (ast->op == "-") {
                new_ast = new AST(std::string("imm"), ast->a->n - ast->b->n);
            } else if (ast->op == "*") {
                new_ast = new AST(std::string("imm"), ast->a->n * ast->b->n);
            } else if (ast->op == "/") {
                new_ast = new AST(std::string("imm"), ast->a->n / ast->b->n);
            }
            delete ast;
            return new_ast;
        }


        return ast;
    }

    // Returns assembly instructions
    vector <string> pass3 (AST* ast) {
        std::vector<string> asm_program = pass3iteration(ast);
        asm_program.push_back("PO");
        asm_program = optimize_asm_stack_operations(asm_program);
        return asm_program;
    }

    vector<string> pass3iteration (AST* ast) {
        std::vector<string> asm_program;
        if (((ast->a->op == "imm") || (ast->a->op == "arg")) &&
                ((ast->b->op == "imm") || (ast->b->op == "arg"))) {
            // a + b
            if (ast->b->op == "imm") {
                asm_program.push_back(std::string("IM ") + std::to_string(ast->b->n));
            } else if (ast->b->op == "arg") {
                asm_program.push_back(std::string("AR ") + std::to_string(ast->b->n));
            }
            asm_program.push_back("SW");
            if (ast->a->op == "imm") {
                asm_program.push_back(std::string("IM ") + std::to_string(ast->a->n));
            } else if (ast->a->op == "arg") {
                asm_program.push_back(std::string("AR ") + std::to_string(ast->a->n));
            }
        } else if (((ast->a->op == "imm") || (ast->a->op == "arg")) &&
                   (ast->b->op != "imm") && (ast->b->op != "arg")) {
            // a + ()
            asm_program = pass3iteration(ast->b);
            asm_program.push_back("PO");
            asm_program.push_back("SW");

            if (ast->a->op == "imm") {
                asm_program.push_back(std::string("IM ") + std::to_string(ast->a->n));
            } else if (ast->a->op == "arg") {
                asm_program.push_back(std::string("AR ") + std::to_string(ast->a->n));
            }
        } else if (((ast->b->op == "imm") || (ast->b->op == "arg")) &&
                    (ast->a->op != "imm") && (ast->a->op != "arg")) {
            // () + b
            asm_program = pass3iteration(ast->a);

            if (ast->b->op == "imm") {
                asm_program.push_back(std::string("IM ") + std::to_string(ast->b->n));
            } else if (ast->b->op == "arg") {
                asm_program.push_back(std::string("AR ") + std::to_string(ast->b->n));
            }

            asm_program.push_back("SW");
            asm_program.push_back("PO");
        } else {
            // () + ()
            asm_program = pass3iteration(ast->a);
            vector<string> rhs_asm_program = pass3iteration(ast->b);
            asm_program.insert(asm_program.end(), rhs_asm_program.begin(), rhs_asm_program.end()); // asm_program += rhs_asm_program;
            asm_program.push_back("PO");
            asm_program.push_back("SW");
            asm_program.push_back("PO");
        }

        if (ast->op == "+") {
            asm_program.push_back("AD");
        } else if (ast->op == "-") {
            asm_program.push_back("SU");
        } else if (ast->op == "*") {
            asm_program.push_back("MU");
        } else if (ast->op == "/") {
            asm_program.push_back("DI");
        }
        asm_program.push_back("PU");

        return asm_program;
    }

    vector<string> optimize_asm_stack_operations(vector<string> asm_program) {
        vector<string> optimized_asm_program;
        const int asm_program_size = asm_program.size();
        for (int i = 0; i < asm_program_size - 1; ++i) {
            if ((asm_program[i] == "PU") && (asm_program[i+1] == "PO")) {
                i += 1;
            } else {
                optimized_asm_program.push_back(asm_program[i]);
            }
        }
        return optimized_asm_program;
    }
};

// End solutions

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'sockMerchant' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER_ARRAY ar
 */

int main() {
    string n_temp;
    getline(cin, n_temp);

    string program = ltrim(rtrim(n_temp));

    Compiler compiler;
    auto result1 = compiler.pass1(program);
    std::cout << "pass1 result pointer" <<  result1 << "\n";
    compiler.PrintDebugAstInfo(result1);

    auto result2 = compiler.pass2(result1);
    std::cout << "pass2 result pointer" <<  result2 << "\n";
    compiler.PrintDebugAstInfo(result2);

    vector<string> asm_program = compiler.pass3(result2);
    std::cout << "pass3 result " << "\n";
    for (auto i: asm_program)
      std::cout << i << endl;

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string& str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
