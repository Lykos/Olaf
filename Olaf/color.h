#ifndef COLOR_H
#define COLOR_H

/**
 * @brief The Color enum represents the colors of the chess players. They are guaranteed
 * to be White = 0 and Black = 1, so they can be used as indices safely.
 */
enum Color {
  White = 0,
  Black = 1
};

Color next(Color);

#endif // COLOR_H
