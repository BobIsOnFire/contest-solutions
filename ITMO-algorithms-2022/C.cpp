#include <bits/stdc++.h>
#include <variant>

class History {
private:
    struct variable {
        int depth = 0;
        int start = 0;
        int value = 0;
    };

    std::vector<int> block_starts = {0};
    std::unordered_map<std::string, std::vector<variable>> variables;
    int enter_count = 0;

    void clean_outdated(std::vector<variable> &v) {
        while (v.back().depth >= block_starts.size() || block_starts[v.back().depth] != v.back().start) {
            v.pop_back();
        }
    }

public:
    void enter_block() {
        enter_count++;
        block_starts.push_back(enter_count);
    }

    void leave_block() {
        block_starts.pop_back();
    }

    int get(std::string &var) {
        std::vector<variable> &stack = variables.emplace(var, std::vector<variable>{{}}).first->second;
        clean_outdated(stack);
        return stack.back().value;
    }

    void set(std::string &var, int value) {
        std::vector<variable> &stack = variables.emplace(var, std::vector<variable>{{}}).first->second;
        clean_outdated(stack);

        variable new_var {
            (int) block_starts.size() - 1,
            block_starts.back(),
            value
        };

        if (stack.back().depth == new_var.depth) {
            stack.back() = new_var;
        } else {
            stack.push_back(new_var);
        }
    }
};

struct OpenBracket {};
struct CloseBracket {};
struct NumberAssign { std::string var; int num; };
struct VarAssign { std::string var1; std::string var2; };

using ParseResult = std::variant<OpenBracket, CloseBracket, NumberAssign, VarAssign>;

// helper type for the std::visit and explicit deduction guide
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

ParseResult parse_line(std::string &line) {
    if (line[0] == '{') return OpenBracket {};
    if (line[0] == '}') return CloseBracket {};

    int delim = line.find("=");
    std::string lvalue = line.substr(0, delim);
    std::string rvalue = line.substr(delim + 1);

    char* p;
    int value = (int) strtol(rvalue.data(), &p, 10);

    if (*p) return VarAssign { lvalue, rvalue };
    return NumberAssign { lvalue, value };
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    History hist;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::visit(overloaded {
            [&](OpenBracket) { hist.enter_block(); },
            [&](CloseBracket) { hist.leave_block(); },
            [&](NumberAssign res) { hist.set(res.var, res.num); },
            [&](VarAssign res) { 
                int val = hist.get(res.var2);
                std::cout << val << "\n";
                hist.set(res.var1, val);
            },
        }, parse_line(line));
    }
}
