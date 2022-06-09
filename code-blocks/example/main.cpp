#include <iostream>
#include <simple-text-parser/stp.hpp>

int main() {
    {
        std::string text = u8"Test! Bla Bla Bla\n\n\n. Ok! Simple text parser";
        std::cout << "text:" << std::endl;
        std::cout << text << std::endl;
        std::cout << "start split:" << std::endl;
        std::vector<std::string> temp = simple_text_parser::split(text);
        for (auto &item : temp) {
            std::cout << item << std::endl;
        }
    }
    {
        std::cout << "start calc_levenshtein_distance:" << std::endl;
        std::cout << "date | data: " << simple_text_parser::calc_levenshtein_distance("date", "data") << std::endl;
        std::cout << "matata | meta: " << simple_text_parser::calc_levenshtein_distance("matata", "meta") << std::endl;
    }
    {
        std::cout << "start compare_word:" << std::endl;
        std::cout << "#0 date | data: " << simple_text_parser::compare_word("date", "data", 0) << std::endl;
        std::cout << "#1 date | data: " << simple_text_parser::compare_word("date", "data", 0.1) << std::endl;
        std::cout << "#2 botatananima | batatananime: " << simple_text_parser::compare_word("botatananima", "batatananime", 0.15) << std::endl;
        std::cout << "#3 botatananima | banatananime: " << simple_text_parser::compare_word("botatananima", "banatananime", 0.15) << std::endl;
    }
    return 0;
}
