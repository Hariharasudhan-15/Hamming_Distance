#include "ee25b052_ee1103.h"


// Hamming Distance
int hamming_distance(const unsigned char *bits1, const unsigned char *bits2, int num_bits) {
    if (!bits1 || !bits2 || num_bits <= 0) return -1;
    int distance = 0;
    int num_bytes = (num_bits + 7) / 8;
    for (int byte = 0; byte < num_bytes; byte++) {
        unsigned char xor_result = bits1[byte] ^ bits2[byte];
        for (int bit = 0; bit < 8 && (byte * 8 + bit) < num_bits; bit++) {
            if ((xor_result >> bit) & 1) distance++;
        }
    }
    return distance;
}

// Get Bit Value
int get_bit(const unsigned char *arr, int bit_index) {
    if (!arr || bit_index < 0) return 0;
    return (arr[bit_index / 8] >> (bit_index % 8)) & 1;
}

// Set Bit Value
void set_bit(unsigned char *arr, int bit_index, int value) {
    if (!arr || bit_index < 0) return;
    if (value)
        arr[bit_index / 8] |= (1 << (bit_index % 8));
    else
        arr[bit_index / 8] &= ~(1 << (bit_index % 8));
}

// Flip Bit Value
void flip_bit(unsigned char *arr, int bit_index) {
    if (!arr || bit_index < 0) return;
    arr[bit_index / 8] ^= (1 << (bit_index % 8));
}

// Generate random bit values
void generate_random_bits(unsigned char *arr, int num_bits) {
    if (!arr || num_bits <= 0) return;
    int num_bytes = (num_bits + 7) / 8;
    for (int i = 0; i < num_bytes; i++) {
        arr[i] = (unsigned char)(rand() & 0xFF);
    }
    // Zero out unused bits in last byte
    int unused = num_bytes * 8 - num_bits;
    if (unused > 0) {
        arr[num_bytes - 1] &= (0xFF >> unused);
    }
}

// Flip bits with a probability
void flip_bits_with_probability(unsigned char *arr, int num_bits, double probability) {
    if (!arr || num_bits <= 0 || probability < 0.0 || probability > 1.0) return;
    for (int i = 0; i < num_bits; i++) {
        double r = (double)rand() / RAND_MAX;
        if (r < probability) flip_bit(arr, i);
    }
}

// Hamming distance for a window in a bitstream
int hamming_distance_bits(const unsigned char *bitstream, const unsigned char *codeword, int start, int codeword_length) {
    if (!bitstream || !codeword || start < 0 || codeword_length <= 0) return -1;
    int distance = 0;
    for (int i = 0; i < codeword_length; i++) {
        int b1 = get_bit(bitstream, start + i);
        int b2 = get_bit(codeword, i);
        if (b1 != b2) distance++;
    }
    return distance;
}

// Finding codeword in a bit stream
int find_codeword(const unsigned char *bitstream, int stream_length,
                  const unsigned char *codeword, int codeword_length,
                  HammingResult *results, int max_results) {
    if (!bitstream || !codeword || !results || stream_length <= 0 || codeword_length <= 0 || max_results <= 0)
        return 0;
    int found = 0;
    for (int i = 0; i <= stream_length - codeword_length; i++) {
        int dist = hamming_distance_bits(bitstream, codeword, i, codeword_length);
        if (found < max_results) {
            results[found].location = i;
            results[found].distance = dist;
            found++;
        } else {
            int worst = 0;
            for (int j = 1; j < max_results; j++)
                if (results[j].distance > results[worst].distance)
                    worst = j;
            if (dist < results[worst].distance) {
                results[worst].location = i;
                results[worst].distance = dist;
            }
        }
    }
    return found;
}

// Converting string to bit arrays
void string_to_bits(const char *str, unsigned char *arr, int length) {
    if (!str || !arr || length <= 0) return;
    int num_bytes = (length + 7) / 8;
    for (int i = 0; i < num_bytes; i++)
        arr[i] = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] == '1')
            arr[i / 8] |= (1 << (i % 8));
        else
            arr[i / 8] &= ~(1 << (i % 8));
    }
}

// Writing bit arrays into binary file
void write_bits_to_file(const char *filename, const unsigned char *arr, int num_bits) {
    if (!filename || !arr || num_bits <= 0) return;
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Error: cannot open file %s for writing\n", filename);
        return;
    }
    int num_bytes = (num_bits + 7) / 8;
    fwrite(arr, sizeof(unsigned char), num_bytes, fp);
    fclose(fp);
}

// Reading bit arrays from binary file
void read_bits_from_file(const char *filename, unsigned char *arr, int num_bits) {
    if (!filename || !arr || num_bits <= 0) return;
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Error: cannot open file %s for reading\n", filename);
        return;
    }
    int num_bytes = (num_bits + 7) / 8;
    fread(arr, sizeof(unsigned char), num_bytes, fp);
    fclose(fp);
}
