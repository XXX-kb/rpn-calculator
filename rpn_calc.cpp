#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <iomanip>
using namespace std;

// 计算历史记录结构
struct HistoryItem {
    string expression;
    double result;
};

vector<HistoryItem> history;

// 显示帮助信息
void showHelp() {
    cout << "\n=== RPN计算器帮助 ===" << endl;
    cout << "基本运算: 数字 + - * /" << endl;
    cout << "特殊命令:" << endl;
    cout << "  help     - 显示帮助" << endl;
    cout << "  history  - 显示计算历史" << endl;
    cout << "  clear    - 清空历史记录" << endl;
    cout << "  quit     - 退出程序" << endl;
    cout << "批量计算: 用分号 ; 分隔多个表达式" << endl;
    cout << "示例: '5 5 + ; 10 2 / ; 3 4 *'" << endl;
    cout << "====================\n" << endl;
}

// 显示历史记录
void showHistory() {
    if (history.empty()) {
        cout << "历史记录为空" << endl;
        return;
    }
    
    cout << "\n=== 计算历史 ===" << endl;
    for (int i = 0; i < history.size(); i++) {
        cout << i + 1 << ". " << history[i].expression 
             << " = " << fixed << setprecision(6) << history[i].result << endl;
    }
    cout << "总计: " << history.size() << " 条记录" << endl;
}

// 清空历史记录
void clearHistory() {
    history.clear();
    cout << "历史记录已清空" << endl;
}

// 计算单个RPN表达式
bool calculateExpression(const string& expr, double& result) {
    stack<double> st;
    istringstream iss(expr);
    string token;
    
    while (iss >> token) {
        if (token == "+") {
            if (st.size() < 2) return false;
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            st.push(a + b);
        }
        else if (token == "-") {
            if (st.size() < 2) return false;
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            st.push(a - b);
        }
        else if (token == "*") {
            if (st.size() < 2) return false;
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            st.push(a * b);
        }
        else if (token == "/") {
            if (st.size() < 2) return false;
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            if (b == 0) return false;
            st.push(a / b);
        }
        else {
            // 尝试转换为数字
            double num;
            istringstream tokenStream(token);
            if (tokenStream >> num) {
                st.push(num);
            } else {
                return false; // 不是数字也不是操作符
            }
        }
    }
    
    if (st.size() == 1) {
        result = st.top();
        return true;
    }
    return false;
}

// 处理批量计算
void processBatch(const string& input) {
    vector<string> expressions;
    string expr;
    
    // 手动分割分号
    for (int i = 0; i < input.length(); i++) {
        char c = input[i];
        if (c == ';') {
            if (!expr.empty()) {
                expressions.push_back(expr);
                expr.clear();
            }
        } else {
            expr += c;
        }
    }
    if (!expr.empty()) {
        expressions.push_back(expr);
    }
    
    if (expressions.empty()) {
        cout << "错误: 没有有效的表达式" << endl;
        return;
    }
    
    cout << "批量计算 " << expressions.size() << " 个表达式:" << endl;
    for (int i = 0; i < expressions.size(); i++) {
        double result;
        if (calculateExpression(expressions[i], result)) {
            HistoryItem item;
            item.expression = expressions[i];
            item.result = result;
            history.push_back(item);
            cout << "  " << (i + 1) << ". " << expressions[i] 
                 << " = " << fixed << setprecision(6) << result << endl;
        } else {
            cout << "  " << (i + 1) << ". " << expressions[i] 
                 << " = [错误]" << endl;
        }
    }
}

int main() {
    string input;
    
    cout << "=== RPN计算器 ===" << endl;
    cout << "输入 'help' 查看使用说明" << endl;
    
    while (true) {
        cout << "> ";
        getline(cin, input);
        
        // 去除前后空格
        string cmd;
        int start = 0;
        int end = input.length() - 1;
        
        // 找到第一个非空格字符
        while (start <= end && (input[start] == ' ' || input[start] == '\t')) {
            start++;
        }
        // 找到最后一个非空格字符
        while (end >= start && (input[end] == ' ' || input[end] == '\t')) {
            end--;
        }
        
        if (start > end) {
            continue; // 空输入
        }
        
        cmd = input.substr(start, end - start + 1);
        
        if (cmd == "quit" || cmd == "q") {
            break;
        }
        else if (cmd == "help") {
            showHelp();
        }
        else if (cmd == "history") {
            showHistory();
        }
        else if (cmd == "clear") {
            clearHistory();
        }
        else if (cmd.find(';') != string::npos) {
            // 批量计算
            processBatch(cmd);
        }
        else {
            // 单个表达式计算
            double result;
            if (calculateExpression(cmd, result)) {
                HistoryItem item;
                item.expression = cmd;
                item.result = result;
                history.push_back(item);
                cout << "结果: " << fixed << setprecision(6) << result << endl;
            } else {
                cout << "错误: 表达式无效" << endl;
            }
        }
    }
    
    cout << "再见! 本次计算了 " << history.size() << " 个表达式" << endl;
    return 0;
}
