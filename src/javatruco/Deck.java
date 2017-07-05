/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javatruco;

/**
 *
 * @author kaique
 */
public class Deck implements PuxaCarta{
    private Carta[] deck;
    private int topo;
    public static final int NUM_CARTAS = 40;
    
    public Deck(){
        deck = new Carta[NUM_CARTAS];
        fazerMonte();
    }
    
    public void fazerMonte(){
        criaDeck();
        embaralha();
    }
    
    private void criaDeck(){
        topo = NUM_CARTAS-1;
        for(int v=0; v<10; v++){
            for(int n=0; n<4; n++){
                deck[v*4+n] = new Carta(v, n);
            }
        }
    }
    
    private int sorteia(int n){
        return (int)(n*Math.random());
    }
    
    private void embaralha(){
        Carta aux;
        int sort;
        
        for(int i=0; i<NUM_CARTAS;i++){
            sort = sorteia(NUM_CARTAS-i);
            aux = deck[sort];
            deck[sort] = deck[NUM_CARTAS-i-1];
            deck[NUM_CARTAS-i-1] = aux;
        }
    }
    
    public void imprimeDeck(){
        for(int i=0; i<NUM_CARTAS; i++){
            System.out.print(deck[i].Desenho());
        }
        System.out.print("\n");
    }

    @Override
    public Carta obterCarta() {
        Carta c = deck[topo];
        topo--;
        return c;
    }
}
