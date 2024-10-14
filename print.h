/**
 * @file print.h
 * @author yuzujr
 * @brief 终端个性化输出
 * @version 1.10
 * @date 2024-09-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef PRINT_H
#define PRINT_H

#include "print_utils.h"

#define OUTPUT_COLUMN 42

namespace stdprint {

using namespace print_utils;

inline bool isFirstPrint = true;

/**
 * @brief 打印格式字符串
 *
 * @tparam Args
 * @param format_str
 * @param args
 */
template <typename... Args>
void print(const std::string &format_str, Args &&...args) {
    static const std::string color = ColorGenerator::getColor();

#ifndef NO_INTERFACE
    if (isFirstPrint) {
        moveTo(row, OUTPUT_COLUMN);
        isFirstPrint = false;
    }
#endif

    std::string formatted_text =
        std::vformat(format_str, std::make_format_args(args...));

    size_t start = 0;
    size_t end = formatted_text.find('\n');
    while (end != std::string::npos) {
        std::string line = formatted_text.substr(start, end - start);
        std::print("{}{}{}", color, line, "\033[0m");
        moveTo(++row, OUTPUT_COLUMN);
        start = end + 1;
        end = formatted_text.find('\n', start);
    }

    if (start < formatted_text.size()) {
        std::print("{}{}{}", color, formatted_text.substr(start), "\033[0m");
    }
}

/**
 * @brief 打印+换行
 *
 * @tparam Args
 * @param format_str
 * @param args
 */
template <typename... Args>
void println(const std::string &format_str, Args &&...args) {
    print(format_str, args...);
    moveTo(++row, OUTPUT_COLUMN);
}

}  // namespace stdprint

// 避免与标准库print冲突, 非必要，可直接使用stdprint::print 和 stdprint::println
// #define print stdprint::print
// #define println stdprint::println

#endif  // PRINT_H