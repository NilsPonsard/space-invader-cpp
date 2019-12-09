#include <gameUtils.h>

struct termios saved_attributes;

termTexture::termTexture(/* args */)
{
}

termTexture::~termTexture()
{
}

void termTexture::show()
{
}
void reset_input_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode(void)
{
    struct termios tattr;
    //char *name;

    /* Make sure stdin is a terminal. */
    if (!isatty(STDIN_FILENO))
    {
        fprintf(stderr, "Not a terminal.\n");
        exit(EXIT_FAILURE);
    }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr(STDIN_FILENO, &saved_attributes);
    atexit(reset_input_mode);

    /* Set the funny terminal modes. */
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON | ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = 0;
    tattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

void Couleur(const std::string &coul)
{
    std::cout << "\033[" << coul << "m";
}

void GotoXY(unsigned X, unsigned Y)
{
    std::cout << "\033[" << X << ';' << Y << "H";

} // gotoxy()

void ClearScreen()
{
    std::cout << "\033[H\033[2J";
}