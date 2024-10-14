/**
 * @file print_utils.h
 * @author yuzujr
 * @brief print工具类
 * @version 1.1
 * @date 2024-09-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <cstdlib>
#include <ctime>
#include <print>
#include <string>

// 禁用界面
// #define NO_INTERFACE

namespace print_utils {

/**
 * @brief 终端当前行数
 */
inline int row = 3;

/**
 * @brief 颜色生成类
 *
 */
class ColorGenerator {
   public:
    static const std::string &getColor() {
        static const std::string color = generateColor();
        return color;
    }

   private:
    static std::string generateColor() {
        return "\033[3" + std::to_string(rand() % 6 + 1) + ";3m";
    }
};

/**
 * @brief 界面管理类
 *  用于初始化和销毁界面
 */
class interfaceManager {
   public:
    interfaceManager() {
        srand(static_cast<unsigned>(time(nullptr)));
        const std::string color =
            "\033[3" + std::to_string(rand() % 6 + 1) + ";3m";
        std::print(
            R"({}┌───────────────────────────────────┐  Console output:
│                            _      │
│  _   _ _   _ _____   _    | |_ __ │
│ | | | | | | |_  / | | |_  | | '__|│
│ | |_| | |_| |/ /| |_| | |_| | |   │
│ \__, |\__,_/___|\__,_|\____|_|    │
│ |___/                             │
└───────────────────────────────────┘
)",
            color);
        std::print("Console input: {}", "\033[0m");
    }
    ~interfaceManager() {
        std::print("\033[{};0H", std::max<int>(row + 1, 11));
    }
};

/**
 * @brief 移动光标到指定行和列
 * @brief NO_INTERFACE为true时, moveTo退化为换行
 */
inline void moveTo(int row, int col);

#ifdef NO_INTERFACE
inline void moveTo(int row [[maybe_unused]], int col [[maybe_unused]]) {
    std::print("\n");
}
#else
inline interfaceManager initializer;  // 自动触发构造和析构
inline void moveTo(int row, int col) {
    std::print("\033[{};{}H", row, col);
}
#endif

}  // namespace print_utils