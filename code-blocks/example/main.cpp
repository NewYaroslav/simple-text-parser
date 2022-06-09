#include <iostream>
#include <simple-text-parser/stp.hpp>

int main() {
    {
        std::string text = u8"Test! Bla Bla Bla\n\n\n. Ok! Simple text parser";
        std::cout << "src text:" << std::endl;
        std::cout << text << std::endl;
        std::cout << "split:" << std::endl;
        std::vector<std::string> temp = simple_text_parser::split(text);
        for (auto &item : temp) {
            std::cout << item << std::endl;
        }
        std::cout << "split (2):" << std::endl;
        std::vector<std::string> temp2 = simple_text_parser::split("?");
        for (auto &item : temp2) {
            std::cout << item << std::endl;
        }
    }
    {
        std::cout << "calc_levenshtein_distance:" << std::endl;
        std::cout << "date | data: " << simple_text_parser::calc_levenshtein_distance("date", "data") << std::endl;
        std::cout << "matata | meta: " << simple_text_parser::calc_levenshtein_distance("matata", "meta") << std::endl;
    }
    {
        std::cout << "compare_word:" << std::endl;
        std::cout << "#0 date | data: " << simple_text_parser::compare_word("date", "data", 0) << std::endl;
        std::cout << "#1 date | data: " << simple_text_parser::compare_word("date", "data", 0.1) << std::endl;
        std::cout << "#2A botatananima | batatananime: " << simple_text_parser::compare_word("botatananima", "batatananime", 0.15) << std::endl;
        std::cout << "#2B botatananima | batatananime: " << simple_text_parser::compare_word_v2("botatananima", {"batatananime"}, {}, 0.15) << std::endl;
        std::cout << "#3A botatananima | banatananime: " << simple_text_parser::compare_word("botatananima", "banatananime", 0.15) << std::endl;
        std::cout << "#3B botatananima | banatananime: " << simple_text_parser::compare_word_v2("botatananima", {"banatananime"}, {}, 0.15) << std::endl;
        std::cout << "#4 ? | banatananime: " << simple_text_parser::compare_word_v2("?", {"banatananime"}, {}, 0.15) << std::endl;
        std::cout << "#5 ? | data: " << simple_text_parser::compare_word("?", "data", 0.1) << std::endl;
    }
    {
        std::string text = u8"Вот Это Прикол! That's funny!";
        std::cout << "src text:" << std::endl;
        std::cout << text << std::endl;
        std::cout << "utf8_to_upr_utf8:" << std::endl;
        std::cout << simple_text_parser::utf8_to_upr_utf8(text) << std::endl;
        std::cout << "utf8_to_lwr_utf8:" << std::endl;
        std::cout << simple_text_parser::utf8_to_lwr_utf8(simple_text_parser::utf8_to_upr_utf8(text)) << std::endl;
    }
    return 0;
}
