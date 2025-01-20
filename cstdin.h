#ifndef CSTDIN_H
#define CSTDIN_H
#include <ctype.h>

struct termios old, current;

char buffer[100];

/**
 * @brief Clears the standard input buffer.
 *
 * This function sets the read pointer of the standard input stream to the end
 * of the input buffer, effectively discarding any unread input.
 *
 * @note This function directly manipulates the internal structure of the
 *       standard input stream, which may not be portable across different
 *       platforms or library implementations.
 * 
 * @warning
 * This function is not portable and may not work as expected on all systems. 
 * The intention is to flush the input buffer, but the implementation may vary.
 * If you want a more portable solution, consider using the following approach:
 * 
 * ```
 * int c;
 * while ((c = getchar()) != '\n' && c != EOF);
 * ```
 * 
 * The reason the approach above is not being used is only because it does not 
 * discard the input from the buffer, it just reads the next character from the
 * buffer, and if there isn't a character in the buffer, it'll wait for a input 
 * from the keyboard, which is not the desired approach.
 * 
 * Be careful when using this function, as it may not work as expected on a long
 * or complex program.
 */
void clear_stdin() {
    stdin->_IO_read_ptr = stdin->_IO_read_end;
}
/**
 * @brief Converts a string to uppercase.
 *
 * This function takes a string and its size as input and converts all
 * lowercase characters in the string to their uppercase equivalents.
 *
 * @param str The string to be converted to uppercase.
 * @param size The size of the string.
 */

void _strupr_(char *str, int size) {
    for (int i = 0; i < size && str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}


/**
 * @brief Initializes terminal I/O settings.
 *
 * This function modifies the terminal settings to enable or disable canonical mode and echo.
 *
 * @param echo If non-zero, echoing of input characters is enabled. If zero, echoing is disabled.
 */
void initTermios(int echo)  {
      tcgetattr(0, &old);
      current = old;
      current.c_lflag &= ~ICANON;
      if (echo) {
          current.c_lflag |= ECHO;
      } else {
          current.c_lflag &= ~ECHO;
      }
      tcsetattr(0, TCSANOW, &current);
}

/**
 * @brief Resets the terminal attributes to their previous state.
 *
 * This function restores the terminal attributes to the state saved in the
 * global variable `old`. It uses the `tcsetattr` function to apply the
 * changes immediately.
 *
 * @note This function assumes that the global variable `old` has been
 *       properly initialized with the previous terminal attributes.
 */
void resetTermios(void)  {
    tcsetattr(0, TCSANOW, &old);
}


/**
 * @brief Reads a single character from standard input.
 *
 * This function reads a single character from standard input without waiting for the Enter key.
 * It temporarily changes the terminal settings to disable or enable echoing of the input character.
 *
 * @param echo If non-zero, the input character will be echoed to the terminal. If zero, the input character will not be echoed.
 * @return The character read from standard input.
 */
char getch_(int echo) {
    initTermios(echo);
    char ch = getchar();
    resetTermios();
    return ch;
}

/**
 * @brief Reads a single character from the standard input.
 *
 * This function reads a single character from the standard input using the
 * `getch_` function and then clears the input buffer using `clear_stdin`.
 *
 * @return The character read from the standard input.
 */
char getch(void) {
    char ch = getch_(0);
    clear_stdin();
    return ch;
}
/**
 * @brief Fills the buffer with input from stdin, converts it to uppercase, and removes the newline character.
 *
 * This function reads a string from stdin into the global buffer, ensuring that the string does not exceed the specified size.
 * It then removes the newline character from the input and converts the string to uppercase.
 *
 * @param size The maximum number of characters to read from stdin (excluding the null terminator).
 */

void fillBuffer(int size) {
    fgets(buffer, size+3, stdin);
    clear_stdin();
    buffer[strcspn(buffer, "\n")] = '\0';
    buffer[size] = '\0';
    _strupr_(buffer, size);
}
#endif