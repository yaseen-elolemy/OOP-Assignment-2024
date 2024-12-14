template <typename T>
void ultimateTTT_board<T>::display_board() {
    // Print column numbers
    std::cout << "    ";
    for (int j = 0; j < this->columns; ++j) {
        std::cout << "   " << j << "    ";
    }
    std::cout << std::endl;

    for (int i = 0; i < this->rows; ++i) {
        // Print row separator
        std::cout << "  +";
        for (int j = 0; j < this->columns; ++j) {
            std::cout << "------+"; // Adjusted for more space
        }
        std::cout << std::endl;

        // Print row number and board content
        std::cout << i << " | ";
        for (int j = 0; j < this->columns; ++j) {
            std::cout << "  " << this->board[i][j] << "   | "; // Adjusted for more space
        }
        std::cout << std::endl;
    }

    // Print bottom row separator
    std::cout << "  +";
    for (int j = 0; j < this->columns; ++j) {
        std::cout << "------+"; // Adjusted for more space
    }
    std::cout << std::endl;
}
