#ifndef SIMPLE_TEXT_PARSER_HPP_INCLUDED
#define SIMPLE_TEXT_PARSER_HPP_INCLUDED

#include <vector>
#include <string>
#include "utf8.h"

namespace simple_text_parser {

	/** \brief Разобрать строку списка
	 * \param text 		Исходный текст
	 * \param delimiter	Список разделителей
	 */
	std::vector<std::string> split(const std::string &text, const std::string &delimiter = "\t\n\r!,. ") noexcept {
		std::vector<std::string> result;

		size_t found = text.find_first_of(delimiter);
		size_t start_index = 0;

		while(found != std::string::npos) {
			std::size_t len = found - start_index;
            if(len > 0) result.push_back(text.substr(start_index, len));
            start_index = found + 1;
            found = text.find_first_of(delimiter, start_index);
			/*
			result.push_back(std::string(text.begin() + start_index, text.begin() + found));
			start_index = found + 1;
			found = text.find_first_of(delimiter, start_index);
			*/
		}
		if(start_index != text.size()) {
			result.push_back(std::string(text.begin() + start_index, text.end()));
		}
		return result;
	}

	/* Алгоритм Расстояния Левенштейна
	 * Расстояние Левенштейна между двумя словами-это минимальное количество односимвольных правок
	 * (т. е. вставок, удалений или замен),
	 * необходимых для изменения одного слова в другое
	 * Оригинал кода: https://www.nookery.ru/hamming-distance-and-lowenstein-distance-example-implementation-in-c/
	 */
	size_t calc_levenshtein_distance(
			const std::vector<std::string> &s,
			const std::vector<std::string> &t) noexcept {
		const size_t n = s.size();
		const size_t m = t.size();
		// step 1
		if (n == 0) return m;
		if (m == 0) return n;
		// step 2
		std::vector<std::vector<size_t>> d(n + 1, std::vector<size_t>(m + 1, 0));
		for (size_t i = 0; i <= n; ++i) {
			d[i][0] = i;
		}
		for (size_t j = 0; j <= m; ++j) {
			d[0][j] = j;
		}
		// Step 3
		for (size_t i = 1; i <= n; ++i) {
			//Step 4
			for (size_t j = 1; j <= m; j++) {
				// Step 5
				const size_t cost = (t[j - 1] == s[i - 1]) ? 0 : 1;
				// Step 6
				d[i][j] = std::min(
					std::min(d[i - 1][j] + 1, d[i][j - 1] + 1),
					d[i - 1][j - 1] + cost);
			}
		}
		// Step 7
		return d[n][m];
    }

	std::vector<std::string> utf8_to_vector(const std::string &text) noexcept {
		if (text.empty()) return std::vector<std::string>();
		std::vector<std::string> temp;

		const std::string utf8_text = utf8::replace_invalid(text);

		char* str = (char*)utf8_text.c_str();    	// utf-8 string
		char* str_i = str;                  	// string iterator
		char* str_end = str + utf8_text.size() + 1;  // end iterator

		while (str_i < str_end) {
			char32_t code = 0;
			try {
				code = utf8::next(str_i, str_end); // get 32 bit code of a utf-8 symbol
			} catch(...) {
				return std::move(temp);
			}
			if (code == 0) continue;
			std::string symbol;
			utf8::append(code, symbol);
			temp.push_back(symbol);
		}
		return std::move(temp);
	}

    size_t calc_levenshtein_distance(const std::string &s, const std::string &t) {
        return calc_levenshtein_distance(utf8_to_vector(s), utf8_to_vector(t));
    }

	bool compare_word_v2(
			const std::string &src,
			const std::vector<std::string> &dst,
			const std::vector<std::string> no_dst,
			const double max_threshold = 0.15) {
		std::vector<std::string> src_utf8 = utf8_to_vector(src);
		std::vector<std::vector<std::string>> dst_utf8;
		std::vector<std::vector<std::string>> no_dst_utf8;

		for (size_t i = 0; i < dst.size(); ++i) {
			dst_utf8.push_back(utf8_to_vector(dst[i]));
		}

		for (size_t i = 0; i < no_dst.size(); ++i) {
			no_dst_utf8.push_back(utf8_to_vector(no_dst[i]));
		}

		size_t min_distance = src_utf8.size();
		bool is_ok = false;
		for (size_t i = 0; i < dst_utf8.size(); ++i) {
			size_t max_distance = (size_t)(max_threshold * (double)dst_utf8[i].size() + 0.5d);
			if (max_threshold > 0 && max_distance == 0) max_distance = 1;
			if (max_distance < min_distance) min_distance = max_distance;
			const size_t distance = calc_levenshtein_distance(src_utf8, dst_utf8[i]);
			if (distance <= max_distance) {
				is_ok = true;
				break;
			}
		}

		if (!is_ok) return false;

		for (size_t i = 0; i < no_dst.size(); ++i) {
			const size_t no_dst_distance = calc_levenshtein_distance(src_utf8, no_dst_utf8[i]);
			if (no_dst_distance <= min_distance) return false;
		}
		return true;
	}

	bool compare_word(
            const std::string &src,
            const std::string &dst,
            const std::vector<std::string> &no_dst,
            const double max_threshold = 0.15) {
		std::vector<std::string> src_utf8 = utf8_to_vector(src);
		std::vector<std::string> dst_utf8 = utf8_to_vector(dst);
		std::vector<std::vector<std::string>> no_dst_utf8;

		for (size_t i = 0; i < no_dst.size(); ++i) {
			no_dst_utf8.push_back(utf8_to_vector(no_dst[i]));
		}

		size_t max_distance = (size_t)(max_threshold * (double)dst_utf8.size() + 0.5d);
		if (max_threshold > 0 && max_distance == 0) max_distance = 1;
		const size_t distance = calc_levenshtein_distance(src_utf8, dst_utf8);

		if (distance > max_distance) return false;

		for (size_t i = 0; i < no_dst.size(); ++i) {
			const size_t no_dst_distance = calc_levenshtein_distance(src_utf8, no_dst_utf8[i]);
			if (no_dst_distance <= max_distance) return false;
		}
		return true;
	}

	bool compare_word(
            const std::string &src,
            const std::string &dst,
            const double max_threshold = 0.15) {
		std::vector<std::string> src_utf8 = utf8_to_vector(src);
		std::vector<std::string> dst_utf8 = utf8_to_vector(dst);

		size_t max_distance = (size_t)(max_threshold * (double)dst_utf8.size() + 0.5d);
		if (max_threshold > 0 && max_distance == 0) max_distance = 1;
		const size_t distance = calc_levenshtein_distance(src_utf8, dst_utf8);
		if (distance > max_distance) return false;
		return true;
	}
};

#endif
