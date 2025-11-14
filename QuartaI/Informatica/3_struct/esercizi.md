# Esercizi sulle struct
## Esercizio 1.
Si crei la struttura libro, in cui ogni libro ha un codice numerico (numero intero) che lo caratterizza, un numero di pagine e un costo.
Si memorizzino i dati di tre libri e si calcoli il costo medio per pagina dei libri e si stampino i dati dei tre libri in ordine crescente di costo per pagina.

## Esercizio 2.
Una società di autonoleggio vuole creare un archivio delle auto disponibili.
Per ogni auto si devono memorizzare:
- Targa
- Marca
- Modello
- Prezzo giornaliero di noleggio

Scrivere un programma in C che:
- Definisca una struct Auto con i campi indicati.
- Implementi le seguenti funzioni:
    - Auto* inserisciAuto(Auto* parco, int* n); → inserisce una nuova auto chiedendo i dati all’utente e rialloca dinamicamente la memoria.
    - void stampaAuto(Auto* parco, int n); → mostra a video tutte le auto memorizzate in formato tabellare.
- Nel main(), permettere di aggiungere più auto fino a quando l’utente lo desidera.
- Aggiungi una funzione void cercaAuto(Auto* parco, int n, char marca[]) per visualizzare solo le auto di una certa marca.

## Esercizio 3.
Un'agenzia viaggi ha bisogno di un piccolo gestionale per memorizzare le prenotazioni dei biglietti aerei fatte per i suoi clienti. 
Per ogni prenotazione si vuole memorizzare: 
- Nome e cognome del cliente
- Codice del volo prenotato
- Data del viaggio
- Prezzo pagato
Scrivere un programma in C che:
- Definisca una struct Prenotazione con i campi indicati (considera di creare una struct Data).
- Implementi le seguenti funzioni:
    - Prenotazione* inserisciPrenotazione(Prenotazione* elenco, int* n); → inserisce una nuova prenotazione chiedendo i dati all’utente e rialloca dinamicamente la memoria.
    - void stampaPrenotazioni(Prenotazione* elenco, int n); → mostra a video tutte le prenotazioni memorizzate in formato tabellare.
- Nel main(), permettere di aggiungere più prenotazioni fino a quando l’utente lo desidera.
- Aggiungi una funzione void cercaPrenotazione(Auto* parco, int n, Data giorno) per visualizzare solo le prenotazioni di un certo giorno.