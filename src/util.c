#include <include/util.h>
#include <stdio.h>

void
print_info(const char *msg, color_t color, bool exit_process,
		bool print_line, const char* file, int line)
{
	char text_col_bold[10] = {0};
	col_str_style(color, BOLD, text_col_bold);

	// Can't see how to use a ternary operator on an integer (__LINE__)
	if(print_line) {
		printf("\n%s%s Line %d: %s%s\n",
			text_col_bold,
			file,
			line,
			msg,
			RESET);
	} else {
		printf("%s%s%s\n", text_col_bold, msg, RESET);
	}

	if(exit_process) {
		exit(1);
	}
}


/**
 * @brief This splits the string s at the first occurence of character c in s.
 *
 * Then s becomes the original string till that character, while the returned
 * value points to the string that was split from it. It can be used like this:
 *
 * char s[] = "hello world foo bye";
 *
 * char *k = tokenize(s, ' ');
 *
 * now s is "hello" while k is "world foo bye"
 *
 * @warning This attempts to modify the string, so please do not use
 * 			string literals
 *
 * @param s
 * @param c
 * @return char*
 */
char*
tokenize(char* s, char c)
{
	char *k = s;
	for(k; *k != c && *k != 0; k++);

	if(*k) {
		*k = 0;
		k++;
	}
	return k;
}