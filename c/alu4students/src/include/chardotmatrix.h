unsigned int ndots = 8;
unsigned int mdots = 5;
unsigned int maxchar = 96;
struct charmapentry {
	int ix; // dotmatrix table index
	unsigned char symbol; // symbol in dotmatix table at index ix
	char * namestr;
};
unsigned char charscreen[] = " #!#! ";
struct charmapentry chartable[] = { { 0, ' ', "space" }, { 1, '!', "space" }, {
		2, '"', "double quote" }, { 3, '#', "hash" } };

char *dot5x8matrix[] = {
//space
		"00000000", "00000000", "00000000", "00000000", "00000000",

//exclamation_mark
		"00000000", "00000000", "01111001", "00000000", "00000000",

//double_quotes
		"00000000", "01110000", "00000000", "01110000", "00000000",

//hash
		"00010100", "01111111", "00010100", "01111111", "00010100",

//dollar_sign
		"00010010", "00101010", "01111111", "00101010", "00100100",

//percent
		"01100010", "01100100", "00001000", "00010011", "00100011",

//ampersand
		"00110110", "01001001", "01010101", "00100010", "00000101",

//apostrophe
		"00000000", "01010000", "01100000", "00000000", "00000000",

//left_parenthesis
		"00000000", "00011100", "00100010", "01000001", "00000000",

//right_parenthesis
		"00000000", "01000001", "00100010", "00011100", "00000000",

//asterisk
		"00010100", "00001000", "00111110", "00001000", "00010100",

//plus
		"00001000", "00001000", "00111110", "00001000", "00001000",

//comma
		"00000000", "00000101", "00000110", "00000000", "00000000",

//minus
		"00001000", "00001000", "00001000", "00001000", "00001000",

//full_stop
		"00000000", "00000011", "00000011", "00000000", "00000000",

//forward_slash
		"00000010", "00000100", "00001000", "00010000", "00100000",

//zero
		"00111110", "01000101", "01001001", "01010001", "00111110",

//one
		"00000000", "00100001", "01111111", "00000001", "00000000",

//two
		"00100001", "01000011", "01000101", "01001001", "00110001",

//three
		"01000010", "01000001", "01010001", "01101001", "01000110",

//four
		"00001100", "00010100", "00100100", "01111111", "00000100",

//five
		"01110010", "01010001", "01010001", "01010001", "01001110",

//six
		"00011110", "00101001", "01001001", "01001001", "00000110",

//seven
		"01000000", "01000111", "01001000", "01010000", "01100000",

//eight
		"00110110", "01001001", "01001001", "01001001", "00110110",

//nine
		"00110000", "01001001", "01001001", "01001010", "00111100",

//colon
		"00000000", "00110110", "00110110", "00000000", "00000000",

//semicolon
		"00000000", "00110101", "00110110", "00000000", "00000000",

//less_than
		"00001000", "00010100", "00100010", "01000001", "00000000",

//equals
		"00010100", "00010100", "00010100", "00010100", "00010100",

//greater_than
		"00000000", "01000001", "00100010", "00010100", "00001000",

//question_mark
		"00100000", "01000000", "01000101", "01001000", "00110000",

//at
		"00100110", "01001001", "01001111", "01000001", "00111110",

//A
		"00111111", "01000100", "01000100", "01000100", "00111111",

//B
		"01111111", "01001001", "01001001", "01001001", "00110110",

//C
		"00111110", "01000001", "01000001", "01000001", "00100010",

//D
		"01111111", "01000001", "01000001", "00100010", "00011100",

//E
		"01111111", "01001001", "01001001", "01001001", "01000001",

//F
		"01111111", "01001000", "01001000", "01001000", "01000000",

//G
		"00111110", "01000001", "01001001", "01001001", "00101111",

//H
		"01111111", "00001000", "00001000", "00001000", "01111111",

//I
		"00000000", "01000001", "01111111", "01000001", "00000000",

//J
		"00000010", "00000001", "01000001", "01111110", "01000000",

//K
		"01111111", "00001000", "00010100", "00100010", "01000001",

//L
		"01111111", "00000001", "00000001", "00000001", "00000001",

//M
		"01111111", "00100000", "00011000", "00100000", "01111111",

//N
		"01111111", "00010000", "00001000", "00000100", "01111111",

//O
		"00111110", "01000001", "01000001", "01000001", "00111110",

//P
		"01111111", "01001000", "01001000", "01001000", "00110000",

//Q
		"00111110", "01000001", "01000101", "01000010", "00111101",

//R
		"01111111", "01001000", "01001100", "01001010", "00110001",

//S
		"00110001", "01001001", "01001001", "01001001", "01000110",

//T
		"01000000", "01000000", "01111111", "01000000", "01000000",

//U
		"01111110", "00000001", "00000001", "00000001", "01111110",

//V
		"01111100", "00000010", "00000001", "00000010", "01111100",

//W
		"01111110", "00000001", "00001110", "00000001", "01111110",

//X
		"01100011", "00010100", "00001000", "00010100", "01100011",

//Y
		"01110000", "00001000", "00000111", "00001000", "01110000",

//Z
		"01000011", "01000101", "01001001", "01010001", "01100001",

//left_square
		"00000000", "01111111", "01000001", "01000001", "00000000",

//back_slash
		"00100000", "00010000", "00001000", "00000100", "00000010",

//right_square
		"00000000", "01000001", "01000001", "01111111", "00000000",

//circumflex
		"00010000", "00100000", "01000000", "00100000", "00010000",

//underscore
		"00000001", "00000001", "00000001", "00000001", "00000001",

//grave_accent
		"00000000", "01000000", "00100000", "00010000", "00000000",

//a
		"00000010", "00010101", "00010101", "00010101", "00001111",

//b
		"01111111", "00001001", "00001001", "00001001", "00000110",

//c
		"00001110", "00010001", "00010001", "00010001", "00010001",

//d
		"00000110", "00001001", "00001001", "00001001", "01111111",

//e
		"00001110", "00010101", "00010101", "00010101", "00001101",

//f
		"00000000", "00001000", "00111111", "01001000", "00100000",

//g
		"00001001", "00010101", "00010101", "00010101", "00011110",

//h
		"01111111", "00001000", "00001000", "00001000", "00000111",

//i
		"00000000", "00000000", "00101111", "00000000", "00000000",

//j
		"00000010", "00000001", "00000001", "01011110", "00000000",

//k
		"00000000", "01111111", "00000100", "00001010", "00010001",

//l
		"00000000", "01000001", "01111111", "00000001", "00000000",

//m
		"00011111", "00010000", "00001110", "00010000", "00011111",

//n
		"00011111", "00001000", "00010000", "00010000", "00001111",

//o
		"00001110", "00010001", "00010001", "00010001", "00001110",

//p
		"00011111", "00010100", "00010100", "00010100", "00001000",

//q
		"00001000", "00010100", "00010100", "00010100", "00011111",

//r
		"00011111", "00001000", "00010000", "00010000", "00001000",

//s
		"00001001", "00010101", "00010101", "00010101", "00010010",

//t
		"00010000", "00010000", "01111110", "00010001", "00010010",

//u
		"00011110", "00000001", "00000001", "00000001", "00011110",

//v
		"00011100", "00000010", "00000001", "00000010", "00011100",

//w
		"00011110", "00000001", "00000110", "00000001", "00011110",

//x
		"00010001", "00001010", "00000100", "00001010", "00010001",

//y
		"00010000", "00001001", "00000110", "00001000", "00010000",

//z
		"00010001", "00010011", "00010101", "00011001", "00010001",

//leftcurly
		"00001000", "00110110", "01000001", "01000001", "00000000",

//vertline
		"00000000", "00000000", "01111111", "00000000", "00000000",

//rightcurly
		"00000000", "01000001", "01000001", "00110110", "00001000",

//tilde
		"00000100", "00001000", "00001000", "00001000", "00010000",

		//del
		"01111111", "01000001", "01000001", "01000001", "01111111" };