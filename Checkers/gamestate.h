#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
@brief     Klasa obslugujaca stan punktowy gry.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class GameState
{
private:
    int blacklPoints;
    int whitePoints;
    bool ifHereWhite;
public:
    /** Konstruktor. */
    GameState();

    /** Pobiera liczbe "czarny" punktow.
    @return Liczba "czarnych" punktow. */
    int getBlackPoints();

    /** Pobiera liczbe "bialych" punktow.
    @return Liczba "bialych" punktow. */
    int getWhitePoints();

    /** Sprawdza, czy lokalnie gracz gra "bialymi" czy "czarnymi" kamieniami.
    @return "true", gdy gracz gra "bialymi", w przeciwnym wypadku "false". */
    bool getIfHereWhite();

    /** Ustawia punktu dla koloru "bialego".
    @param points Liczba punktow.*/
    void setWhitePoints(int points);

    /** Ustawia punktu dla koloru "czarnego".
    @param points Liczba punktow.*/
    void setBlackPoints(int points);

    /** Ustawia, czy gracz gra lokalnie "bialymi" kamieniami.
    @param var "true", gdy gracz gra "bialymi, "false" w przecim wypadku.*/
    void setIfHereWhite(bool var);
};

#endif // GAMESTATE_H
