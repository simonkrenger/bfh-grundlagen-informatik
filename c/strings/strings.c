/**
 * Strings exercise
 *
 * Prologue: there is no such thing as string in C
 * (Olivier Buechel, 2006)
 *
 * Before reading this, note that this is our first shot at C, so
 * beware of bad code...
 *
 * Author: Simon Krenger, Dec 2011
 */
#include <stdio.h>

/**
 * Calculate the length of a character array.
 * Well, better use strlen()!
 */
int length(char str[]) {
	int len;
	for (len = 0; str[len] != '\0'; len++)
		;
	return len;
}

/**
 * Calculates the (one-based) last position of a character <letter> in a string
 * <str>. If <letter> does not occur in <str>, returns -1.
 */
int last(char letter, char str[]) {
	int str_len = length(str);

	int i = 0;
	for (i = (str_len - 1); i >= 0; i--) {
		if (str[i] == letter)
			return i;
	}
	return -1;
}

/**
 * Calculates the (one-based) first position of a character <letter> in
 * a string <str>. If <letter> doesn't  occur in <str> it returns -1
 */
int first(char letter, char str[]) {
	int str_len = length(str);

	int i;
	for (i = 0; i < str_len; i++) {
		if (str[i] == letter)
			return i + 1;
	}
	return -1;
}

/**
 * Function to count the occurrences of a single character in a character array.
 */
int count(char t, char s[]) {
	int occ = 0;
	int str_len = length(s);

	int i;
	for (i = 0; i < str_len; i++) {
		if (s[i] == t)
			occ++;
	}
	return occ;
}

/**
 * Return index of first letter of longest word in string <str>
 */
int longest(char str[]) {

	int cur_word_len = 0, longest_len = 0;
	int i, longest_idx = 0, cur_word_idx = 0;
	int total_len = length(str);

	for (i = 0; i < total_len; i++) {
		if (str[i] == ' ') {
			// Uhoh, a new word!
			cur_word_idx = i + 1;
			cur_word_len = 0;
		} else {
			cur_word_len++;
			if (cur_word_len > longest_len) {
				longest_len = cur_word_len;
				longest_idx = cur_word_idx;
			}
		}
	}
	return longest_idx;
}

/**
 * When are two string equal?
 * Returns 0 when they are equal, or 1 if they are not
 * If you want something sophisticated, use strcmp()!
 */
int cmp_strings(char str_a[], char str_b[]) {
	if (length(str_a) == length(str_b)) {
		int i;
		for (i = 0; i < length(str_a); i++) {
			if (str_a[i] != str_b[i])
				return 1;
		}
		return 0;
	}
	return 1;
}

/**
 * Print the distribution of the chars in <str>, i.e.
 * For each char in alphabet, how many time does it appear in <str>?
 */
void print_char_distr(char str[]) {
	int characters[26] = { };
	int str_len = length(str);

	// Count
	int i;
	for (i = 0; i < str_len; i++) {
		int chars_upper = (str[i] >= 65 && str[i] <= 90);
		int chars_lower = (str[i] >= 97 && str[i] <= 122);
		if (chars_upper || chars_lower) {
			if (chars_upper) {
				characters[str[i] - 65]++;
			} else {
				characters[str[i] - 97]++;
			}
		}
	}

	// Print the occurrences
	for (i = 0; i < 26; i++) {
		if (characters[i] != 0)
			printf("%c: %d\n", i + 65, characters[i]);
	}
}

/**
 * Replaces each instance of character <old> in string <str> with
 * character <new>. Returns the number of changed characters.
 */
int substitute(char old, char new, char str[]) {
	int str_length = length(str);
	int chars_changed = 0;

	int i;
	for (i = 0; i < str_length; i++) {
		if (str[i] == old) {
			str[i] = new;
			chars_changed++;
		}
	}
	return chars_changed;
}

/**
 * Replace upper case characters with lower case characters
 * Return number of occurrences
 */
int str_to_lower(char str[]) {
	int str_len = length(str);
	int occ = 0;

	int i;
	for (i = 0; i < str_len; i++) {
		if (str[i] >= 65 && str[i] <= 90) {
			str[i] = str[i] + 32;
			occ++;
		}
	}
	return occ;
}

/**
 * Replace lower case characters with upper case characters.
 * Return number of occurrences
 */
int str_to_upper(char str[]) {
	int str_len = length(str);
	int occ = 0;

	int i;
	for (i = 0; i < str_len; i++) {
		if (str[i] >= 97 && str[i] <= 122) {
			str[i] = str[i] - 32;
			occ++;
		}
	}
	return occ;
}

int main(int argc, char *argv[]) {

	// Quite ugly to print it like this, but hey...

	char test_string[] = "Hello World";
	char another_string[] = "hella warld";
	char single_char = 'l';

	printf("Length of test-string \"%s\": %d\n", test_string,
			length(test_string));

	printf("Last occurrence of character %c in test-string \"%s\": %d\n",
			single_char, test_string, last(single_char, test_string));

	printf("First occurrence of character %c in test-string \"%s\": %d\n",
			single_char, test_string, first(single_char, test_string));

	printf("Count of character %c in test-string \"%s\": %d\n", single_char,
			test_string, count(single_char, test_string));

	printf("Longest word of test-string \"%s\" is at index: %d\n", test_string,
			longest(test_string));

	printf("Character distribution in \"%s\":\n", test_string);
	print_char_distr(test_string);

	printf("When substituting %c with %c, you have to do %d substitutions.\n",
			'o', 'a', substitute('o', 'a', test_string));
	printf("The string is now \"%s\"\n", test_string);

	printf("Let us convert \"%s\" to lower case.\n", test_string);
	printf("When converting to lower case, %d chars have to be replaced\n",
			str_to_lower(test_string));
	printf("The string is now \"%s\"\n", test_string);

	printf("Result of comparison: %d\n",
			cmp_strings(test_string, another_string));

	return 0;
}
