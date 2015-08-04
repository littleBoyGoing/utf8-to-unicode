/* Convert UTF-8 code to Unicode */
#include <stdio.h>
#include <inttypes.h>

/* 0177 == 01111111(bin), 0377 == 11111111(bin) */
#define ONES_COUNT_MASK (0177)
#define MEET_ZERO (0177)
#define MEET_ONE (0377)

int count_prefix_ones(uint8_t c)
{
	int n_ones = 0;
	while ((c | ONES_COUNT_MASK) == MEET_ONE) {
		n_ones++;
		c = c << 1;
	}
	
	return n_ones;
}

int count_utf8_bytes(uint8_t c)
{
	int n_ones = count_prefix_ones(c);
	switch(n_ones) {
	case 0:
		return 1;
		break;
	case 1:
		return 0;
		break;
	default:
		return n_ones;
		break;
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		fprintf(stderr, "Usage: %s <WORDS> [TO] [BE] [CONVERTED]...\n",
				argv[0]);
		return 1;
	}

	int n_remaining_bytes = 0;
	int i, j;
	int nprefix;
	uint32_t bytes = 0;
	for (i = 1; i < argc; i++) {
		for (j = 0; argv[i][j] != '\0';
				j++) {
			n_remaining_bytes = count_utf8_bytes(argv[i][j]);
			while (n_remaining_bytes > 0) {
				/* nprefix = 1s + the divider 0, thus 1 + */
				nprefix = 1 + count_prefix_ones(argv[i][j]);

				argv[i][j] = argv[i][j] << nprefix;
				argv[i][j] = argv[i][j] >> nprefix;

				bytes = bytes << (8-nprefix);
				bytes = bytes | (uint32_t)(argv[i][j]);

				n_remaining_bytes--;
				j++;
			}

			printf("\\u%04X", bytes);
			bytes = 0;
		}

		putchar('\n');
	}

	return 0;
}
