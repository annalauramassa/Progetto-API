# Progetto-API
Repository per la Prova Finale di Algoritmi e Principi dell'Informatica AA 2020/2021 @Politecnico di Milano

Lo scopo del progetto è di implemantare in linguaggio C la gestione di una classifica di grafi diretti pesati.

## Problema
Il programma riceve in ingresso una sola volta due parametri (numero di nodi nei grafi e lunghezza della classifica) e in seguito un comando a scelta tra:
* **AggiungiGrafo**, seguito dalla matrice di adiacenza, per aggiungere un nuovo grafo;
* **TopK**, per mostrare i k grafi migliori inseriti dall'esecuzione del programma.

## Implementazione
Sono state utilizzate le seguenti strutture dati:
* **matrice** per contenere la matrice di adiacenza del grafo in ingresso;
* **maxheap** per la classifica dei grafi.

Per calcolare i cammini minimi dei grafi è stato utilizzata un'implementazione riadattata dell'[algoritmo di Dijkstra](https://it.wikipedia.org/wiki/Algoritmo_di_Dijkstra)

## Testing
L'efficienza spaziale e temporale del codice è stata testata tramite il verificatore online messo a disposizione dai docenti del corso.

