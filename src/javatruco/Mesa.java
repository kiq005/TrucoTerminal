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
public class Mesa {
    
    private Carta maior;
    private Carta vira;
    private int time1;
    private int time2;
    private int rodada;// Quem está ganhando a rodada
    private int valor;// Quanto está valendo a rodada
    
    public Mesa(){
        this.vira = null;
        this.maior = null;
        this.time1 = 0;
        this.time2 = 0;
        this.rodada=0;
        this.valor = 1;
    }
    
    public void imprimeMesa(){
        String v="", m="", r="empatada";
        if(this.vira!=null)
            v=this.vira.Desenho();
        if(this.maior!=null)
            m=this.maior.Desenho();
        if(rodada>0)
            r="Time 1 vencendo.";
        else if(rodada<0)
            r="Time 2 vencendo.";
        
        System.out.println("Vira: " + v + "\tMaior: " + m + "\nValor da Rodada: " + this.valor + " ["+this.time1+":"+this.time2+"] " + r);
    }
    
    public void vira(Carta v){
        this.vira = v;
    }
    
    public void add(int time){
        if(time==2){
            this.rodada--;
            System.out.println("Time 2 marcou!");
        }
        else{
            this.rodada++;
            System.out.println("Time 1 marcou!");
        }
    }
    
    public void limpar(){
        this.maior = null;
    }
    
    public void finalizaRodada(){
        this.vira = null;
        this.maior = null;
        if(this.rodada>0){
            this.time1+=this.valor;
            System.out.println("Time 1 venceu a rodada!");
        }
        else if(this.rodada<0){
            this.time2+=this.valor;
            System.out.println("Time 2 venceu a rodada!");
        }
        this.valor=1;
        this.rodada=0;
    }

    /**
     * @return the vira
     */
    public Carta getVira() {
        return this.vira;
    }
    
    public void setMaior(Carta c){
        this.maior = c;
    }

    /**
     * @return the maior
     */
    public Carta getMaior() {
        return this.maior;
    }

    /**
     * @return the time1
     */
    public int getTime1() {
        return this.time1;
    }

    /**
     * @return the time2
     */
    public int getTime2() {
        return this.time2;
    }

    /**
     * @return the valor
     */
    public int getValor() {
        return this.valor;
    }
    
    /**
     * @return valor da partida atual, negativo para time 2, positivo para time 1
     */
    public int getPartida() {
        return this.rodada;
    }
}
