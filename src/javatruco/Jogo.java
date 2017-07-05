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
public class Jogo {
    
    private Mesa mesa;
    private Deck deck;
    private Jogador jogadores[];
    private int emJogo;
    private int proximo;
    private int daCarta;
    
    
    public Jogo(int jogadores){
        mesa = new Mesa();
        deck = new Deck();
        this.jogadores = new Jogador[jogadores];
        emJogo = 0;
        daCarta = 0; 
        proximo = 0;
    }
    
    public void addJogador(Jogador j){
        this.jogadores[emJogo] = j;
        emJogo++;
    }
    
    public void distribuirCartas(){
        /* Faz a distribuição um a um */
        for(int i=0; i<3; i++){
            for(int j=0; j<emJogo; j++){
                this.jogadores[j].darCarta(deck.obterCarta());
            }
        }
        /* Vira a ultima carta */
        mesa.vira(deck.obterCarta());
    }
    
    private int verMaior(Carta[] c){
        int maior = 0, disp;
        for(int i=0; i<emJogo; i++){
            if(c[i]==null)
                continue;
            if(mesa.getMaior()==null)
                mesa.setMaior(c[i]);
            if(mesa.getMaior()==c[i])
                continue;
            disp = c[i].Ganha(mesa.getMaior(), mesa.getVira());
            if(disp==Carta.GANHA){
                //System.out.println("--Nova carta ganha!");
                maior=i;
                mesa.setMaior(c[i]);
            }
            else if(disp==Carta.EMPATA){
                //System.out.println("--Nova carta empata!");
                maior=-1;
            }
        }
        return maior;
    }
    public void iniciar(){
        Carta[] c = new Carta[emJogo];
        int maior=0;
        while(mesa.getTime1()<12 && mesa.getTime2()<12){
            // Junta as cartas no monte
            deck.fazerMonte();
            // Distribui as cartas
            this.distribuirCartas();
            // Inicia a rodada
            for(int turno=0; turno<3; turno++){
                // Cada jogador desce uma carta
                for(int i=0; i<emJogo; i++){
                    mesa.imprimeMesa();
                    c[proximo] = this.jogadores[proximo].obterCarta();
                    proximo=(proximo+1)%(emJogo);
                    maior = verMaior(c);
                }
                // Verifica quem venceu
                mesa.limpar();
                if(maior<0){
                    // Empate
                    System.out.println("Empate!");
                    if(turno>1 && mesa.getPartida()!=0)
                        break;
                    continue;
                }
                else if(maior%2==0){
                    // Adversários marcam
                    mesa.add(1);
                }
                else{
                    // Adversários marcam
                    mesa.add(2);
                }
                if(Math.abs(mesa.getPartida())>1)
                    break;
                // Quem ganha, joga primeiro
                proximo=maior;
            }
            // Depois de jogarem todas as cartas
            // Verifica qual time ganhou a rodada
            mesa.finalizaRodada();
        }
    }
}
