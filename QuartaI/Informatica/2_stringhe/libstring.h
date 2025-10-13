/***
 * Libreria per le stringhe:
 * 1. crea stringa con lunghezza massima predefinita
 * 2. crea stringa di lunghezza variabile in base all'input dell'utente
 * 3. calcola lunghezza stringa
 * 4. concatena due stringhe
 * 5. occorenze di un carattere in una stringa
 * 6. cerca parola in una stringa
 * 7. crea una copia di una stringa
 * 8. confronta se due stringhe sono identiche
 * 9. dividi una stringa in due in base a un separatore
 * 10. trasforma caratteri da minuscolo a maiuscolo o viceversa
 */

typedef char* Stringa; 

/**
 * Pulisce il buffer stdin da eventuali caratteri residui rimasti dal precedente inserimento.
 */
void clear_buffer();

/**
 * Funzione che permette di far inserire all'utente una stringa di dimensione massima N 
 * (compreso il carattere terminatore)
 * @param int n numero di caratteri massimo della stringa compreso '\0'
 * @return stringa puntatore alla stringa allocata
 */
Stringa crea_stringa_dimensionata(int n);

/**
 * Funzione che permette di far inserire all'utente una stringa di qualunque dimensione e di scegliere con quale 
 * carattere terminare l'inserimento
 * @param char terminator carattere che fa terminare la stringa (specificare '\n' di default)
 * @return stringa puntatore alla stringa allocata
 */
Stringa crea_stringa_dinamica(char terminator);

/**
 * Funzione che restituisce il numero di caratteri di una stringa (senza il \0)
 * @param stringa c la stringa di cui calcolare la lunghezza
 * @return int il numero di caratteri (escluso \0)
 */
int calcola_lunghezza_stringa(Stringa s);

/**
 * Funzione che unisce due stringhe con un carattere separatore e restituisce 
 * una terza stringa unica.
 * @param stringa s1 
 * @param stringa  s2 
 * @return stringa che unisce le due in input
 */
Stringa concatena_stringhe(Stringa s1, Stringa s2, char separatore);

/**
 * Funziona che restituisce quante volte compare un carattere
 * in una stringa.
 * @param stringa s1 la stringa in cui cercare
 * @param char carattere il carattere da cercare
 * @return int numero di volte in cui compare il carattere
 */
int conta_occorrenze(Stringa s1, char carattere);

/**
 * Funziona che restituisce quante volte compare una stringa s2
 * in una stringa s1.
 * @param stringa s1 la stringa in cui cercare
 * @param stringa s2 la stringa da cercare
 * @return int numero di volte in cui compare la stringa s2 in s1
 */
int stringa_in_stringa(Stringa s1, Stringa s2);