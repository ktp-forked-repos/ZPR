#ifndef TESTS_H
#define TESTS_H

#include "board.h"
#include "networkmanager.h"

/**
@brief     Klasa odpowiedzialna za testy jednostkowe.
@details   Wywoluje testy jednostkowe gry oraz testy sieciowe.
@author    Piotr Jastrzebski
@author    Lukasz Tomczak*/
class Tests
{
public:
    Tests();

    /** Wywoluje wszystkie testy.
    @param *board Wskaznik na plansze.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false". */
    static bool runTests(Board *board);

    /** Wywoluje testy sprawdzajace funkcjonalnosc gry.
    @param *board Wskaznik na plansze.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool CheckersTests(Board *board);

    /** Wywoluje testy sprawdzajace poprawnosc ruchow piona.
    @param *board Wskaznik na plansze.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool CTManMove(Board *board);

    /** Wywoluje testy sprawdzajace poprawnosc ruchow damki.
    @param *board Wskaznik na plansze.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool CTKingMove(Board *board);

    /** Wywoluje testy sprawdzajace poprawnosc zbicia piona.
    @param *board Wskaznik na plansze.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool CTManCaptures(Board *board);

    /** Wywoluje testy sprawdzajace poprawnosc zbicia damki.
    @param *board Wskaznik na plansze.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool CTKingCaptures(Board *board);

    /** Wywoluje testy sprawdzajace poprawnosc przemiany w damke.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool CTMakeKing(Board *board);

    /** Wywoluje testy sprawdzajace moment wygranej.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool CTWhiteWins(bool ifTest);

    /** Wywoluje testy sprawdzajace moment przegranej.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool CTBlackWins(bool ifTest);

    /** Wywoluje testy sprawdzajace funkcjonalnosc sieci.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool NetworkTests();

    /** Wywoluje testy sprawdzajace poprawnosc ustanawiania polaczen.
    @param *ns Instancja serwera.
    @param *nc Instancja klienta.
    @param port Zadany port gry.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool NTConnectionTests(NetworkManager *ns, NetworkManager *nc, short port);

    /** Wywoluje testy sprawdzajace poprawnosc startu serwera.
    @param *ns Instancja serwera.
    @param port Zadany port gry.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool NTStartServer(NetworkManager *ns, short port);

    /** Wywoluje testy sprawdzajace poprawnosc dolaczenia klienta.
    @param *nc Instancja klienta.
    @param port Zadany port gry.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool NTConnectClient(NetworkManager *nc, short port);

    /** Wywoluje testy sprawdzajace poprawnosc transportu wiadomosci.
    @param *ns Instancja serwera.
    @param *nc Instancja klienta.
    @param port Zadany port gry.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool NTTransferTests(NetworkManager *ns, NetworkManager *nc, short port);

    /** Wywoluje testy sprawdzajace poprawnosc wyslania wiadomosci od klenta.
    @param *nc Instancja klienta.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool NTClientSends(NetworkManager *nc);

    /** Wywoluje testy sprawdzajace poprawnosc wyslania wiadomosci od serwera.
    @param *ns Instancja serwera.
    @return "true", gdy zaliczono, w przeciwnym wypadku "false".*/
    static bool NTServerSends(NetworkManager *ns);
};

#endif // TESTS_H
