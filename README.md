# rpn-calculator

C++ RPN Calculator - 学校作业

逆波兰表示法（RPN）计算器

## 项目描述
这是一个用C++实现的逆波兰表示法（RPN）计算器，支持四则运算、批量计算和历史记录功能。
操作指南：https://xmy1047206645.github.io/rpn-calculator/

## 功能特性
- 基本四则运算（+ - * /）
- 批量表达式计算（使用分号分隔）
- 计算历史记录
- 错误处理机制
- 输入help查看帮助

## 编译运行

### 使用 Visual C++ 编译（windows）或g++（linux）
```bash
（windows）
#生成.exe文件
cl /EHsc rpn_calc.cpp
#执行exe文件
rpn_calc.exe

（linux）
#编译并生成二进制可执行文件
g++ rpn_calc.cpp -o rpn_calc
#执行文件
./rpn_calc

示例
输入: 5 2 +
结果: 7

输入: 3 4 * 2 / 
结果: 6

输入：5 5 + ;10 2 /
输出：
批量计算 2 个表达式:
  1. 5 5 +  = 10.000000
  2. 10 2 / = 5.000000
